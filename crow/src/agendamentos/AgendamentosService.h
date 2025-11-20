#pragma once
#include "crow.h"
#include "helpers/HelpersAgendamento.h"

class AgendamentosService
{
public:
    static crow::response criarAgendamento(crow::json::rvalue &body);
    static crow::response alterarStatus(std::string status, int id);
    static crow::response buscaPorData(std::string data);
    static crow::response buscaPorCpf(std::string cpf);
    static crow::response getAll();
};