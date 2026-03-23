#ifndef _CAMERA_
#define _CAMERA_

#include "opencv4/opencv2/opencv.hpp"
#include <iostream>

#include "ImageMetadata.hpp"
#include <thread>
#include <chrono>
#include <vector>

class Camera{

    private:
        cv::VideoCapture cap;
        ImageMetadata imageMetadata;
        std::mutex cameraMtx;

        cv::dnn::Net net;

        std::vector<ObjectDetectionInfo> detectedObjects;

        uint64_t frameTimeCpy = 0;
        uint64_t frameTime = 0;

        void detectObjects(cv::Mat& img);

    public:
        Camera();
        ~Camera() = default;
        void cameraCaptureStart();
        bool cameraGetMetadata(ImageMetadata& data) const;
        
        cv::Mat getFrame();
        cv::Mat frame;

        const std::vector<ObjectDetectionInfo>& getDetections() const;

};

#endif
