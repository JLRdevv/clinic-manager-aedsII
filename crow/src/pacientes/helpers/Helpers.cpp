#include "HelpersPaciente.h"
#include "../../helpers/Common.h"
#include <sstream>

HelpersPaciente::Paciente HelpersPaciente::json2struct(const crow::json::rvalue &json, std::string cpf)
{
    Paciente p;
    p.nome = json["nome"].s();
    p.cpf = cpf;
    p.nascimento = json["nascimento"].s();
    p.telefone = json["telefone"].s();
    p.convenio = json["convenio"].s();
    return p;
}

std::string HelpersPaciente::structPcsv(const HelpersPaciente::Paciente &p)
{
    std::ostringstream ss;
    ss << p.nome << ";"
       << p.cpf << ";"
       << p.nascimento << ";"
       << p.telefone << ";"
       << p.convenio << ";\n";
    return ss.str();
}

crow::json::wvalue HelpersPaciente::struct2json(const HelpersPaciente::Paciente &p)
{
    crow::json::wvalue json;
    json["nome"] = p.nome;
    json["cpf"] = p.cpf;
    json["nascimento"] = p.nascimento;
    json["telefone"] = p.telefone;
    json["convenio"] = p.convenio;
    return json;
}