#include "Core/App.h"

int main() {
    Tapedawf::App app;

    if (!app.init()) {
        return -1;
    }

    app.run();
    app.shutdown();

    return 0;
}