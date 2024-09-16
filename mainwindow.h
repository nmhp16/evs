#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QImage>
#include <QElapsedTimer>
#include <opencv2/opencv.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// MainWindow class definition
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor with optional parent widget
    explicit MainWindow(QWidget *parent = nullptr);

    // Destructor
    ~MainWindow() override;

private slots:
    // Slot for processing video frames
    void processFrame();

    // Slot for handling play button click
    void on_playButton_clicked();

    // Slot for handling pause button click
    void on_pauseButton_clicked();

    // Slot for handling reset button click
    void on_resetButton_clicked();

    // Slot for handling exit action
    void on_actionExit_triggered();

    // Slot for handling save snapshot button click
    void on_saveSnapshotButton_clicked();

private:
    // Method to overlay date and time on the frame
    void overlayDateTime(cv::Mat &frame);

    // Method to update the frame rate label
    void updateFrameRateLabel();

    // Method to save the current frame as a snapshot
    void saveSnapshot();

    Ui::MainWindow *ui; // Pointer to the UI components
    cv::VideoCapture cap; // OpenCV VideoCapture object for accessing the camera
    cv::Mat currentFrame; // Mat object to store the current video frame
    QTimer *timer; // QTimer object for periodic frame processing
    bool isPaused; // Flag to indicate if video playback is paused
    int frameCounter; // Counter for frames to calculate frame rate
    QElapsedTimer frameTimer; // Timer to measure elapsed time for frame rate calculation

    class FaceDetector *faceDetector; // Pointer to the FaceDetector class instance
};

#endif // MAINWINDOW_H
