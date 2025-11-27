#pragma once
#include "crow.h"

class HelpersPaciente
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
    static crow::json::wvalue struct2json(const Paciente &p);
};


