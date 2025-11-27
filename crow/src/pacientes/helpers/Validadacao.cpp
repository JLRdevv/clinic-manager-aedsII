#include "ValidacaoPaciente.h"
#include "HelpersPaciente.h"
#include "../../helpers/Common.h"
#include <sstream>

std::variant<bool, std::string> ValidacaoPaciente::bodyCadastro(const crow::json::rvalue &json)
{
    auto campos = {"nome", "cpf", "nascimento", "telefone", "convenio"};
    for (auto campo : campos)
    {
        if (!json.has(campo))
            return (std::stringstream() << "Campo '" << campo << "' faltando").str();
        if (json[campo].t() != crow::json::type::String)
            return (std::stringstream() << "Campo '" << campo << "' não é uma string").str();
    }

    std::string tel = json["telefone"].s();
    std::string cpf = json["cpf"].s();
    if (!Common::regexTelefoneECPF(tel))
        return "Telefone inválido (11 digitos)";

    if (!Common::regexTelefoneECPF(cpf))
        return "CPF inválido (11 digitos)";

    std::string data = json["nascimento"].s();
    if (!Common::regexData(data))
        return "Data de nascimento inválida (dd-mm-yyyy)";

    return true;
}

std::variant<bool, std::string> ValidacaoPaciente::bodyPatch(const crow::json::rvalue &json)
{
    auto campos = {"nome", "nascimento", "telefone", "convenio"};
    for (auto campo : campos)
    {
        if (!json.has(campo))
            return (std::stringstream() << "Campo '" << campo << "' faltando").str();
        if (json[campo].t() != crow::json::type::String)
            return (std::stringstream() << "Campo '" << campo << "' não é uma string").str();
    }

    std::string tel = json["telefone"].s();
    if (!Common::regexTelefoneECPF(tel))
        return "Telefone inválido (11 digitos)";

    std::string data = json["nascimento"].s();
    if (!Common::regexData(data))
        return "Data de nascimento inválida (dd-mm-yyyy)";

    return true;
}
