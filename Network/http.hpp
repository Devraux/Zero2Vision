#ifndef _HTTP_
#define _HTTP_

#include "httplib.h"
#include "opencv4/opencv2/opencv.hpp"
#include <thread>
#include <queue>
#include <mutex>
#include <iostream>
#include <chrono> 

#include "Camera.hpp"
#include "ImageMetadata.hpp"

// HTTP SERVER IMPLEMENTATION

class Http{

    private:
        Camera& camera;
        ObjectDetection& objectDetection;
        ImageMetadata imageMetadata;

    public:
        Http(Camera& cam, ObjectDetection& objDet);
        ~Http() = default;

        void httpServerStart();
};

#endif
