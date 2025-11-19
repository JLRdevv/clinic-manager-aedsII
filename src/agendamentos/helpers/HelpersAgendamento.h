#pragma once
#include <string>
#include "crow.h"

class HelpersAgendamento
{
public:
    struct Agendamento
    {
        int id;
        std::string cpf;
        std::string data;
        std::string horario;
        std::string medico;
        std::string especialidade;
        std::string status = "agendado";
    };
    static bool regexHorario(std::string horario);
    static Agendamento json2struct(const crow::json::rvalue &json, int id);
    static std::string structPcsv(const Agendamento &a);
    static crow::response createdComId(const crow::json::rvalue &json, int id);
};