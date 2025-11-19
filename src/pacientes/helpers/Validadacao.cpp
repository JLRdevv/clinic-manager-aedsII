#include "Validacao.h"
#include "Helpers.h"

bool ValidacaoPaciente::bodyCadastro(const crow::json::rvalue &json)
{
    auto campos = {"nome", "cpf", "nascimento", "telefone", "convenio"};
    for (auto campo : campos)
    {
        if (!json.has(campo))
            return false;
        if (json[campo].t() != crow::json::type::String)
            return false;
    }

    std::string tel = json["telefone"].s();
    std::string cpf = json["cpf"].s();
    if (!Helpers::regexTelefoneECPF(tel) || !Helpers::regexTelefoneECPF(cpf))
        return false;

    std::string data = json["nascimento"].s();
    if (!Helpers::regexData(data))
        return false;

    return true;
}

bool ValidacaoPaciente::bodyPatch(const crow::json::rvalue &json)
{
    auto campos = {"nome", "nascimento", "telefone", "convenio"};
    for (auto campo : campos)
    {
        if (!json.has(campo))
            return false;
        if (json[campo].t() != crow::json::type::String)
            return false;
    }

    std::string tel = json["telefone"].s();
    if (!Helpers::regexTelefoneECPF(tel))
        return false;

    std::string data = json["nascimento"].s();
    if (!Helpers::regexData(data))
        return false;

    return true;
}
