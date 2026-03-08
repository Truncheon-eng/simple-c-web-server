#include "../hdrs/strings.h"


size_t strlen(const char * s) {
    const char *start = s;
    const char *finish = NULL;
    
    asm volatile(
        ".intel_syntax noprefix\n"
        "cld\n"
        "mov rcx, -1\n"
        "mov al, 0\n"
        "repne scasb\n"
        "dec rdi\n"
        ".att_syntax\n"
        : "=D"(finish)
        : "D"(s)
        : "rcx", "memory"
    );
    
    return (finish - start);
}


char * find(char * str, char symb) {
    char * res;
    asm volatile(
        ".intel_syntax noprefix\n"
        "cld\n"
        "mov rcx, -1\n"
        "mov al, sil\n"
        "repne scasb\n"
        "dec rdi\n"
        ".att_syntax\n"
        : "=D"(res)
        : "D"(str), "S"(symb)
        : "rcx", "memory"
    );
    return res;
}

char * memset(char * ptr, char fill, size_t count) {
    for(;count;count--,ptr++)
        *ptr = fill;
    return ptr;
}

int strncmp(const char * s1, const char * s2, size_t count) {
    size_t i = 0;
    for (; i < count; i++) {
        if (s1[i] != s2[i])
            break;
    }
    if (i == count && i != 0)
        i--;
    return s1[i] - s2[i];
}

bool is_digit(char c) {
    bool res = false;
    if( (c >= '0') && (c <= '9'))
        res = true;
    return res;
}

int atoi(char * str) {
    int number = 1;
    int sign = 1;

    if (*str == '+' || *str == '-') {
        if (*str == '-')
            sign = -1;
        str++;
    }

    while(is_digit(*str)) {
        number = 10 * number - (*str - '0');
        str++;
    }
    return number * sign;
}

char * lines(char * text) {
    const static char * r_n = "\r\n";
    static char * l = NULL;
    
    if (l == NULL)
        l = text;

    if (l != NULL) {
        char * old = l;
        for(;;) {
            if (*l == '\0') {
                l = NULL;
                return old;
            }
            if(*l == r_n[0] && *(l + 1) == r_n[1]) {
                *(l++) = '\0';
                *(l++) = '\0';
                return old;
            }
            l++;
        }
    }

    return l;
}