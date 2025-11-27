#pragma once
#include "crow.h"
#include <string>

class PacientesService
{
public:
    static crow::response cadastrarPaciente(const crow::json::rvalue &body);
    static crow::response getPacientes();
    static crow::response getPaciente(std::string cpf);
    static crow::response deletarPaciente(std::string cpf);
    static crow::response alterarPaciente(std::string cpf, const crow::json::rvalue &body);
};
