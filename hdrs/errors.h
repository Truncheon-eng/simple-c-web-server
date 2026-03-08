#ifndef ERRORS_H
#define ERRORS_H

#define SOCKET_ERR "Error when invoked \"socket\"\n"
#define SETSECKOPT_ERR "Error when invoked \"setsockopt\"\n"
#define BIND_ERR "Error when invoked \"bind\"\n"
#define LISTEN_ERR "Error when invoked  \"listen\"\n"
#define PARSER_ERR "Request method should be \"POST\" ot \"GET\"\n"
#define GET_FILE_ERR "Error when tried to open file from user's request (method: \"GET\")\n"
#define POST_FILE_ERR "Error when tried to open file from user's request (method: \"POST\")\n"

#define _error(message, label) \
    do { \
        perror(message); \
        goto label; \
    } while (0);

void perror(const char * error_msg);

#endif