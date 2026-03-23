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
            detectObjects(frame);
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

void Camera::detectObjects(cv::Mat& img)
{
    cv::Mat blob;
    cv::dnn::blobFromImage(img, blob, 1/255.0, cv::Size(416, 416));

    net.setInput(blob);

    std::vector<cv::Mat> outputs;
    net.forward(outputs, net.getUnconnectedOutLayersNames());

    ObjectDetectionInfo objectInfo;

    detectedObjects.clear();

    // Check MAT0 and MAT1
    for (size_t i = 0; i < outputs.size(); i++)
    {

        // SKIP BIGGER (FASTER) OBJECT DETECTION -> SKIP MAT0 //
        if(i == 0)
        {
            continue;
        }
        // -------------------------------------------------- //

        cv::Mat& out = outputs[i];
        float* data = (float*)out.data;

        for (int j = 0; j < out.rows; j++)
        {
            float confidence = data[4];
                
            if(confidence < minConfidenceLevel)
            {
                data += 85; // jump to next row
                continue; 
            }
            
            float w = data[2] * img.cols;
            float h = data[3] * img.rows;

            objectInfo.x            = (data[0] * img.cols) - (w / 2.0f); // X_center
            objectInfo.y            = (data[1] * img.rows) - (h / 2.0f); // Y_center
            objectInfo.width        = w; // Width
            objectInfo.height       = h; // Height
            objectInfo.objectness   = data[4]; // Objectness
            
            // Find highest confidence and related object
            cv::Mat scores = out.row(j).colRange(5, 85);
            double classConfidence {0.0f};
            cv::Point classId;

            cv::minMaxLoc(scores, 0, &classConfidence, 0, &classId);
            objectInfo.classId      = classId.x;
            objectInfo.confidence   = (float)classConfidence;
            
            detectedObjects.insert(detectedObjects.begin(), objectInfo);
            if(detectedObjects.size() > 100)
            {
                detectedObjects.pop_back();
            }
        
            data += 85; // jump to next row
        }
    }
}

const std:: vector<ObjectDetectionInfo>& Camera::getDetections() const
{
    return detectedObjects;
}

