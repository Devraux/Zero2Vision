#include "http.hpp"
#include <opencv2/opencv.hpp>
#include <chrono>
#include <thread>
#include <iostream>
#include "httplib.h"

Http::Http(Camera& cam) : camera(cam) {}

void Http::httpServerStart()
{
    httplib::Server svr;

    svr.Get("/frame.jpg", [this](const httplib::Request&, httplib::Response& res) {
        cv::Mat frame = camera.getFrame();

        if (frame.empty()) {
            res.status = 503; 
            res.set_content("No frame available", "text/plain");
            return;
        }

        std::vector<uchar> buf;
        std::vector<int> params = {cv::IMWRITE_JPEG_QUALITY, 80};
        cv::imencode(".jpg", frame, buf, params);

        res.set_content(reinterpret_cast<const char*>(buf.data()), buf.size(), "image/jpeg");
    });

    std::cout << "HTTP server started at http://0.0.0.0:8080/frame.jpg" << std::endl;

    svr.listen("0.0.0.0", 8080);
}
