#ifndef IMAGE_METADATA_HPP
#define IMAGE_METADATA_HPP

#include <cstdint>
#include <mutex>

struct ImageMetadata {
    uint64_t frameTime = 0;
    uint64_t frameCounter = 0;
    double fpsValue = 0.0;
    uint32_t frameWidth = 640;
    uint32_t frameHeight = 480;
};

#endif
