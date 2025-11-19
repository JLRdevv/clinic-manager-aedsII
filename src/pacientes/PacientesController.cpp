#include "helpers/Validacao.h"
#include "helpers/Helpers.h"
#include "PacientesService.h"
#include "../helpers/Common.h"

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
                return Resposta::badRequest("Corpo da requisição inválido");
            if (!ValidacaoPaciente::bodyCadastro(json)) {
                return Resposta::badRequest("Erro de validação");
            }
            return PacientesService::cadastrarPaciente(json);
        });
        
        //patch
        CROW_BP_ROUTE(bp, "/<string>").methods(crow::HTTPMethod::Patch)
        ([](const crow::request& req, std::string cpf){
            auto json = crow::json::load(req.body);
            if (!json)
                return Resposta::badRequest("Corpo da requisição inválido");
            if (!ValidacaoPaciente::bodyPatch(json)) {
                return Resposta::badRequest("Erro de validação");
            }
            return PacientesService::alterarPaciente(cpf, json);
        });

        //del
        CROW_BP_ROUTE(bp, "/<string>").methods(crow::HTTPMethod::Delete)
        ([](std::string cpf){
            return PacientesService::deletarPaciente(cpf);
        });

        return bp;
    }
};