#ifndef SOCKET_H
#define SOCKET_H

#include <stdint.h>
#include <stddef.h>


#define SYS_ACCEPT 43
#define SYS_SOCKET 41
#define SYS_BIND 49
#define SYS_LISTEN 50
#define SYS_SETSOCKOPT 54

typedef uint32_t socklen_t;

#define AF_INET 2
#define SOCK_STREAM 1
#define SOL_SOCKET 1 
#define SO_REUSEADDR 2
// #define NULL 0

struct sockaddr {
    uint16_t sa_family;
    uint8_t sa_data[14];
};

struct sockaddr_in {
    uint16_t sin_family;
    uint16_t sin_port;
    uint32_t sin_addr;
    uint8_t __pad[8]; 
};


int socket(int domain, int type, int protocol);
int bind(int sockfd, const struct sockaddr * addr, socklen_t addrlen);
int accept(int sockfd, struct sockaddr * addr, socklen_t * addrlen_p);
int listen(int sockfd, int backlog);
int setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_len);

#endif
