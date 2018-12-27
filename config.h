/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building universal (internal helper macro) */
#undef AC_APPLE_UNIVERSAL_BUILD

/* Define to 1 if your C++ compiler doesn't accept -c and -o together. */
#undef CXX_NO_MINUS_C_MINUS_O

/* always defined to indicate that i18n is enabled */
#undef ENABLE_NLS

/* set to 1 if sdl2 is enabled */
#undef ENABLE_SDL2

/* set to 1 if sfml is enabled */
#undef ENABLE_SFML

/* guvcview */
#undef GETTEXT_PACKAGE

/* gview_v4l2core */
#undef GETTEXT_PACKAGE_V4L2CORE
#define GETTEXT_PACKAGE_V4L2CORE v4l2_close

/* set to 1 if gsl is enabled */
#undef HAS_GSL

/* set to 1 if gtk3 installed */
#undef HAS_GTK3

/* set to 1 if pulseaudio installed */
#undef HAS_PULSEAUDIO

/* set to 1 if Qt5 installed */
#undef HAS_QT5
#define HAS_QT5 1

/* Define to 1 if you have the `bind_textdomain_codeset' function. */
#undef HAVE_BIND_TEXTDOMAIN_CODESET

/* Define to 1 if you have the Mac OS X function CFLocaleCopyCurrent in the
   CoreFoundation framework. */
#undef HAVE_CFLOCALECOPYCURRENT

/* Define to 1 if you have the Mac OS X function CFPreferencesCopyAppValue in
   the CoreFoundation framework. */
#undef HAVE_CFPREFERENCESCOPYAPPVALUE

/* Define to 1 if you have the `dcgettext' function. */
#undef HAVE_DCGETTEXT

/* Define to 1 if you have the `dirfd' function. */
#undef HAVE_DIRFD

/* Define to 1 if you have the <dlfcn.h> header file. */
#undef HAVE_DLFCN_H

/* libm includes exp */
#undef HAVE_EXP

/* Define to 1 if you have the <ffmpeg/avcodec.h> header file. */
#undef HAVE_FFMPEG_AVCODEC_H

/* Define to 1 if you have the `fpathconf' function. */
#undef HAVE_FPATHCONF

/* Define if the GNU gettext() function is already present or preinstalled. */
#undef HAVE_GETTEXT

/* Define to 1 if you have the <inttypes.h> header file. */
#undef HAVE_INTTYPES_H

/* Define if your <locale.h> file defines LC_MESSAGES. */
#undef HAVE_LC_MESSAGES

/* Define to 1 if you have the <libavcodec/avcodec.h> header file. */
#undef HAVE_LIBAVCODEC_AVCODEC_H

/* Define to 1 if you have the <libavutil/version.h> header file. */
#undef HAVE_LIBAVUTIL_VERSION_H

/* Define to 1 if you have the <locale.h> header file. */
#undef HAVE_LOCALE_H

/* Define to 1 if you have the <math.h> header file. */
#undef HAVE_MATH_H

/* Define to 1 if you have the <memory.h> header file. */
#undef HAVE_MEMORY_H

/* libm includes pow */
#undef HAVE_POW

/* Define if you have POSIX threads libraries and header files. */
#undef HAVE_PTHREAD

/* libm includes roundf */
#undef HAVE_ROUNDF

/* Define to 1 if you have the <stdint.h> header file. */
#undef HAVE_STDINT_H

/* Define to 1 if you have the <stdlib.h> header file. */
#undef HAVE_STDLIB_H

/* Define to 1 if you have the <strings.h> header file. */
#undef HAVE_STRINGS_H

/* Define to 1 if you have the <string.h> header file. */
#undef HAVE_STRING_H

/* Define to 1 if you have the <sys/stat.h> header file. */
#undef HAVE_SYS_STAT_H

/* Define to 1 if you have the <sys/types.h> header file. */
#undef HAVE_SYS_TYPES_H

/* Define to 1 if you have the <unistd.h> header file. */
#undef HAVE_UNISTD_H

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#undef LT_OBJDIR

/* set to 1 if builtin decoder is enabled */
#undef MJPG_BUILTIN

/* Name of package */
#undef PACKAGE

/* Define to the address where bug reports for this package should be sent. */
#undef PACKAGE_BUGREPORT

/* Define to the full name of this package. */
#undef PACKAGE_NAME

/* 2 */
#undef PACKAGE_RELEASE

/* Define to the full name and version of this package. */
#undef PACKAGE_STRING
#define PACKAGE_STRING 1
/* Define to the one symbol short name of this package. */
#undef PACKAGE_TARNAME
#define PACKAGE_TARNAME camera
/* Define to the home page for this package. */
#undef PACKAGE_URL

/* Define to the version of this package. */
#undef PACKAGE_VERSION

/* Define to necessary symbol if this constant uses a non-standard name on
   your system. */
#undef PTHREAD_CREATE_JOINABLE

/* Define to 1 if you have the ANSI C header files. */
#undef STDC_HEADERS

/* Version number of package */
#undef VERSION

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
#  undef WORDS_BIGENDIAN
# endif
#endif

/* Enable large inode numbers on Mac OS X 10.5.  */
#ifndef _DARWIN_USE_64_BIT_INODE
# define _DARWIN_USE_64_BIT_INODE 1
#endif

/* Number of bits in a file offset, on hosts where this is settable. */
#undef _FILE_OFFSET_BITS

/* Define for large files, on AIX-style hosts. */
#undef _LARGE_FILES
