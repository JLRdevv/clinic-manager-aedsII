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
};
