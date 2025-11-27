#pragma once
#include "crow.h"
#include <variant>

class ValidacaoPaciente
{
public:
    static std::variant<bool, std::string> bodyCadastro(const crow::json::rvalue &json);
    static std::variant<bool, std::string> bodyPatch(const crow::json::rvalue &json);
};
