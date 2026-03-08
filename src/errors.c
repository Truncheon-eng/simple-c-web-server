#include "../hdrs/errors.h"

void perror(const char * error_msg) {
    write(1, error_msg, strlen(error_msg));
    return;
}