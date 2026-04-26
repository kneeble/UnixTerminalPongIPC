#include <stdint.h>

int read_key() {
    uint8_t status;
    uint8_t scancode;

    asm volatile ("inb %1, %0" : "=a"(status) : "dN"(0x64));

    if (status & 1) {
        asm volatile ("inb %1, %0" : "=a"(scancode) : "dN"(0x60));
        return scancode;
    }

    return -1;
}
