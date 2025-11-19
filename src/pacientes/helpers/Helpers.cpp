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