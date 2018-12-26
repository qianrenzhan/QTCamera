#-------------------------------------------------
#
# Project created by QtCreator 2018-12-20T16:25:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CameraV4l2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp

linux{
SOURCES += \
    V4L2/capture.c \
    V4L2/color.c \
    V4L2/decoder_mjpeg.c \
    V4L2/decoder_yuv422.c \
    V4L2new/v4l2_controls.c \
    V4L2new/v4l2_core.c \
    V4L2new/v4l2_devices.c \
    V4L2new/v4l2_formats.c \
    V4L2new/colorspaces.c \
    V4L2new/control_profile.c \
    V4L2new/save_image.c \
    V4L2new/save_image_bmp.c \
    V4L2new/save_image_jpeg.c \
    V4L2new/save_image_png.c \
    V4L2new/soft_autofocus.c \
    V4L2new/uvc_h264.c \
    V4L2new/core_time.c \
    V4L2new/dct.c \
    V4L2new/frame_decoder.c \
    V4L2new/jpeg_decoder.c \
    V4L2new/v4l2_xu_ctrls.c \
    V4L2/v4l2camera.c
}
HEADERS += \
        mainwindow.h
linux{
HEADERS += \
    V4L2/capture.h \
    V4L2/color.h \
    V4L2/decoder.h \
    V4L2/decoder_mjpeg.h \
    V4L2/decoder_yuv422.h \
    V4L2/huffman.h \
    V4L2new/v4l2_controls.h \
    V4L2new/v4l2_core.h \
    V4L2new/v4l2_devices.h \
    V4L2new/v4l2_formats.h \
    V4L2new/colorspaces.h \
    V4L2new/control_profile.h \
    V4L2new/save_image.h \
    V4L2new/soft_autofocus.h \
    V4L2new/uvc_h264.h \
    includes/gview.h \
    V4L2new/core_time.h \
    V4L2new/dct.h \
    V4L2new/frame_decoder.h \
    V4L2new/jpeg_decoder.h \
    V4L2new/v4l2_xu_ctrls.h \
    config.h \
    V4L2/v4l2camera.h
}
FORMS += \
        mainwindow.ui

win32{
INCLUDEPATH+= D:\OpenCV\vs2015-64build-opencv3.3\install\include    \
            D:\ffmpeg\include

LIBS += D:/ffmpeg/lib/avcodec.lib
LIBS += D:/ffmpeg/lib/avdevice.lib
LIBS += D:/ffmpeg/lib/avfilter.lib
LIBS += D:/ffmpeg/lib/avformat.lib
LIBS += D:/ffmpeg/lib/avutil.lib

LIBS += D:/ffmpeg/lib/postproc.lib
LIBS += D:/ffmpeg/lib/swresample.lib
LIBS += D:/ffmpeg/lib/swscale.lib

CONFIG(debug, debug|release) {
message("debug")
LIBS += D:\OpenCV\vs2015-64build-opencv3.3\install\x64\vc14\lib\opencv_*330d.lib
} else {
message("release")
LIBS += D:\OpenCV\vs2015-64build-opencv3.3\install\x64\vc14\lib\opencv_*330.lib
}

}


linux{
INCLUDEPATH += V4L2
INCLUDEPATH += V4L2new
INCLUDEPATH += includes

QMAKE_DEFAULT_INCDIRS = ...

INCLUDEPATH += /usr/local/include \
    /usr/include/opencv \
    /usr/include/opencv2

INCLUDEPATH+=/usr/include

    if(contains(DEFINES,ARM)){
        message("compile for arm linux")
        LIBS += /usr/lib/aarch64-linux-gnu/libmysqlclient.so
        LIBS += /usr/lib/libopencv_*.so.3.3

    }else{
        message("compile for amd linux")
        LIBS += /usr/lib/x86_64-linux-gnu/libmysqlclient.so
        LIBS += /usr/lib/x86_64-linux-gnu/libopencv_*.so.3.2

        LIBS += /usr/lib/x86_64-linux-gnu/libjpeg.so    \
                /usr/lib/x86_64-linux-gnu/libpng.so     \
                /usr/lib/x86_64-linux-gnu/libv4l2.so    \
                /lib/x86_64-linux-gnu/libudev.so    \
                /usr/lib/x86_64-linux-gnu/libusb-1.0.so   \
                /usr/lib/x86_64-linux-gnu/libusb.so     \
                /usr/lib/x86_64-linux-gnu/libavcodec.so    \
                /usr/lib/x86_64-linux-gnu/libavutil.so
    }
}
