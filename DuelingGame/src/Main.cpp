#include "App/App.h"
#include <iostream>
int main()
{
    App app = App();
    Status status = app.run();
    return status;
    std::cout << "hello" << std::endl;
    return 0;
}