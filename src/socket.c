#include "../hdrs/socket.h"

int accept(int sockfd, struct sockaddr * addr, socklen_t * addrlen_p) {
    int clien_sockfd;

    asm volatile(
        "syscall\n"
        :"=a"(clien_sockfd)
        :"D"(sockfd), "S"(addr), "d"(addrlen_p), "a"(SYS_ACCEPT)
        : "r10", "rcx", "memory"
    );

    return clien_sockfd;
}

int socket(int domain, int type, int protocol) {
    int socketfd;
    asm volatile (
        "syscall\n"
        : "=a"(socketfd)
        : "D"(domain), "S"(type), "d"(protocol), "a"(SYS_SOCKET)
        : "rcx","r11","memory"
    );
    return socketfd;
}

int bind(int sockfd, const struct sockaddr * addr, socklen_t addrlen) {
    int res;
    asm volatile(
        "syscall\n"
        : "=a"(res)
        : "D"(sockfd), "S"(addr), "d"(addrlen), "a"(SYS_BIND)
        : "rcx", "r11", "memory"
    );
    return res;
}

int listen(int sockfd, int backlog) {
    int res;
    asm volatile(
        "syscall\n"
        :"=a"(res)
        :"D"(sockfd), "S"(backlog), "a"(SYS_LISTEN)
        : "r10", "rcx", "memory"
    );

    return res;
}

int setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_len) {
    int res;

    register const void * option_value_copy asm("r10") = option_value;
    register socklen_t option_len_copy asm("r8") = option_len;

    asm volatile(
        "syscall\n"
        :"=a"(res)
        :"D"(socket), "S"(level), "d"(option_name), "r"(option_value), "r"(option_len), "a"(SYS_SETSOCKOPT)
        : "rcx", "r11", "r10", "r8", "memory"
    );

    return res;
}