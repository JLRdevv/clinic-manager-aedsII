#include "ValidacaoPaciente.h"
#include "HelpersPaciente.h"
#include "../../helpers/Common.h"
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
    if (!Common::regexTelefoneECPF(tel) || !Common::regexTelefoneECPF(cpf))
        return false;

    std::string data = json["nascimento"].s();
    if (!Common::regexData(data))
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
    if (!Common::regexTelefoneECPF(tel))
        return false;

    std::string data = json["nascimento"].s();
    if (!Common::regexData(data))
        return false;

    return true;
}
