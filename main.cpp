#include <iostream>

#include "http.hpp"
#include "Camera.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>


int main() {

    std::cout << "Raspberry Pi Zero 2 W ZeroToVision App" << std::endl;
    std::cout << "Camera hardware initialization" << std::endl;
    Camera camera;
    ObjectDetection objectDetection;

    std::thread cameraThread(&Camera::cameraCaptureStart, &camera);

    std::cout<< "HTTP server initialization ..." << std::endl;
    Http http(camera, objectDetection);
    std::thread httpThread(&Http::httpServerStart, &http);
    //http.httpServerStart();


    std::thread detectionThread(&ObjectDetection::objectDetectionStart, 
                                &objectDetection,
                                std::ref(camera));
    
    cameraThread.join();
    detectionThread.join();
    httpThread.join();
    return 0;
 
}
