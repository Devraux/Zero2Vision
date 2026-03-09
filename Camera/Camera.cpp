#include "Camera.hpp"

Camera::Camera() : cap(0, cv::CAP_V4L2)
{
    if(!cap.isOpened())
    {
        std::cerr << "Firmware can't open camera device" << std::endl;
        throw std::runtime_error("Firmware can't ope camera device");
    }

    // set camera resolution
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    // todo set other camera properties
}

void Camera::cameraCaptureStart()
{
    
    std::cout << "Camera started video capturig" << std::endl;
    while(true)
    {
        // Capture new frame
        cv::Mat newFrame;
        cap.read(newFrame);
        
        //Check frame corecctness
        if(newFrame.empty())
        {
            std::cerr << "Received empty or can't receive frame, check hardware camera connection" << std::endl;
            break;
        }

        cv::waitKey(1);
            
        
        std::lock_guard<std::mutex> lock(frameMutex);
        frame = newFrame;
    }
}

cv::Mat Camera::getFrame()
{

    std::lock_guard<std::mutex> lock(frameMutex);

    return frame.clone();
}
