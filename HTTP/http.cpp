#include "http.hpp"

Http::Http(Camera& cam) : camera(cam) { }

Http::httpServerStart()
{

    httplib::Server server;



    while(true)
    {
        std::vector<cv::Mat> frameCopy;
        
        // todo
    }
}
