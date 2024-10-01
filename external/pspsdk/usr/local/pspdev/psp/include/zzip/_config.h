/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if pointers to integers require aligned access */
/* #undef ZZIP_HAVE_ALIGNED_ACCESS_REQUIRED */

/* Define to 1 if you have the <byteswap.h> header file. */
/* #undef ZZIP_HAVE_BYTESWAP_H */

/* Define to 1 if you have the <direct.h> header file. */
/* #undef ZZIP_HAVE_DIRECT_H */

/* Define to 1 if you have the <dirent.h> header file, and it defines `DIR'.*/
#define ZZIP_HAVE_DIRENT_H 1

/* Define to 1 if you have the <dlfcn.h> header file. */
/* #undef ZZIP_HAVE_DLFCN_H */

/* Define to 1 if you have the <fnmatch.h> header file. */
#define ZZIP_HAVE_FNMATCH_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define ZZIP_HAVE_INTTYPES_H 1

/* Define to 1 if you have the <io.h> header file. */
/* #undef ZZIP_HAVE_IO_H */

/* Define to 1 if you have the <memory.h> header file. */
#define ZZIP_HAVE_MEMORY_H 1

/* Define to 1 if you have the <ndir.h> header file, and it defines `DIR'. */
/* #undef ZZIP_HAVE_NDIR_H */

/* Define to 1 if you have the <stdint.h> header file. */
#define ZZIP_HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define ZZIP_HAVE_STDLIB_H 1

/* Define to 1 if you have the `strcasecmp' function. */
#define ZZIP_HAVE_STRCASECMP 1

/* Define to 1 if you have the <strings.h> header file. */
#define ZZIP_HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define ZZIP_HAVE_STRING_H 1

/* Define to 1 if you have the `strndup' function. */
#define ZZIP_HAVE_STRNDUP 1

/* Define to 1 if you have the <sys/dir.h> header file, and it defines `DIR'.*/
#define ZZIP_HAVE_SYS_DIR_H 1

/* Define to 1 if you have the <sys/int_types.h> header file. */
/* #undef ZZIP_HAVE_SYS_INT_TYPES_H */

/* Define to 1 if you have the <sys/mman.h> header file. */
/* #undef ZZIP_HAVE_SYS_MMAN_H */

/* Define to 1 if you have the <sys/ndir.h> header file, and it defines `DIR'.*/
/* #undef ZZIP_HAVE_SYS_NDIR_H */

/* Define to 1 if you have the <sys/param.h> header file. */
#define ZZIP_HAVE_SYS_PARAM_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define ZZIP_HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define ZZIP_HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define ZZIP_HAVE_UNISTD_H 1

/* Define to 1 if you have the <winbase.h> header file. */
/* #undef ZZIP_HAVE_WINBASE_H */

/* Define to 1 if you have the <windows.h> header file. */
/* #undef ZZIP_HAVE_WINDOWS_H */

/* Define to 1 if you have the <winnt.h> header file. */
/* #undef ZZIP_HAVE_WINNT_H */

/* Define to 1 if you have the <zlib.h> header file. */
#define ZZIP_HAVE_ZLIB_H 1

/* whether the system defaults to 32bit off_t but can do 64bit when requested */
/* #undef ZZIP_LARGEFILE_SENSITIVE */

/* Name of package */
#define ZZIP_PACKAGE "zziplib"

/* Define to the address where bug reports for this package should be sent. */
/* #undef ZZIP_PACKAGE_BUGREPORT */

/* Define to the full name of this package. */
#define ZZIP_PACKAGE_NAME "zziplib"

/* Define to the full name and version of this package. */
/* #undef ZZIP_PACKAGE_STRING */

/* Define to the one symbol short name of this package. */
/* #undef ZZIP_PACKAGE_TARNAME */

/* Define to the version of this package. */
#define ZZIP_PACKAGE_VERSION "0.13.72"

/* The number of bytes in type int */
#define ZZIP_SIZEOF_INT 4

/* The number of bytes in type long */
#define ZZIP_SIZEOF_LONG 4

/* The number of bytes in type short */
#define ZZIP_SIZEOF_SHORT 2

/* Define to 1 if you have the ANSI C header files. */
#define ZZIP_STDC_HEADERS 1

/* Version number of package */
#define ZZIP_VERSION 0.13.72

/* Define to 1 if your processor stores words with the most significant byte
   first (like Motorola and SPARC, unlike Intel and VAX). */
/* #undef ZZIP_WORDS_BIGENDIAN */

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to `long long' if <sys/types.h> does not define. */
/* #undef __int64 */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
#ifndef _zzip_inline
#define _zzip_inline  __inline
#endif
#endif


/* Define to `_zzip_off_t' if <sys/types.h> does not define. */
#define _zzip_off64_t _zzip_off_t

/* Define to `long int' if <sys/types.h> does not define. */
/* #undef _zzip_off_t */

/* Define to equivalent of C99 restrict keyword, or to nothing if this is not
   supported. Do not define if restrict is supported directly. */
#ifndef _zzip_restrict
#define _zzip_restrict
#endif


/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef _zzip_size_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef _zzip_ssize_t */
