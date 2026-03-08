#include "../hdrs/fork_exit.h"


pid_t fork(void) {
    pid_t pid;

    asm volatile(
        "syscall\n"
        : "=a"(pid)
        : "a"(SYS_FORK)
        : "rcx", "r11", "memory"
    );

    return pid;
}


void sys_exit(void) {
    asm volatile(
        "syscall\n"
        :
        : "D"(0), "a"(SYS_EXIT)
        : "rcx","r11","memory"
    );
}
