#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <sys/types.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <unistd.h>


///*摄像头参数id列表*/
//#define BRIGHTNESS_ID 0x00980900
//#define CONTRAST_ID 0x00980901
//#define SATURATION_ID 0x00980902
//#define HUE_ID 0x00980903
//#define WHITE_BALANCE_TEMP_AUTO_ID 0x0098090c
//#define GAMMA_ID 0x00980910
//#define POWER_LINE_FREQUENCY_ID 0x00980918
//#define WHITE_BALANCE_TEMP_ID 0x0098091a
//#define SHARPNESS_ID 0x0098091b
//#define BACKLIGHT_COMPENSATION_ID 0x0098091c
//#define EXPOSURE_AUTO_ID 0x009a0901
//#define EXPOSURE_ABSOLUTE_ID 0x009a0902
//#define EXPOSURE_AUTO_PRIORITY_ID 0x009a0903

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

    static void draw_image(void *buf_start, int buf_size);

private slots:
    void on_pushButton_clicked();
    void update();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QTimer * timer;
    static bool Save_Flag;

    struct v4l2_capability cap;
    struct v4l2_queryctrl qctrl;
    struct v4l2_control ctrl;
    struct v4l2_format Format;
    struct v4l2_streamparm Stream_Parm;
};

#endif // MAINWINDOW_H
