#ifndef FACE_DETECTOR_H
#define FACE_DETECTOR_H

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <set>

// Structure to represent a detected face with its bounding box and area
struct Face {
    cv::Rect rect;  // Bounding box of the detected face
    float area;     // Area of the bounding box

    // Constructor that initializes rect and area
    Face(const cv::Rect& rect, float area) : rect(rect), area(area) {}

    // Comparison operator to allow sorting of faces by area in descending order
    bool operator<(const Face& other) const {
        return area > other.area; // Sort faces by area, larger areas first
    }
};

// Class for detecting faces in video frames using OpenCV's DNN module
class FaceDetector {
public:
    // Constructor that initializes the face detector with model configuration and weights
    FaceDetector(const std::string& modelConfiguration, const std::string& modelWeights);

    // Destructor that releases resources
    ~FaceDetector();

    // Method to process a video frame for face detection
    void processFrame(cv::Mat& frame);

private:
    cv::dnn::Net net;           // Deep neural network for face detection
    cv::VideoCapture cap;       // Video capture object for accessing video frames
    cv::VideoWriter videoWriter; // Video writer object for saving processed video
    std::string modelConfiguration; // Path to the model configuration file
    std::string modelWeights;       // Path to the model weights file
};

#endif // FACE_DETECTOR_H
