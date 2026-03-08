#include "../hdrs/parser.h"

enum METHOD detect_method(char * line) {
    if (strncmp(line, GET, 3) == 0)
        return GET_METHOD;
    
    if (strncmp(line, POST, 4) == 0)
        return POST_METHOD;

    return UNDEFINED;
}

void response(int file_fd, int client_socket, enum METHOD method, char * line) {
    char message[] = "HTTP/1.0 200 OK\r\n\r\n";

    switch (method)
    {
        case GET_METHOD: {
            char file_content[BUF_SIZE];
            
            int file_length = read(file_fd, file_content, BUF_SIZE);
            close(file_fd);

            write(client_socket, message, strlen(message));
            
            if (file_length == BUF_SIZE)
                file_content[BUF_SIZE-1] = '\0';
            else
                file_content[file_length] = '\0';

            write(client_socket, file_content, strlen(file_content));
            break;
        }
    
        case POST_METHOD: {
            write(file_fd, line, strlen(line));
            close(file_fd);
            write(client_socket, message, strlen(message));
            break;
        }
    
        default:
            break;
    }
}