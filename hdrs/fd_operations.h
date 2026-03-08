#ifndef FD_OPERATIONS_H
#define FD_OPERATIONS_H

#include <stddef.h>
#include <stdint.h>

#define SYS_OPEN 2
#define SYS_WRITE 1
#define SYS_READ 0
#define SYS_CLOSE 3

#define O_WRONLY (01)
#define O_CREAT (0100)
#define O_RDONLY (00)
#define O_RDWR (02)

typedef int32_t pid_t;
typedef uint32_t mode_t;

int read(int fd, char * buf, size_t count);
int write(int fd, char * buf, size_t count);
int open(const char * pathname, int flags, mode_t mode);
int close(int fd);

#endif