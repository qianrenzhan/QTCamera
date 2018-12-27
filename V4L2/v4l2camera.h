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

/*
 * File: v4l2camera.h
 * Modifier: qianrenzhan
 * Brief:
 */ 

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>

int v4l2cameraopen(struct v4l2_capability *cap);

void printcamerapara(int fd);

void get_v4l2_info(int fd);

void set_v4l2_para(int fd);
