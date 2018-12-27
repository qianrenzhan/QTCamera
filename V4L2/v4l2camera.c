/****************************************************************************
#	 	GspcaGui:  Gspca/Spca5xx Grabber                                        #
# 		Copyright (C) 2004 2005 2006 Michel Xhaard                            #
#                                                                           #
# This program is free software; you can redistribute it and/or modify      #
# it under the terms of the GNU General Public License as published by      #
# the Free Software Foundation; either version 2 of the License, or         #
# (at your option) any later version.                                       #
#                                                                           #
# This program is distributed in the hope that it will be useful,           #
# but WITHOUT ANY WARRANTY; without even the implied warranty of            #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             #
# GNU General Public License for more details.                              #
#                                                                           #
# You should have received a copy of the GNU General Public License         #
# along with this program; if not, write to the Free Software               #
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA #
#                                                                           #
****************************************************************************/
#include "v4l2camera.h"

/*
 * File: v4l2camera.c
 * Modifier: qianrenzhan
 * Brief:
 */ 


int v4l2cameraopen(struct v4l2_capability *cap)
{
    //struct v4l2_capability newcap;
    int fd=-1;
    int rel=-1;
    fd= open("/dev/video0",O_RDWR,0);
    if(fd==-1)
    {
        perror("fd");
        exit(EXIT_FAILURE);
    }
    rel= ioctl(fd,VIDIOC_QUERYCAP,cap);
    if(rel==-1)
    {
        perror("ioctl");
        exit(EXIT_FAILURE);
    }

    printf("*********************Querycap Success**************************\n");

    if(cap->capabilities & V4L2_CAP_VIDEO_CAPTURE)
        printf("*****************capture is on*****************************\n");

    if(cap->capabilities & V4L2_CAP_STREAMING)
        printf("*****************Stream is on******************************\n");

    printf("\n");
    printf("\n");
    printf("*************************Capabilities**************************\n");
    printf(">:[Driver:%s]\n>:[card:%s]\n>:[bus_info:%s]\n>:[version:%d]\n",
           cap->driver,cap->card,cap->bus_info,cap->version);
    printf("**************************************************************\n");
    printf("\n");
    printf("\n");

    return fd;
}

void v4l2cameraclose(int fd)
{
    close(fd);
}

void printcamerapara(int fd)
{
    int i = 0;
    struct v4l2_queryctrl qctrl;
    struct v4l2_control ctrl;
    for(i=V4L2_CID_BASE;i<V4L2_CID_LASTP1;i++)
    {
        qctrl.id=i;
        if(ioctl(fd,VIDIOC_QUERYCTRL,&qctrl)==0)
        {
            ctrl.id=qctrl.id;
            if(ioctl(fd,VIDIOC_G_CTRL,&ctrl)<0)
                perror("**********************get ctrl failed**************\n");
            printf(">:[name:%s]\t[id:%08x]\n",qctrl.name,qctrl.id);
            printf(">:[type:%d]\n",qctrl.type);
            printf(">:[min:%d]\t[max:%d]\n",qctrl.minimum,qctrl.maximum);
            printf(">:[value:%d]\t[stp:%d]\n",ctrl.value,qctrl.step);
            printf(">:[default_value:%d]\n",qctrl.default_value);
            printf("\n");
        }
    }

    printf("------------------------------------------------------------------\n");

    for(i=V4L2_CID_CAMERA_CLASS_BASE;i<V4L2_CID_CAMERA_CLASS_BASE+32;i++)
    {
        qctrl.id=i;
        if(ioctl(fd,VIDIOC_QUERYCTRL,&qctrl)==0)
        {
            ctrl.id=qctrl.id;
            if(ioctl(fd,VIDIOC_G_CTRL,&ctrl)<0)
                perror("**********************get ctrl failed**************\n");
            printf(">:[name:%s]\t[id:%08x]\n",qctrl.name,qctrl.id);
            printf(">:[type:%d]\n",qctrl.type);
            printf(">:[min:%d]\t[max:%d]\n",qctrl.minimum,qctrl.maximum);
            printf(">:[value:%d]\t[stp:%d]\n",ctrl.value,qctrl.step);
            printf(">:[default_value:%d]\n",qctrl.default_value);
            printf("\n");
        }
    }

    printf("------------------------------------------------------------------\n");
}

void get_v4l2_info(int fd)
{
    struct v4l2_format Format;
    printf("************************Get format info********************************\n");
    Format.type= V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if(ioctl(fd,VIDIOC_G_FMT,&Format)==-1)
    {
        perror("ioctl");
        exit(EXIT_FAILURE);
    }
    printf(">:[width:%d]\t[pixelformat:%d]\n",Format.fmt.pix.width,Format.fmt.pix.height);
    printf(">:[format:%d]\t[field:%d]\n",Format.fmt.pix.pixelformat,Format.fmt.pix.field);
    printf(">:[bytesperline:%d]\t[sizeimage:%d]\n",Format.fmt.pix.bytesperline,Format.fmt.pix.sizeimage);
    printf(">:[colorspace:%d]\n",Format.fmt.pix.colorspace);
    printf("***********************************************************************\n");
    printf("\n");

    printf("************************Get Stream_Parm********************************\n");
    struct v4l2_streamparm Stream_Parm;
    Stream_Parm.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if(ioctl(fd,VIDIOC_G_PARM,&Stream_Parm)==-1)
    {
        perror("ioctl");
        exit(EXIT_FAILURE);
    }
    printf(">:[Frame rate:%u] [%u]\n",Stream_Parm.parm.capture.timeperframe.numerator,Stream_Parm.parm.capture.timeperframe.denominator);
    printf(">:[capability:%d] [capturemode:%d]\n",Stream_Parm.parm.capture.capability,Stream_Parm.parm.capture.capturemode);
    printf(">:[extendemode:%d] [readbuffers:%d]\n",Stream_Parm.parm.capture.extendedmode,Stream_Parm.parm.capture.readbuffers);
    printf("***********************************************************************\n");
    printf("\n");

    struct v4l2_control ctrl;
    ctrl.id=V4L2_CID_EXPOSURE_AUTO;
    if(ioctl(fd,VIDIOC_G_CTRL,&ctrl)==-1)
    {
        perror("ioctl");
        exit(EXIT_FAILURE);
    }
    printf(">:Get Exposure Auto:[%d]\n",ctrl.value);

    ctrl.id=V4L2_CID_EXPOSURE_ABSOLUTE;
    if(ioctl(fd,VIDIOC_G_CTRL,&ctrl)==-1)
    {
        perror("ioctl");
        exit(EXIT_FAILURE);
    }
    printf(">:Get Exposure Absolute:[%d]\n",ctrl.value);

    ctrl.id=V4L2_CID_EXPOSURE_AUTO_PRIORITY;
    if(ioctl(fd,VIDIOC_G_CTRL,&ctrl)==-1)
    {
        perror("ioctl");
        exit(EXIT_FAILURE);
    }
    printf(">:[Get Exposure Auto Priority:%d] \n",ctrl.value);

    ctrl.id=V4L2_CID_AUTO_WHITE_BALANCE;
    if(ioctl(fd,VIDIOC_G_CTRL,&ctrl)==-1)
    {
        perror("ioctl");
        exit(EXIT_FAILURE);
    }
    printf(">:[Get white balance auto value:%d] \n",ctrl.value);

    ctrl.id=V4L2_CID_WHITE_BALANCE_TEMPERATURE;
    if(ioctl(fd,VIDIOC_G_CTRL,&ctrl)==-1)
    {
        perror("ioctl");
        exit(EXIT_FAILURE);
    }
    printf(">:[Get white balance value:%d] \n",ctrl.value);

    ctrl.id=V4L2_CID_BRIGHTNESS;
    if(ioctl(fd,VIDIOC_G_CTRL,&ctrl)==-1)
    {
        perror("ioctl");
        exit(EXIT_FAILURE);
    }
    printf(">:[Get brightness value:%d] \n",ctrl.value);

    ctrl.id=V4L2_CID_CONTRAST;
    if(ioctl(fd,VIDIOC_G_CTRL,&ctrl)==-1)
    {
        perror("ioctl");
        exit(EXIT_FAILURE);
    }
    printf(">:[Get contrast value:%d] \n",ctrl.value);

    ctrl.id=V4L2_CID_SATURATION;
    if(ioctl(fd,VIDIOC_G_CTRL,&ctrl)==-1)
    {
        perror("ioctl");
        exit(EXIT_FAILURE);
    }
    printf(">:[Get saturation value:%d] \n",ctrl.value);

}

void set_v4l2_para(int fd)
{
    struct v4l2_control ctrl;
    printf("Set white balance Temperature Auto……………………\n");
    ctrl.id=V4L2_CID_AUTO_WHITE_BALANCE;
    ctrl.value=0;   //value   0 manual  1 auto
    if(ioctl(fd,VIDIOC_S_CTRL,&ctrl)==-1)
    {
        perror("ioctl");
        exit(EXIT_FAILURE);
    }
    sleep(1);
    printf("done\n");

    printf("Set white balance Temperature……………………\n");
    ctrl.id=V4L2_CID_WHITE_BALANCE_TEMPERATURE;
    ctrl.value=4000;  //value
    if(ioctl(fd,VIDIOC_S_CTRL,&ctrl)==-1)
    {
        perror("ioctl");
        exit(EXIT_FAILURE);
    }
    sleep(1);
    printf("done2\n");

    printf("Set Exposure Auto ………………\n");
    ctrl.id=V4L2_CID_EXPOSURE_AUTO;
    ctrl.value=1;   //1 manual
    if(ioctl(fd,VIDIOC_S_CTRL,&ctrl)==-1)
    {
        printf("failed\n");
        perror("ioctl");
        exit(EXIT_FAILURE);
    }
    sleep(1);
    printf("done3\n");

    printf("Set Exposure Absolute ………………\n");
    ctrl.id = V4L2_CID_EXPOSURE_ABSOLUTE;
    ctrl.value = 100;   //4
    if(ioctl(fd,VIDIOC_S_CTRL,&ctrl)==-1)
    {
        printf("failed\n");
        perror("ioctl");
        exit(EXIT_FAILURE);
    }
    sleep(1);
    printf("done4\n");
}
