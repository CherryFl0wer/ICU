#ifndef _UTILS_HEADER
#define _UTILS_HEADER
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <sys/types.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <stdlib.h>

/* Always add at least this many bytes when extending the buffer.  */
#define MIN_CHUNK 64

/* Read up to (and including) a TERMINATOR from STREAM into *LINEPTR
 *    + OFFSET (and null-terminate it). *LINEPTR is a pointer returned from
 *       malloc (or NULL), pointing to *N characters of space.  It is realloc'd
 *          as necessary.  Return the number of characters read (not including the
 *             null terminator), or -1 on error or EOF.  On a -1 return, the caller
 *                should check feof(), if not then errno has been set to indicate
 *                   the error.  */

int getstr(char **lineptr, size_t *n, FILE *stream, char terminator, int offset);

int getlines(char** lineptr, size_t *n, FILE *stream);
#endif
