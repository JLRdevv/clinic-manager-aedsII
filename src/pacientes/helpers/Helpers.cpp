#include "Helpers.h"
#include <regex>

Helpers::Paciente Helpers::json2struct(const crow::json::rvalue &json, std::string cpf)
{
    Paciente p;
    p.nome = json["nome"].s();
    p.cpf = cpf;
    p.nascimento = json["nascimento"].s();
    p.telefone = json["telefone"].s();
    p.convenio = json["convenio"].s();
    return p;
}

std::string Helpers::structPcsv(const Helpers::Paciente &p)
{
    std::ostringstream ss;
    ss << p.nome << ";"
       << p.cpf << ";"
       << p.nascimento << ";"
       << p.telefone << ";"
       << p.convenio << "\n";
    return ss.str();
}

bool Helpers::regexTelefoneECPF(std::string telefoneOuCpf)
{
    std::regex telefone_regex(R"(^\d{11}$)");
    if (!std::regex_match(telefoneOuCpf, telefone_regex))
        return false;
    return true;
}

bool Helpers::regexData(std::string data)
{
    std::regex dataRegex(R"(^(0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[0-2])-\d{4}$)");
    if (!std::regex_match(data, dataRegex))
        return false;
    return true;
}

crow::json::wvalue Helpers::json(std::string mensagem)
{
    return crow::json::wvalue({{"mensagem", mensagem}});
}

crow::response Resposta::notFound(std::string mensagem)
{
    return crow::response(404, Helpers::json(mensagem));
}

crow::response Resposta::unprocessableEntity(std::string mensagem)
{
    return crow::response(422, Helpers::json(mensagem));
}

crow::response Resposta::internalServerError(std::string mensagem)
{
    return crow::response(500, Helpers::json(mensagem));
}

crow::response Resposta::forbidden(std::string mensagem)
{
    return crow::response(403, Helpers::json(mensagem));
}

crow::response Resposta::ok(std::string mensagem)
{
    return crow::response(200, Helpers::json(mensagem));
}

crow::response Resposta::created(std::string mensagem)
{
    return crow::response(201, Helpers::json(mensagem));
}