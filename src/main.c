#include "../hdrs/socket.h"
#include "../hdrs/strings.h"
#include "../hdrs/fd_operations.h"
#include "../hdrs/noperations.h"
#include "../hdrs/fork_exit.h"
#include "../hdrs/errors.h"
#include "../hdrs/parser.h"

#include <stdbool.h>

#define INVALID_FD (-1)
#define INVALID_SETSECKOPT (-1)
#define INVALID_BIND (-1)
#define INVALID_LISTEN (-1)




void _start(void) {
    // binding
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_FD)
        _error(SOCKET_ERR, exit);
    
    // setting socket options
    int option;
    int opt_res = setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    if(opt_res == INVALID_SETSECKOPT)
        _error(SETSECKOPT_ERR, close_server);
    
    // binding socket with 0.0.0.0:80 ip address and port
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_addr = htons_ip((uint32_t) 0x00000000), // just 0.0.0.0
        .sin_port = htons_port((uint16_t) 0x0050), // hist 80th port
        .__pad = {0}
    };
    int bind_res = bind(server_socket, (const struct sockaddr *) &addr, sizeof(struct sockaddr_in));
    if(bind_res == INVALID_BIND)
        _error(BIND_ERR, close_server);

    // listening
    int listen_res = listen(server_socket, 0);
    if(listen_res == INVALID_LISTEN)
        _error(LISTEN_ERR, close_server)
    
    int client_socket = INVALID_FD;
    while((client_socket = accept(server_socket, NULL, NULL)) != INVALID_FD) {
        if (!fork()) {
            char request[BUF_SIZE];

            memset(request, '\0', BUF_SIZE);
            
            int len_request = read(client_socket, request, BUF_SIZE);
            
            if (len_request == BUF_SIZE)
                request[BUF_SIZE-1] = '\0';
            else
                request[len_request] = '\0';

            char * line = lines(request);
            char * filename = NULL;
            int file_fd = INVALID_FD;

            enum METHOD method = detect_method(line);

            if (method == UNDEFINED)
                _error(PARSER_ERR, close_client);
            
            switch (method)
            {
                case GET_METHOD: {
                    char * space = find(line + 4, ' ');
                    *space = '\0';
                    filename = line + 4;
                    file_fd = open(filename, O_RDONLY | O_CREAT, 0644);
                    if (file_fd == INVALID_FD)
                        _error(GET_FILE_ERR, close_client);
                    break;
                }
                case POST_METHOD: {
                    char * space = find(line + 5, ' ');
                    *space = '\0';
                    filename = line + 5;
                    file_fd = open(filename, O_WRONLY | O_CREAT, 0777);
                    if (file_fd == INVALID_FD)
                        _error(POST_FILE_ERR, close_client);
                    break;
                }
                
                default:
                    break;
            }
            
            bool is_data = false;

            while(line) {
                int pre_data = strncmp(line, "", 0);

                if (is_data) {
                    is_data = false;
                    response(file_fd, client_socket, method, line);
                }
                
                if (pre_data == 0)
                    is_data = true;

                line = lines(NULL);
            }
            
            goto close_client;
        }
        close(client_socket);
    }
    goto close_server;

close_client:
    close(client_socket);
close_server:
    close(server_socket);
exit:
    sys_exit();
}