#include <iostream>
#include <cstdlib> // for std::system()
#include "io.h"

const int KB_ESCAPE = 27;

bool handleRegularKey(int c);
void handleSpecialKey();

int main()
{
    std::system("cls");

    std::cout << "Hello world!\n";
    Screen::resetLocation();

    // Bad! doesn't overwrite all the previously printed text
    std::cout << "Hi world!\n";

    for (auto exit = false; !exit; )
    {
        auto c = Keyboard::getch();
        switch (c)
        {
        case 0:
        case SPECIAL_KEY:
            handleSpecialKey();
            break;
        default:
            exit = handleRegularKey(c);
            break;
        }
    }
}

bool handleRegularKey(int c)
{
    switch (c)
    {
    case 'A':
        std::cout << "A pressed\n";
        break;
    case 'a':
        std::cout << "a pressed\n";
        break;
    case KB_ESCAPE:
        std::cout << "Escape pressed. Exiting...\n";
        return true;
    default:
        std::cout << "Unknown regular key pressed (code = " << c << ")\n";
        break;
    }

    return false;
}

void handleSpecialKey()
{
    auto c = Keyboard::getch();
    switch (c)
    {
    case KB_UP:
        std::cout << "Arrow Up pressed\n";
        break;
    case KB_DOWN:
        std::cout << "Arrow Down pressed\n";
        break;
    case KB_LEFT:
        std::cout << "Arrow Left pressed\n";
        break;
    case KB_RIGHT:
        std::cout << "Arrow Right pressed\n";
        break;
    default:
        std::cout << "Unknown special key pressed (code = " << c << ")\n";
        break;
    }
}
