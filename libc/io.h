#ifndef _LIBC_IO_H
#define _LIBC_IO_H 1

#include <drivers/vga/vga.h>

void prints_col(string_t str, vga_attr_t attr);
void printc_col(char c, vga_attr_t attr);
void prints(string_t str);
void printc(char c);

char getc(bool_t catch);
void gets(string_t dst, bool_t catch);

#endif