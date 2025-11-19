#include "Helpers.h"
#include "../../helpers/Common.h"
#include <sstream>

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