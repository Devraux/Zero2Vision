#ifndef _CAMERA_
#define _CAMERA_

#include "opencv4/opencv2/opencv.hpp"
#include <iostream>

#include "http.hpp"
#include <thread>

class Camera{

    private:
        cv::VideoCapture cap;

    public:
        Camera();
        ~Camera() = default;
        void cameraCaptureStart();
        
        cv::Mat getFrame();
        std::mutex frameMutex;
        cv::Mat frame;

};

#endif
