#include "Camera.hpp"

Camera::Camera() : cap( "libcamerasrc ! "
                        "video/x-raw,width=640,height=480,framerate=30/1 ! "
                        "videoconvert ! "
                        "appsink drop=true",
                        cv::CAP_GSTREAMER)
{
    if(!cap.isOpened())
        throw std::runtime_error("Camera can't open device");

    net = cv::dnn::readNetFromDarknet("../tinyYolo/yolov4-tiny.cfg", "../tinyYolo/yolov4-tiny.weights");
 
}

void Camera::cameraCaptureStart()
{
    std::cout << "Camera started video capturing" << std::endl;

    cv::Mat newFrame;
    static uint32_t frameDetectCounter = 0;
    
    while(true)
    {
        // Capture new frame
        if(!cap.read(newFrame)) {
            std::cerr << "Camera read failed" << std::endl;
            continue;
        }

        if(newFrame.empty()) {
            std::cerr << "Received empty frame" << std::endl;
            continue;
        }

        // Debug only
        //std::cout << "Frame: " << newFrame.cols << "x" << newFrame.rows << std::endl;

        // Free  
        std::lock_guard<std::mutex> lock(cameraMtx);
        frame = newFrame.clone();

 	    // fill metada
        frameTimeCpy = imageMetadata.frameTime;
        frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        imageMetadata.frameTime = frameTime;
        imageMetadata.frameCounter++;
        imageMetadata.fpsValue = (1000.0 / (frameTime - frameTimeCpy));
   
        static uint32_t detectionCounter = 0;
        if(++detectionCounter > 5)
        {
            // Calculate object detections
            detectObjects(frame, detectionsMaxNumber);
            detectionCounter = 0;
        }
    }
}


cv::Mat Camera::getFrame()
{
    std::lock_guard<std::mutex> lock(cameraMtx);
    return frame.clone();
}

bool Camera::cameraGetMetadata(ImageMetadata& data) const
{
    data = imageMetadata;
    return true;
}

void Camera::detectObjects(cv::Mat& img, uint detectionLimit)
{
    cv::Mat blob;
    cv::dnn::blobFromImage(img, blob, 1/255.0, cv::Size(416, 416));

    net.setInput(blob);

    std::vector<cv::Mat> outputs;
    net.forward(outputs, net.getUnconnectedOutLayersNames());

    std::vector<ObjectDetectionInfo> detection;
    detection.reserve(detectionLimit);

    const float confThreshold = 0.5f;

    for (size_t o = 0; o < outputs.size(); o++)
    {
        cv::Mat& out = outputs[o];
        float* data = (float*)out.data;

        for (int j = 0; j < out.rows; j++)
        {
            float objConf = data[4];

            if (true /*objConf > confThreshold*/)
            {
                int classId = 0;
                float bestClass = data[5];

                for (int c = 1; c < 80; c++)
                {
                    if (data[5 + c] > bestClass)
                    {
                        bestClass = data[5 + c];
                        classId = c;
                    }
                }

                ObjectDetectionInfo obj;

                obj.x = data[0];
                obj.y = data[1];
                obj.width = data[2];
                obj.height = data[3];
                obj.confidence = objConf * bestClass;
                obj.classId = classId;

                detection.push_back(obj);

                if (detection.size() > detectionLimit)
                {
                    detection.erase(detection.begin());
                }
            }

            data += 85;
        }
    }

    detectedObjects = detection;
}

const std:: vector<ObjectDetectionInfo>& Camera::getDetections() const
{
    return detectedObjects;
}

