#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void processAndUpdate();

private:
    Ui::MainWindow *ui;

    cv::VideoCapture capWebCam;
    cv::Mat matOriginal;
    cv::Mat matProcessed;

    QImage qimageOriginal;
    QImage qimageProcessed;

    std::vector<cv::Vec3f> vecCircles;
    std::vector<cv::Vec3f>::iterator iterCircles;

    QTimer *tmrTimer;

private slots:
    void pushButtonClicked();

};

#endif // MAINWINDOW_H
