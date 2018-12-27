#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDebug>

#include <QTime>


extern "C" {
#include "decoder.h"
#include "decoder_mjpeg.h"
#include "decoder_yuv422.h"
#include "capture.h"
#include "v4l2camera.h"
}

#include <opencv.hpp>
using namespace cv;


#define CAM_WIDTH       1280
#define CAM_HEIGHT      720
CameraDevice camera;
Decoder *decoder = NULL;
unsigned char rgb_buf[CAM_WIDTH * CAM_HEIGHT * 3];

bool MainWindow::Save_Flag = 0;

void MainWindow::draw_image(void *buf_start, int buf_size)   //void *ctx,
{
    QTime timedebuge;//声明一个时钟对象
    timedebuge.start();//开始计时

    decoder_decode(decoder, rgb_buf, (unsigned char*)buf_start, buf_size);
    Mat test;
    test.create(CAM_HEIGHT, CAM_WIDTH, CV_8UC3);
    memcpy(test.data, rgb_buf, CAM_HEIGHT * CAM_WIDTH * 3);

    Mat testshow;
    Size size(CAM_WIDTH / 2, CAM_HEIGHT / 2);
    cv::resize(test, testshow, size);

    Mat rgb;
    cvtColor(test,rgb,CV_RGB2BGR);

    namedWindow("img");
    imshow("img", rgb);

    if(Save_Flag)
    {
        QTime time = QTime::currentTime();
        QString str = time.toString()+".bmp";
        //save picture
        imwrite(str.toStdString(),rgb);

    }
    Save_Flag = 0;

    qDebug()<<"time:"<<timedebuge.elapsed()/1000.0<<"s";   //16ms
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer();
    timer->setInterval(30);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));

    Save_Flag = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
    qDebug() << "camera" << endl;
    camera_read_frame(&camera, this->draw_image);   //, user_data
}

void MainWindow::on_pushButton_clicked()
{
    decoder = decoder_mjpeg_create();

    QString device = "/dev/video0";
    int format = PIX_FMT_MJPEG;
    camera_init(&camera, (char*)device.toStdString().c_str(), CAM_WIDTH, CAM_HEIGHT, 30, (PixelFormat)format);
    camera_open_set(&camera);
    timer->start();
}

void MainWindow::on_pushButton_2_clicked()
{
    int fd = v4l2cameraopen(&cap);
    printcamerapara(fd);
    get_v4l2_info(fd);
    set_v4l2_para(fd);
}

void MainWindow::on_pushButton_3_clicked()
{
    if(!Save_Flag)
        Save_Flag = 1;
}
