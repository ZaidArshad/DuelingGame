#include "App/App.hpp"

int main(void)
{
    App app = App();
    Status status = app.run();
    return status;
}