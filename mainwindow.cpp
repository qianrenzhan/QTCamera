#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDebug>
#include <QTime>
#include <QProcess>

#include <stdio.h>
#include <iostream>
using namespace  std;

#if defined (Q_OS_LINUX)
extern "C" {
#include "decoder.h"
#include "decoder_mjpeg.h"
#include "decoder_yuv422.h"
#include "capture.h"
#include "v4l2camera.h"
}
#endif

QImage MatToQImage(cv::Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}

bool MainWindow::Save_Flag = 0;

#if defined (Q_OS_WIN32)
#define CAM_WIDTH       1920
#define CAM_HEIGHT      1080
Mat MainWindow::test = Mat::zeros(CAM_HEIGHT,CAM_WIDTH,CV_8UC3);
Mat avframe_to_cvmat(AVFrame *frame)
{
    AVFrame dst;
    cv::Mat m;

    memset(&dst, 0, sizeof(dst));

    int w = frame->width, h = frame->height;
    m = cv::Mat(h, w, CV_8UC3);
    dst.data[0] = (uint8_t *)m.data;
    avpicture_fill((AVPicture *)&dst, dst.data[0], AV_PIX_FMT_BGR24, w, h);

    struct SwsContext *convert_ctx = NULL;
    //enum PixelFormat src_pixfmt = (enum PixelFormat)frame->format;
    AVPixelFormat src_pixfmt = (AVPixelFormat)frame->format;
    //enum PixelFormat dst_pixfmt = AV_PIX_FMT_BGR24;
    AVPixelFormat dst_pixfmt = AV_PIX_FMT_BGR24;
    convert_ctx = sws_getContext(w, h, src_pixfmt, w, h, dst_pixfmt,
        SWS_FAST_BILINEAR, NULL, NULL, NULL);
    sws_scale(convert_ctx, frame->data, frame->linesize, 0, h,
        dst.data, dst.linesize);
    sws_freeContext(convert_ctx);

    return m;
}

//Show Dshow Device
void show_dshow_device() {
    AVFormatContext *pFormatCtx = avformat_alloc_context();
    AVDictionary* options = NULL;
    av_dict_set(&options, "list_devices", "true", 0);
    AVInputFormat *iformat = av_find_input_format("dshow");
    printf("========Device Info=============\n");
    avformat_open_input(&pFormatCtx, "video=dummy", iformat, &options);
    printf("================================\n");
}
#endif

#if defined (Q_OS_LINUX)
#define CAM_WIDTH       1280
#define CAM_HEIGHT      720
CameraDevice camera;
Decoder *decoder = NULL;
unsigned char rgb_buf[CAM_WIDTH * CAM_HEIGHT * 3];

bool MainWindow::Ready_Flag = 0;
Mat MainWindow::test = Mat::zeros(CAM_HEIGHT,CAM_WIDTH,CV_8UC3);
void MainWindow::draw_image(void *buf_start, int buf_size)   //void *ctx,
{
    decoder_decode(decoder, rgb_buf, (unsigned char*)buf_start, buf_size);
    test.create(CAM_HEIGHT, CAM_WIDTH, CV_8UC3);
    memcpy(test.data, rgb_buf, CAM_HEIGHT * CAM_WIDTH * 3);

    cvtColor(test,test,CV_RGB2BGR);
    Ready_Flag = 1;

    if(Save_Flag)
    {
        QTime time = QTime::currentTime();
        QString str = time.toString()+".bmp";
        //save picture
        imwrite(str.toStdString(),test);
    }
    Save_Flag = 0;
}
#endif


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer();
    timer->setInterval(1);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
#if defined (Q_OS_LINUX)
    Save_Flag = 0;
#endif
#if defined (Q_OS_WIN32)
    pFrame = av_frame_alloc();
    packet = (AVPacket *)av_malloc(sizeof(AVPacket));
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
//    clock_t start = clock();
    //qDebug() << "camera" << endl;
#if defined (Q_OS_LINUX)
    camera_read_frame(&camera, this->draw_image);   //, user_data
    while(!Ready_Flag);
    QImage disImage = MatToQImage(test);
    ui->label->setPixmap(QPixmap::fromImage(disImage.scaled(ui->label->size())));
#endif

#if defined (Q_OS_WIN32)
    while (1)
    {
        if (av_read_frame(pFormatCtx, packet)<0)
            return;
        if (packet->stream_index == videoindex)
            break;
    }

    ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);

    if (got_picture)
        test = avframe_to_cvmat(pFrame);

    if(Save_Flag)
    {
        QString path = QCoreApplication::applicationDirPath();
        QTime time = QTime::currentTime();
        QString timestr = QString::number(time.hour())+QString::number(time.minute())+QString::number(time.second());
        QString str = path + "/" +timestr+".bmp";
        //save picture
        imwrite(str.toStdString(),test);
        qDebug() << "saved" << endl;
    }
    Save_Flag = 0;

    QImage disImage = MatToQImage(test);
    ui->label->setPixmap(QPixmap::fromImage(disImage.scaled(ui->label->size())));

#endif

//    clock_t end = clock();
//    double totaltime = (double)(end - start) / CLOCKS_PER_SEC;
//    qDebug() << "\ntime is:" << totaltime << "秒！" << endl;
}

void MainWindow::on_pushButton_clicked()   //打开摄像头
{
#if defined (Q_OS_LINUX)
    decoder = decoder_mjpeg_create();

    QString device = "/dev/video0";
    int format = PIX_FMT_MJPEG;
    camera_init(&camera, (char*)device.toStdString().c_str(), CAM_WIDTH, CAM_HEIGHT, 30, (PixelFormat)format);
    camera_open_set(&camera);
    timer->start();
#endif

#if defined (Q_OS_WIN32)
    av_register_all();
    avformat_network_init();
    avdevice_register_all();//Register Device

    show_dshow_device();

    pFormatCtx = avformat_alloc_context();

    AVInputFormat *ifmt = av_find_input_format("dshow");

    if (avformat_open_input(&pFormatCtx, "video=HD USB Camera", ifmt, NULL) != 0)
    {
        printf("Couldn't open input stream.\n");
        return;
    }

    if (avformat_find_stream_info(pFormatCtx, NULL)<0)
    {
        printf("Couldn't find stream information.\n");
        return ;
    }

    videoindex = -1;

    for (i = 0; i<pFormatCtx->nb_streams; i++)
    {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoindex = i;
        }
    }

    if (videoindex == -1)
    {
        printf("Couldn't find a video stream.\n");
        return;
    }

    pCodecCtx = pFormatCtx->streams[videoindex]->codec;
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);

    if (pCodec == NULL)
    {
        printf("Codec not found.\n");
        return;
    }

    if (avcodec_open2(pCodecCtx, pCodec, NULL)<0)
    {
        printf("Could not open codec.\n");
        return ;
    }

    fprintf(stderr, "w= %d h= %d\n", pCodecCtx->width, pCodecCtx->height);

    timer->start();

#endif
}

void MainWindow::on_pushButton_2_clicked()    //设置参数
{
#if defined (Q_OS_LINUX)
    int fd = v4l2cameraopen(&cap);
    printcamerapara(fd);
    get_v4l2_info(fd);
    set_v4l2_para(fd);
#endif
#if defined (Q_OS_WIN32)
    QProcess *process = new QProcess();
    process->start("CameraAutoConfiguration.exe");
#endif
}

void MainWindow::on_pushButton_3_clicked()
{
    if(!Save_Flag)
        Save_Flag = 1;
}

void MainWindow::on_pushButton_4_clicked()
{
#if defined (Q_OS_WIN32)
    timer->stop();
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);
#endif
#if defined (Q_OS_LINUX)
    camera_close(&camera);
#endif
}
