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

    std::cout << "Raspberry Pi Zero 2 W" << std::endl;
    Camera camera;
    std::thread cameraThread(&Camera::cameraCaptureStart, &camera);

    Http http(camera);
    http.httpServerStart();
    
    cameraThread.join();
    
    return 0;

}
