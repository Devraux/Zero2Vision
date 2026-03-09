#ifndef _HTTP_
#define _HTTP_

#include "httplib.h"
#include "opencv4/opencv2/opencv.hpp"
#include <thread>
#include <queue>
#include <mutex>

#include "Camera.hpp"

// HTTP SERVER IMPLEMENTATION

class Http{

    private:
        Camera& camera;

    public:
        Http(Camera& cam);
        ~Http() = default;

        void httpServerStart();
};

#endif
