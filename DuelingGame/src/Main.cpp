#include "App/App.h"

int main(void)
{
    App app = App();
    Status status = app.run();
    return status;
}