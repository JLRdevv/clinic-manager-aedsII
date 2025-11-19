#pragma once
#include "crow.h"
#include "helpers/HelpersAgendamento.h"

class AgendamentosService
{
public:
    static crow::response criarAgendamento(crow::json::rvalue &body);
    static crow::response alterarStatus(std::string status, int id);
};