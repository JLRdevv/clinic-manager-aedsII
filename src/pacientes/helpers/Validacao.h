#pragma once
#include "crow.h"

class ValidacaoPaciente
{
public:
    static bool bodyCadastro(const crow::json::rvalue &json);
    static bool bodyPatch(const crow::json::rvalue &json);
};
