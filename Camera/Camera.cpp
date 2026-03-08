#include "Camera.hpp"

camera::camera()
{
    cv::VideoCapture cap(0, cv::CAP_V4L2);

    if(!cap.isOpened())
    {
        std::cerr << "Firmware can't open camera device" << std::endl;
        throw std::runtime_error("Firmware can't ope camera device");
    }


    // set camera resolution
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);

    // todo set other camera properties
}

void camera::cameraCaptureStart()
{
    
    std::cout << "Camera started video capturig" << std::endl;
    while(true)
    {
        cap.read(frame);
        
        if(frame.empty())
        {
            std::cerr << "Received empty or can't receive frame, check hardware camera connection" << std::endl;
            break;
        }
        
    // todo push received frame to queue | check mutex
    
    }
}
