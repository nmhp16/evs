# Embedded Vision System (EVS)

## Overview

This project is a real-time face detection application developed using OpenCV and Qt. 
It captures video from the default camera and performs face detection.
Displays the video with head counts for detected faces, date and time, and frame rate information. 
The application also allows users to take snapshots and save them to disk.

## Features

- Real-time face detection using a pre-trained Caffe deep learning model.
- Custom GUI for video playback control (play, pause, reset) and snapshot capture.
- Real-time video processing with overlayed date and time.
- Perform head count on all detected faces.
- Efficient frame rate display and video recording capabilities.
- Cross-platform support using CMake for compilation and deployment.

## Requirements

- **Qt**: For creating the GUI.
- **OpenCV**: For face detection and video processing.
- **CMake**: For building the project.
- **Caffe Model**: The pre-trained Caffe deep learning model for face detection.
  - [Deploy.prototxt](path/to/deploy.prototxt)
  - [Caffemodel file](path/to/res10_300x300_ssd_iter_140000.caffemodel)

## Installation

### Prerequisites

1. **Install Qt**: Follow the [Qt installation guide](https://www.qt.io/download) to set up Qt.
2. **Install OpenCV**: You can download and install OpenCV from the [official OpenCV website](https://opencv.org/releases/).
3. **Install CMake**: Download and install CMake from the [CMake website](https://cmake.org/download/).

### Building the Project

1. Clone the repository:
    ```bash
    git clone https://github.com/nmhp16/evs
    cd evs
    ```

2. Create a build directory and navigate into it:
    ```bash
    mkdir build
    cd build
    ```

3. Generate the build files using CMake:
    ```bash
    cmake ..
    ```

4. Build the project:
    ```bash
    cmake --build .
    ```

5. Run the application:
    ```bash
    cd Debug
    EmbeddedVisionSystem.exe
    ```
    or Run
   (`build\Debug\EmbeddedVisionSystem.exe`)

## Usage

1. **Start the Application**: Run the executable built from the project.

2. **Control the Video**: Use the provided buttons to play, pause, or reset the video feed.

3. **Take Snapshots**: Click the "Snapshot" button to capture and save the current frame.

4. **Exit**: Click the "Exit" button to close the application.


