#include "face_detector.h"
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>
#include <set>

// Constructor for FaceDetector class, initializing the DNN model and opening the video stream
FaceDetector::FaceDetector(const std::string& modelConfiguration, const std::string& modelWeights)
    : modelConfiguration(modelConfiguration), modelWeights(modelWeights) {
    // Load pre-trained DNN model from Caffe configuration and weights
    net = cv::dnn::readNetFromCaffe(modelConfiguration, modelWeights);
    if (net.empty()) {
        std::cerr << "Error loading DNN model!" << std::endl;
        return;
    }

    // Open the default camera (0)
    cap.open(0);
    if (!cap.isOpened()) {
        std::cerr << "Error opening video stream!" << std::endl;
        return;
    }

    // Initialize video writer for saving output to a file
    videoWriter.open("output_video.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30,
                     cv::Size(static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)),
                              static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT))));
    if (!videoWriter.isOpened()) {
        std::cerr << "Error opening video writer!" << std::endl;
    }
}

// Destructor for FaceDetector class, releasing video stream and writer
FaceDetector::~FaceDetector() {
    cap.release();         // Release the camera
    videoWriter.release(); // Release the video writer
}

// Processes a video frame and performs face detection
void FaceDetector::processFrame(cv::Mat& frame) {
    // Prepare the image as a blob for DNN input
    cv::Mat blob;
    cv::dnn::blobFromImage(frame, blob, 1.0, cv::Size(300, 300), cv::Scalar(104.0, 177.0, 123.0), false, false);
    net.setInput(blob);

    // Forward pass through the network to detect faces
    cv::Mat detections = net.forward();
    cv::Mat detectionMat(detections.size[2], detections.size[3], CV_32F, detections.ptr<float>());

    // Set to store detected faces based on their area
    std::set<Face> faces;

    // Iterate over each detection and filter based on confidence
    for (int i = 0; i < detectionMat.rows; ++i) {
        float confidence = detectionMat.at<float>(i, 2);
        if (confidence > 0.2) { // Confidence threshold
            // Calculate bounding box coordinates for detected face
            int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols);
            int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
            int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
            int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);
            cv::Rect faceRect(x1, y1, x2 - x1, y2 - y1);
            float area = faceRect.width * faceRect.height;
            faces.emplace(faceRect, area); // Add face to the set
        }
    }

    // Draw bounding boxes around detected faces
    for (const auto& face : faces) {
        cv::rectangle(frame, face.rect, cv::Scalar(0, 255, 0), 2);
    }

    // Display head count on the frame
    int headCount = faces.size();
    std::string headCountText = "Head count: " + std::to_string(headCount);

    // Set font, size, and position for headcount text
    int fontFace = cv::FONT_HERSHEY_SIMPLEX;
    double fontScale = 0.8;
    int thickness = 3;
    cv::Scalar textColor = cv::Scalar(255, 255, 255); // White text
    cv::Scalar outlineColor = cv::Scalar(0, 0, 0);   // Black outline
    cv::Size textSize = cv::getTextSize(headCountText, fontFace, fontScale, thickness, nullptr);
    cv::Point textOrg(10, 30 + textSize.height);

    // Draw outline and text on the frame
    cv::putText(frame, headCountText, textOrg + cv::Point(2, 2), fontFace, fontScale, outlineColor, thickness + 2, cv::LINE_AA);
    cv::putText(frame, headCountText, textOrg, fontFace, fontScale, textColor, thickness, cv::LINE_AA);

    // Save the processed frame to the output video file
    if (videoWriter.isOpened()) {
        videoWriter.write(frame);
    } else {
        std::cerr << "Video writer not opened!" << std::endl;
    }
}
