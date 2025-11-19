#pragma once
#include "crow.h"
#include "Validadacao.h"
#include "PacientesService.h"

class PacientesController {
public:
    static crow::Blueprint& get_routes() {
        static crow::Blueprint bp("pacientes");

        //get todos
        CROW_BP_ROUTE(bp, "/").methods(crow::HTTPMethod::Get)
        ([](){
            return PacientesService::getPacientes();
        });
        
        //get especifico
        CROW_BP_ROUTE(bp, "/<string>").methods(crow::HTTPMethod::Get)
        ([](std::string cpf){
            return PacientesService::getPaciente(cpf);
        });

        //post
        CROW_BP_ROUTE(bp, "/").methods(crow::HTTPMethod::Post)
        ([](const crow::request& req){
            auto json = crow::json::load(req.body);
            if (!json)
                return crow::response(400, crow::json::wvalue{
                    {"mensagem", "Corpo da requisição inválido"}
                });
            if (!ValidacaoPaciente::body(json)) {
                return crow::response(400, crow::json::wvalue{
                    {"mensagem", "Erro de validação"}
                });
            }
            return PacientesService::cadastrarPaciente(json);
        });
        
        //patch
        CROW_BP_ROUTE(bp, "/").methods(crow::HTTPMethod::Patch)
        ([](){
            return crow::response(201, "placeholder");
        });

        //del
        CROW_BP_ROUTE(bp, "/<string>").methods(crow::HTTPMethod::Delete)
        ([](std::string cpf){
            return PacientesService::deletarPaciente(cpf);
        });

        return bp;
    }
};