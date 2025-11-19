#include "crow.h"

class AgendamentosController {
public:
    static crow::Blueprint& get_routes() {
        static crow::Blueprint bp("agendamentos");

        CROW_BP_ROUTE(bp, "/").methods(crow::HTTPMethod::Get)
        ([](){
            return "placeholder";
        });
        
        return bp;
    }
};