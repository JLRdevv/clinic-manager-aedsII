#pragma once
#include <fstream>
#include <optional>
#include "../helpers/AbstractRepo.h"
#include "helpers/HelpersAgendamento.h"

class AgendamentosRepository : public AbstractRepo
{
public:
    enum class BuscarPor
    {
        Data,
        CPF
    };

    inline static std::string path = "/app/dados/agendamentos.txt";
    inline static int max = 200;

    static int getId(std::fstream &file);
    static bool idValido(int id, std::fstream &file);
    static bool podeCadastrar(std::fstream &file);
    static void criar(std::string agendamento, std::fstream &file);
    static HelpersAgendamento::Agendamento updateStatus(int id, std::string status, std::fstream &file);
    static std::optional<std::vector<HelpersAgendamento::Agendamento>> buscarPor(BuscarPor tipo, std::string valor, std::fstream &file);
    static std::optional<std::vector<HelpersAgendamento::Agendamento>> findAll(std::fstream &file);
};