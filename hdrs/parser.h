#ifndef PARSER_H
#define PARSER_H

#define CONTENT_LENGTH "Content-Length"
#define GET "GET"
#define POST "POST"
#define BUF_SIZE 512

enum METHOD {
    GET_METHOD,
    POST_METHOD,
    UNDEFINED
};


enum METHOD detect_method(char * line);
void response(int file_fd, int client_socket, enum METHOD method, char * line);


#endif