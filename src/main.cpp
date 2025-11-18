#include "crow.h"
#include "pacientes/PacientesController.h"

int main() {
    crow::SimpleApp app;

    app.register_blueprint(PacientesController::get_routes());

    app.port(3000).multithreaded().run();
}