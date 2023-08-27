// #include "keyboard.h"
// #include <iostream>

// void handle_event(KEYBOARD::keyboard_event kbevent)
// {
//     std::cout << "Key " << kbevent.key << " is " << (kbevent.status ? "down" : "up") << std::endl;
// }

// int main()
// {
//     // initialize the keyboard
//     KEYBOARD::init();

//     // register the event handler
//     KEYBOARD::keyboard_processer handler = {handle_event};
//     KEYBOARD::getc(handler);

//     return 0;
// }

#include <iostream>
#include "keyboard.h"

using namespace hal::keyboard;

void handle_event(keyboard_event kbevent)
{
    if (kbevent.status)
    {
        std::cout << "Key " << kbevent.key << " is down" << std::endl;
    }
    else
    {
        std::cout << "Key " << kbevent.key << " is up" << std::endl;
    }
}

int main()
{
    init();
    keyboard_processer kp = { handle_event };
    getc(kp);

    while (true)
    {
        keyboard_event kbevent = get_event();
        handle_event(kbevent);
    }

    return 0;
}
