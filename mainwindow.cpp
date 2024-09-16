#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "face_detector.h"
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    cap(0),
    isPaused(false),
    frameCounter(0)
{
    ui->setupUi(this);

    // Initialize FaceDetector
    faceDetector = new FaceDetector("C:/Users/minhh/OneDrive/Desktop/CS/evsProject/build/Debug/deploy.prototxt",
                                    "C:/Users/minhh/OneDrive/Desktop/CS/evsProject/build/Debug/res10_300x300_ssd_iter_140000.caffemodel");

    // Initialize QTimer for frame processing
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::processFrame);
    timer->start(30); // Set the timer interval to 30 ms

    // Start frame rate calculation
    frameTimer.start();

    // Set fixed size for videoLabel (640x480) and center it
    ui->videoLabel->setFixedSize(1920, 1080);

    // Connect actions to slots
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::on_actionExit_triggered);
    connect(ui->snapshotButton, &QPushButton::clicked, this, &MainWindow::on_saveSnapshotButton_clicked);
}

MainWindow::~MainWindow()
{
    delete faceDetector;
    delete timer;
}

void MainWindow::processFrame()
{
    if (isPaused) return;

    // Capture a frame from the camera
    cap >> currentFrame;

    if (currentFrame.empty()) {
        qDebug() << "Failed to capture frame!";
        return;
    }

    // Process frame for face detection
    faceDetector->processFrame(currentFrame);

    // Overlay date and time on the frame
    overlayDateTime(currentFrame);

    // Convert frame to QImage for display in QLabel
    QImage qImage(currentFrame.data, currentFrame.cols, currentFrame.rows, currentFrame.step, QImage::Format_BGR888);

    // Create a QPixmap from QImage
    QPixmap pixmap = QPixmap::fromImage(qImage);

    // Scale the pixmap to fit the QLabel while keeping the aspect ratio
    QPixmap scaledPixmap = pixmap.scaled(ui->videoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Set the scaled pixmap to the QLabel
    ui->videoLabel->setPixmap(scaledPixmap);

    // Center the videoLabel contents
    ui->videoLabel->setAlignment(Qt::AlignCenter);

    // Update frame rate label efficiently
    updateFrameRateLabel();
}




void MainWindow::overlayDateTime(cv::Mat &frame)
{
    // Get the current date and time
    QString dateTimeText = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    // Convert QString to std::string
    std::string text = dateTimeText.toStdString();

    // Set the position and font for the text
    int fontFace = cv::FONT_HERSHEY_SIMPLEX;
    double fontScale = 1.0;
    int thickness = 2;
    int baseline = 0;
    cv::Size textSize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);
    cv::Point textOrg((frame.cols - textSize.width) - 10, (frame.rows - 10));

    // Draw the text on the frame
    cv::putText(frame, text, textOrg, fontFace, fontScale, cv::Scalar(255, 255, 255), thickness);
}

void MainWindow::updateFrameRateLabel()
{
    frameCounter++;
    qint64 elapsed = frameTimer.elapsed();

    if (elapsed >= 1000) { // Every second
        double fps = frameCounter * 1000.0 / elapsed;
        ui->frameRateLabel->setText(QString("Frame Rate: %1 FPS").arg(fps, 0, 'f', 2));

        // Reset for the next second
        frameCounter = 0;
        frameTimer.restart();
    }
}

void MainWindow::on_playButton_clicked()
{
    isPaused = false;
    qDebug() << "Video resumed.";
}

void MainWindow::on_pauseButton_clicked()
{
    isPaused = true;
    qDebug() << "Video paused.";
}

void MainWindow::on_resetButton_clicked()
{
    cap.release();
    cap.open(0); // Restart the camera feed
    qDebug() << "Video feed reset.";
}

void MainWindow::on_actionExit_triggered()
{
    close(); // Close the application
}

void MainWindow::saveSnapshot()
{
    if (currentFrame.empty()) {
        QMessageBox::warning(this, "Error", "No frame available to capture!");
        return;
    }

    // Open file dialog to specify save location
    QString filePath = QFileDialog::getSaveFileName(this, "Save Snapshot", "", "Images (*.jpg)");

    if (!filePath.isEmpty()) {
        // Convert QString to std::string
        std::string file = filePath.toStdString();
        // Save the current frame as a JPG file using OpenCV
        if (cv::imwrite(file, currentFrame)) {
            QMessageBox::information(this, "Success", "Snapshot saved successfully!");
        } else {
            QMessageBox::warning(this, "Error", "Failed to save snapshot.");
        }
    }
}

void MainWindow::on_saveSnapshotButton_clicked()
{
    // Call the saveSnapshot function you have already defined
    saveSnapshot();
}


