#include "crow.h"

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return "teste";
    });

    app.port(3000).multithreaded().run();
}