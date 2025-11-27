#pragma once
#include "crow.h"
#include <variant>
class ValidacaoAgendamento
{
public:
    static std::variant<bool, std::string> bodyCadastro(crow::json::rvalue &body);
};