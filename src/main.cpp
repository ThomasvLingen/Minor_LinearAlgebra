#include <iostream>
#include "SDLImguiApplication.hpp"
#include "linal/LinalVector.hpp"

using std::cout;
using std::endl;

int main()
{
    std::cout << "Hi" << std::endl;

    SDLImguiApplication application;
    application.run();

    return 0;
}
