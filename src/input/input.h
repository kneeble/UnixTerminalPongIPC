#ifndef INPUT_H
#define INPUT_H

extern unsigned char keyboard_map[128];

void poll_keyboard();
int is_key_down(unsigned char ascii);

#endif
