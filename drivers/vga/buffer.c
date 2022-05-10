#include "vga.h"

static vga_buff_t _screen = (vga_buff_t)VGA_OFFSET;

void vgabuff_fill(char c) {
    vga_attr_t attr = vga_get_attr();

    for (uint16_t i = 0; i < VGA_SIZE; i++) {
        _screen[i * 2]     = c;
        _screen[i * 2 + 1] = attr;
    }
}

void vgabuff_fill_row(char c, uint16_t row) {
    vga_attr_t attr = vga_get_attr();
    
    for (uint16_t x = row * VGA_WIDTH; x < row * VGA_WIDTH + VGA_WIDTH; x++) {
        _screen[x * 2]      = c;
        _screen[x * 2 + 1] = attr;
    }
}

void vgabuff_fill_col(char c, uint16_t col) {
    vga_attr_t attr = vga_get_attr();

    for (uint16_t y = col; col < VGA_SIZE - VGA_WIDTH; y += VGA_WIDTH) {
        _screen[y * 2]     = c;
        _screen[y * 2 + 1] = attr;
    }
}

void vgabuff_cpy(vga_buff_t buffer) {
    for (uint16_t i = 0; i < VGA_SIZE * 2; i++)
        buffer[i] = _screen[i];
}

void vgabuff_push(vga_buff_t buffer) {
    for (uint16_t i = 0; i < VGA_SIZE * 2; i++)
        _screen[i] = buffer[i];
}

uint16_t vgabuff_output_c(char c, int32_t offset) {
    if (offset == -1)
        offset = (int32_t)vgacur_get_offset();

    if (offset < 0 || offset >= VGA_SIZE)
        return VGA_SIZE - 1;
    
    vga_attr_t attr = vga_get_attr();
    
    switch (c) {
        case '\b':
            return offset == 0
                   ? 0
                   : offset - 1;
        
        case '\n':
            return CALC_ROW(offset) == VGA_HEIGHT - 1
                   ? offset
                   : (offset + VGA_WIDTH) - (offset % VGA_WIDTH);
        
        case '\r':
            return offset - offset % VGA_WIDTH;
        
        case '\t':
            return offset > VGA_SIZE - 5
                   ? VGA_SIZE - 1
                   : offset + 4;
        
        default: {
            _screen[offset * 2]     = c;
            _screen[offset * 2 + 1] = attr;
            return offset + 1;
        }
    }
}