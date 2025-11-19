#include "HelpersAgendamento.h"
#include "regex"

bool HelpersAgendamento::regexHorario(std::string horario)
{
    std::regex regexHorario(R"(^(?:[01]\d|2[0-3]):[0-5]\d$)");
    if (!std::regex_match(horario, regexHorario))
        return false;
    return true;
}

HelpersAgendamento::Agendamento HelpersAgendamento::json2struct(const crow::json::rvalue &json, int id)
{
    HelpersAgendamento::Agendamento a;
    a.id = id;
    a.cpf = json["cpf"].s();
    a.data = json["data"].s();
    a.horario = json["horario"].s();
    a.medico = json["medico"].s();
    a.especialidade = json["especialidade"].s();
    return a;
}

std::string HelpersAgendamento::structPcsv(const HelpersAgendamento::Agendamento &a)
{
    std::ostringstream ss;
    ss << a.id << ";"
       << a.cpf << ";"
       << a.data << ";"
       << a.horario << ";"
       << a.medico << ";"
       << a.especialidade << ";"
       << a.status << "\n";
    return ss.str();
}

crow::response HelpersAgendamento::createdComId(const crow::json::rvalue &json, int id) {
    crow::json::wvalue writeJson;
    for (auto &campo : json) {
        writeJson[campo.key()] = campo;  
    }
    writeJson["id"] = id;
    return crow::response(201, writeJson);
}

crow::json::wvalue HelpersAgendamento::struct2json(const HelpersAgendamento::Agendamento &a)
{
    crow::json::wvalue json;
    auto campos = {"id","cpf", "data", "horario", "medico", "especialidade", "status"};
    json["id"] = a.id;
    json["cpf"] = a.cpf;
    json["data"] = a.data;
    json["horario"] = a.horario;
    json["medico"] = a.medico;
    json["especialidade"] = a.especialidade;
    json["status"] = a.status;
    return json;
}