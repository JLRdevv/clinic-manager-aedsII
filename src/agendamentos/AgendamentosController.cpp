#include "crow.h"
#include "helpers/ValidacaoAgendamento.h"
#include "../helpers/Common.h"
#include "AgendamentosService.h"

class AgendamentosController {
public:
    static crow::Blueprint& get_routes() {
        static crow::Blueprint bp("agendamentos");

        CROW_BP_ROUTE(bp, "/").methods(crow::HTTPMethod::Post)
        ([](const crow::request& req){
            auto json = crow::json::load(req.body);
            if (!json)
                return Resposta::badRequest("Corpo da requisição inválido");
            if (!ValidacaoAgendamento::bodyCadastro(json)) {
                return Resposta::badRequest("Erro de validação");
            }
            return AgendamentosService::criarAgendamento(json);
        });
        
        return bp;
    }
};