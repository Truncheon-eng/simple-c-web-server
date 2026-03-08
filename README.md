This web-server can process two types of HTTP requests:
- GET (with inserting value from the file in the case when this file isn't idle)
- POST (inserting data to file even if this file doesn't exist because of `O_CREAT` flag)

Core functions are divided in three groups:
- socket operations: [socket.h](https://github.com/Truncheon-eng/simple-c-web-server/blob/main/hdrs/socket.h)
- file descriptors operations: [fd_operations.h](https://github.com/Truncheon-eng/simple-c-web-server/blob/main/hdrs/fd_operations.h)
- file and exit wrappers: [fork_exit.h](https://github.com/Truncheon-eng/simple-c-web-server/blob/main/hdrs/fork_exit.h)

The rest part of files is about processing request data and interacting with strings (very similar to standard library `strings.h` but my own implementation)

Example of work:
- POST method
```shell
sudo strace --follow-forks ./main > /dev/null

execve("./main", ["./main"], 0x7ffea6169d48 /* 14 vars */) = 0
socket(AF_INET, SOCK_STREAM, IPPROTO_IP) = 3
setsockopt(3, SOL_SOCKET, SO_REUSEADDR, [0], 4) = 0
bind(3, {sa_family=AF_INET, sin_port=htons(80), sin_addr=inet_addr("0.0.0.0")}, 16) = 0
listen(3, 0)                            = 0
accept(3, NULL, NULL)                   = 4
fork(strace: Process 37925 attached
)                                  = 37925
[pid 37843] close(4 <unfinished ...>
[pid 37925] read(4,  <unfinished ...>
[pid 37843] <... close resumed>)        = 0
[pid 37925] <... read resumed>"POST /tmp/tmprbx_y491 HTTP/1.1\r\n"..., 512) = 222
[pid 37843] accept(3, NULL, NULL <unfinished ...>
[pid 37925] open("/tmp/tmprbx_y491", O_WRONLY|O_CREAT, 0777) = 5
[pid 37925] write(5, "zfXqN3UDHNavkfw5CAUy8bjvkYfiWuC6"..., 40) = 40
[pid 37925] close(5)                    = 0
[pid 37925] write(4, "HTTP/1.0 200 OK\r\n\r\n", 19) = 19
[pid 37925] close(4)                    = 0
[pid 37925] close(3)                    = 0
[pid 37925] exit(0)                     = ?
[pid 37925] +++ exited with 0 +++
<... accept resumed>)                   = ? ERESTARTSYS (To be restarted if SA_RESTART is set)
--- SIGCHLD {si_signo=SIGCHLD, si_code=CLD_EXITED, si_pid=37925, si_uid=0, si_status=0, si_utime=0, si_stime=0} ---
```
- GET method
```shell
sudo strace --follow-forks ./main > /dev/null

execve("./main", ["./main"], 0x7ffdc94ba528 /* 14 vars */) = 0
socket(AF_INET, SOCK_STREAM, IPPROTO_IP) = 3
setsockopt(3, SOL_SOCKET, SO_REUSEADDR, [0], 4) = 0
bind(3, {sa_family=AF_INET, sin_port=htons(80), sin_addr=inet_addr("0.0.0.0")}, 16) = 0
listen(3, 0)                            = 0
accept(3, NULL, NULL)                   = 4
fork(strace: Process 39230 attached
)                                  = 39230
[pid 39191] close(4 <unfinished ...>
[pid 39230] read(4, "GET /tmp/tmprbx_y491 HTTP/1.1\r\nH"..., 512) = 275
[pid 39191] <... close resumed>)        = 0
[pid 39230] open("/tmp/tmprbx_y491", O_RDONLY|O_CREAT, 0644) = 5
[pid 39191] accept(3, NULL, NULL <unfinished ...>
[pid 39230] read(5, "zfXqN3UDHNavkfw5CAUy8bjvkYfiWuC6"..., 512) = 40
[pid 39230] close(5)                    = 0
[pid 39230] write(4, "HTTP/1.0 200 OK\r\n\r\n", 19) = 19
[pid 39230] write(4, "zfXqN3UDHNavkfw5CAUy8bjvkYfiWuC6"..., 40) = 40
[pid 39230] close(4)                    = 0
[pid 39230] close(3)                    = 0
[pid 39230] exit(0)                     = ?
[pid 39230] +++ exited with 0 +++
<... accept resumed>)                   = ? ERESTARTSYS (To be restarted if SA_RESTART is set)
--- SIGCHLD {si_signo=SIGCHLD, si_code=CLD_EXITED, si_pid=39230, si_uid=0, si_status=0, si_utime=0, si_stime=0} ---

# response with file /tmp/tmprbx_y491 content
# HTTP/1.0 200 OK
#
# zfXqN3UDHNavkfw5CAUy8bjvkYfiWuC6aq6VQUPf%
```
Usage:
```shell
make all # compiling the server
make clean # cleanning all object and exe files
make debug # preapring gdb for debugging
```