#include <QApplication>  // Include QApplication for managing application-wide resources
#include "mainwindow.h"  // Include the header for the MainWindow class

int main(int argc, char *argv[]) {
    // Create an instance of QApplication, which manages application-wide resources and settings
    QApplication a(argc, argv);

    // Create an instance of MainWindow, which is the main window of the application
    MainWindow w;

    // Show the MainWindow instance
    w.show();

    // Enter the application's event loop and wait for events such as user interactions
    return a.exec();
}
