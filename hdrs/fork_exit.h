#ifndef FORK_EXIT_H
#define FORK_EXIT_H

#include <stdint.h>

#define SYS_EXIT 60
#define SYS_FORK 57

typedef int32_t pid_t;

pid_t fork(void);
void sys_exit(void);

#endif