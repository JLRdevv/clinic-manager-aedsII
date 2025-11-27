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
            auto validacao = ValidacaoAgendamento::bodyCadastro(json);
            if (std::holds_alternative<std::string>(validacao)) {
                return Resposta::badRequest(std::get<std::string>(validacao));
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
        
        CROW_BP_ROUTE(bp, "/buscar").methods(crow::HTTPMethod::Get)
        ([](const crow::request& req){
            auto data = req.url_params.get("data");
            auto cpf = req.url_params.get("cpf");
            if (!data && !cpf)
                return Resposta::badRequest("Parâmetro 'data' ou 'cpf' faltando");
            if (data && !Common::regexData(data))
                return Resposta::badRequest("'data' deve estar no formato 'dd-mm-yyyy'");
            if (cpf && !Common::regexTelefoneECPF(cpf))
                return Resposta::badRequest("CPF inválido, deve conter 11 dígitos");
            if (data && cpf)
                return Resposta::badRequest("Apenas um parâmetro por vez");
            if (data)
                return AgendamentosService::buscaPor(AgendamentosRepository::BuscarPor::Data, data);
            if (cpf)
                return AgendamentosService::buscaPor(AgendamentosRepository::BuscarPor::CPF, cpf);
        });
        
        CROW_BP_ROUTE(bp, "/").methods(crow::HTTPMethod::Get)
        ([](){
            return AgendamentosService::getAll();
        });

        return bp;
    }
};