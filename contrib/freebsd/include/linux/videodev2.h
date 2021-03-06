/*
 *  Video for Linux Two header file
 *
 *  Copyright (C) 1999-2007 the contributors
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  Alternatively you can redistribute this file under the terms of the
 *  BSD license as stated below:
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *  3. The names of its contributors may not be used to endorse or promote
 *     products derived from this software without specific prior written
 *     permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 *  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *	Header file for v4l or V4L2 drivers and applications
 * with public API.
 * All kernel-specific stuff were moved to media/v4l2-dev.h, so
 * no #if __KERNEL tests are allowed here
 *
 *	See http://linuxtv.org for more info
 *
 *	Author: Bill Dirks <bill@thedirks.org>
 *		Justin Schoeman
 *              Hans Verkuil <hverkuil@xs4all.nl>
 *		et al.
 */
#ifndef __LINUX_VIDEODEV2_H
#define __LINUX_VIDEODEV2_H

#include <stdint.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ioctl.h>

#ifndef HAVE_LINUX_INTEGER_TYPES
/* XXX remove when depending software has been updated */
#ifndef __u64
typedef uint64_t __u64;
#endif
#ifndef __u32
typedef uint32_t __u32;
#endif
#ifndef __u16
typedef uint16_t __u16;
#endif
#ifndef __u8
typedef uint8_t __u8;
#endif

#ifndef __s64
typedef int64_t __s64;
#endif
#ifndef __s32
typedef int32_t __s32;
#endif
#ifndef __s16
typedef int16_t __s16;
#endif
#ifndef __s8
typedef int8_t __s8;
#endif
#endif

/*
 * Common stuff for both V4L1 and V4L2
 * Moved from videodev.h
 */
#define VIDEO_MAX_FRAME               32
#define VIDEO_MAX_PLANES               8

#ifndef __KERNEL__

/* These defines are V4L1 specific and should not be used with the V4L2 API!
   They will be removed from this header in the future. */

#define VID_TYPE_CAPTURE	1	/* Can capture */
#define VID_TYPE_TUNER		2	/* Can tune */
#define VID_TYPE_TELETEXT	4	/* Does teletext */
#define VID_TYPE_OVERLAY	8	/* Overlay onto frame buffer */
#define VID_TYPE_CHROMAKEY	16	/* Overlay by chromakey */
#define VID_TYPE_CLIPPING	32	/* Can clip */
#define VID_TYPE_FRAMERAM	64	/* Uses the frame buffer memory */
#define VID_TYPE_SCALES		128	/* Scalable */
#define VID_TYPE_MONOCHROME	256	/* Monochrome only */
#define VID_TYPE_SUBCAPTURE	512	/* Can capture subareas of the image */
#define VID_TYPE_MPEG_DECODER	1024	/* Can decode MPEG streams */
#define VID_TYPE_MPEG_ENCODER	2048	/* Can encode MPEG streams */
#define VID_TYPE_MJPEG_DECODER	4096	/* Can decode MJPEG streams */
#define VID_TYPE_MJPEG_ENCODER	8192	/* Can encode MJPEG streams */
#endif

/*
 *	M I S C E L L A N E O U S
 */

/*  Four-character-code (FOURCC) */
#define v4l2_fourcc(a, b, c, d)\
	((uint32_t)(a) | ((uint32_t)(b) << 8) | ((uint32_t)(c) << 16) | ((uint32_t)(d) << 24))

/*
 *	E N U M S
 */
enum v4l2_field {
	V4L2_FIELD_ANY           = 0, /* driver can choose from none,
					 top, bottom, interlaced
					 depending on whatever it thinks
					 is approximate ... */
	V4L2_FIELD_NONE          = 1, /* this device has no fields ... */
	V4L2_FIELD_TOP           = 2, /* top field only */
	V4L2_FIELD_BOTTOM        = 3, /* bottom field only */
	V4L2_FIELD_INTERLACED    = 4, /* both fields interlaced */
	V4L2_FIELD_SEQ_TB        = 5, /* both fields sequential into one
					 buffer, top-bottom order */
	V4L2_FIELD_SEQ_BT        = 6, /* same as above + bottom-top order */
	V4L2_FIELD_ALTERNATE     = 7, /* both fields alternating into
					 separate buffers */
	V4L2_FIELD_INTERLACED_TB = 8, /* both fields interlaced, top field
					 first and the top field is
					 transmitted first */
	V4L2_FIELD_INTERLACED_BT = 9, /* both fields interlaced, top field
					 first and the bottom field is
					 transmitted first */
};
#define V4L2_FIELD_HAS_TOP(field)	\
	((field) == V4L2_FIELD_TOP 	||\
	 (field) == V4L2_FIELD_INTERLACED ||\
	 (field) == V4L2_FIELD_INTERLACED_TB ||\
	 (field) == V4L2_FIELD_INTERLACED_BT ||\
	 (field) == V4L2_FIELD_SEQ_TB	||\
	 (field) == V4L2_FIELD_SEQ_BT)
#define V4L2_FIELD_HAS_BOTTOM(field)	\
	((field) == V4L2_FIELD_BOTTOM 	||\
	 (field) == V4L2_FIELD_INTERLACED ||\
	 (field) == V4L2_FIELD_INTERLACED_TB ||\
	 (field) == V4L2_FIELD_INTERLACED_BT ||\
	 (field) == V4L2_FIELD_SEQ_TB	||\
	 (field) == V4L2_FIELD_SEQ_BT)
#define V4L2_FIELD_HAS_BOTH(field)	\
	((field) == V4L2_FIELD_INTERLACED ||\
	 (field) == V4L2_FIELD_INTERLACED_TB ||\
	 (field) == V4L2_FIELD_INTERLACED_BT ||\
	 (field) == V4L2_FIELD_SEQ_TB ||\
	 (field) == V4L2_FIELD_SEQ_BT)

enum v4l2_buf_type {
	V4L2_BUF_TYPE_VIDEO_CAPTURE        = 1,
	V4L2_BUF_TYPE_VIDEO_OUTPUT         = 2,
	V4L2_BUF_TYPE_VIDEO_OVERLAY        = 3,
	V4L2_BUF_TYPE_VBI_CAPTURE          = 4,
	V4L2_BUF_TYPE_VBI_OUTPUT           = 5,
	V4L2_BUF_TYPE_SLICED_VBI_CAPTURE   = 6,
	V4L2_BUF_TYPE_SLICED_VBI_OUTPUT    = 7,
#if 1
	/* Experimental */
	V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY = 8,
#endif
	V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE = 9,
	V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE  = 10,
	V4L2_BUF_TYPE_PRIVATE              = 0x80,
};

#define V4L2_TYPE_IS_MULTIPLANAR(type)			\
	((type) == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE	\
	 || (type) == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)

#define V4L2_TYPE_IS_OUTPUT(type)				\
	((type) == V4L2_BUF_TYPE_VIDEO_OUTPUT			\
	 || (type) == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE		\
	 || (type) == V4L2_BUF_TYPE_VIDEO_OVERLAY		\
	 || (type) == V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY	\
	 || (type) == V4L2_BUF_TYPE_VBI_OUTPUT			\
	 || (type) == V4L2_BUF_TYPE_SLICED_VBI_OUTPUT)

enum v4l2_tuner_type {
	V4L2_TUNER_RADIO	     = 1,
	V4L2_TUNER_ANALOG_TV	     = 2,
	V4L2_TUNER_DIGITAL_TV	     = 3,
};

enum v4l2_memory {
	V4L2_MEMORY_MMAP             = 1,
	V4L2_MEMORY_USERPTR          = 2,
	V4L2_MEMORY_OVERLAY          = 3,
};

/* see also http://vektor.theorem.ca/graphics/ycbcr/ */
enum v4l2_colorspace {
	/* ITU-R 601 -- broadcast NTSC/PAL */
	V4L2_COLORSPACE_SMPTE170M     = 1,

	/* 1125-Line (US) HDTV */
	V4L2_COLORSPACE_SMPTE240M     = 2,

	/* HD and modern captures. */
	V4L2_COLORSPACE_REC709        = 3,

	/* broken BT878 extents (601, luma range 16-253 instead of 16-235) */
	V4L2_COLORSPACE_BT878         = 4,

	/* These should be useful.  Assume 601 extents. */
	V4L2_COLORSPACE_470_SYSTEM_M  = 5,
	V4L2_COLORSPACE_470_SYSTEM_BG = 6,

	/* I know there will be cameras that send this.  So, this is
	 * unspecified chromaticities and full 0-255 on each of the
	 * Y'CbCr components
	 */
	V4L2_COLORSPACE_JPEG          = 7,

	/* For RGB colourspaces, this is probably a good start. */
	V4L2_COLORSPACE_SRGB          = 8,
};

enum v4l2_priority {
	V4L2_PRIORITY_UNSET       = 0,  /* not initialized */
	V4L2_PRIORITY_BACKGROUND  = 1,
	V4L2_PRIORITY_INTERACTIVE = 2,
	V4L2_PRIORITY_RECORD      = 3,
	V4L2_PRIORITY_DEFAULT     = V4L2_PRIORITY_INTERACTIVE,
};

struct v4l2_rect {
	int32_t   left;
	int32_t   top;
	int32_t   width;
	int32_t   height;
};

struct v4l2_fract {
	uint32_t   numerator;
	uint32_t   denominator;
};

/**
  * struct v4l2_capability - Describes V4L2 device caps returned by VIDIOC_QUERYCAP
  *
  * @driver:	   name of the driver module (e.g. "bttv")
  * @card:	   name of the card (e.g. "Hauppauge WinTV")
  * @bus_info:	   name of the bus (e.g. "PCI:" + pci_name(pci_dev) )
  * @version:	   KERNEL_VERSION
  * @capabilities: capabilities of the physical device as a whole
  * @device_caps:  capabilities accessed via this particular device (node)
  * @reserved:	   reserved fields for future extensions
  */
struct v4l2_capability {
	uint8_t	driver[16];
	uint8_t	card[32];
	uint8_t	bus_info[32];
	uint32_t   version;
	uint32_t	capabilities;
	uint32_t	device_caps;
	uint32_t	reserved[3];
};

/* Values for 'capabilities' field */
#define V4L2_CAP_VIDEO_CAPTURE		0x00000001  /* Is a video capture device */
#define V4L2_CAP_VIDEO_OUTPUT		0x00000002  /* Is a video output device */
#define V4L2_CAP_VIDEO_OVERLAY		0x00000004  /* Can do video overlay */
#define V4L2_CAP_VBI_CAPTURE		0x00000010  /* Is a raw VBI capture device */
#define V4L2_CAP_VBI_OUTPUT		0x00000020  /* Is a raw VBI output device */
#define V4L2_CAP_SLICED_VBI_CAPTURE	0x00000040  /* Is a sliced VBI capture device */
#define V4L2_CAP_SLICED_VBI_OUTPUT	0x00000080  /* Is a sliced VBI output device */
#define V4L2_CAP_RDS_CAPTURE		0x00000100  /* RDS data capture */
#define V4L2_CAP_VIDEO_OUTPUT_OVERLAY	0x00000200  /* Can do video output overlay */
#define V4L2_CAP_HW_FREQ_SEEK		0x00000400  /* Can do hardware frequency seek  */
#define V4L2_CAP_RDS_OUTPUT		0x00000800  /* Is an RDS encoder */

/* Is a video capture device that supports multiplanar formats */
#define V4L2_CAP_VIDEO_CAPTURE_MPLANE	0x00001000
/* Is a video output device that supports multiplanar formats */
#define V4L2_CAP_VIDEO_OUTPUT_MPLANE	0x00002000

#define V4L2_CAP_TUNER			0x00010000  /* has a tuner */
#define V4L2_CAP_AUDIO			0x00020000  /* has audio support */
#define V4L2_CAP_RADIO			0x00040000  /* is a radio device */
#define V4L2_CAP_MODULATOR		0x00080000  /* has a modulator */

#define V4L2_CAP_READWRITE              0x01000000  /* read/write systemcalls */
#define V4L2_CAP_ASYNCIO                0x02000000  /* async I/O */
#define V4L2_CAP_STREAMING              0x04000000  /* streaming I/O ioctls */

#define V4L2_CAP_DEVICE_CAPS            0x80000000  /* sets device capabilities field */

/*
 *	V I D E O   I M A G E   F O R M A T
 */
struct v4l2_pix_format {
	uint32_t         		width;
	uint32_t			height;
	uint32_t			pixelformat;
	uint32_t			field;		/* enum v4l2_field */
	uint32_t            	bytesperline;	/* for padding, zero if unused */
	uint32_t          		sizeimage;
	uint32_t			colorspace;	/* enum v4l2_colorspace */
	uint32_t			priv;		/* private data, depends on pixelformat */
};

/*      Pixel format         FOURCC                          depth  Description  */

/* RGB formats */
#define V4L2_PIX_FMT_RGB332  v4l2_fourcc('R', 'G', 'B', '1') /*  8  RGB-3-3-2     */
#define V4L2_PIX_FMT_RGB444  v4l2_fourcc('R', '4', '4', '4') /* 16  xxxxrrrr ggggbbbb */
#define V4L2_PIX_FMT_RGB555  v4l2_fourcc('R', 'G', 'B', 'O') /* 16  RGB-5-5-5     */
#define V4L2_PIX_FMT_RGB565  v4l2_fourcc('R', 'G', 'B', 'P') /* 16  RGB-5-6-5     */
#define V4L2_PIX_FMT_RGB555X v4l2_fourcc('R', 'G', 'B', 'Q') /* 16  RGB-5-5-5 BE  */
#define V4L2_PIX_FMT_RGB565X v4l2_fourcc('R', 'G', 'B', 'R') /* 16  RGB-5-6-5 BE  */
#define V4L2_PIX_FMT_BGR666  v4l2_fourcc('B', 'G', 'R', 'H') /* 18  BGR-6-6-6	  */
#define V4L2_PIX_FMT_BGR24   v4l2_fourcc('B', 'G', 'R', '3') /* 24  BGR-8-8-8     */
#define V4L2_PIX_FMT_RGB24   v4l2_fourcc('R', 'G', 'B', '3') /* 24  RGB-8-8-8     */
#define V4L2_PIX_FMT_BGR32   v4l2_fourcc('B', 'G', 'R', '4') /* 32  BGR-8-8-8-8   */
#define V4L2_PIX_FMT_RGB32   v4l2_fourcc('R', 'G', 'B', '4') /* 32  RGB-8-8-8-8   */

/* Grey formats */
#define V4L2_PIX_FMT_GREY    v4l2_fourcc('G', 'R', 'E', 'Y') /*  8  Greyscale     */
#define V4L2_PIX_FMT_Y4      v4l2_fourcc('Y', '0', '4', ' ') /*  4  Greyscale     */
#define V4L2_PIX_FMT_Y6      v4l2_fourcc('Y', '0', '6', ' ') /*  6  Greyscale     */
#define V4L2_PIX_FMT_Y10     v4l2_fourcc('Y', '1', '0', ' ') /* 10  Greyscale     */
#define V4L2_PIX_FMT_Y12     v4l2_fourcc('Y', '1', '2', ' ') /* 12  Greyscale     */
#define V4L2_PIX_FMT_Y16     v4l2_fourcc('Y', '1', '6', ' ') /* 16  Greyscale     */

/* Grey bit-packed formats */
#define V4L2_PIX_FMT_Y10BPACK    v4l2_fourcc('Y', '1', '0', 'B') /* 10  Greyscale bit-packed */

/* Palette formats */
#define V4L2_PIX_FMT_PAL8    v4l2_fourcc('P', 'A', 'L', '8') /*  8  8-bit palette */

/* Luminance+Chrominance formats */
#define V4L2_PIX_FMT_YVU410  v4l2_fourcc('Y', 'V', 'U', '9') /*  9  YVU 4:1:0     */
#define V4L2_PIX_FMT_YVU420  v4l2_fourcc('Y', 'V', '1', '2') /* 12  YVU 4:2:0     */
#define V4L2_PIX_FMT_YUYV    v4l2_fourcc('Y', 'U', 'Y', 'V') /* 16  YUV 4:2:2     */
#define V4L2_PIX_FMT_YYUV    v4l2_fourcc('Y', 'Y', 'U', 'V') /* 16  YUV 4:2:2     */
#define V4L2_PIX_FMT_YVYU    v4l2_fourcc('Y', 'V', 'Y', 'U') /* 16 YVU 4:2:2 */
#define V4L2_PIX_FMT_UYVY    v4l2_fourcc('U', 'Y', 'V', 'Y') /* 16  YUV 4:2:2     */
#define V4L2_PIX_FMT_VYUY    v4l2_fourcc('V', 'Y', 'U', 'Y') /* 16  YUV 4:2:2     */
#define V4L2_PIX_FMT_YUV422P v4l2_fourcc('4', '2', '2', 'P') /* 16  YVU422 planar */
#define V4L2_PIX_FMT_YUV411P v4l2_fourcc('4', '1', '1', 'P') /* 16  YVU411 planar */
#define V4L2_PIX_FMT_Y41P    v4l2_fourcc('Y', '4', '1', 'P') /* 12  YUV 4:1:1     */
#define V4L2_PIX_FMT_YUV444  v4l2_fourcc('Y', '4', '4', '4') /* 16  xxxxyyyy uuuuvvvv */
#define V4L2_PIX_FMT_YUV555  v4l2_fourcc('Y', 'U', 'V', 'O') /* 16  YUV-5-5-5     */
#define V4L2_PIX_FMT_YUV565  v4l2_fourcc('Y', 'U', 'V', 'P') /* 16  YUV-5-6-5     */
#define V4L2_PIX_FMT_YUV32   v4l2_fourcc('Y', 'U', 'V', '4') /* 32  YUV-8-8-8-8   */
#define V4L2_PIX_FMT_YUV410  v4l2_fourcc('Y', 'U', 'V', '9') /*  9  YUV 4:1:0     */
#define V4L2_PIX_FMT_YUV420  v4l2_fourcc('Y', 'U', '1', '2') /* 12  YUV 4:2:0     */
#define V4L2_PIX_FMT_HI240   v4l2_fourcc('H', 'I', '2', '4') /*  8  8-bit color   */
#define V4L2_PIX_FMT_HM12    v4l2_fourcc('H', 'M', '1', '2') /*  8  YUV 4:2:0 16x16 macroblocks */
#define V4L2_PIX_FMT_M420    v4l2_fourcc('M', '4', '2', '0') /* 12  YUV 4:2:0 2 lines y, 1 line uv interleaved */

/* two planes -- one Y, one Cr + Cb interleaved  */
#define V4L2_PIX_FMT_NV12    v4l2_fourcc('N', 'V', '1', '2') /* 12  Y/CbCr 4:2:0  */
#define V4L2_PIX_FMT_NV21    v4l2_fourcc('N', 'V', '2', '1') /* 12  Y/CrCb 4:2:0  */
#define V4L2_PIX_FMT_NV16    v4l2_fourcc('N', 'V', '1', '6') /* 16  Y/CbCr 4:2:2  */
#define V4L2_PIX_FMT_NV61    v4l2_fourcc('N', 'V', '6', '1') /* 16  Y/CrCb 4:2:2  */
#define V4L2_PIX_FMT_NV24    v4l2_fourcc('N', 'V', '2', '4') /* 24  Y/CbCr 4:4:4  */
#define V4L2_PIX_FMT_NV42    v4l2_fourcc('N', 'V', '4', '2') /* 24  Y/CrCb 4:4:4  */

/* two non contiguous planes - one Y, one Cr + Cb interleaved  */
#define V4L2_PIX_FMT_NV12M   v4l2_fourcc('N', 'M', '1', '2') /* 12  Y/CbCr 4:2:0  */
#define V4L2_PIX_FMT_NV12MT  v4l2_fourcc('T', 'M', '1', '2') /* 12  Y/CbCr 4:2:0 64x32 macroblocks */

/* three non contiguous planes - Y, Cb, Cr */
#define V4L2_PIX_FMT_YUV420M v4l2_fourcc('Y', 'M', '1', '2') /* 12  YUV420 planar */

/* Bayer formats - see http://www.siliconimaging.com/RGB%20Bayer.htm */
#define V4L2_PIX_FMT_SBGGR8  v4l2_fourcc('B', 'A', '8', '1') /*  8  BGBG.. GRGR.. */
#define V4L2_PIX_FMT_SGBRG8  v4l2_fourcc('G', 'B', 'R', 'G') /*  8  GBGB.. RGRG.. */
#define V4L2_PIX_FMT_SGRBG8  v4l2_fourcc('G', 'R', 'B', 'G') /*  8  GRGR.. BGBG.. */
#define V4L2_PIX_FMT_SRGGB8  v4l2_fourcc('R', 'G', 'G', 'B') /*  8  RGRG.. GBGB.. */
#define V4L2_PIX_FMT_SBGGR10 v4l2_fourcc('B', 'G', '1', '0') /* 10  BGBG.. GRGR.. */
#define V4L2_PIX_FMT_SGBRG10 v4l2_fourcc('G', 'B', '1', '0') /* 10  GBGB.. RGRG.. */
#define V4L2_PIX_FMT_SGRBG10 v4l2_fourcc('B', 'A', '1', '0') /* 10  GRGR.. BGBG.. */
#define V4L2_PIX_FMT_SRGGB10 v4l2_fourcc('R', 'G', '1', '0') /* 10  RGRG.. GBGB.. */
#define V4L2_PIX_FMT_SBGGR12 v4l2_fourcc('B', 'G', '1', '2') /* 12  BGBG.. GRGR.. */
#define V4L2_PIX_FMT_SGBRG12 v4l2_fourcc('G', 'B', '1', '2') /* 12  GBGB.. RGRG.. */
#define V4L2_PIX_FMT_SGRBG12 v4l2_fourcc('B', 'A', '1', '2') /* 12  GRGR.. BGBG.. */
#define V4L2_PIX_FMT_SRGGB12 v4l2_fourcc('R', 'G', '1', '2') /* 12  RGRG.. GBGB.. */
	/* 10bit raw bayer DPCM compressed to 8 bits */
#define V4L2_PIX_FMT_SBGGR10DPCM8 v4l2_fourcc('b', 'B', 'A', '8')
#define V4L2_PIX_FMT_SGBRG10DPCM8 v4l2_fourcc('b', 'G', 'A', '8')
#define V4L2_PIX_FMT_SGRBG10DPCM8 v4l2_fourcc('B', 'D', '1', '0')
#define V4L2_PIX_FMT_SRGGB10DPCM8 v4l2_fourcc('b', 'R', 'A', '8')
	/*
	 * 10bit raw bayer, expanded to 16 bits
	 * xxxxrrrrrrrrrrxxxxgggggggggg xxxxggggggggggxxxxbbbbbbbbbb...
	 */
#define V4L2_PIX_FMT_SBGGR16 v4l2_fourcc('B', 'Y', 'R', '2') /* 16  BGBG.. GRGR.. */

/* compressed formats */
#define V4L2_PIX_FMT_MJPEG    v4l2_fourcc('M', 'J', 'P', 'G') /* Motion-JPEG   */
#define V4L2_PIX_FMT_JPEG     v4l2_fourcc('J', 'P', 'E', 'G') /* JFIF JPEG     */
#define V4L2_PIX_FMT_DV       v4l2_fourcc('d', 'v', 's', 'd') /* 1394          */
#define V4L2_PIX_FMT_MPEG     v4l2_fourcc('M', 'P', 'E', 'G') /* MPEG-1/2/4 Multiplexed */
#define V4L2_PIX_FMT_H264     v4l2_fourcc('H', '2', '6', '4') /* H264 with start codes */
#define V4L2_PIX_FMT_H264_NO_SC v4l2_fourcc('A', 'V', 'C', '1') /* H264 without start codes */
#define V4L2_PIX_FMT_H263     v4l2_fourcc('H', '2', '6', '3') /* H263          */
#define V4L2_PIX_FMT_MPEG1    v4l2_fourcc('M', 'P', 'G', '1') /* MPEG-1 ES     */
#define V4L2_PIX_FMT_MPEG2    v4l2_fourcc('M', 'P', 'G', '2') /* MPEG-2 ES     */
#define V4L2_PIX_FMT_MPEG4    v4l2_fourcc('M', 'P', 'G', '4') /* MPEG-4 ES     */
#define V4L2_PIX_FMT_XVID     v4l2_fourcc('X', 'V', 'I', 'D') /* Xvid           */
#define V4L2_PIX_FMT_VC1_ANNEX_G v4l2_fourcc('V', 'C', '1', 'G') /* SMPTE 421M Annex G compliant stream */
#define V4L2_PIX_FMT_VC1_ANNEX_L v4l2_fourcc('V', 'C', '1', 'L') /* SMPTE 421M Annex L compliant stream */

/*  Vendor-specific formats   */
#define V4L2_PIX_FMT_CPIA1    v4l2_fourcc('C', 'P', 'I', 'A') /* cpia1 YUV */
#define V4L2_PIX_FMT_WNVA     v4l2_fourcc('W', 'N', 'V', 'A') /* Winnov hw compress */
#define V4L2_PIX_FMT_SN9C10X  v4l2_fourcc('S', '9', '1', '0') /* SN9C10x compression */
#define V4L2_PIX_FMT_SN9C20X_I420 v4l2_fourcc('S', '9', '2', '0') /* SN9C20x YUV 4:2:0 */
#define V4L2_PIX_FMT_PWC1     v4l2_fourcc('P', 'W', 'C', '1') /* pwc older webcam */
#define V4L2_PIX_FMT_PWC2     v4l2_fourcc('P', 'W', 'C', '2') /* pwc newer webcam */
#define V4L2_PIX_FMT_ET61X251 v4l2_fourcc('E', '6', '2', '5') /* ET61X251 compression */
#define V4L2_PIX_FMT_SPCA501  v4l2_fourcc('S', '5', '0', '1') /* YUYV per line */
#define V4L2_PIX_FMT_SPCA505  v4l2_fourcc('S', '5', '0', '5') /* YYUV per line */
#define V4L2_PIX_FMT_SPCA508  v4l2_fourcc('S', '5', '0', '8') /* YUVY per line */
#define V4L2_PIX_FMT_SPCA561  v4l2_fourcc('S', '5', '6', '1') /* compressed GBRG bayer */
#define V4L2_PIX_FMT_PAC207   v4l2_fourcc('P', '2', '0', '7') /* compressed BGGR bayer */
#define V4L2_PIX_FMT_MR97310A v4l2_fourcc('M', '3', '1', '0') /* compressed BGGR bayer */
#define V4L2_PIX_FMT_JL2005BCD v4l2_fourcc('J', 'L', '2', '0') /* compressed RGGB bayer */
#define V4L2_PIX_FMT_SN9C2028 v4l2_fourcc('S', 'O', 'N', 'X') /* compressed GBRG bayer */
#define V4L2_PIX_FMT_SQ905C   v4l2_fourcc('9', '0', '5', 'C') /* compressed RGGB bayer */
#define V4L2_PIX_FMT_PJPG     v4l2_fourcc('P', 'J', 'P', 'G') /* Pixart 73xx JPEG */
#define V4L2_PIX_FMT_OV511    v4l2_fourcc('O', '5', '1', '1') /* ov511 JPEG */
#define V4L2_PIX_FMT_OV518    v4l2_fourcc('O', '5', '1', '8') /* ov518 JPEG */
#define V4L2_PIX_FMT_STV0680  v4l2_fourcc('S', '6', '8', '0') /* stv0680 bayer */
#define V4L2_PIX_FMT_TM6000   v4l2_fourcc('T', 'M', '6', '0') /* tm5600/tm60x0 */
#define V4L2_PIX_FMT_CIT_YYVYUY v4l2_fourcc('C', 'I', 'T', 'V') /* one line of Y then 1 line of VYUY */
#define V4L2_PIX_FMT_KONICA420  v4l2_fourcc('K', 'O', 'N', 'I') /* YUV420 planar in blocks of 256 pixels */
#define V4L2_PIX_FMT_JPGL	v4l2_fourcc('J', 'P', 'G', 'L') /* JPEG-Lite */
#define V4L2_PIX_FMT_SE401      v4l2_fourcc('S', '4', '0', '1') /* se401 janggu compressed rgb */

/*
 *	F O R M A T   E N U M E R A T I O N
 */
struct v4l2_fmtdesc {
	uint32_t		    index;             /* Format number      */
	uint32_t		    type;              /* enum v4l2_buf_type */
	uint32_t               flags;
	uint8_t		    description[32];   /* Description string */
	uint32_t		    pixelformat;       /* Format fourcc      */
	uint32_t		    reserved[4];
};

#define V4L2_FMT_FLAG_COMPRESSED 0x0001
#define V4L2_FMT_FLAG_EMULATED   0x0002

#if 1
	/* Experimental Frame Size and frame rate enumeration */
/*
 *	F R A M E   S I Z E   E N U M E R A T I O N
 */
enum v4l2_frmsizetypes {
	V4L2_FRMSIZE_TYPE_DISCRETE	= 1,
	V4L2_FRMSIZE_TYPE_CONTINUOUS	= 2,
	V4L2_FRMSIZE_TYPE_STEPWISE	= 3,
};

struct v4l2_frmsize_discrete {
	uint32_t			width;		/* Frame width [pixel] */
	uint32_t			height;		/* Frame height [pixel] */
};

struct v4l2_frmsize_stepwise {
	uint32_t			min_width;	/* Minimum frame width [pixel] */
	uint32_t			max_width;	/* Maximum frame width [pixel] */
	uint32_t			step_width;	/* Frame width step size [pixel] */
	uint32_t			min_height;	/* Minimum frame height [pixel] */
	uint32_t			max_height;	/* Maximum frame height [pixel] */
	uint32_t			step_height;	/* Frame height step size [pixel] */
};

struct v4l2_frmsizeenum {
	uint32_t			index;		/* Frame size number */
	uint32_t			pixel_format;	/* Pixel format */
	uint32_t			type;		/* Frame size type the device supports. */

	union {					/* Frame size */
		struct v4l2_frmsize_discrete	discrete;
		struct v4l2_frmsize_stepwise	stepwise;
	};

	uint32_t   reserved[2];			/* Reserved space for future use */
};

/*
 *	F R A M E   R A T E   E N U M E R A T I O N
 */
enum v4l2_frmivaltypes {
	V4L2_FRMIVAL_TYPE_DISCRETE	= 1,
	V4L2_FRMIVAL_TYPE_CONTINUOUS	= 2,
	V4L2_FRMIVAL_TYPE_STEPWISE	= 3,
};

struct v4l2_frmival_stepwise {
	struct v4l2_fract	min;		/* Minimum frame interval [s] */
	struct v4l2_fract	max;		/* Maximum frame interval [s] */
	struct v4l2_fract	step;		/* Frame interval step size [s] */
};

struct v4l2_frmivalenum {
	uint32_t			index;		/* Frame format index */
	uint32_t			pixel_format;	/* Pixel format */
	uint32_t			width;		/* Frame width */
	uint32_t			height;		/* Frame height */
	uint32_t			type;		/* Frame interval type the device supports. */

	union {					/* Frame interval */
		struct v4l2_fract		discrete;
		struct v4l2_frmival_stepwise	stepwise;
	};

	uint32_t	reserved[2];			/* Reserved space for future use */
};
#endif

/*
 *	T I M E C O D E
 */
struct v4l2_timecode {
	uint32_t	type;
	uint32_t	flags;
	uint8_t	frames;
	uint8_t	seconds;
	uint8_t	minutes;
	uint8_t	hours;
	uint8_t	userbits[4];
};

/*  Type  */
#define V4L2_TC_TYPE_24FPS		1
#define V4L2_TC_TYPE_25FPS		2
#define V4L2_TC_TYPE_30FPS		3
#define V4L2_TC_TYPE_50FPS		4
#define V4L2_TC_TYPE_60FPS		5

/*  Flags  */
#define V4L2_TC_FLAG_DROPFRAME		0x0001 /* "drop-frame" mode */
#define V4L2_TC_FLAG_COLORFRAME		0x0002
#define V4L2_TC_USERBITS_field		0x000C
#define V4L2_TC_USERBITS_USERDEFINED	0x0000
#define V4L2_TC_USERBITS_8BITCHARS	0x0008
/* The above is based on SMPTE timecodes */

struct v4l2_jpegcompression {
	int quality;

	int  APPn;              /* Number of APP segment to be written,
				 * must be 0..15 */
	int  APP_len;           /* Length of data in JPEG APPn segment */
	char APP_data[60];      /* Data in the JPEG APPn segment. */

	int  COM_len;           /* Length of data in JPEG COM segment */
	char COM_data[60];      /* Data in JPEG COM segment */

	uint32_t jpeg_markers;     /* Which markers should go into the JPEG
				 * output. Unless you exactly know what
				 * you do, leave them untouched.
				 * Inluding less markers will make the
				 * resulting code smaller, but there will
				 * be fewer applications which can read it.
				 * The presence of the APP and COM marker
				 * is influenced by APP_len and COM_len
				 * ONLY, not by this property! */

#define V4L2_JPEG_MARKER_DHT (1<<3)    /* Define Huffman Tables */
#define V4L2_JPEG_MARKER_DQT (1<<4)    /* Define Quantization Tables */
#define V4L2_JPEG_MARKER_DRI (1<<5)    /* Define Restart Interval */
#define V4L2_JPEG_MARKER_COM (1<<6)    /* Comment segment */
#define V4L2_JPEG_MARKER_APP (1<<7)    /* App segment, driver will
					* allways use APP0 */
};

/*
 *	M E M O R Y - M A P P I N G   B U F F E R S
 */
struct v4l2_requestbuffers {
	uint32_t			count;
	uint32_t			type;		/* enum v4l2_buf_type */
	uint32_t			memory;		/* enum v4l2_memory */
	uint32_t			reserved[2];
};

/**
 * struct v4l2_plane - plane info for multi-planar buffers
 * @bytesused:		number of bytes occupied by data in the plane (payload)
 * @length:		size of this plane (NOT the payload) in bytes
 * @mem_offset:		when memory in the associated struct v4l2_buffer is
 *			V4L2_MEMORY_MMAP, equals the offset from the start of
 *			the device memory for this plane (or is a "cookie" that
 *			should be passed to mmap() called on the video node)
 * @userptr:		when memory is V4L2_MEMORY_USERPTR, a userspace pointer
 *			pointing to this plane
 * @data_offset:	offset in the plane to the start of data; usually 0,
 *			unless there is a header in front of the data
 *
 * Multi-planar buffers consist of one or more planes, e.g. an YCbCr buffer
 * with two planes can have one plane for Y, and another for interleaved CbCr
 * components. Each plane can reside in a separate memory buffer, or even in
 * a completely separate memory node (e.g. in embedded devices).
 */
struct v4l2_plane {
	uint32_t			bytesused;
	uint32_t			length;
	union {
		uint32_t		mem_offset;
		unsigned long	userptr;
	} m;
	uint32_t			data_offset;
	uint32_t			reserved[11];
};

/**
 * struct v4l2_buffer - video buffer info
 * @index:	id number of the buffer
 * @type:	enum v4l2_buf_type; buffer type (type == *_MPLANE for
 *		multiplanar buffers);
 * @bytesused:	number of bytes occupied by data in the buffer (payload);
 *		unused (set to 0) for multiplanar buffers
 * @flags:	buffer informational flags
 * @field:	enum v4l2_field; field order of the image in the buffer
 * @timestamp:	frame timestamp
 * @timecode:	frame timecode
 * @sequence:	sequence count of this frame
 * @memory:	enum v4l2_memory; the method, in which the actual video data is
 *		passed
 * @offset:	for non-multiplanar buffers with memory == V4L2_MEMORY_MMAP;
 *		offset from the start of the device memory for this plane,
 *		(or a "cookie" that should be passed to mmap() as offset)
 * @userptr:	for non-multiplanar buffers with memory == V4L2_MEMORY_USERPTR;
 *		a userspace pointer pointing to this buffer
 * @planes:	for multiplanar buffers; userspace pointer to the array of plane
 *		info structs for this buffer
 * @length:	size in bytes of the buffer (NOT its payload) for single-plane
 *		buffers (when type != *_MPLANE); number of elements in the
 *		planes array for multi-plane buffers
 * @input:	input number from which the video data has has been captured
 *
 * Contains data exchanged by application and driver using one of the Streaming
 * I/O methods.
 */
struct v4l2_buffer {
	uint32_t			index;
	uint32_t			type;
	uint32_t			bytesused;
	uint32_t			flags;
	uint32_t			field;
	struct timeval		timestamp;
	struct v4l2_timecode	timecode;
	uint32_t			sequence;

	/* memory location */
	uint32_t			memory;
	union {
		uint32_t           offset;
		unsigned long   userptr;
		struct v4l2_plane *planes;
	} m;
	uint32_t			length;
	uint32_t			input;
	uint32_t			reserved;
};

/*  Flags for 'flags' field */
#define V4L2_BUF_FLAG_MAPPED	0x0001  /* Buffer is mapped (flag) */
#define V4L2_BUF_FLAG_QUEUED	0x0002	/* Buffer is queued for processing */
#define V4L2_BUF_FLAG_DONE	0x0004	/* Buffer is ready */
#define V4L2_BUF_FLAG_KEYFRAME	0x0008	/* Image is a keyframe (I-frame) */
#define V4L2_BUF_FLAG_PFRAME	0x0010	/* Image is a P-frame */
#define V4L2_BUF_FLAG_BFRAME	0x0020	/* Image is a B-frame */
/* Buffer is ready, but the data contained within is corrupted. */
#define V4L2_BUF_FLAG_ERROR	0x0040
#define V4L2_BUF_FLAG_TIMECODE	0x0100	/* timecode field is valid */
#define V4L2_BUF_FLAG_INPUT     0x0200  /* input field is valid */
#define V4L2_BUF_FLAG_PREPARED	0x0400	/* Buffer is prepared for queuing */
/* Cache handling flags */
#define V4L2_BUF_FLAG_NO_CACHE_INVALIDATE	0x0800
#define V4L2_BUF_FLAG_NO_CACHE_CLEAN		0x1000

/*
 *	O V E R L A Y   P R E V I E W
 */
struct v4l2_framebuffer {
	uint32_t			capability;
	uint32_t			flags;
/* FIXME: in theory we should pass something like PCI device + memory
 * region + offset instead of some physical address */
	void                    *base;
	struct v4l2_pix_format	fmt;
};
/*  Flags for the 'capability' field. Read only */
#define V4L2_FBUF_CAP_EXTERNOVERLAY	0x0001
#define V4L2_FBUF_CAP_CHROMAKEY		0x0002
#define V4L2_FBUF_CAP_LIST_CLIPPING     0x0004
#define V4L2_FBUF_CAP_BITMAP_CLIPPING	0x0008
#define V4L2_FBUF_CAP_LOCAL_ALPHA	0x0010
#define V4L2_FBUF_CAP_GLOBAL_ALPHA	0x0020
#define V4L2_FBUF_CAP_LOCAL_INV_ALPHA	0x0040
#define V4L2_FBUF_CAP_SRC_CHROMAKEY	0x0080
/*  Flags for the 'flags' field. */
#define V4L2_FBUF_FLAG_PRIMARY		0x0001
#define V4L2_FBUF_FLAG_OVERLAY		0x0002
#define V4L2_FBUF_FLAG_CHROMAKEY	0x0004
#define V4L2_FBUF_FLAG_LOCAL_ALPHA	0x0008
#define V4L2_FBUF_FLAG_GLOBAL_ALPHA	0x0010
#define V4L2_FBUF_FLAG_LOCAL_INV_ALPHA	0x0020
#define V4L2_FBUF_FLAG_SRC_CHROMAKEY	0x0040

struct v4l2_clip {
	struct v4l2_rect        c;
	struct v4l2_clip	 *next;
};

struct v4l2_window {
	struct v4l2_rect        w;
	uint32_t			field;	 /* enum v4l2_field */
	uint32_t			chromakey;
	struct v4l2_clip	 *clips;
	uint32_t			clipcount;
	void			 *bitmap;
	uint8_t                    global_alpha;
};

/*
 *	C A P T U R E   P A R A M E T E R S
 */
struct v4l2_captureparm {
	uint32_t		   capability;	  /*  Supported modes */
	uint32_t		   capturemode;	  /*  Current mode */
	struct v4l2_fract  timeperframe;  /*  Time per frame in .1us units */
	uint32_t		   extendedmode;  /*  Driver-specific extensions */
	uint32_t              readbuffers;   /*  # of buffers for read */
	uint32_t		   reserved[4];
};

/*  Flags for 'capability' and 'capturemode' fields */
#define V4L2_MODE_HIGHQUALITY	0x0001	/*  High quality imaging mode */
#define V4L2_CAP_TIMEPERFRAME	0x1000	/*  timeperframe field is supported */

struct v4l2_outputparm {
	uint32_t		   capability;	 /*  Supported modes */
	uint32_t		   outputmode;	 /*  Current mode */
	struct v4l2_fract  timeperframe; /*  Time per frame in seconds */
	uint32_t		   extendedmode; /*  Driver-specific extensions */
	uint32_t              writebuffers; /*  # of buffers for write */
	uint32_t		   reserved[4];
};

/*
 *	I N P U T   I M A G E   C R O P P I N G
 */
struct v4l2_cropcap {
	uint32_t			type;	/* enum v4l2_buf_type */
	struct v4l2_rect        bounds;
	struct v4l2_rect        defrect;
	struct v4l2_fract       pixelaspect;
};

struct v4l2_crop {
	uint32_t			type;	/* enum v4l2_buf_type */
	struct v4l2_rect        c;
};

/* Hints for adjustments of selection rectangle */
#define V4L2_SEL_FLAG_GE	0x00000001
#define V4L2_SEL_FLAG_LE	0x00000002

/* Selection targets */

/* Current cropping area */
#define V4L2_SEL_TGT_CROP_ACTIVE	0x0000
/* Default cropping area */
#define V4L2_SEL_TGT_CROP_DEFAULT	0x0001
/* Cropping bounds */
#define V4L2_SEL_TGT_CROP_BOUNDS	0x0002
/* Current composing area */
#define V4L2_SEL_TGT_COMPOSE_ACTIVE	0x0100
/* Default composing area */
#define V4L2_SEL_TGT_COMPOSE_DEFAULT	0x0101
/* Composing bounds */
#define V4L2_SEL_TGT_COMPOSE_BOUNDS	0x0102
/* Current composing area plus all padding pixels */
#define V4L2_SEL_TGT_COMPOSE_PADDED	0x0103

/**
 * struct v4l2_selection - selection info
 * @type:	buffer type (do not use *_MPLANE types)
 * @target:	selection target, used to choose one of possible rectangles
 * @flags:	constraints flags
 * @r:		coordinates of selection window
 * @reserved:	for future use, rounds structure size to 64 bytes, set to zero
 *
 * Hardware may use multiple helper windows to process a video stream.
 * The structure is used to exchange this selection areas between
 * an application and a driver.
 */
struct v4l2_selection {
	uint32_t			type;
	uint32_t			target;
	uint32_t                   flags;
	struct v4l2_rect        r;
	uint32_t                   reserved[9];
};


/*
 *      A N A L O G   V I D E O   S T A N D A R D
 */

typedef uint64_t v4l2_std_id;

/* one bit for each */
#define V4L2_STD_PAL_B          ((v4l2_std_id)0x00000001)
#define V4L2_STD_PAL_B1         ((v4l2_std_id)0x00000002)
#define V4L2_STD_PAL_G          ((v4l2_std_id)0x00000004)
#define V4L2_STD_PAL_H          ((v4l2_std_id)0x00000008)
#define V4L2_STD_PAL_I          ((v4l2_std_id)0x00000010)
#define V4L2_STD_PAL_D          ((v4l2_std_id)0x00000020)
#define V4L2_STD_PAL_D1         ((v4l2_std_id)0x00000040)
#define V4L2_STD_PAL_K          ((v4l2_std_id)0x00000080)

#define V4L2_STD_PAL_M          ((v4l2_std_id)0x00000100)
#define V4L2_STD_PAL_N          ((v4l2_std_id)0x00000200)
#define V4L2_STD_PAL_Nc         ((v4l2_std_id)0x00000400)
#define V4L2_STD_PAL_60         ((v4l2_std_id)0x00000800)

#define V4L2_STD_NTSC_M         ((v4l2_std_id)0x00001000)	/* BTSC */
#define V4L2_STD_NTSC_M_JP      ((v4l2_std_id)0x00002000)	/* EIA-J */
#define V4L2_STD_NTSC_443       ((v4l2_std_id)0x00004000)
#define V4L2_STD_NTSC_M_KR      ((v4l2_std_id)0x00008000)	/* FM A2 */

#define V4L2_STD_SECAM_B        ((v4l2_std_id)0x00010000)
#define V4L2_STD_SECAM_D        ((v4l2_std_id)0x00020000)
#define V4L2_STD_SECAM_G        ((v4l2_std_id)0x00040000)
#define V4L2_STD_SECAM_H        ((v4l2_std_id)0x00080000)
#define V4L2_STD_SECAM_K        ((v4l2_std_id)0x00100000)
#define V4L2_STD_SECAM_K1       ((v4l2_std_id)0x00200000)
#define V4L2_STD_SECAM_L        ((v4l2_std_id)0x00400000)
#define V4L2_STD_SECAM_LC       ((v4l2_std_id)0x00800000)

/* ATSC/HDTV */
#define V4L2_STD_ATSC_8_VSB     ((v4l2_std_id)0x01000000)
#define V4L2_STD_ATSC_16_VSB    ((v4l2_std_id)0x02000000)

/* FIXME:
   Although std_id is 64 bits, there is an issue on PPC32 architecture that
   makes switch(uint64_t) to break. So, there's a hack on v4l2-common.c rounding
   this value to 32 bits.
   As, currently, the max value is for V4L2_STD_ATSC_16_VSB (30 bits wide),
   it should work fine. However, if needed to add more than two standards,
   v4l2-common.c should be fixed.
 */

/*
 * Some macros to merge video standards in order to make live easier for the
 * drivers and V4L2 applications
 */

/*
 * "Common" NTSC/M - It should be noticed that V4L2_STD_NTSC_443 is
 * Missing here.
 */
#define V4L2_STD_NTSC           (V4L2_STD_NTSC_M	|\
				 V4L2_STD_NTSC_M_JP     |\
				 V4L2_STD_NTSC_M_KR)
/* Secam macros */
#define V4L2_STD_SECAM_DK      	(V4L2_STD_SECAM_D	|\
				 V4L2_STD_SECAM_K	|\
				 V4L2_STD_SECAM_K1)
/* All Secam Standards */
#define V4L2_STD_SECAM		(V4L2_STD_SECAM_B	|\
				 V4L2_STD_SECAM_G	|\
				 V4L2_STD_SECAM_H	|\
				 V4L2_STD_SECAM_DK	|\
				 V4L2_STD_SECAM_L       |\
				 V4L2_STD_SECAM_LC)
/* PAL macros */
#define V4L2_STD_PAL_BG		(V4L2_STD_PAL_B		|\
				 V4L2_STD_PAL_B1	|\
				 V4L2_STD_PAL_G)
#define V4L2_STD_PAL_DK		(V4L2_STD_PAL_D		|\
				 V4L2_STD_PAL_D1	|\
				 V4L2_STD_PAL_K)
/*
 * "Common" PAL - This macro is there to be compatible with the old
 * V4L1 concept of "PAL": /BGDKHI.
 * Several PAL standards are mising here: /M, /N and /Nc
 */
#define V4L2_STD_PAL		(V4L2_STD_PAL_BG	|\
				 V4L2_STD_PAL_DK	|\
				 V4L2_STD_PAL_H		|\
				 V4L2_STD_PAL_I)
/* Chroma "agnostic" standards */
#define V4L2_STD_B		(V4L2_STD_PAL_B		|\
				 V4L2_STD_PAL_B1	|\
				 V4L2_STD_SECAM_B)
#define V4L2_STD_G		(V4L2_STD_PAL_G		|\
				 V4L2_STD_SECAM_G)
#define V4L2_STD_H		(V4L2_STD_PAL_H		|\
				 V4L2_STD_SECAM_H)
#define V4L2_STD_L		(V4L2_STD_SECAM_L	|\
				 V4L2_STD_SECAM_LC)
#define V4L2_STD_GH		(V4L2_STD_G		|\
				 V4L2_STD_H)
#define V4L2_STD_DK		(V4L2_STD_PAL_DK	|\
				 V4L2_STD_SECAM_DK)
#define V4L2_STD_BG		(V4L2_STD_B		|\
				 V4L2_STD_G)
#define V4L2_STD_MN		(V4L2_STD_PAL_M		|\
				 V4L2_STD_PAL_N		|\
				 V4L2_STD_PAL_Nc	|\
				 V4L2_STD_NTSC)

/* Standards where MTS/BTSC stereo could be found */
#define V4L2_STD_MTS		(V4L2_STD_NTSC_M	|\
				 V4L2_STD_PAL_M		|\
				 V4L2_STD_PAL_N		|\
				 V4L2_STD_PAL_Nc)

/* Standards for Countries with 60Hz Line frequency */
#define V4L2_STD_525_60		(V4L2_STD_PAL_M		|\
				 V4L2_STD_PAL_60	|\
				 V4L2_STD_NTSC		|\
				 V4L2_STD_NTSC_443)
/* Standards for Countries with 50Hz Line frequency */
#define V4L2_STD_625_50		(V4L2_STD_PAL		|\
				 V4L2_STD_PAL_N		|\
				 V4L2_STD_PAL_Nc	|\
				 V4L2_STD_SECAM)

#define V4L2_STD_ATSC           (V4L2_STD_ATSC_8_VSB    |\
				 V4L2_STD_ATSC_16_VSB)
/* Macros with none and all analog standards */
#define V4L2_STD_UNKNOWN        0
#define V4L2_STD_ALL            (V4L2_STD_525_60	|\
				 V4L2_STD_625_50)

struct v4l2_standard {
	uint32_t		     index;
	v4l2_std_id          id;
	uint8_t		     name[24];
	struct v4l2_fract    frameperiod; /* Frames, not fields */
	uint32_t		     framelines;
	uint32_t		     reserved[4];
};

/* The DV Preset API is deprecated in favor of the DV Timings API.
   New drivers shouldn't use this anymore! */

/*
 *	V I D E O	T I M I N G S	D V	P R E S E T
 */
struct v4l2_dv_preset {
	uint32_t	preset;
	uint32_t	reserved[4];
};

/*
 *	D V	P R E S E T S	E N U M E R A T I O N
 */
struct v4l2_dv_enum_preset {
	uint32_t	index;
	uint32_t	preset;
	uint8_t	name[32]; /* Name of the preset timing */
	uint32_t	width;
	uint32_t	height;
	uint32_t	reserved[4];
};

/*
 * 	D V	P R E S E T	V A L U E S
 */
#define		V4L2_DV_INVALID		0
#define		V4L2_DV_480P59_94	1 /* BT.1362 */
#define		V4L2_DV_576P50		2 /* BT.1362 */
#define		V4L2_DV_720P24		3 /* SMPTE 296M */
#define		V4L2_DV_720P25		4 /* SMPTE 296M */
#define		V4L2_DV_720P30		5 /* SMPTE 296M */
#define		V4L2_DV_720P50		6 /* SMPTE 296M */
#define		V4L2_DV_720P59_94	7 /* SMPTE 274M */
#define		V4L2_DV_720P60		8 /* SMPTE 274M/296M */
#define		V4L2_DV_1080I29_97	9 /* BT.1120/ SMPTE 274M */
#define		V4L2_DV_1080I30		10 /* BT.1120/ SMPTE 274M */
#define		V4L2_DV_1080I25		11 /* BT.1120 */
#define		V4L2_DV_1080I50		12 /* SMPTE 296M */
#define		V4L2_DV_1080I60		13 /* SMPTE 296M */
#define		V4L2_DV_1080P24		14 /* SMPTE 296M */
#define		V4L2_DV_1080P25		15 /* SMPTE 296M */
#define		V4L2_DV_1080P30		16 /* SMPTE 296M */
#define		V4L2_DV_1080P50		17 /* BT.1120 */
#define		V4L2_DV_1080P60		18 /* BT.1120 */

/*
 *	D V 	B T	T I M I N G S
 */

/** struct v4l2_bt_timings - BT.656/BT.1120 timing data
 * @width:	total width of the active video in pixels
 * @height:	total height of the active video in lines
 * @interlaced:	Interlaced or progressive
 * @polarities:	Positive or negative polarities
 * @pixelclock:	Pixel clock in HZ. Ex. 74.25MHz->74250000
 * @hfrontporch:Horizontal front porch in pixels
 * @hsync:	Horizontal Sync length in pixels
 * @hbackporch:	Horizontal back porch in pixels
 * @vfrontporch:Vertical front porch in lines
 * @vsync:	Vertical Sync length in lines
 * @vbackporch:	Vertical back porch in lines
 * @il_vfrontporch:Vertical front porch for the even field
 *		(aka field 2) of interlaced field formats
 * @il_vsync:	Vertical Sync length for the even field
 *		(aka field 2) of interlaced field formats
 * @il_vbackporch:Vertical back porch for the even field
 *		(aka field 2) of interlaced field formats
 * @standards:	Standards the timing belongs to
 * @flags:	Flags
 * @reserved:	Reserved fields, must be zeroed.
 *
 * A note regarding vertical interlaced timings: height refers to the total
 * height of the active video frame (= two fields). The blanking timings refer
 * to the blanking of each field. So the height of the total frame is
 * calculated as follows:
 *
 * tot_height = height + vfrontporch + vsync + vbackporch +
 *                       il_vfrontporch + il_vsync + il_vbackporch
 *
 * The active height of each field is height / 2.
 */
struct v4l2_bt_timings {
	uint32_t	width;
	uint32_t	height;
	uint32_t	interlaced;
	uint32_t	polarities;
	uint64_t	pixelclock;
	uint32_t	hfrontporch;
	uint32_t	hsync;
	uint32_t	hbackporch;
	uint32_t	vfrontporch;
	uint32_t	vsync;
	uint32_t	vbackporch;
	uint32_t	il_vfrontporch;
	uint32_t	il_vsync;
	uint32_t	il_vbackporch;
	uint32_t	standards;
	uint32_t	flags;
	uint32_t	reserved[14];
} __attribute__ ((packed));

/* Interlaced or progressive format */
#define	V4L2_DV_PROGRESSIVE	0
#define	V4L2_DV_INTERLACED	1

/* Polarities. If bit is not set, it is assumed to be negative polarity */
#define V4L2_DV_VSYNC_POS_POL	0x00000001
#define V4L2_DV_HSYNC_POS_POL	0x00000002

/* Timings standards */
#define V4L2_DV_BT_STD_CEA861	(1 << 0)  /* CEA-861 Digital TV Profile */
#define V4L2_DV_BT_STD_DMT	(1 << 1)  /* VESA Discrete Monitor Timings */
#define V4L2_DV_BT_STD_CVT	(1 << 2)  /* VESA Coordinated Video Timings */
#define V4L2_DV_BT_STD_GTF	(1 << 3)  /* VESA Generalized Timings Formula */

/* Flags */

/* CVT/GTF specific: timing uses reduced blanking (CVT) or the 'Secondary
   GTF' curve (GTF). In both cases the horizontal and/or vertical blanking
   intervals are reduced, allowing a higher resolution over the same
   bandwidth. This is a read-only flag. */
#define V4L2_DV_FL_REDUCED_BLANKING		(1 << 0)
/* CEA-861 specific: set for CEA-861 formats with a framerate of a multiple
   of six. These formats can be optionally played at 1 / 1.001 speed.
   This is a read-only flag. */
#define V4L2_DV_FL_CAN_REDUCE_FPS		(1 << 1)
/* CEA-861 specific: only valid for video transmitters, the flag is cleared
   by receivers.
   If the framerate of the format is a multiple of six, then the pixelclock
   used to set up the transmitter is divided by 1.001 to make it compatible
   with 60 Hz based standards such as NTSC and PAL-M that use a framerate of
   29.97 Hz. Otherwise this flag is cleared. If the transmitter can't generate
   such frequencies, then the flag will also be cleared. */
#define V4L2_DV_FL_REDUCED_FPS			(1 << 2)
/* Specific to interlaced formats: if set, then field 1 is really one half-line
   longer and field 2 is really one half-line shorter, so each field has
   exactly the same number of half-lines. Whether half-lines can be detected
   or used depends on the hardware. */
#define V4L2_DV_FL_HALF_LINE			(1 << 0)


/** struct v4l2_dv_timings - DV timings
 * @type:	the type of the timings
 * @bt:	BT656/1120 timings
 */
struct v4l2_dv_timings {
	uint32_t type;
	union {
		struct v4l2_bt_timings	bt;
		uint32_t	reserved[32];
	};
} __attribute__ ((packed));

/* Values for the type field */
#define V4L2_DV_BT_656_1120	0	/* BT.656/1120 timing type */


/** struct v4l2_enum_dv_timings - DV timings enumeration
 * @index:	enumeration index
 * @reserved:	must be zeroed
 * @timings:	the timings for the given index
 */
struct v4l2_enum_dv_timings {
	uint32_t index;
	uint32_t reserved[3];
	struct v4l2_dv_timings timings;
};

/** struct v4l2_bt_timings_cap - BT.656/BT.1120 timing capabilities
 * @min_width:		width in pixels
 * @max_width:		width in pixels
 * @min_height:		height in lines
 * @max_height:		height in lines
 * @min_pixelclock:	Pixel clock in HZ. Ex. 74.25MHz->74250000
 * @max_pixelclock:	Pixel clock in HZ. Ex. 74.25MHz->74250000
 * @standards:		Supported standards
 * @capabilities:	Supported capabilities
 * @reserved:		Must be zeroed
 */
struct v4l2_bt_timings_cap {
	uint32_t	min_width;
	uint32_t	max_width;
	uint32_t	min_height;
	uint32_t	max_height;
	uint64_t	min_pixelclock;
	uint64_t	max_pixelclock;
	uint32_t	standards;
	uint32_t	capabilities;
	uint32_t	reserved[16];
} __attribute__ ((packed));

/* Supports interlaced formats */
#define V4L2_DV_BT_CAP_INTERLACED	(1 << 0)
/* Supports progressive formats */
#define V4L2_DV_BT_CAP_PROGRESSIVE	(1 << 1)
/* Supports CVT/GTF reduced blanking */
#define V4L2_DV_BT_CAP_REDUCED_BLANKING	(1 << 2)
/* Supports custom formats */
#define V4L2_DV_BT_CAP_CUSTOM		(1 << 3)

/** struct v4l2_dv_timings_cap - DV timings capabilities
 * @type:	the type of the timings (same as in struct v4l2_dv_timings)
 * @bt:		the BT656/1120 timings capabilities
 */
struct v4l2_dv_timings_cap {
	uint32_t type;
	uint32_t reserved[3];
	union {
		struct v4l2_bt_timings_cap bt;
		uint32_t raw_data[32];
	};
};


/*
 *	V I D E O   I N P U T S
 */
struct v4l2_input {
	uint32_t	     index;		/*  Which input */
	uint8_t	     name[32];		/*  Label */
	uint32_t	     type;		/*  Type of input */
	uint32_t	     audioset;		/*  Associated audios (bitfield) */
	uint32_t        tuner;             /*  enum v4l2_tuner_type */
	v4l2_std_id  std;
	uint32_t	     status;
	uint32_t	     capabilities;
	uint32_t	     reserved[3];
};

/*  Values for the 'type' field */
#define V4L2_INPUT_TYPE_TUNER		1
#define V4L2_INPUT_TYPE_CAMERA		2

/* field 'status' - general */
#define V4L2_IN_ST_NO_POWER    0x00000001  /* Attached device is off */
#define V4L2_IN_ST_NO_SIGNAL   0x00000002
#define V4L2_IN_ST_NO_COLOR    0x00000004

/* field 'status' - sensor orientation */
/* If sensor is mounted upside down set both bits */
#define V4L2_IN_ST_HFLIP       0x00000010 /* Frames are flipped horizontally */
#define V4L2_IN_ST_VFLIP       0x00000020 /* Frames are flipped vertically */

/* field 'status' - analog */
#define V4L2_IN_ST_NO_H_LOCK   0x00000100  /* No horizontal sync lock */
#define V4L2_IN_ST_COLOR_KILL  0x00000200  /* Color killer is active */

/* field 'status' - digital */
#define V4L2_IN_ST_NO_SYNC     0x00010000  /* No synchronization lock */
#define V4L2_IN_ST_NO_EQU      0x00020000  /* No equalizer lock */
#define V4L2_IN_ST_NO_CARRIER  0x00040000  /* Carrier recovery failed */

/* field 'status' - VCR and set-top box */
#define V4L2_IN_ST_MACROVISION 0x01000000  /* Macrovision detected */
#define V4L2_IN_ST_NO_ACCESS   0x02000000  /* Conditional access denied */
#define V4L2_IN_ST_VTR         0x04000000  /* VTR time constant */

/* capabilities flags */
#define V4L2_IN_CAP_PRESETS		0x00000001 /* Supports S_DV_PRESET */
#define V4L2_IN_CAP_CUSTOM_TIMINGS	0x00000002 /* Supports S_DV_TIMINGS */
#define V4L2_IN_CAP_STD			0x00000004 /* Supports S_STD */

/*
 *	V I D E O   O U T P U T S
 */
struct v4l2_output {
	uint32_t	     index;		/*  Which output */
	uint8_t	     name[32];		/*  Label */
	uint32_t	     type;		/*  Type of output */
	uint32_t	     audioset;		/*  Associated audios (bitfield) */
	uint32_t	     modulator;         /*  Associated modulator */
	v4l2_std_id  std;
	uint32_t	     capabilities;
	uint32_t	     reserved[3];
};
/*  Values for the 'type' field */
#define V4L2_OUTPUT_TYPE_MODULATOR		1
#define V4L2_OUTPUT_TYPE_ANALOG			2
#define V4L2_OUTPUT_TYPE_ANALOGVGAOVERLAY	3

/* capabilities flags */
#define V4L2_OUT_CAP_PRESETS		0x00000001 /* Supports S_DV_PRESET */
#define V4L2_OUT_CAP_CUSTOM_TIMINGS	0x00000002 /* Supports S_DV_TIMINGS */
#define V4L2_OUT_CAP_STD		0x00000004 /* Supports S_STD */

/*
 *	C O N T R O L S
 */
struct v4l2_control {
	uint32_t		     id;
	int32_t		     value;
};

struct v4l2_ext_control {
	uint32_t id;
	uint32_t size;
	uint32_t reserved2[1];
	union {
		int32_t value;
		int64_t value64;
		char *string;
	};
} __attribute__ ((packed));

struct v4l2_ext_controls {
	uint32_t ctrl_class;
	uint32_t count;
	uint32_t error_idx;
	uint32_t reserved[2];
	struct v4l2_ext_control *controls;
};

/*  Values for ctrl_class field */
#define V4L2_CTRL_CLASS_USER 0x00980000	/* Old-style 'user' controls */
#define V4L2_CTRL_CLASS_MPEG 0x00990000	/* MPEG-compression controls */
#define V4L2_CTRL_CLASS_CAMERA 0x009a0000	/* Camera class controls */
#define V4L2_CTRL_CLASS_FM_TX 0x009b0000	/* FM Modulator control class */
#define V4L2_CTRL_CLASS_FLASH 0x009c0000	/* Camera flash controls */
#define V4L2_CTRL_CLASS_JPEG 0x009d0000		/* JPEG-compression controls */
#define V4L2_CTRL_CLASS_IMAGE_SOURCE 0x009e0000	/* Image source controls */
#define V4L2_CTRL_CLASS_IMAGE_PROC 0x009f0000	/* Image processing controls */

#define V4L2_CTRL_ID_MASK      	  (0x0fffffff)
#define V4L2_CTRL_ID2CLASS(id)    ((id) & 0x0fff0000UL)
#define V4L2_CTRL_DRIVER_PRIV(id) (((id) & 0xffff) >= 0x1000)

enum v4l2_ctrl_type {
	V4L2_CTRL_TYPE_INTEGER	     = 1,
	V4L2_CTRL_TYPE_BOOLEAN	     = 2,
	V4L2_CTRL_TYPE_MENU	     = 3,
	V4L2_CTRL_TYPE_BUTTON	     = 4,
	V4L2_CTRL_TYPE_INTEGER64     = 5,
	V4L2_CTRL_TYPE_CTRL_CLASS    = 6,
	V4L2_CTRL_TYPE_STRING        = 7,
	V4L2_CTRL_TYPE_BITMASK       = 8,
	V4L2_CTRL_TYPE_INTEGER_MENU = 9,
};

/*  Used in the VIDIOC_QUERYCTRL ioctl for querying controls */
struct v4l2_queryctrl {
	uint32_t		     id;
	uint32_t		     type;	/* enum v4l2_ctrl_type */
	uint8_t		     name[32];	/* Whatever */
	int32_t		     minimum;	/* Note signedness */
	int32_t		     maximum;
	int32_t		     step;
	int32_t		     default_value;
	uint32_t                flags;
	uint32_t		     reserved[2];
};

/*  Used in the VIDIOC_QUERYMENU ioctl for querying menu items */
struct v4l2_querymenu {
	uint32_t		id;
	uint32_t		index;
	union {
		uint8_t	name[32];	/* Whatever */
		int64_t	value;
	};
	uint32_t		reserved;
} __attribute__ ((packed));

/*  Control flags  */
#define V4L2_CTRL_FLAG_DISABLED		0x0001
#define V4L2_CTRL_FLAG_GRABBED		0x0002
#define V4L2_CTRL_FLAG_READ_ONLY 	0x0004
#define V4L2_CTRL_FLAG_UPDATE 		0x0008
#define V4L2_CTRL_FLAG_INACTIVE 	0x0010
#define V4L2_CTRL_FLAG_SLIDER 		0x0020
#define V4L2_CTRL_FLAG_WRITE_ONLY 	0x0040
#define V4L2_CTRL_FLAG_VOLATILE		0x0080

/*  Query flag, to be ORed with the control ID */
#define V4L2_CTRL_FLAG_NEXT_CTRL	0x80000000

/*  User-class control IDs defined by V4L2 */
#define V4L2_CID_MAX_CTRLS		1024
#define V4L2_CID_BASE			(V4L2_CTRL_CLASS_USER | 0x900)
#define V4L2_CID_USER_BASE 		V4L2_CID_BASE
/*  IDs reserved for driver specific controls */
#define V4L2_CID_PRIVATE_BASE		0x08000000

#define V4L2_CID_USER_CLASS 		(V4L2_CTRL_CLASS_USER | 1)
#define V4L2_CID_BRIGHTNESS		(V4L2_CID_BASE+0)
#define V4L2_CID_CONTRAST		(V4L2_CID_BASE+1)
#define V4L2_CID_SATURATION		(V4L2_CID_BASE+2)
#define V4L2_CID_HUE			(V4L2_CID_BASE+3)
#define V4L2_CID_AUDIO_VOLUME		(V4L2_CID_BASE+5)
#define V4L2_CID_AUDIO_BALANCE		(V4L2_CID_BASE+6)
#define V4L2_CID_AUDIO_BASS		(V4L2_CID_BASE+7)
#define V4L2_CID_AUDIO_TREBLE		(V4L2_CID_BASE+8)
#define V4L2_CID_AUDIO_MUTE		(V4L2_CID_BASE+9)
#define V4L2_CID_AUDIO_LOUDNESS		(V4L2_CID_BASE+10)
#define V4L2_CID_BLACK_LEVEL		(V4L2_CID_BASE+11) /* Deprecated */
#define V4L2_CID_AUTO_WHITE_BALANCE	(V4L2_CID_BASE+12)
#define V4L2_CID_DO_WHITE_BALANCE	(V4L2_CID_BASE+13)
#define V4L2_CID_RED_BALANCE		(V4L2_CID_BASE+14)
#define V4L2_CID_BLUE_BALANCE		(V4L2_CID_BASE+15)
#define V4L2_CID_GAMMA			(V4L2_CID_BASE+16)
#define V4L2_CID_WHITENESS		(V4L2_CID_GAMMA) /* Deprecated */
#define V4L2_CID_EXPOSURE		(V4L2_CID_BASE+17)
#define V4L2_CID_AUTOGAIN		(V4L2_CID_BASE+18)
#define V4L2_CID_GAIN			(V4L2_CID_BASE+19)
#define V4L2_CID_HFLIP			(V4L2_CID_BASE+20)
#define V4L2_CID_VFLIP			(V4L2_CID_BASE+21)

/* Deprecated; use V4L2_CID_PAN_RESET and V4L2_CID_TILT_RESET */
#define V4L2_CID_HCENTER		(V4L2_CID_BASE+22)
#define V4L2_CID_VCENTER		(V4L2_CID_BASE+23)

#define V4L2_CID_POWER_LINE_FREQUENCY	(V4L2_CID_BASE+24)
enum v4l2_power_line_frequency {
	V4L2_CID_POWER_LINE_FREQUENCY_DISABLED	= 0,
	V4L2_CID_POWER_LINE_FREQUENCY_50HZ	= 1,
	V4L2_CID_POWER_LINE_FREQUENCY_60HZ	= 2,
	V4L2_CID_POWER_LINE_FREQUENCY_AUTO	= 3,
};
#define V4L2_CID_HUE_AUTO			(V4L2_CID_BASE+25)
#define V4L2_CID_WHITE_BALANCE_TEMPERATURE	(V4L2_CID_BASE+26)
#define V4L2_CID_SHARPNESS			(V4L2_CID_BASE+27)
#define V4L2_CID_BACKLIGHT_COMPENSATION 	(V4L2_CID_BASE+28)
#define V4L2_CID_CHROMA_AGC                     (V4L2_CID_BASE+29)
#define V4L2_CID_COLOR_KILLER                   (V4L2_CID_BASE+30)
#define V4L2_CID_COLORFX			(V4L2_CID_BASE+31)
enum v4l2_colorfx {
	V4L2_COLORFX_NONE			= 0,
	V4L2_COLORFX_BW				= 1,
	V4L2_COLORFX_SEPIA			= 2,
	V4L2_COLORFX_NEGATIVE			= 3,
	V4L2_COLORFX_EMBOSS			= 4,
	V4L2_COLORFX_SKETCH			= 5,
	V4L2_COLORFX_SKY_BLUE			= 6,
	V4L2_COLORFX_GRASS_GREEN		= 7,
	V4L2_COLORFX_SKIN_WHITEN		= 8,
	V4L2_COLORFX_VIVID			= 9,
	V4L2_COLORFX_AQUA			= 10,
	V4L2_COLORFX_ART_FREEZE			= 11,
	V4L2_COLORFX_SILHOUETTE			= 12,
	V4L2_COLORFX_SOLARIZATION		= 13,
	V4L2_COLORFX_ANTIQUE			= 14,
	V4L2_COLORFX_SET_CBCR			= 15,
};
#define V4L2_CID_AUTOBRIGHTNESS			(V4L2_CID_BASE+32)
#define V4L2_CID_BAND_STOP_FILTER		(V4L2_CID_BASE+33)

#define V4L2_CID_ROTATE				(V4L2_CID_BASE+34)
#define V4L2_CID_BG_COLOR			(V4L2_CID_BASE+35)

#define V4L2_CID_CHROMA_GAIN                    (V4L2_CID_BASE+36)

#define V4L2_CID_ILLUMINATORS_1			(V4L2_CID_BASE+37)
#define V4L2_CID_ILLUMINATORS_2			(V4L2_CID_BASE+38)

#define V4L2_CID_MIN_BUFFERS_FOR_CAPTURE	(V4L2_CID_BASE+39)
#define V4L2_CID_MIN_BUFFERS_FOR_OUTPUT		(V4L2_CID_BASE+40)

#define V4L2_CID_ALPHA_COMPONENT		(V4L2_CID_BASE+41)
#define V4L2_CID_COLORFX_CBCR			(V4L2_CID_BASE+42)

/* last CID + 1 */
#define V4L2_CID_LASTP1                         (V4L2_CID_BASE+43)

/*  MPEG-class control IDs defined by V4L2 */
#define V4L2_CID_MPEG_BASE 			(V4L2_CTRL_CLASS_MPEG | 0x900)
#define V4L2_CID_MPEG_CLASS 			(V4L2_CTRL_CLASS_MPEG | 1)

/*  MPEG streams, specific to multiplexed streams */
#define V4L2_CID_MPEG_STREAM_TYPE 		(V4L2_CID_MPEG_BASE+0)
enum v4l2_mpeg_stream_type {
	V4L2_MPEG_STREAM_TYPE_MPEG2_PS   = 0, /* MPEG-2 program stream */
	V4L2_MPEG_STREAM_TYPE_MPEG2_TS   = 1, /* MPEG-2 transport stream */
	V4L2_MPEG_STREAM_TYPE_MPEG1_SS   = 2, /* MPEG-1 system stream */
	V4L2_MPEG_STREAM_TYPE_MPEG2_DVD  = 3, /* MPEG-2 DVD-compatible stream */
	V4L2_MPEG_STREAM_TYPE_MPEG1_VCD  = 4, /* MPEG-1 VCD-compatible stream */
	V4L2_MPEG_STREAM_TYPE_MPEG2_SVCD = 5, /* MPEG-2 SVCD-compatible stream */
};
#define V4L2_CID_MPEG_STREAM_PID_PMT 		(V4L2_CID_MPEG_BASE+1)
#define V4L2_CID_MPEG_STREAM_PID_AUDIO 		(V4L2_CID_MPEG_BASE+2)
#define V4L2_CID_MPEG_STREAM_PID_VIDEO 		(V4L2_CID_MPEG_BASE+3)
#define V4L2_CID_MPEG_STREAM_PID_PCR 		(V4L2_CID_MPEG_BASE+4)
#define V4L2_CID_MPEG_STREAM_PES_ID_AUDIO 	(V4L2_CID_MPEG_BASE+5)
#define V4L2_CID_MPEG_STREAM_PES_ID_VIDEO 	(V4L2_CID_MPEG_BASE+6)
#define V4L2_CID_MPEG_STREAM_VBI_FMT 		(V4L2_CID_MPEG_BASE+7)
enum v4l2_mpeg_stream_vbi_fmt {
	V4L2_MPEG_STREAM_VBI_FMT_NONE = 0,  /* No VBI in the MPEG stream */
	V4L2_MPEG_STREAM_VBI_FMT_IVTV = 1,  /* VBI in private packets, IVTV format */
};

/*  MPEG audio controls specific to multiplexed streams  */
#define V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ 	(V4L2_CID_MPEG_BASE+100)
enum v4l2_mpeg_audio_sampling_freq {
	V4L2_MPEG_AUDIO_SAMPLING_FREQ_44100 = 0,
	V4L2_MPEG_AUDIO_SAMPLING_FREQ_48000 = 1,
	V4L2_MPEG_AUDIO_SAMPLING_FREQ_32000 = 2,
};
#define V4L2_CID_MPEG_AUDIO_ENCODING 		(V4L2_CID_MPEG_BASE+101)
enum v4l2_mpeg_audio_encoding {
	V4L2_MPEG_AUDIO_ENCODING_LAYER_1 = 0,
	V4L2_MPEG_AUDIO_ENCODING_LAYER_2 = 1,
	V4L2_MPEG_AUDIO_ENCODING_LAYER_3 = 2,
	V4L2_MPEG_AUDIO_ENCODING_AAC     = 3,
	V4L2_MPEG_AUDIO_ENCODING_AC3     = 4,
};
#define V4L2_CID_MPEG_AUDIO_L1_BITRATE 		(V4L2_CID_MPEG_BASE+102)
enum v4l2_mpeg_audio_l1_bitrate {
	V4L2_MPEG_AUDIO_L1_BITRATE_32K  = 0,
	V4L2_MPEG_AUDIO_L1_BITRATE_64K  = 1,
	V4L2_MPEG_AUDIO_L1_BITRATE_96K  = 2,
	V4L2_MPEG_AUDIO_L1_BITRATE_128K = 3,
	V4L2_MPEG_AUDIO_L1_BITRATE_160K = 4,
	V4L2_MPEG_AUDIO_L1_BITRATE_192K = 5,
	V4L2_MPEG_AUDIO_L1_BITRATE_224K = 6,
	V4L2_MPEG_AUDIO_L1_BITRATE_256K = 7,
	V4L2_MPEG_AUDIO_L1_BITRATE_288K = 8,
	V4L2_MPEG_AUDIO_L1_BITRATE_320K = 9,
	V4L2_MPEG_AUDIO_L1_BITRATE_352K = 10,
	V4L2_MPEG_AUDIO_L1_BITRATE_384K = 11,
	V4L2_MPEG_AUDIO_L1_BITRATE_416K = 12,
	V4L2_MPEG_AUDIO_L1_BITRATE_448K = 13,
};
#define V4L2_CID_MPEG_AUDIO_L2_BITRATE 		(V4L2_CID_MPEG_BASE+103)
enum v4l2_mpeg_audio_l2_bitrate {
	V4L2_MPEG_AUDIO_L2_BITRATE_32K  = 0,
	V4L2_MPEG_AUDIO_L2_BITRATE_48K  = 1,
	V4L2_MPEG_AUDIO_L2_BITRATE_56K  = 2,
	V4L2_MPEG_AUDIO_L2_BITRATE_64K  = 3,
	V4L2_MPEG_AUDIO_L2_BITRATE_80K  = 4,
	V4L2_MPEG_AUDIO_L2_BITRATE_96K  = 5,
	V4L2_MPEG_AUDIO_L2_BITRATE_112K = 6,
	V4L2_MPEG_AUDIO_L2_BITRATE_128K = 7,
	V4L2_MPEG_AUDIO_L2_BITRATE_160K = 8,
	V4L2_MPEG_AUDIO_L2_BITRATE_192K = 9,
	V4L2_MPEG_AUDIO_L2_BITRATE_224K = 10,
	V4L2_MPEG_AUDIO_L2_BITRATE_256K = 11,
	V4L2_MPEG_AUDIO_L2_BITRATE_320K = 12,
	V4L2_MPEG_AUDIO_L2_BITRATE_384K = 13,
};
#define V4L2_CID_MPEG_AUDIO_L3_BITRATE 		(V4L2_CID_MPEG_BASE+104)
enum v4l2_mpeg_audio_l3_bitrate {
	V4L2_MPEG_AUDIO_L3_BITRATE_32K  = 0,
	V4L2_MPEG_AUDIO_L3_BITRATE_40K  = 1,
	V4L2_MPEG_AUDIO_L3_BITRATE_48K  = 2,
	V4L2_MPEG_AUDIO_L3_BITRATE_56K  = 3,
	V4L2_MPEG_AUDIO_L3_BITRATE_64K  = 4,
	V4L2_MPEG_AUDIO_L3_BITRATE_80K  = 5,
	V4L2_MPEG_AUDIO_L3_BITRATE_96K  = 6,
	V4L2_MPEG_AUDIO_L3_BITRATE_112K = 7,
	V4L2_MPEG_AUDIO_L3_BITRATE_128K = 8,
	V4L2_MPEG_AUDIO_L3_BITRATE_160K = 9,
	V4L2_MPEG_AUDIO_L3_BITRATE_192K = 10,
	V4L2_MPEG_AUDIO_L3_BITRATE_224K = 11,
	V4L2_MPEG_AUDIO_L3_BITRATE_256K = 12,
	V4L2_MPEG_AUDIO_L3_BITRATE_320K = 13,
};
#define V4L2_CID_MPEG_AUDIO_MODE 		(V4L2_CID_MPEG_BASE+105)
enum v4l2_mpeg_audio_mode {
	V4L2_MPEG_AUDIO_MODE_STEREO       = 0,
	V4L2_MPEG_AUDIO_MODE_JOINT_STEREO = 1,
	V4L2_MPEG_AUDIO_MODE_DUAL         = 2,
	V4L2_MPEG_AUDIO_MODE_MONO         = 3,
};
#define V4L2_CID_MPEG_AUDIO_MODE_EXTENSION 	(V4L2_CID_MPEG_BASE+106)
enum v4l2_mpeg_audio_mode_extension {
	V4L2_MPEG_AUDIO_MODE_EXTENSION_BOUND_4  = 0,
	V4L2_MPEG_AUDIO_MODE_EXTENSION_BOUND_8  = 1,
	V4L2_MPEG_AUDIO_MODE_EXTENSION_BOUND_12 = 2,
	V4L2_MPEG_AUDIO_MODE_EXTENSION_BOUND_16 = 3,
};
#define V4L2_CID_MPEG_AUDIO_EMPHASIS 		(V4L2_CID_MPEG_BASE+107)
enum v4l2_mpeg_audio_emphasis {
	V4L2_MPEG_AUDIO_EMPHASIS_NONE         = 0,
	V4L2_MPEG_AUDIO_EMPHASIS_50_DIV_15_uS = 1,
	V4L2_MPEG_AUDIO_EMPHASIS_CCITT_J17    = 2,
};
#define V4L2_CID_MPEG_AUDIO_CRC 		(V4L2_CID_MPEG_BASE+108)
enum v4l2_mpeg_audio_crc {
	V4L2_MPEG_AUDIO_CRC_NONE  = 0,
	V4L2_MPEG_AUDIO_CRC_CRC16 = 1,
};
#define V4L2_CID_MPEG_AUDIO_MUTE 		(V4L2_CID_MPEG_BASE+109)
#define V4L2_CID_MPEG_AUDIO_AAC_BITRATE		(V4L2_CID_MPEG_BASE+110)
#define V4L2_CID_MPEG_AUDIO_AC3_BITRATE		(V4L2_CID_MPEG_BASE+111)
enum v4l2_mpeg_audio_ac3_bitrate {
	V4L2_MPEG_AUDIO_AC3_BITRATE_32K  = 0,
	V4L2_MPEG_AUDIO_AC3_BITRATE_40K  = 1,
	V4L2_MPEG_AUDIO_AC3_BITRATE_48K  = 2,
	V4L2_MPEG_AUDIO_AC3_BITRATE_56K  = 3,
	V4L2_MPEG_AUDIO_AC3_BITRATE_64K  = 4,
	V4L2_MPEG_AUDIO_AC3_BITRATE_80K  = 5,
	V4L2_MPEG_AUDIO_AC3_BITRATE_96K  = 6,
	V4L2_MPEG_AUDIO_AC3_BITRATE_112K = 7,
	V4L2_MPEG_AUDIO_AC3_BITRATE_128K = 8,
	V4L2_MPEG_AUDIO_AC3_BITRATE_160K = 9,
	V4L2_MPEG_AUDIO_AC3_BITRATE_192K = 10,
	V4L2_MPEG_AUDIO_AC3_BITRATE_224K = 11,
	V4L2_MPEG_AUDIO_AC3_BITRATE_256K = 12,
	V4L2_MPEG_AUDIO_AC3_BITRATE_320K = 13,
	V4L2_MPEG_AUDIO_AC3_BITRATE_384K = 14,
	V4L2_MPEG_AUDIO_AC3_BITRATE_448K = 15,
	V4L2_MPEG_AUDIO_AC3_BITRATE_512K = 16,
	V4L2_MPEG_AUDIO_AC3_BITRATE_576K = 17,
	V4L2_MPEG_AUDIO_AC3_BITRATE_640K = 18,
};
#define V4L2_CID_MPEG_AUDIO_DEC_PLAYBACK	(V4L2_CID_MPEG_BASE+112)
enum v4l2_mpeg_audio_dec_playback {
	V4L2_MPEG_AUDIO_DEC_PLAYBACK_AUTO	    = 0,
	V4L2_MPEG_AUDIO_DEC_PLAYBACK_STEREO	    = 1,
	V4L2_MPEG_AUDIO_DEC_PLAYBACK_LEFT	    = 2,
	V4L2_MPEG_AUDIO_DEC_PLAYBACK_RIGHT	    = 3,
	V4L2_MPEG_AUDIO_DEC_PLAYBACK_MONO	    = 4,
	V4L2_MPEG_AUDIO_DEC_PLAYBACK_SWAPPED_STEREO = 5,
};
#define V4L2_CID_MPEG_AUDIO_DEC_MULTILINGUAL_PLAYBACK (V4L2_CID_MPEG_BASE+113)

/*  MPEG video controls specific to multiplexed streams */
#define V4L2_CID_MPEG_VIDEO_ENCODING 		(V4L2_CID_MPEG_BASE+200)
enum v4l2_mpeg_video_encoding {
	V4L2_MPEG_VIDEO_ENCODING_MPEG_1     = 0,
	V4L2_MPEG_VIDEO_ENCODING_MPEG_2     = 1,
	V4L2_MPEG_VIDEO_ENCODING_MPEG_4_AVC = 2,
};
#define V4L2_CID_MPEG_VIDEO_ASPECT 		(V4L2_CID_MPEG_BASE+201)
enum v4l2_mpeg_video_aspect {
	V4L2_MPEG_VIDEO_ASPECT_1x1     = 0,
	V4L2_MPEG_VIDEO_ASPECT_4x3     = 1,
	V4L2_MPEG_VIDEO_ASPECT_16x9    = 2,
	V4L2_MPEG_VIDEO_ASPECT_221x100 = 3,
};
#define V4L2_CID_MPEG_VIDEO_B_FRAMES 		(V4L2_CID_MPEG_BASE+202)
#define V4L2_CID_MPEG_VIDEO_GOP_SIZE 		(V4L2_CID_MPEG_BASE+203)
#define V4L2_CID_MPEG_VIDEO_GOP_CLOSURE 	(V4L2_CID_MPEG_BASE+204)
#define V4L2_CID_MPEG_VIDEO_PULLDOWN 		(V4L2_CID_MPEG_BASE+205)
#define V4L2_CID_MPEG_VIDEO_BITRATE_MODE 	(V4L2_CID_MPEG_BASE+206)
enum v4l2_mpeg_video_bitrate_mode {
	V4L2_MPEG_VIDEO_BITRATE_MODE_VBR = 0,
	V4L2_MPEG_VIDEO_BITRATE_MODE_CBR = 1,
};
#define V4L2_CID_MPEG_VIDEO_BITRATE 		(V4L2_CID_MPEG_BASE+207)
#define V4L2_CID_MPEG_VIDEO_BITRATE_PEAK 	(V4L2_CID_MPEG_BASE+208)
#define V4L2_CID_MPEG_VIDEO_TEMPORAL_DECIMATION (V4L2_CID_MPEG_BASE+209)
#define V4L2_CID_MPEG_VIDEO_MUTE 		(V4L2_CID_MPEG_BASE+210)
#define V4L2_CID_MPEG_VIDEO_MUTE_YUV 		(V4L2_CID_MPEG_BASE+211)
#define V4L2_CID_MPEG_VIDEO_DECODER_SLICE_INTERFACE		(V4L2_CID_MPEG_BASE+212)
#define V4L2_CID_MPEG_VIDEO_DECODER_MPEG4_DEBLOCK_FILTER	(V4L2_CID_MPEG_BASE+213)
#define V4L2_CID_MPEG_VIDEO_CYCLIC_INTRA_REFRESH_MB		(V4L2_CID_MPEG_BASE+214)
#define V4L2_CID_MPEG_VIDEO_FRAME_RC_ENABLE			(V4L2_CID_MPEG_BASE+215)
#define V4L2_CID_MPEG_VIDEO_HEADER_MODE				(V4L2_CID_MPEG_BASE+216)
enum v4l2_mpeg_video_header_mode {
	V4L2_MPEG_VIDEO_HEADER_MODE_SEPARATE			= 0,
	V4L2_MPEG_VIDEO_HEADER_MODE_JOINED_WITH_1ST_FRAME	= 1,

};
#define V4L2_CID_MPEG_VIDEO_MAX_REF_PIC			(V4L2_CID_MPEG_BASE+217)
#define V4L2_CID_MPEG_VIDEO_MB_RC_ENABLE		(V4L2_CID_MPEG_BASE+218)
#define V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_BYTES	(V4L2_CID_MPEG_BASE+219)
#define V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_MB		(V4L2_CID_MPEG_BASE+220)
#define V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MODE		(V4L2_CID_MPEG_BASE+221)
enum v4l2_mpeg_video_multi_slice_mode {
	V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_SINGLE		= 0,
	V4L2_MPEG_VIDEO_MULTI_SICE_MODE_MAX_MB		= 1,
	V4L2_MPEG_VIDEO_MULTI_SICE_MODE_MAX_BYTES	= 2,
};
#define V4L2_CID_MPEG_VIDEO_VBV_SIZE			(V4L2_CID_MPEG_BASE+222)
#define V4L2_CID_MPEG_VIDEO_DEC_PTS			(V4L2_CID_MPEG_BASE+223)
#define V4L2_CID_MPEG_VIDEO_DEC_FRAME			(V4L2_CID_MPEG_BASE+224)

#define V4L2_CID_MPEG_VIDEO_H263_I_FRAME_QP		(V4L2_CID_MPEG_BASE+300)
#define V4L2_CID_MPEG_VIDEO_H263_P_FRAME_QP		(V4L2_CID_MPEG_BASE+301)
#define V4L2_CID_MPEG_VIDEO_H263_B_FRAME_QP		(V4L2_CID_MPEG_BASE+302)
#define V4L2_CID_MPEG_VIDEO_H263_MIN_QP			(V4L2_CID_MPEG_BASE+303)
#define V4L2_CID_MPEG_VIDEO_H263_MAX_QP			(V4L2_CID_MPEG_BASE+304)
#define V4L2_CID_MPEG_VIDEO_H264_I_FRAME_QP		(V4L2_CID_MPEG_BASE+350)
#define V4L2_CID_MPEG_VIDEO_H264_P_FRAME_QP		(V4L2_CID_MPEG_BASE+351)
#define V4L2_CID_MPEG_VIDEO_H264_B_FRAME_QP		(V4L2_CID_MPEG_BASE+352)
#define V4L2_CID_MPEG_VIDEO_H264_MIN_QP			(V4L2_CID_MPEG_BASE+353)
#define V4L2_CID_MPEG_VIDEO_H264_MAX_QP			(V4L2_CID_MPEG_BASE+354)
#define V4L2_CID_MPEG_VIDEO_H264_8X8_TRANSFORM		(V4L2_CID_MPEG_BASE+355)
#define V4L2_CID_MPEG_VIDEO_H264_CPB_SIZE		(V4L2_CID_MPEG_BASE+356)
#define V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE		(V4L2_CID_MPEG_BASE+357)
enum v4l2_mpeg_video_h264_entropy_mode {
	V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CAVLC	= 0,
	V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CABAC	= 1,
};
#define V4L2_CID_MPEG_VIDEO_H264_I_PERIOD		(V4L2_CID_MPEG_BASE+358)
#define V4L2_CID_MPEG_VIDEO_H264_LEVEL			(V4L2_CID_MPEG_BASE+359)
enum v4l2_mpeg_video_h264_level {
	V4L2_MPEG_VIDEO_H264_LEVEL_1_0	= 0,
	V4L2_MPEG_VIDEO_H264_LEVEL_1B	= 1,
	V4L2_MPEG_VIDEO_H264_LEVEL_1_1	= 2,
	V4L2_MPEG_VIDEO_H264_LEVEL_1_2	= 3,
	V4L2_MPEG_VIDEO_H264_LEVEL_1_3	= 4,
	V4L2_MPEG_VIDEO_H264_LEVEL_2_0	= 5,
	V4L2_MPEG_VIDEO_H264_LEVEL_2_1	= 6,
	V4L2_MPEG_VIDEO_H264_LEVEL_2_2	= 7,
	V4L2_MPEG_VIDEO_H264_LEVEL_3_0	= 8,
	V4L2_MPEG_VIDEO_H264_LEVEL_3_1	= 9,
	V4L2_MPEG_VIDEO_H264_LEVEL_3_2	= 10,
	V4L2_MPEG_VIDEO_H264_LEVEL_4_0	= 11,
	V4L2_MPEG_VIDEO_H264_LEVEL_4_1	= 12,
	V4L2_MPEG_VIDEO_H264_LEVEL_4_2	= 13,
	V4L2_MPEG_VIDEO_H264_LEVEL_5_0	= 14,
	V4L2_MPEG_VIDEO_H264_LEVEL_5_1	= 15,
};
#define V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_ALPHA	(V4L2_CID_MPEG_BASE+360)
#define V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_BETA	(V4L2_CID_MPEG_BASE+361)
#define V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE	(V4L2_CID_MPEG_BASE+362)
enum v4l2_mpeg_video_h264_loop_filter_mode {
	V4L2_MPEG_VIDEO_H264_LOOP_FILTER_MODE_ENABLED				= 0,
	V4L2_MPEG_VIDEO_H264_LOOP_FILTER_MODE_DISABLED				= 1,
	V4L2_MPEG_VIDEO_H264_LOOP_FILTER_MODE_DISABLED_AT_SLICE_BOUNDARY	= 2,
};
#define V4L2_CID_MPEG_VIDEO_H264_PROFILE		(V4L2_CID_MPEG_BASE+363)
enum v4l2_mpeg_video_h264_profile {
	V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE			= 0,
	V4L2_MPEG_VIDEO_H264_PROFILE_CONSTRAINED_BASELINE	= 1,
	V4L2_MPEG_VIDEO_H264_PROFILE_MAIN			= 2,
	V4L2_MPEG_VIDEO_H264_PROFILE_EXTENDED			= 3,
	V4L2_MPEG_VIDEO_H264_PROFILE_HIGH			= 4,
	V4L2_MPEG_VIDEO_H264_PROFILE_HIGH_10			= 5,
	V4L2_MPEG_VIDEO_H264_PROFILE_HIGH_422			= 6,
	V4L2_MPEG_VIDEO_H264_PROFILE_HIGH_444_PREDICTIVE	= 7,
	V4L2_MPEG_VIDEO_H264_PROFILE_HIGH_10_INTRA		= 8,
	V4L2_MPEG_VIDEO_H264_PROFILE_HIGH_422_INTRA		= 9,
	V4L2_MPEG_VIDEO_H264_PROFILE_HIGH_444_INTRA		= 10,
	V4L2_MPEG_VIDEO_H264_PROFILE_CAVLC_444_INTRA		= 11,
	V4L2_MPEG_VIDEO_H264_PROFILE_SCALABLE_BASELINE		= 12,
	V4L2_MPEG_VIDEO_H264_PROFILE_SCALABLE_HIGH		= 13,
	V4L2_MPEG_VIDEO_H264_PROFILE_SCALABLE_HIGH_INTRA	= 14,
	V4L2_MPEG_VIDEO_H264_PROFILE_STEREO_HIGH		= 15,
	V4L2_MPEG_VIDEO_H264_PROFILE_MULTIVIEW_HIGH		= 16,
};
#define V4L2_CID_MPEG_VIDEO_H264_VUI_EXT_SAR_HEIGHT	(V4L2_CID_MPEG_BASE+364)
#define V4L2_CID_MPEG_VIDEO_H264_VUI_EXT_SAR_WIDTH	(V4L2_CID_MPEG_BASE+365)
#define V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_ENABLE		(V4L2_CID_MPEG_BASE+366)
#define V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_IDC		(V4L2_CID_MPEG_BASE+367)
enum v4l2_mpeg_video_h264_vui_sar_idc {
	V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_UNSPECIFIED	= 0,
	V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_1x1		= 1,
	V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_12x11		= 2,
	V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_10x11		= 3,
	V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_16x11		= 4,
	V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_40x33		= 5,
	V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_24x11		= 6,
	V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_20x11		= 7,
	V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_32x11		= 8,
	V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_80x33		= 9,
	V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_18x11		= 10,
	V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_15x11		= 11,
	V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_64x33		= 12,
	V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_160x99		= 13,
	V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_4x3		= 14,
	V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_3x2		= 15,
	V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_2x1		= 16,
	V4L2_MPEG_VIDEO_H264_VUI_SAR_IDC_EXTENDED	= 17,
};
#define V4L2_CID_MPEG_VIDEO_MPEG4_I_FRAME_QP	(V4L2_CID_MPEG_BASE+400)
#define V4L2_CID_MPEG_VIDEO_MPEG4_P_FRAME_QP	(V4L2_CID_MPEG_BASE+401)
#define V4L2_CID_MPEG_VIDEO_MPEG4_B_FRAME_QP	(V4L2_CID_MPEG_BASE+402)
#define V4L2_CID_MPEG_VIDEO_MPEG4_MIN_QP	(V4L2_CID_MPEG_BASE+403)
#define V4L2_CID_MPEG_VIDEO_MPEG4_MAX_QP	(V4L2_CID_MPEG_BASE+404)
#define V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL		(V4L2_CID_MPEG_BASE+405)
enum v4l2_mpeg_video_mpeg4_level {
	V4L2_MPEG_VIDEO_MPEG4_LEVEL_0	= 0,
	V4L2_MPEG_VIDEO_MPEG4_LEVEL_0B	= 1,
	V4L2_MPEG_VIDEO_MPEG4_LEVEL_1	= 2,
	V4L2_MPEG_VIDEO_MPEG4_LEVEL_2	= 3,
	V4L2_MPEG_VIDEO_MPEG4_LEVEL_3	= 4,
	V4L2_MPEG_VIDEO_MPEG4_LEVEL_3B	= 5,
	V4L2_MPEG_VIDEO_MPEG4_LEVEL_4	= 6,
	V4L2_MPEG_VIDEO_MPEG4_LEVEL_5	= 7,
};
#define V4L2_CID_MPEG_VIDEO_MPEG4_PROFILE	(V4L2_CID_MPEG_BASE+406)
enum v4l2_mpeg_video_mpeg4_profile {
	V4L2_MPEG_VIDEO_MPEG4_PROFILE_SIMPLE				= 0,
	V4L2_MPEG_VIDEO_MPEG4_PROFILE_ADVANCED_SIMPLE			= 1,
	V4L2_MPEG_VIDEO_MPEG4_PROFILE_CORE				= 2,
	V4L2_MPEG_VIDEO_MPEG4_PROFILE_SIMPLE_SCALABLE			= 3,
	V4L2_MPEG_VIDEO_MPEG4_PROFILE_ADVANCED_CODING_EFFICIENCY	= 4,
};
#define V4L2_CID_MPEG_VIDEO_MPEG4_QPEL		(V4L2_CID_MPEG_BASE+407)

/*  MPEG-class control IDs specific to the CX2341x driver as defined by V4L2 */
#define V4L2_CID_MPEG_CX2341X_BASE 				(V4L2_CTRL_CLASS_MPEG | 0x1000)
#define V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE 	(V4L2_CID_MPEG_CX2341X_BASE+0)
enum v4l2_mpeg_cx2341x_video_spatial_filter_mode {
	V4L2_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE_MANUAL = 0,
	V4L2_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE_AUTO   = 1,
};
#define V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER 		(V4L2_CID_MPEG_CX2341X_BASE+1)
#define V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE 	(V4L2_CID_MPEG_CX2341X_BASE+2)
enum v4l2_mpeg_cx2341x_video_luma_spatial_filter_type {
	V4L2_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE_OFF                  = 0,
	V4L2_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE_1D_HOR               = 1,
	V4L2_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE_1D_VERT              = 2,
	V4L2_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE_2D_HV_SEPARABLE      = 3,
	V4L2_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE_2D_SYM_NON_SEPARABLE = 4,
};
#define V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE 	(V4L2_CID_MPEG_CX2341X_BASE+3)
enum v4l2_mpeg_cx2341x_video_chroma_spatial_filter_type {
	V4L2_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE_OFF    = 0,
	V4L2_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE_1D_HOR = 1,
};
#define V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE 	(V4L2_CID_MPEG_CX2341X_BASE+4)
enum v4l2_mpeg_cx2341x_video_temporal_filter_mode {
	V4L2_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE_MANUAL = 0,
	V4L2_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE_AUTO   = 1,
};
#define V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER 		(V4L2_CID_MPEG_CX2341X_BASE+5)
#define V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE 		(V4L2_CID_MPEG_CX2341X_BASE+6)
enum v4l2_mpeg_cx2341x_video_median_filter_type {
	V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_OFF      = 0,
	V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_HOR      = 1,
	V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_VERT     = 2,
	V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_HOR_VERT = 3,
	V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_DIAG     = 4,
};
#define V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_BOTTOM 	(V4L2_CID_MPEG_CX2341X_BASE+7)
#define V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP 	(V4L2_CID_MPEG_CX2341X_BASE+8)
#define V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_BOTTOM	(V4L2_CID_MPEG_CX2341X_BASE+9)
#define V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_TOP 	(V4L2_CID_MPEG_CX2341X_BASE+10)
#define V4L2_CID_MPEG_CX2341X_STREAM_INSERT_NAV_PACKETS 	(V4L2_CID_MPEG_CX2341X_BASE+11)

/*  MPEG-class control IDs specific to the Samsung MFC 5.1 driver as defined by V4L2 */
#define V4L2_CID_MPEG_MFC51_BASE				(V4L2_CTRL_CLASS_MPEG | 0x1100)

#define V4L2_CID_MPEG_MFC51_VIDEO_DECODER_H264_DISPLAY_DELAY		(V4L2_CID_MPEG_MFC51_BASE+0)
#define V4L2_CID_MPEG_MFC51_VIDEO_DECODER_H264_DISPLAY_DELAY_ENABLE	(V4L2_CID_MPEG_MFC51_BASE+1)
#define V4L2_CID_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE			(V4L2_CID_MPEG_MFC51_BASE+2)
enum v4l2_mpeg_mfc51_video_frame_skip_mode {
	V4L2_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE_DISABLED		= 0,
	V4L2_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE_LEVEL_LIMIT	= 1,
	V4L2_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE_BUF_LIMIT		= 2,
};
#define V4L2_CID_MPEG_MFC51_VIDEO_FORCE_FRAME_TYPE			(V4L2_CID_MPEG_MFC51_BASE+3)
enum v4l2_mpeg_mfc51_video_force_frame_type {
	V4L2_MPEG_MFC51_VIDEO_FORCE_FRAME_TYPE_DISABLED		= 0,
	V4L2_MPEG_MFC51_VIDEO_FORCE_FRAME_TYPE_I_FRAME		= 1,
	V4L2_MPEG_MFC51_VIDEO_FORCE_FRAME_TYPE_NOT_CODED	= 2,
};
#define V4L2_CID_MPEG_MFC51_VIDEO_PADDING				(V4L2_CID_MPEG_MFC51_BASE+4)
#define V4L2_CID_MPEG_MFC51_VIDEO_PADDING_YUV				(V4L2_CID_MPEG_MFC51_BASE+5)
#define V4L2_CID_MPEG_MFC51_VIDEO_RC_FIXED_TARGET_BIT			(V4L2_CID_MPEG_MFC51_BASE+6)
#define V4L2_CID_MPEG_MFC51_VIDEO_RC_REACTION_COEFF			(V4L2_CID_MPEG_MFC51_BASE+7)
#define V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_ACTIVITY		(V4L2_CID_MPEG_MFC51_BASE+50)
#define V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_DARK			(V4L2_CID_MPEG_MFC51_BASE+51)
#define V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_SMOOTH		(V4L2_CID_MPEG_MFC51_BASE+52)
#define V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_STATIC		(V4L2_CID_MPEG_MFC51_BASE+53)
#define V4L2_CID_MPEG_MFC51_VIDEO_H264_NUM_REF_PIC_FOR_P		(V4L2_CID_MPEG_MFC51_BASE+54)

/*  Camera class control IDs */
#define V4L2_CID_CAMERA_CLASS_BASE 	(V4L2_CTRL_CLASS_CAMERA | 0x900)
#define V4L2_CID_CAMERA_CLASS 		(V4L2_CTRL_CLASS_CAMERA | 1)

#define V4L2_CID_EXPOSURE_AUTO			(V4L2_CID_CAMERA_CLASS_BASE+1)
enum  v4l2_exposure_auto_type {
	V4L2_EXPOSURE_AUTO = 0,
	V4L2_EXPOSURE_MANUAL = 1,
	V4L2_EXPOSURE_SHUTTER_PRIORITY = 2,
	V4L2_EXPOSURE_APERTURE_PRIORITY = 3
};
#define V4L2_CID_EXPOSURE_ABSOLUTE		(V4L2_CID_CAMERA_CLASS_BASE+2)
#define V4L2_CID_EXPOSURE_AUTO_PRIORITY		(V4L2_CID_CAMERA_CLASS_BASE+3)

#define V4L2_CID_PAN_RELATIVE			(V4L2_CID_CAMERA_CLASS_BASE+4)
#define V4L2_CID_TILT_RELATIVE			(V4L2_CID_CAMERA_CLASS_BASE+5)
#define V4L2_CID_PAN_RESET			(V4L2_CID_CAMERA_CLASS_BASE+6)
#define V4L2_CID_TILT_RESET			(V4L2_CID_CAMERA_CLASS_BASE+7)

#define V4L2_CID_PAN_ABSOLUTE			(V4L2_CID_CAMERA_CLASS_BASE+8)
#define V4L2_CID_TILT_ABSOLUTE			(V4L2_CID_CAMERA_CLASS_BASE+9)

#define V4L2_CID_FOCUS_ABSOLUTE			(V4L2_CID_CAMERA_CLASS_BASE+10)
#define V4L2_CID_FOCUS_RELATIVE			(V4L2_CID_CAMERA_CLASS_BASE+11)
#define V4L2_CID_FOCUS_AUTO			(V4L2_CID_CAMERA_CLASS_BASE+12)

#define V4L2_CID_ZOOM_ABSOLUTE			(V4L2_CID_CAMERA_CLASS_BASE+13)
#define V4L2_CID_ZOOM_RELATIVE			(V4L2_CID_CAMERA_CLASS_BASE+14)
#define V4L2_CID_ZOOM_CONTINUOUS		(V4L2_CID_CAMERA_CLASS_BASE+15)

#define V4L2_CID_PRIVACY			(V4L2_CID_CAMERA_CLASS_BASE+16)

#define V4L2_CID_IRIS_ABSOLUTE			(V4L2_CID_CAMERA_CLASS_BASE+17)
#define V4L2_CID_IRIS_RELATIVE			(V4L2_CID_CAMERA_CLASS_BASE+18)

#define V4L2_CID_AUTO_EXPOSURE_BIAS		(V4L2_CID_CAMERA_CLASS_BASE+19)

#define V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE	(V4L2_CID_CAMERA_CLASS_BASE+20)
enum v4l2_auto_n_preset_white_balance {
	V4L2_WHITE_BALANCE_MANUAL		= 0,
	V4L2_WHITE_BALANCE_AUTO			= 1,
	V4L2_WHITE_BALANCE_INCANDESCENT		= 2,
	V4L2_WHITE_BALANCE_FLUORESCENT		= 3,
	V4L2_WHITE_BALANCE_FLUORESCENT_H	= 4,
	V4L2_WHITE_BALANCE_HORIZON		= 5,
	V4L2_WHITE_BALANCE_DAYLIGHT		= 6,
	V4L2_WHITE_BALANCE_FLASH		= 7,
	V4L2_WHITE_BALANCE_CLOUDY		= 8,
	V4L2_WHITE_BALANCE_SHADE		= 9,
};

#define V4L2_CID_WIDE_DYNAMIC_RANGE		(V4L2_CID_CAMERA_CLASS_BASE+21)
#define V4L2_CID_IMAGE_STABILIZATION		(V4L2_CID_CAMERA_CLASS_BASE+22)

#define V4L2_CID_ISO_SENSITIVITY		(V4L2_CID_CAMERA_CLASS_BASE+23)
#define V4L2_CID_ISO_SENSITIVITY_AUTO		(V4L2_CID_CAMERA_CLASS_BASE+24)
enum v4l2_iso_sensitivity_auto_type {
	V4L2_ISO_SENSITIVITY_MANUAL		= 0,
	V4L2_ISO_SENSITIVITY_AUTO		= 1,
};

#define V4L2_CID_EXPOSURE_METERING		(V4L2_CID_CAMERA_CLASS_BASE+25)
enum v4l2_exposure_metering {
	V4L2_EXPOSURE_METERING_AVERAGE		= 0,
	V4L2_EXPOSURE_METERING_CENTER_WEIGHTED	= 1,
	V4L2_EXPOSURE_METERING_SPOT		= 2,
};

#define V4L2_CID_SCENE_MODE			(V4L2_CID_CAMERA_CLASS_BASE+26)
enum v4l2_scene_mode {
	V4L2_SCENE_MODE_NONE			= 0,
	V4L2_SCENE_MODE_BACKLIGHT		= 1,
	V4L2_SCENE_MODE_BEACH_SNOW		= 2,
	V4L2_SCENE_MODE_CANDLE_LIGHT		= 3,
	V4L2_SCENE_MODE_DAWN_DUSK		= 4,
	V4L2_SCENE_MODE_FALL_COLORS		= 5,
	V4L2_SCENE_MODE_FIREWORKS		= 6,
	V4L2_SCENE_MODE_LANDSCAPE		= 7,
	V4L2_SCENE_MODE_NIGHT			= 8,
	V4L2_SCENE_MODE_PARTY_INDOOR		= 9,
	V4L2_SCENE_MODE_PORTRAIT		= 10,
	V4L2_SCENE_MODE_SPORTS			= 11,
	V4L2_SCENE_MODE_SUNSET			= 12,
	V4L2_SCENE_MODE_TEXT			= 13,
};

#define V4L2_CID_3A_LOCK			(V4L2_CID_CAMERA_CLASS_BASE+27)
#define V4L2_LOCK_EXPOSURE			(1 << 0)
#define V4L2_LOCK_WHITE_BALANCE			(1 << 1)
#define V4L2_LOCK_FOCUS				(1 << 2)

#define V4L2_CID_AUTO_FOCUS_START		(V4L2_CID_CAMERA_CLASS_BASE+28)
#define V4L2_CID_AUTO_FOCUS_STOP		(V4L2_CID_CAMERA_CLASS_BASE+29)
#define V4L2_CID_AUTO_FOCUS_STATUS		(V4L2_CID_CAMERA_CLASS_BASE+30)
#define V4L2_AUTO_FOCUS_STATUS_IDLE		(0 << 0)
#define V4L2_AUTO_FOCUS_STATUS_BUSY		(1 << 0)
#define V4L2_AUTO_FOCUS_STATUS_REACHED		(1 << 1)
#define V4L2_AUTO_FOCUS_STATUS_FAILED		(1 << 2)

#define V4L2_CID_AUTO_FOCUS_RANGE		(V4L2_CID_CAMERA_CLASS_BASE+31)
enum v4l2_auto_focus_range {
	V4L2_AUTO_FOCUS_RANGE_AUTO		= 0,
	V4L2_AUTO_FOCUS_RANGE_NORMAL		= 1,
	V4L2_AUTO_FOCUS_RANGE_MACRO		= 2,
	V4L2_AUTO_FOCUS_RANGE_INFINITY		= 3,
};

/* FM Modulator class control IDs */
#define V4L2_CID_FM_TX_CLASS_BASE		(V4L2_CTRL_CLASS_FM_TX | 0x900)
#define V4L2_CID_FM_TX_CLASS			(V4L2_CTRL_CLASS_FM_TX | 1)

#define V4L2_CID_RDS_TX_DEVIATION		(V4L2_CID_FM_TX_CLASS_BASE + 1)
#define V4L2_CID_RDS_TX_PI			(V4L2_CID_FM_TX_CLASS_BASE + 2)
#define V4L2_CID_RDS_TX_PTY			(V4L2_CID_FM_TX_CLASS_BASE + 3)
#define V4L2_CID_RDS_TX_PS_NAME			(V4L2_CID_FM_TX_CLASS_BASE + 5)
#define V4L2_CID_RDS_TX_RADIO_TEXT		(V4L2_CID_FM_TX_CLASS_BASE + 6)

#define V4L2_CID_AUDIO_LIMITER_ENABLED		(V4L2_CID_FM_TX_CLASS_BASE + 64)
#define V4L2_CID_AUDIO_LIMITER_RELEASE_TIME	(V4L2_CID_FM_TX_CLASS_BASE + 65)
#define V4L2_CID_AUDIO_LIMITER_DEVIATION	(V4L2_CID_FM_TX_CLASS_BASE + 66)

#define V4L2_CID_AUDIO_COMPRESSION_ENABLED	(V4L2_CID_FM_TX_CLASS_BASE + 80)
#define V4L2_CID_AUDIO_COMPRESSION_GAIN		(V4L2_CID_FM_TX_CLASS_BASE + 81)
#define V4L2_CID_AUDIO_COMPRESSION_THRESHOLD	(V4L2_CID_FM_TX_CLASS_BASE + 82)
#define V4L2_CID_AUDIO_COMPRESSION_ATTACK_TIME	(V4L2_CID_FM_TX_CLASS_BASE + 83)
#define V4L2_CID_AUDIO_COMPRESSION_RELEASE_TIME	(V4L2_CID_FM_TX_CLASS_BASE + 84)

#define V4L2_CID_PILOT_TONE_ENABLED		(V4L2_CID_FM_TX_CLASS_BASE + 96)
#define V4L2_CID_PILOT_TONE_DEVIATION		(V4L2_CID_FM_TX_CLASS_BASE + 97)
#define V4L2_CID_PILOT_TONE_FREQUENCY		(V4L2_CID_FM_TX_CLASS_BASE + 98)

#define V4L2_CID_TUNE_PREEMPHASIS		(V4L2_CID_FM_TX_CLASS_BASE + 112)
enum v4l2_preemphasis {
	V4L2_PREEMPHASIS_DISABLED	= 0,
	V4L2_PREEMPHASIS_50_uS		= 1,
	V4L2_PREEMPHASIS_75_uS		= 2,
};
#define V4L2_CID_TUNE_POWER_LEVEL		(V4L2_CID_FM_TX_CLASS_BASE + 113)
#define V4L2_CID_TUNE_ANTENNA_CAPACITOR		(V4L2_CID_FM_TX_CLASS_BASE + 114)

/* Flash and privacy (indicator) light controls */
#define V4L2_CID_FLASH_CLASS_BASE		(V4L2_CTRL_CLASS_FLASH | 0x900)
#define V4L2_CID_FLASH_CLASS			(V4L2_CTRL_CLASS_FLASH | 1)

#define V4L2_CID_FLASH_LED_MODE			(V4L2_CID_FLASH_CLASS_BASE + 1)
enum v4l2_flash_led_mode {
	V4L2_FLASH_LED_MODE_NONE,
	V4L2_FLASH_LED_MODE_FLASH,
	V4L2_FLASH_LED_MODE_TORCH,
};

#define V4L2_CID_FLASH_STROBE_SOURCE		(V4L2_CID_FLASH_CLASS_BASE + 2)
enum v4l2_flash_strobe_source {
	V4L2_FLASH_STROBE_SOURCE_SOFTWARE,
	V4L2_FLASH_STROBE_SOURCE_EXTERNAL,
};

#define V4L2_CID_FLASH_STROBE			(V4L2_CID_FLASH_CLASS_BASE + 3)
#define V4L2_CID_FLASH_STROBE_STOP		(V4L2_CID_FLASH_CLASS_BASE + 4)
#define V4L2_CID_FLASH_STROBE_STATUS		(V4L2_CID_FLASH_CLASS_BASE + 5)

#define V4L2_CID_FLASH_TIMEOUT			(V4L2_CID_FLASH_CLASS_BASE + 6)
#define V4L2_CID_FLASH_INTENSITY		(V4L2_CID_FLASH_CLASS_BASE + 7)
#define V4L2_CID_FLASH_TORCH_INTENSITY		(V4L2_CID_FLASH_CLASS_BASE + 8)
#define V4L2_CID_FLASH_INDICATOR_INTENSITY	(V4L2_CID_FLASH_CLASS_BASE + 9)

#define V4L2_CID_FLASH_FAULT			(V4L2_CID_FLASH_CLASS_BASE + 10)
#define V4L2_FLASH_FAULT_OVER_VOLTAGE		(1 << 0)
#define V4L2_FLASH_FAULT_TIMEOUT		(1 << 1)
#define V4L2_FLASH_FAULT_OVER_TEMPERATURE	(1 << 2)
#define V4L2_FLASH_FAULT_SHORT_CIRCUIT		(1 << 3)
#define V4L2_FLASH_FAULT_OVER_CURRENT		(1 << 4)
#define V4L2_FLASH_FAULT_INDICATOR		(1 << 5)

#define V4L2_CID_FLASH_CHARGE			(V4L2_CID_FLASH_CLASS_BASE + 11)
#define V4L2_CID_FLASH_READY			(V4L2_CID_FLASH_CLASS_BASE + 12)

/*  JPEG-class control IDs defined by V4L2 */
#define V4L2_CID_JPEG_CLASS_BASE		(V4L2_CTRL_CLASS_JPEG | 0x900)
#define V4L2_CID_JPEG_CLASS			(V4L2_CTRL_CLASS_JPEG | 1)

#define	V4L2_CID_JPEG_CHROMA_SUBSAMPLING	(V4L2_CID_JPEG_CLASS_BASE + 1)
enum v4l2_jpeg_chroma_subsampling {
	V4L2_JPEG_CHROMA_SUBSAMPLING_444	= 0,
	V4L2_JPEG_CHROMA_SUBSAMPLING_422	= 1,
	V4L2_JPEG_CHROMA_SUBSAMPLING_420	= 2,
	V4L2_JPEG_CHROMA_SUBSAMPLING_411	= 3,
	V4L2_JPEG_CHROMA_SUBSAMPLING_410	= 4,
	V4L2_JPEG_CHROMA_SUBSAMPLING_GRAY	= 5,
};
#define	V4L2_CID_JPEG_RESTART_INTERVAL		(V4L2_CID_JPEG_CLASS_BASE + 2)
#define	V4L2_CID_JPEG_COMPRESSION_QUALITY	(V4L2_CID_JPEG_CLASS_BASE + 3)

#define	V4L2_CID_JPEG_ACTIVE_MARKER		(V4L2_CID_JPEG_CLASS_BASE + 4)
#define	V4L2_JPEG_ACTIVE_MARKER_APP0		(1 << 0)
#define	V4L2_JPEG_ACTIVE_MARKER_APP1		(1 << 1)
#define	V4L2_JPEG_ACTIVE_MARKER_COM		(1 << 16)
#define	V4L2_JPEG_ACTIVE_MARKER_DQT		(1 << 17)
#define	V4L2_JPEG_ACTIVE_MARKER_DHT		(1 << 18)

/* Image source controls */
#define V4L2_CID_IMAGE_SOURCE_CLASS_BASE	(V4L2_CTRL_CLASS_IMAGE_SOURCE | 0x900)
#define V4L2_CID_IMAGE_SOURCE_CLASS		(V4L2_CTRL_CLASS_IMAGE_SOURCE | 1)

#define V4L2_CID_VBLANK				(V4L2_CID_IMAGE_SOURCE_CLASS_BASE + 1)
#define V4L2_CID_HBLANK				(V4L2_CID_IMAGE_SOURCE_CLASS_BASE + 2)
#define V4L2_CID_ANALOGUE_GAIN			(V4L2_CID_IMAGE_SOURCE_CLASS_BASE + 3)

/* Image processing controls */
#define V4L2_CID_IMAGE_PROC_CLASS_BASE		(V4L2_CTRL_CLASS_IMAGE_PROC | 0x900)
#define V4L2_CID_IMAGE_PROC_CLASS		(V4L2_CTRL_CLASS_IMAGE_PROC | 1)

#define V4L2_CID_LINK_FREQ			(V4L2_CID_IMAGE_PROC_CLASS_BASE + 1)
#define V4L2_CID_PIXEL_RATE			(V4L2_CID_IMAGE_PROC_CLASS_BASE + 2)

/*
 *	T U N I N G
 */
struct v4l2_tuner {
	uint32_t                   index;
	uint8_t			name[32];
	uint32_t			type;	/* enum v4l2_tuner_type */
	uint32_t			capability;
	uint32_t			rangelow;
	uint32_t			rangehigh;
	uint32_t			rxsubchans;
	uint32_t			audmode;
	int32_t			signal;
	int32_t			afc;
	uint32_t			band;
	uint32_t			reserved[3];
};

struct v4l2_modulator {
	uint32_t			index;
	uint8_t			name[32];
	uint32_t			capability;
	uint32_t			rangelow;
	uint32_t			rangehigh;
	uint32_t			txsubchans;
	uint32_t			band;
	uint32_t			reserved[3];
};

/*  Flags for the 'capability' field */
#define V4L2_TUNER_CAP_LOW		0x0001
#define V4L2_TUNER_CAP_NORM		0x0002
#define V4L2_TUNER_CAP_HWSEEK_BOUNDED	0x0004
#define V4L2_TUNER_CAP_HWSEEK_WRAP	0x0008
#define V4L2_TUNER_CAP_STEREO		0x0010
#define V4L2_TUNER_CAP_LANG2		0x0020
#define V4L2_TUNER_CAP_SAP		0x0020
#define V4L2_TUNER_CAP_LANG1		0x0040
#define V4L2_TUNER_CAP_RDS		0x0080
#define V4L2_TUNER_CAP_RDS_BLOCK_IO	0x0100
#define V4L2_TUNER_CAP_RDS_CONTROLS	0x0200
#define V4L2_TUNER_CAP_BAND_FM_EUROPE_US     0x00010000
#define V4L2_TUNER_CAP_BAND_FM_JAPAN         0x00020000
#define V4L2_TUNER_CAP_BAND_FM_RUSSIAN       0x00040000
#define V4L2_TUNER_CAP_BAND_FM_WEATHER       0x00080000
#define V4L2_TUNER_CAP_BAND_AM_MW            0x00100000
#define V4L2_TUNER_CAP_BANDS_MASK            0x001f0000

/*  Flags for the 'rxsubchans' field */
#define V4L2_TUNER_SUB_MONO		0x0001
#define V4L2_TUNER_SUB_STEREO		0x0002
#define V4L2_TUNER_SUB_LANG2		0x0004
#define V4L2_TUNER_SUB_SAP		0x0004
#define V4L2_TUNER_SUB_LANG1		0x0008
#define V4L2_TUNER_SUB_RDS		0x0010

/*  Values for the 'audmode' field */
#define V4L2_TUNER_MODE_MONO		0x0000
#define V4L2_TUNER_MODE_STEREO		0x0001
#define V4L2_TUNER_MODE_LANG2		0x0002
#define V4L2_TUNER_MODE_SAP		0x0002
#define V4L2_TUNER_MODE_LANG1		0x0003
#define V4L2_TUNER_MODE_LANG1_LANG2	0x0004

/*  Values for the 'band' field */
#define V4L2_TUNER_BAND_DEFAULT       0
#define V4L2_TUNER_BAND_FM_EUROPE_US  1       /* 87.5 Mhz - 108 MHz */
#define V4L2_TUNER_BAND_FM_JAPAN      2       /* 76 MHz - 90 MHz */
#define V4L2_TUNER_BAND_FM_RUSSIAN    3       /* 65.8 MHz - 74 MHz */
#define V4L2_TUNER_BAND_FM_WEATHER    4       /* 162.4 MHz - 162.55 MHz */
#define V4L2_TUNER_BAND_AM_MW         5

struct v4l2_frequency {
	uint32_t		      tuner;
	uint32_t		      type;	/* enum v4l2_tuner_type */
	uint32_t		      frequency;
	uint32_t		      reserved[8];
};

struct v4l2_hw_freq_seek {
	uint32_t		      tuner;
	uint32_t		      type;	/* enum v4l2_tuner_type */
	uint32_t		      seek_upward;
	uint32_t		      wrap_around;
	uint32_t		      spacing;
	uint32_t		      reserved[7];
};

/*
 *	R D S
 */

struct v4l2_rds_data {
	uint8_t 	lsb;
	uint8_t 	msb;
	uint8_t 	block;
} __attribute__ ((packed));

#define V4L2_RDS_BLOCK_MSK 	 0x7
#define V4L2_RDS_BLOCK_A 	 0
#define V4L2_RDS_BLOCK_B 	 1
#define V4L2_RDS_BLOCK_C 	 2
#define V4L2_RDS_BLOCK_D 	 3
#define V4L2_RDS_BLOCK_C_ALT 	 4
#define V4L2_RDS_BLOCK_INVALID 	 7

#define V4L2_RDS_BLOCK_CORRECTED 0x40
#define V4L2_RDS_BLOCK_ERROR 	 0x80

/*
 *	A U D I O
 */
struct v4l2_audio {
	uint32_t	index;
	uint8_t	name[32];
	uint32_t	capability;
	uint32_t	mode;
	uint32_t	reserved[2];
};

/*  Flags for the 'capability' field */
#define V4L2_AUDCAP_STEREO		0x00001
#define V4L2_AUDCAP_AVL			0x00002

/*  Flags for the 'mode' field */
#define V4L2_AUDMODE_AVL		0x00001

struct v4l2_audioout {
	uint32_t	index;
	uint8_t	name[32];
	uint32_t	capability;
	uint32_t	mode;
	uint32_t	reserved[2];
};

/*
 *	M P E G   S E R V I C E S
 *
 *	NOTE: EXPERIMENTAL API
 */
#if 1
#define V4L2_ENC_IDX_FRAME_I    (0)
#define V4L2_ENC_IDX_FRAME_P    (1)
#define V4L2_ENC_IDX_FRAME_B    (2)
#define V4L2_ENC_IDX_FRAME_MASK (0xf)

struct v4l2_enc_idx_entry {
	uint64_t offset;
	uint64_t pts;
	uint32_t length;
	uint32_t flags;
	uint32_t reserved[2];
};

#define V4L2_ENC_IDX_ENTRIES (64)
struct v4l2_enc_idx {
	uint32_t entries;
	uint32_t entries_cap;
	uint32_t reserved[4];
	struct v4l2_enc_idx_entry entry[V4L2_ENC_IDX_ENTRIES];
};


#define V4L2_ENC_CMD_START      (0)
#define V4L2_ENC_CMD_STOP       (1)
#define V4L2_ENC_CMD_PAUSE      (2)
#define V4L2_ENC_CMD_RESUME     (3)

/* Flags for V4L2_ENC_CMD_STOP */
#define V4L2_ENC_CMD_STOP_AT_GOP_END    (1 << 0)

struct v4l2_encoder_cmd {
	uint32_t cmd;
	uint32_t flags;
	union {
		struct {
			uint32_t data[8];
		} raw;
	};
};

/* Decoder commands */
#define V4L2_DEC_CMD_START       (0)
#define V4L2_DEC_CMD_STOP        (1)
#define V4L2_DEC_CMD_PAUSE       (2)
#define V4L2_DEC_CMD_RESUME      (3)

/* Flags for V4L2_DEC_CMD_START */
#define V4L2_DEC_CMD_START_MUTE_AUDIO	(1 << 0)

/* Flags for V4L2_DEC_CMD_PAUSE */
#define V4L2_DEC_CMD_PAUSE_TO_BLACK	(1 << 0)

/* Flags for V4L2_DEC_CMD_STOP */
#define V4L2_DEC_CMD_STOP_TO_BLACK	(1 << 0)
#define V4L2_DEC_CMD_STOP_IMMEDIATELY	(1 << 1)

/* Play format requirements (returned by the driver): */

/* The decoder has no special format requirements */
#define V4L2_DEC_START_FMT_NONE		(0)
/* The decoder requires full GOPs */
#define V4L2_DEC_START_FMT_GOP		(1)

/* The structure must be zeroed before use by the application
   This ensures it can be extended safely in the future. */
struct v4l2_decoder_cmd {
	uint32_t cmd;
	uint32_t flags;
	union {
		struct {
			uint64_t pts;
		} stop;

		struct {
			/* 0 or 1000 specifies normal speed,
			   1 specifies forward single stepping,
			   -1 specifies backward single stepping,
			   >1: playback at speed/1000 of the normal speed,
			   <-1: reverse playback at (-speed/1000) of the normal speed. */
			int32_t speed;
			uint32_t format;
		} start;

		struct {
			uint32_t data[16];
		} raw;
	};
};
#endif


/*
 *	D A T A   S E R V I C E S   ( V B I )
 *
 *	Data services API by Michael Schimek
 */

/* Raw VBI */
struct v4l2_vbi_format {
	uint32_t	sampling_rate;		/* in 1 Hz */
	uint32_t	offset;
	uint32_t	samples_per_line;
	uint32_t	sample_format;		/* V4L2_PIX_FMT_* */
	int32_t	start[2];
	uint32_t	count[2];
	uint32_t	flags;			/* V4L2_VBI_* */
	uint32_t	reserved[2];		/* must be zero */
};

/*  VBI flags  */
#define V4L2_VBI_UNSYNC		(1 << 0)
#define V4L2_VBI_INTERLACED	(1 << 1)

/* Sliced VBI
 *
 *    This implements is a proposal V4L2 API to allow SLICED VBI
 * required for some hardware encoders. It should change without
 * notice in the definitive implementation.
 */

struct v4l2_sliced_vbi_format {
	uint16_t   service_set;
	/* service_lines[0][...] specifies lines 0-23 (1-23 used) of the first field
	   service_lines[1][...] specifies lines 0-23 (1-23 used) of the second field
				 (equals frame lines 313-336 for 625 line video
				  standards, 263-286 for 525 line standards) */
	uint16_t   service_lines[2][24];
	uint32_t   io_size;
	uint32_t   reserved[2];            /* must be zero */
};

/* Teletext World System Teletext
   (WST), defined on ITU-R BT.653-2 */
#define V4L2_SLICED_TELETEXT_B          (0x0001)
/* Video Program System, defined on ETS 300 231*/
#define V4L2_SLICED_VPS                 (0x0400)
/* Closed Caption, defined on EIA-608 */
#define V4L2_SLICED_CAPTION_525         (0x1000)
/* Wide Screen System, defined on ITU-R BT1119.1 */
#define V4L2_SLICED_WSS_625             (0x4000)

#define V4L2_SLICED_VBI_525             (V4L2_SLICED_CAPTION_525)
#define V4L2_SLICED_VBI_625             (V4L2_SLICED_TELETEXT_B | V4L2_SLICED_VPS | V4L2_SLICED_WSS_625)

struct v4l2_sliced_vbi_cap {
	uint16_t   service_set;
	/* service_lines[0][...] specifies lines 0-23 (1-23 used) of the first field
	   service_lines[1][...] specifies lines 0-23 (1-23 used) of the second field
				 (equals frame lines 313-336 for 625 line video
				  standards, 263-286 for 525 line standards) */
	uint16_t   service_lines[2][24];
	uint32_t	type;		/* enum v4l2_buf_type */
	uint32_t   reserved[3];    /* must be 0 */
};

struct v4l2_sliced_vbi_data {
	uint32_t   id;
	uint32_t   field;          /* 0: first field, 1: second field */
	uint32_t   line;           /* 1-23 */
	uint32_t   reserved;       /* must be 0 */
	uint8_t    data[48];
};

/*
 * Sliced VBI data inserted into MPEG Streams
 */

/*
 * V4L2_MPEG_STREAM_VBI_FMT_IVTV:
 *
 * Structure of payload contained in an MPEG 2 Private Stream 1 PES Packet in an
 * MPEG-2 Program Pack that contains V4L2_MPEG_STREAM_VBI_FMT_IVTV Sliced VBI
 * data
 *
 * Note, the MPEG-2 Program Pack and Private Stream 1 PES packet header
 * definitions are not included here.  See the MPEG-2 specifications for details
 * on these headers.
 */

/* Line type IDs */
#define V4L2_MPEG_VBI_IVTV_TELETEXT_B     (1)
#define V4L2_MPEG_VBI_IVTV_CAPTION_525    (4)
#define V4L2_MPEG_VBI_IVTV_WSS_625        (5)
#define V4L2_MPEG_VBI_IVTV_VPS            (7)

struct v4l2_mpeg_vbi_itv0_line {
	uint8_t id;	/* One of V4L2_MPEG_VBI_IVTV_* above */
	uint8_t data[42];	/* Sliced VBI data for the line */
} __attribute__ ((packed));

struct v4l2_mpeg_vbi_itv0 {
	uint32_t linemask[2]; /* Bitmasks of VBI service lines present */
	struct v4l2_mpeg_vbi_itv0_line line[35];
} __attribute__ ((packed));

struct v4l2_mpeg_vbi_ITV0 {
	struct v4l2_mpeg_vbi_itv0_line line[36];
} __attribute__ ((packed));

#define V4L2_MPEG_VBI_IVTV_MAGIC0	"itv0"
#define V4L2_MPEG_VBI_IVTV_MAGIC1	"ITV0"

struct v4l2_mpeg_vbi_fmt_ivtv {
	uint8_t magic[4];
	union {
		struct v4l2_mpeg_vbi_itv0 itv0;
		struct v4l2_mpeg_vbi_ITV0 ITV0;
	};
} __attribute__ ((packed));

/*
 *	A G G R E G A T E   S T R U C T U R E S
 */

/**
 * struct v4l2_plane_pix_format - additional, per-plane format definition
 * @sizeimage:		maximum size in bytes required for data, for which
 *			this plane will be used
 * @bytesperline:	distance in bytes between the leftmost pixels in two
 *			adjacent lines
 */
struct v4l2_plane_pix_format {
	uint32_t		sizeimage;
	uint16_t		bytesperline;
	uint16_t		reserved[7];
} __attribute__ ((packed));

/**
 * struct v4l2_pix_format_mplane - multiplanar format definition
 * @width:		image width in pixels
 * @height:		image height in pixels
 * @pixelformat:	little endian four character code (fourcc)
 * @field:		enum v4l2_field; field order (for interlaced video)
 * @colorspace:		enum v4l2_colorspace; supplemental to pixelformat
 * @plane_fmt:		per-plane information
 * @num_planes:		number of planes for this format
 */
struct v4l2_pix_format_mplane {
	uint32_t				width;
	uint32_t				height;
	uint32_t				pixelformat;
	uint32_t				field;
	uint32_t				colorspace;

	struct v4l2_plane_pix_format	plane_fmt[VIDEO_MAX_PLANES];
	uint8_t				num_planes;
	uint8_t				reserved[11];
} __attribute__ ((packed));

/**
 * struct v4l2_format - stream data format
 * @type:	enum v4l2_buf_type; type of the data stream
 * @pix:	definition of an image format
 * @pix_mp:	definition of a multiplanar image format
 * @win:	definition of an overlaid image
 * @vbi:	raw VBI capture or output parameters
 * @sliced:	sliced VBI capture or output parameters
 * @raw_data:	placeholder for future extensions and custom formats
 */
struct v4l2_format {
	uint32_t	 type;
	union {
		struct v4l2_pix_format		pix;     /* V4L2_BUF_TYPE_VIDEO_CAPTURE */
		struct v4l2_pix_format_mplane	pix_mp;  /* V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE */
		struct v4l2_window		win;     /* V4L2_BUF_TYPE_VIDEO_OVERLAY */
		struct v4l2_vbi_format		vbi;     /* V4L2_BUF_TYPE_VBI_CAPTURE */
		struct v4l2_sliced_vbi_format	sliced;  /* V4L2_BUF_TYPE_SLICED_VBI_CAPTURE */
		uint8_t	raw_data[200];                   /* user-defined */
	} fmt;
};

/*	Stream type-dependent parameters
 */
struct v4l2_streamparm {
	uint32_t	 type;			/* enum v4l2_buf_type */
	union {
		struct v4l2_captureparm	capture;
		struct v4l2_outputparm	output;
		uint8_t	raw_data[200];  /* user-defined */
	} parm;
};

/*
 *	E V E N T S
 */

#define V4L2_EVENT_ALL				0
#define V4L2_EVENT_VSYNC			1
#define V4L2_EVENT_EOS				2
#define V4L2_EVENT_CTRL				3
#define V4L2_EVENT_FRAME_SYNC			4
#define V4L2_EVENT_PRIVATE_START		0x08000000

/* Payload for V4L2_EVENT_VSYNC */
struct v4l2_event_vsync {
	/* Can be V4L2_FIELD_ANY, _NONE, _TOP or _BOTTOM */
	uint8_t field;
} __attribute__ ((packed));

/* Payload for V4L2_EVENT_CTRL */
#define V4L2_EVENT_CTRL_CH_VALUE		(1 << 0)
#define V4L2_EVENT_CTRL_CH_FLAGS		(1 << 1)

struct v4l2_event_ctrl {
	uint32_t changes;
	uint32_t type;
	union {
		int32_t value;
		int64_t value64;
	};
	uint32_t flags;
	int32_t minimum;
	int32_t maximum;
	int32_t step;
	int32_t default_value;
};

struct v4l2_event_frame_sync {
	uint32_t frame_sequence;
};

struct v4l2_event {
	uint32_t				type;
	union {
		struct v4l2_event_vsync		vsync;
		struct v4l2_event_ctrl		ctrl;
		struct v4l2_event_frame_sync	frame_sync;
		uint8_t				data[64];
	} u;
	uint32_t				pending;
	uint32_t				sequence;
	struct timespec			timestamp;
	uint32_t				id;
	uint32_t				reserved[8];
};

#define V4L2_EVENT_SUB_FL_SEND_INITIAL		(1 << 0)
#define V4L2_EVENT_SUB_FL_ALLOW_FEEDBACK	(1 << 1)

struct v4l2_event_subscription {
	uint32_t				type;
	uint32_t				id;
	uint32_t				flags;
	uint32_t				reserved[5];
};

/*
 *	A D V A N C E D   D E B U G G I N G
 *
 *	NOTE: EXPERIMENTAL API, NEVER RELY ON THIS IN APPLICATIONS!
 *	FOR DEBUGGING, TESTING AND INTERNAL USE ONLY!
 */

/* VIDIOC_DBG_G_REGISTER and VIDIOC_DBG_S_REGISTER */

#define V4L2_CHIP_MATCH_HOST       0  /* Match against chip ID on host (0 for the host) */
#define V4L2_CHIP_MATCH_I2C_DRIVER 1  /* Match against I2C driver name */
#define V4L2_CHIP_MATCH_I2C_ADDR   2  /* Match against I2C 7-bit address */
#define V4L2_CHIP_MATCH_AC97       3  /* Match against anciliary AC97 chip */

struct v4l2_dbg_match {
	uint32_t type; /* Match type */
	union {     /* Match this chip, meaning determined by type */
		uint32_t addr;
		char name[32];
	};
} __attribute__ ((packed));

struct v4l2_dbg_register {
	struct v4l2_dbg_match match;
	uint32_t size;	/* register size in bytes */
	uint64_t reg;
	uint64_t val;
} __attribute__ ((packed));

/* VIDIOC_DBG_G_CHIP_IDENT */
struct v4l2_dbg_chip_ident {
	struct v4l2_dbg_match match;
	uint32_t ident;       /* chip identifier as specified in <media/v4l2-chip-ident.h> */
	uint32_t revision;    /* chip revision, chip specific */
} __attribute__ ((packed));

/**
 * struct v4l2_create_buffers - VIDIOC_CREATE_BUFS argument
 * @index:	on return, index of the first created buffer
 * @count:	entry: number of requested buffers,
 *		return: number of created buffers
 * @memory:	enum v4l2_memory; buffer memory type
 * @format:	frame format, for which buffers are requested
 * @reserved:	future extensions
 */
struct v4l2_create_buffers {
	uint32_t			index;
	uint32_t			count;
	uint32_t			memory;
	struct v4l2_format	format;
	uint32_t			reserved[8];
};

/*
 *	I O C T L   C O D E S   F O R   V I D E O   D E V I C E S
 *
 */
#define VIDIOC_QUERYCAP		 _IOR('V',  0, struct v4l2_capability)
#define VIDIOC_RESERVED		  _IO('V',  1)
#define VIDIOC_ENUM_FMT         _IOWR('V',  2, struct v4l2_fmtdesc)
#define VIDIOC_G_FMT		_IOWR('V',  4, struct v4l2_format)
#define VIDIOC_S_FMT		_IOWR('V',  5, struct v4l2_format)
#define VIDIOC_REQBUFS		_IOWR('V',  8, struct v4l2_requestbuffers)
#define VIDIOC_QUERYBUF		_IOWR('V',  9, struct v4l2_buffer)
#define VIDIOC_G_FBUF		 _IOR('V', 10, struct v4l2_framebuffer)
#define VIDIOC_S_FBUF		 _IOW('V', 11, struct v4l2_framebuffer)
#define VIDIOC_OVERLAY		 _IOW('V', 14, int)
#define VIDIOC_QBUF		_IOWR('V', 15, struct v4l2_buffer)
#define VIDIOC_DQBUF		_IOWR('V', 17, struct v4l2_buffer)
#define VIDIOC_STREAMON		 _IOW('V', 18, int)
#define VIDIOC_STREAMOFF	 _IOW('V', 19, int)
#define VIDIOC_G_PARM		_IOWR('V', 21, struct v4l2_streamparm)
#define VIDIOC_S_PARM		_IOWR('V', 22, struct v4l2_streamparm)
#define VIDIOC_G_STD		 _IOR('V', 23, v4l2_std_id)
#define VIDIOC_S_STD		 _IOW('V', 24, v4l2_std_id)
#define VIDIOC_ENUMSTD		_IOWR('V', 25, struct v4l2_standard)
#define VIDIOC_ENUMINPUT	_IOWR('V', 26, struct v4l2_input)
#define VIDIOC_G_CTRL		_IOWR('V', 27, struct v4l2_control)
#define VIDIOC_S_CTRL		_IOWR('V', 28, struct v4l2_control)
#define VIDIOC_G_TUNER		_IOWR('V', 29, struct v4l2_tuner)
#define VIDIOC_S_TUNER		 _IOW('V', 30, struct v4l2_tuner)
#define VIDIOC_G_AUDIO		 _IOR('V', 33, struct v4l2_audio)
#define VIDIOC_S_AUDIO		 _IOW('V', 34, struct v4l2_audio)
#define VIDIOC_QUERYCTRL	_IOWR('V', 36, struct v4l2_queryctrl)
#define VIDIOC_QUERYMENU	_IOWR('V', 37, struct v4l2_querymenu)
#define VIDIOC_G_INPUT		 _IOR('V', 38, int)
#define VIDIOC_S_INPUT		_IOWR('V', 39, int)
#define VIDIOC_G_OUTPUT		 _IOR('V', 46, int)
#define VIDIOC_S_OUTPUT		_IOWR('V', 47, int)
#define VIDIOC_ENUMOUTPUT	_IOWR('V', 48, struct v4l2_output)
#define VIDIOC_G_AUDOUT		 _IOR('V', 49, struct v4l2_audioout)
#define VIDIOC_S_AUDOUT		 _IOW('V', 50, struct v4l2_audioout)
#define VIDIOC_G_MODULATOR	_IOWR('V', 54, struct v4l2_modulator)
#define VIDIOC_S_MODULATOR	 _IOW('V', 55, struct v4l2_modulator)
#define VIDIOC_G_FREQUENCY	_IOWR('V', 56, struct v4l2_frequency)
#define VIDIOC_S_FREQUENCY	 _IOW('V', 57, struct v4l2_frequency)
#define VIDIOC_CROPCAP		_IOWR('V', 58, struct v4l2_cropcap)
#define VIDIOC_G_CROP		_IOWR('V', 59, struct v4l2_crop)
#define VIDIOC_S_CROP		 _IOW('V', 60, struct v4l2_crop)
#define VIDIOC_G_JPEGCOMP	 _IOR('V', 61, struct v4l2_jpegcompression)
#define VIDIOC_S_JPEGCOMP	 _IOW('V', 62, struct v4l2_jpegcompression)
#define VIDIOC_QUERYSTD      	 _IOR('V', 63, v4l2_std_id)
#define VIDIOC_TRY_FMT      	_IOWR('V', 64, struct v4l2_format)
#define VIDIOC_ENUMAUDIO	_IOWR('V', 65, struct v4l2_audio)
#define VIDIOC_ENUMAUDOUT	_IOWR('V', 66, struct v4l2_audioout)
#define VIDIOC_G_PRIORITY	 _IOR('V', 67, uint32_t) /* enum v4l2_priority */
#define VIDIOC_S_PRIORITY	 _IOW('V', 68, uint32_t) /* enum v4l2_priority */
#define VIDIOC_G_SLICED_VBI_CAP _IOWR('V', 69, struct v4l2_sliced_vbi_cap)
#define VIDIOC_LOG_STATUS         _IO('V', 70)
#define VIDIOC_G_EXT_CTRLS	_IOWR('V', 71, struct v4l2_ext_controls)
#define VIDIOC_S_EXT_CTRLS	_IOWR('V', 72, struct v4l2_ext_controls)
#define VIDIOC_TRY_EXT_CTRLS	_IOWR('V', 73, struct v4l2_ext_controls)
#if 1
#define VIDIOC_ENUM_FRAMESIZES	_IOWR('V', 74, struct v4l2_frmsizeenum)
#define VIDIOC_ENUM_FRAMEINTERVALS _IOWR('V', 75, struct v4l2_frmivalenum)
#define VIDIOC_G_ENC_INDEX       _IOR('V', 76, struct v4l2_enc_idx)
#define VIDIOC_ENCODER_CMD      _IOWR('V', 77, struct v4l2_encoder_cmd)
#define VIDIOC_TRY_ENCODER_CMD  _IOWR('V', 78, struct v4l2_encoder_cmd)
#endif

#if 1
/* Experimental, meant for debugging, testing and internal use.
   Only implemented if CONFIG_VIDEO_ADV_DEBUG is defined.
   You must be root to use these ioctls. Never use these in applications! */
#define	VIDIOC_DBG_S_REGISTER 	 _IOW('V', 79, struct v4l2_dbg_register)
#define	VIDIOC_DBG_G_REGISTER 	_IOWR('V', 80, struct v4l2_dbg_register)

/* Experimental, meant for debugging, testing and internal use.
   Never use this ioctl in applications! */
#define VIDIOC_DBG_G_CHIP_IDENT _IOWR('V', 81, struct v4l2_dbg_chip_ident)
#endif

#define VIDIOC_S_HW_FREQ_SEEK	 _IOW('V', 82, struct v4l2_hw_freq_seek)

/* These four DV Preset ioctls are deprecated in favor of the DV Timings
   ioctls. */
#define	VIDIOC_ENUM_DV_PRESETS	_IOWR('V', 83, struct v4l2_dv_enum_preset)
#define	VIDIOC_S_DV_PRESET	_IOWR('V', 84, struct v4l2_dv_preset)
#define	VIDIOC_G_DV_PRESET	_IOWR('V', 85, struct v4l2_dv_preset)
#define	VIDIOC_QUERY_DV_PRESET	_IOR('V',  86, struct v4l2_dv_preset)
#define	VIDIOC_S_DV_TIMINGS	_IOWR('V', 87, struct v4l2_dv_timings)
#define	VIDIOC_G_DV_TIMINGS	_IOWR('V', 88, struct v4l2_dv_timings)
#define	VIDIOC_DQEVENT		 _IOR('V', 89, struct v4l2_event)
#define	VIDIOC_SUBSCRIBE_EVENT	 _IOW('V', 90, struct v4l2_event_subscription)
#define	VIDIOC_UNSUBSCRIBE_EVENT _IOW('V', 91, struct v4l2_event_subscription)

/* Experimental, the below two ioctls may change over the next couple of kernel
   versions */
#define VIDIOC_CREATE_BUFS	_IOWR('V', 92, struct v4l2_create_buffers)
#define VIDIOC_PREPARE_BUF	_IOWR('V', 93, struct v4l2_buffer)

/* Experimental selection API */
#define VIDIOC_G_SELECTION	_IOWR('V', 94, struct v4l2_selection)
#define VIDIOC_S_SELECTION	_IOWR('V', 95, struct v4l2_selection)

/* Experimental, these two ioctls may change over the next couple of kernel
   versions. */
#define VIDIOC_DECODER_CMD	_IOWR('V', 96, struct v4l2_decoder_cmd)
#define VIDIOC_TRY_DECODER_CMD	_IOWR('V', 97, struct v4l2_decoder_cmd)

/* Experimental, these three ioctls may change over the next couple of kernel
   versions. */
#define VIDIOC_ENUM_DV_TIMINGS  _IOWR('V', 96, struct v4l2_enum_dv_timings)
#define VIDIOC_QUERY_DV_TIMINGS  _IOR('V', 97, struct v4l2_dv_timings)
#define VIDIOC_DV_TIMINGS_CAP   _IOWR('V', 98, struct v4l2_dv_timings_cap)

/* Reminder: when adding new ioctls please add support for them to
   drivers/media/video/v4l2-compat-ioctl32.c as well! */

#define BASE_VIDIOC_PRIVATE	192		/* 192-255 are private */

#endif /* __LINUX_VIDEODEV2_H */
