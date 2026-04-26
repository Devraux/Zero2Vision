#include "http.hpp"



Http::Http(Camera& cam, ObjectDetection& objDet) : camera(cam), objectDetection(objDet) {}

void Http::httpServerStart()
{
    httplib::Server svr;

    svr.Get("/frame.jpeg", [this](const httplib::Request&, httplib::Response& res) {

        cv::Mat frame = camera.getFrame();

        if (frame.empty()) {
            res.status = 503; 
            res.set_content("No frame available", "text/plain");
            return;
        }

        std::vector<uchar> buf;

        std::vector<int> params = {cv::IMWRITE_JPEG_QUALITY, 80}; // JPEG image type case
        //std::vector<int> params = {cv::IMWRITE_PNG_COMPRESSION, 2};
        cv::imencode(".jpeg", frame, buf, params);

        res.set_content(reinterpret_cast<const char*>(buf.data()), buf.size(), "image/jpeg");
    });


  	// Metadata request handler
    svr.Get("/metadata.json", [this](const httplib::Request&, httplib::Response& res) {

    camera.cameraGetMetadata(imageMetadata);

    std::string metaDataReport =
        "{"
        "\"frameTime\":"    + std::to_string(imageMetadata.frameTime) + ","
        "\"frameCounter\":" + std::to_string(imageMetadata.frameCounter) + ","
        "\"fpsValue\":"     + std::to_string(imageMetadata.fpsValue) + ","
        "\"frameWidth\":"   + std::to_string(imageMetadata.frameWidth) + ","
        "\"frameHeight\":"  + std::to_string(imageMetadata.frameHeight) +
        "}";

       res.set_content(metaDataReport, "application/json");
    });


    // Object detections
	svr.Get("/detections.json", [this](const httplib::Request&, httplib::Response& res)
    {
        const std::vector<ObjectDetectionInfo>& detections = objectDetection.getDetections();

        std::string json = "[";

        for (size_t i = 0; i < detections.size(); i++)
        {
            const auto& d = detections[i];

            json += "{";
            json += "\"classId\":" + std::to_string(d.classId) + ",";
            json += "\"confidence\":" + std::to_string(d.confidence) + ",";
            json += "\"x\":" + std::to_string(d.x) + ",";
            json += "\"y\":" + std::to_string(d.y) + ",";
            json += "\"w\":" + std::to_string(d.width) + ",";
            json += "\"h\":" + std::to_string(d.height);
            json += "}";

            if (i + 1 < detections.size())
            {
                json += ",";
            }
        }

    json += "]";

    res.set_content(json, "application/json");
});


    std::cout << "HTTP server started at http://0.0.0.0:8080/frame.jpeg" << std::endl;

    svr.listen("0.0.0.0", 8080);
}
