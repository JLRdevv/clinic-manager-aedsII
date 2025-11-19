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

        CROW_BP_ROUTE(bp, "/finalizar/<int>").methods(crow::HTTPMethod::Get)
        ([](int id){
            return AgendamentosService::alterarStatus("Finalizado", id);
        });
        
        CROW_BP_ROUTE(bp, "/cancelar/<int>").methods(crow::HTTPMethod::Get)
        ([](int id){
            return AgendamentosService::alterarStatus("Cancelado", id);
        });

        CROW_BP_ROUTE(bp, "/data").methods(crow::HTTPMethod::Get)
        ([](const crow::request& req){
            auto data = req.url_params.get("data");
            if (!data)
                return Resposta::badRequest("Parâmetro 'data' faltando");
            if (!Common::regexData(data))
                return Resposta::badRequest("'data' deve estar no formato 'dd-mm-yyyy'");
            return AgendamentosService::buscaPorData(data);
        });

        CROW_BP_ROUTE(bp, "/cpf").methods(crow::HTTPMethod::Get)
        ([](const crow::request& req){
            auto cpf = req.url_params.get("cpf");
            if (!cpf)
                return Resposta::badRequest("Parâmetro 'cpf' faltando");
            return AgendamentosService::buscaPorCpf(cpf);
        });

        return bp;
    }
};