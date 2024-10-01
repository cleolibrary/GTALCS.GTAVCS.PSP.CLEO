#ifndef _SYS_DIRENT_H
#define _SYS_DIRENT_H

typedef struct __dirdesc {
	int dd_fd;		/* directory file */
    int dd_loc;		/* position in buffer */
    int dd_seek;
    char *dd_buf;	/* buffer */
    int dd_len;		/* buffer length */
    int dd_size;	/* amount of data in buffer */
} DIR;

# define __dirfd(dp)	((dp)->dd_fd)

#include <sys/stat.h>

#undef  MAXNAMLEN	/* from unistd.h */
#define MAXNAMLEN	255

#define d_ino	d_fileno	/* compatibility */

struct dirent {
	ino_t      d_fileno;		    /* file number of entry */
    off_t          d_off;           /* Not an offset; see below */
	unsigned short int d_reclen;    /* Length of this record */
    unsigned char  d_type;          /* Type of file; not supported 
                                       by all filesystem types */
	char d_name[MAXNAMLEN + 1];
};

#define	DT_UNKNOWN	 0
#define	DT_FIFO		 1
#define	DT_CHR		 2
#define	DT_DIR		 4
#define	DT_BLK		 6
#define	DT_REG		 8
#define	DT_LNK		10
#define	DT_SOCK		12
#define	DT_WHT		14

#endif