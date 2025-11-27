#pragma once
#include "crow.h"
#include "helpers/HelpersAgendamento.h"
#include "AgendamentosRepository.h"

class AgendamentosService
{
public:
    static crow::response criarAgendamento(crow::json::rvalue &body);
    static crow::response alterarStatus(std::string status, int id);
    static crow::response buscaPor(AgendamentosRepository::BuscarPor tipo, std::string valor);
    static crow::response getAll();
};