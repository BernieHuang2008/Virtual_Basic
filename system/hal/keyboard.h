#ifndef SYSTEM_HAL_KEYBOARD_H
#define SYSTEM_HAL_KEYBOARD_H

#include <stdio.h>

#define KEYBOARD System::hal::keyboard

namespace System
{
    namespace hal
    {
        namespace keyboard
        {
            struct keyboard_event
            {
                bool status;    // true: keydown, false: keyup
                short key;       // key code
            };

            struct keyboard_processer
            {
                void (*handler)(keyboard_event);
            };

            const short KEYBOARD_BUFFER_SIZE = 256;
            const short HANDLER_QUEUE_SIZE = 256;

            short buffer_tail = 0;
            short handlers_tail = 0;
            keyboard_event buffer[KEYBOARD_BUFFER_SIZE];
            keyboard_processer handlers[HANDLER_QUEUE_SIZE];

            void init();
            void getc(keyboard_processer);
            void interrupt_handler(keyboard_event);
        } // namespace keyboard
    }     // namespace hal
} // namespace System

void KEYBOARD::init()
{
    buffer_tail = 0;
    handlers_tail = 0;
}

void KEYBOARD::getc(keyboard_processer handler)
{
    handlers[handlers_tail++] = handler;
}

void KEYBOARD::interrupt_handler(keyboard_event kbevent)
{
    // Call the handlers
    for (int i = 0; i < handlers_tail; i++)
    {
        handlers[i].handler(kbevent);
    }
    handlers_tail = 0;
}

#endif // SYSTEM_HAL_KEYBOARD_H
