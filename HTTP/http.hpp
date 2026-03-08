#ifndef _HTTP_
#define _HTTP_

#include "httplib.h"
#include "opencv4/opencv2/opencv.hpp"
#include <thread>
#include <queue>
#include <mutex>

// HTTP SERVER IMPLEMENTATION

struct Frame{
    std::mutex Mutex;    // read/write lock
    cv::Mat frame;       // video frame
};

class http{

    private:
        std::queue<Frame> q;
        http();

    public:
        void httpStart();
        bool frameQueuePush();  // todo 
        bool frameQueuPop();    // todo
};

#endif
