#include "crow.h"
#include "pacientes/PacientesController.cpp"
#include "agendamentos/AgendamentosController.cpp"
int main() {
    crow::SimpleApp app;

    app.register_blueprint(PacientesController::get_routes());
    app.register_blueprint(AgendamentosController::get_routes());
    
    app.port(3000).multithreaded().run();
}