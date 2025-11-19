#pragma once
#include "crow.h"
#include <regex>

class ValidacaoPaciente
{
private:
    static bool regexTelefoneECPF(std::string telefoneOuCpf)
    {
        std::regex telefone_regex(R"(^\d{11}$)");
        if (!std::regex_match(telefoneOuCpf, telefone_regex))
            return false;
        return true;
    }

private:
    static bool regexData(std::string data)
    {
        std::regex dataRegex(R"(^(0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[0-2])-\d{4}$)");
        if (!std::regex_match(data, dataRegex))
            return false;
        return true;
    }

public:
    static bool bodyCadastro(const crow::json::rvalue &json)
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
        if (!regexTelefoneECPF(tel) || !regexTelefoneECPF(cpf))
            return false;
        std::string data = json["nascimento"].s();
        if (!regexData(data))
            return false;

        return true;
    }

    static bool bodyPatch(const crow::json::rvalue &json)
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
        if (!regexTelefoneECPF(tel))
            return false;
        std::string data = json["nascimento"].s();
        if (!regexData(data))
            return false;

        return true;
    }
};