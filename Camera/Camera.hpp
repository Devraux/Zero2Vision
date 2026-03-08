#ifndef _CAMERA_
#define _CAMERA_

#include "opencv4/opencv2/opencv.hpp"
#include <iostream>

#include "http.hpp"
#include <thread>

class camera{

    private:
        cv::Mat frame;

    public:
    camera()
    ~camera() = default;

    void cameraCaptureStart();

};

#endif
