#ifndef SYSTEM_HAL_SCREEN_H
#define SYSTEM_HAL_SCREEN_H

#include <stdio.h>

#define SCREEN System::hal::screen

namespace System
{
    namespace hal
    {
        namespace screen
        {
            const int VGA_WIDTH = 80;
            const int VGA_HEIGHT = 25;

            char vga[VGA_WIDTH * VGA_HEIGHT];
            unsigned short x, y;

            void redraw();
            void clear();
            void putc(char c);
            void puts(const char *s);
        } // namespace screen
    }     // namespace hal
}

void SCREEN::redraw()
{
    const char DEFAULT_COLOR = 0x07; // default fg is white, bg is black

    // Traverse the entire VGA buffer
    for (int y = 0; y < VGA_HEIGHT; y++)
    {
        for (int x = 0; x < VGA_WIDTH; x++)
        {
            // Calculate the index of the current character
            int index = y * VGA_WIDTH + x;

            // Get the attribute information of the current character
            char color = SCREEN::vga[index] >> 8;

            // If the attribute information is 0, it means that the character has not been set with color, use the default color
            if (color == 0)
            {
                color = DEFAULT_COLOR;
            }

            // Output the character with the corresponding color
            printf("\033[3%dm\033[4%dm%c", color & 0x0F, (color & 0xF0) >> 4, SCREEN::vga[index] & 0xFF);
        }
        printf("\n");
    }
}

void SCREEN::clear()
{
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
    {
        SCREEN::vga[i] = (SCREEN::vga[i] & 0xFF00) | ' '; // keep the high 8 bits, fill the low 8 bits with `32(space)`
    }
}

void SCREEN::putc(char c)
{
    static int x = 0, y = 0;
    if (c == '\n')
    {
        // new line
        x = 0;
        y++;
    }
    else
    {
        vga[y * VGA_WIDTH + x] = (vga[y * VGA_WIDTH + x] & 0xFF00) | c; // keep the high 8 bits, fill the low 8 bits with `c`
        x++;
        if (x >= VGA_WIDTH)
        {
            // reach the end of line
            x = 0;
            y++;
        }
    }
}

void SCREEN::puts(const char *s)
{
    while (*s)
    {
        putc(*s++);
    }
}

#endif // SYSTEM_HAL_SCREEN_H
