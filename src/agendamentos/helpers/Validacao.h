#pragma once
#include "crow.h"

class ValidacaoAgendamento
{
public:
    static bool bodyCadastro(crow::json::rvalue &body);
};