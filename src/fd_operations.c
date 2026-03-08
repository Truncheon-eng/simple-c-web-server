#include "../hdrs/fd_operations.h"


int read(int fd, char * buf, size_t count) {
    int bytes_read;
    
    asm volatile(
        "syscall\n"
        :"=a"(bytes_read)
        :"D"(fd), "S"(buf), "d"(count), "a"(SYS_READ)
        : "rcx", "r11", "memory"
    );
    
    return bytes_read;
}

int write(int fd, char * buf, size_t count) {
    int bytes_written;
    
    asm volatile(
        "syscall\n"
        :"=a"(bytes_written)
        :"D"(fd), "S"(buf), "d"(count), "a"(SYS_WRITE)
        : "rcx", "r11", "memory"
    );
    
    return bytes_written;
}

int open(const char * pathname, int flags, mode_t mode) {
    int fd;

    asm volatile(
        "syscall\n"
        : "=a"(fd)
        : "D"(pathname), "S"(flags), "d"(mode), "a"(SYS_OPEN)
        : "rcx", "r11", "memory"
    );

    return fd;
}

int close(int fd) {
    int res;
    asm volatile(
        "syscall\n"
        : "=a"(res)
        : "D"(fd), "a"(SYS_CLOSE)
        : "rcx", "r11", "memory"
    );
    return res;
}