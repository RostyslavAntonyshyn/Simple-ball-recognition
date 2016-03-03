#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    capWebCam.open(0);
    if(capWebCam.isOpened() == false)
    {
        ui->plainTextEdit->appendPlainText("error: WebCam not accessed sucsessfully!");
        return;
    }
    tmrTimer = new QTimer(this);

    connect(tmrTimer, &QTimer::timeout, this, &MainWindow::processAndUpdate, Qt::UniqueConnection);
    connect(ui->pushButton, &QAbstractButton::clicked, this, &MainWindow::pushButtonClicked);
    connect(ui->pushButton_2, &QAbstractButton::clicked, this, &QMainWindow::close);
    tmrTimer->start(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processAndUpdate()
{
    capWebCam.read(matOriginal);
    if(matOriginal.empty() == true)
        return;

    cv::inRange(matOriginal, cv::Scalar(0, 0, 175),
                cv::Scalar(100, 100, 256), matProcessed);
    cv::GaussianBlur(matProcessed, matProcessed, cv::Size(9, 9), 1.5);
    cv::HoughCircles(matProcessed, vecCircles,
                     CV_HOUGH_GRADIENT, 1, matProcessed.rows /4, 100, 40, 20, 200);

    for(iterCircles = vecCircles.begin(); iterCircles != vecCircles.end(); iterCircles++)
    {
        ui->plainTextEdit->appendPlainText(QString("Object position x =") +
                                           QString::number((*iterCircles)[0]).rightJustified(4, ' ') +
                                           QString(", y =") + QString::number((*iterCircles)[1]).rightJustified(4, ' ') +
                                           QString(", radius =") + QString::number((*iterCircles)[2], 'f', 3).rightJustified(7, ' '));

        cv::circle(matOriginal, cv::Point((int)(*iterCircles)[0],
                   (int)(*iterCircles)[1]), 3, cv::Scalar(0, 255, 0), CV_FILLED);
        cv::circle(matOriginal, cv::Point((int)(*iterCircles)[0],
                   (int)(*iterCircles)[1]), (int)(*iterCircles)[2], cv::Scalar(0, 0, 255), 3);
    }

    cv::cvtColor(matOriginal, matOriginal, CV_BGR2RGB);

    QImage qimageOriginal((uchar*)matOriginal.data, matOriginal.cols,
                           matOriginal.rows, matOriginal.step, QImage::Format_RGB888);

    QImage qimageProcessed((uchar*)matProcessed.data, matProcessed.cols,
                           matProcessed.rows, matProcessed.step, QImage::Format_Indexed8);

    ui->labelOriginal->setPixmap(QPixmap::fromImage(qimageOriginal));
    ui->labelProcessed->setPixmap(QPixmap::fromImage(qimageProcessed));
}

void MainWindow::pushButtonClicked()
{
    if(tmrTimer->isActive() == true)
    {
        tmrTimer->stop();
        ui->pushButton->setText("Resume");
    }
    else
    {
        tmrTimer->start(20);
        ui->pushButton->setText("Pause");
    }
}
