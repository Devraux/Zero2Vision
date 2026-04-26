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
        ImageMetadata imageMetadata; //Current frame metadata
        std::mutex cameraMtx;   // Camera hardware mutex
        cv::Mat frame;          // Current frame 

        // TODO: Replace with static in dedicated function
        uint64_t frameTimeCpy = 0;
        uint64_t frameTime = 0;

    public:
        Camera();
        ~Camera() = default;

        // Begin camera image capturing in infinite loop
        // Get camera Image and fullfill metadata
        void cameraCaptureStart();

        // Camera metadata getter
        // Returns metadata related with last captured image
        // see ../HTTP/ImageMetadata.hpp
        bool cameraGetMetadata(ImageMetadata& data) const;
        
        // Recently received image getter
        // return last image 
        cv::Mat getFrame();
};


class ObjectDetection{
    private:
        ImageMetadata imageMetadata;
        std::vector<ObjectDetectionInfo> detectedObjects;
        cv::dnn::Net net; // Deep Neural Network
                          
                          
        void detectObjects(cv::Mat& img);
        

    public:
        ObjectDetection();
        ~ObjectDetection() = default;
        void objectDetectionStart(Camera& camera);

        const std::vector<ObjectDetectionInfo>& getDetections() const;
};
    

#endif
