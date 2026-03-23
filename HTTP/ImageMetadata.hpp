#ifndef IMAGE_METADATA_HPP
#define IMAGE_METADATA_HPP

#include <cstdint>
#include <mutex>

#define minConfidenceLevel (0.6)

struct ImageMetadata {
    uint64_t frameTime = 0;
    uint64_t frameCounter = 0;
    double fpsValue = 0.0;
    uint32_t frameWidth = 640;
    uint32_t frameHeight = 480;
};


struct ObjectDetectionInfo {
    uint32_t classId = 0;
    float confidence = 0.0f;
    int x;
    int y;
    int width = 0;
    int height = 0;
};

#endif
