#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#if defined (Q_OS_LINUX)
#include <sys/types.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <unistd.h>
#endif

#if defined (Q_OS_WIN32)
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"
}
#endif

#include <opencv2/opencv.hpp>
using namespace cv;

class QTimer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
#if defined (Q_OS_LINUX)
    static void draw_image(void *buf_start, int buf_size);
#endif

private slots:
    void on_pushButton_clicked();
    void update();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    QTimer * timer;

#if defined (Q_OS_LINUX)
    static bool Save_Flag;
    static bool Ready_Flag;

    struct v4l2_capability cap;
    struct v4l2_queryctrl qctrl;
    struct v4l2_control ctrl;
    struct v4l2_format Format;
    struct v4l2_streamparm Stream_Parm;
#endif

#if defined (Q_OS_WIN32)
    AVFormatContext	*pFormatCtx;
    int				i, videoindex;
    int ret, got_picture;
    AVCodecContext	*pCodecCtx;
    AVCodec			*pCodec;
    AVFrame	*pFrame;
    AVPacket *packet;

    Mat test;
#endif
};

#endif // MAINWINDOW_H
