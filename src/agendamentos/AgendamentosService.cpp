#include "AgendamentosService.h"
#include "helpers/HelpersAgendamento.h"
#include "../helpers/Common.h"

crow::response AgendamentosService::criarAgendamento(crow::json::rvalue &body)
{
    std::fstream file("/app/dados/agendamentos.txt", std::ios::in | std::ios::out | std::ios::app);
    if (!file.is_open())
        return Resposta::internalServerError("Erro ao abrir arquivo");

    std::string linha, ultima, ultimoId = "0";
    while (std::getline(file, linha))
    {
        std::stringstream ss(linha);
        ultima = linha;
        std::getline(ss, ultimoId, ';');
    }
    int id = std::stoi(ultimoId) + 1;
    std::string agendamentoCsv = HelpersAgendamento::structPcsv(HelpersAgendamento::json2struct(body, id));

    file.clear();
    file.seekp(0, std::ios::end);
    file << agendamentoCsv;
    file.close();

    return HelpersAgendamento::createdComId(body, id);
};  