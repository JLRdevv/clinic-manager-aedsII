#pragma once
#include "crow.h"
#include <string>
#include <sstream>

class Helpers
{
public:
    struct Paciente
    {
        std::string nome;
        std::string cpf;
        std::string nascimento;
        std::string telefone;
        std::string convenio;
    };

    static Paciente json2struct(const crow::json::rvalue &json, std::string cpf);
    static std::string structPcsv(const Paciente &p);
    static bool regexTelefoneECPF(std::string telefoneOuCpf);
    static bool regexData(std::string data);
    static crow::json::wvalue json(std::string mensagem);
};

class Resposta
{
public:
    static crow::response notFound(std::string mensagem);
    static crow::response unprocessableEntity(std::string mensagem);
    static crow::response internalServerError(std::string mensagem);
    static crow::response forbidden(std::string mensagem);
    static crow::response ok(std::string mensagem);
    static crow::response created(std::string mensagem);
};
