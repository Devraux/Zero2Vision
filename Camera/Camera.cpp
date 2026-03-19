#include "Camera.hpp"

Camera::Camera() : cap( "libcamerasrc ! "
                        "video/x-raw,width=640,height=480,framerate=30/1 ! "
                        "videoconvert ! "
                        "appsink drop=true",
                        cv::CAP_GSTREAMER)
{
    if(!cap.isOpened())
        throw std::runtime_error("Camera can't open device");
}

void Camera::cameraCaptureStart()
{
    std::cout << "Camera started video capturing" << std::endl;

    cv::Mat newFrame;


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
