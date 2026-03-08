#include "../hdrs/noperations.h"


uint32_t htons_ip(uint32_t addr) {
    return (addr & 0xff) << 24 |
           (addr & 0xff00) << 8 |
           (addr & 0xff0000) >> 8 |
           (addr & 0xff000000) >> 24;
}

uint16_t htons_port(uint16_t port) {
    return (port & 0xff) << 8 |
           (port & 0xff00) >> 8;
}