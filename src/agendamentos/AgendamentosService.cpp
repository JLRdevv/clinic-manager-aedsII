#include "AgendamentosService.h"
#include "helpers/HelpersAgendamento.h"
#include "../helpers/Common.h"

crow::response AgendamentosService::criarAgendamento(crow::json::rvalue &body)
{
    std::fstream file("/app/dados/agendamentos.txt", std::ios::in | std::ios::out | std::ios::app);
    if (!file.is_open())
        return Resposta::internalServerError("Erro ao abrir arquivo");

    std::string linha, ultima, ultimoId = "0";
    int linhas = 0;
    while (std::getline(file, linha))
    {
        std::stringstream ss(linha);
        ultima = linha;
        std::getline(ss, ultimoId, ';');
        linhas++;
    }
    if (linhas >= 200)
        return Resposta::forbidden("Limite de agendamentos atingido");
    int id = std::stoi(ultimoId) + 1;
    std::string agendamentoCsv = HelpersAgendamento::structPcsv(HelpersAgendamento::json2struct(body, id));

    file.clear();
    file.seekp(0, std::ios::end);
    file << agendamentoCsv;
    file.close();

    return HelpersAgendamento::createdComId(body, id);
};

crow::response AgendamentosService::alterarStatus(std::string status, int id)
{
    std::ifstream file("/app/dados/agendamentos.txt");
    if (!file.is_open())
        return Resposta::internalServerError("Erro ao abrir arquivo");

    std::vector<std::string> linhas;
    std::string linha;
    bool encontrado = false;
    HelpersAgendamento::Agendamento agendamento;
    while (std::getline(file, linha))
    {
        HelpersAgendamento::Agendamento a;
        std::stringstream ss(linha);
        std::string idLinha;

        std::getline(ss, idLinha, ';');
        std::getline(ss, a.cpf, ';');
        std::getline(ss, a.data, ';');
        std::getline(ss, a.horario, ';');
        std::getline(ss, a.medico, ';');
        std::getline(ss, a.especialidade, ';');
        a.id = std::stoi(idLinha);
        a.status = status;

        if (id != a.id)
        {
            linhas.push_back(linha + "\n");
        }
        else
        {
            std::string pacienteCsv = HelpersAgendamento::structPcsv(a);
            linhas.push_back(pacienteCsv);
            encontrado = true;
            agendamento = a;
        }
    }
    file.close();
    if (!encontrado)
        return Resposta::notFound("Agendamento não encontrado");

    std::ofstream fileSaida("/app/dados/agendamentos.txt", std::ios::trunc);
    if (!fileSaida.is_open())
        Resposta::internalServerError("Erro ao abrir arquivo");

    for (const auto &lin : linhas)
        fileSaida << lin;

    fileSaida.close();
    return Resposta::okJson(HelpersAgendamento::struct2json(agendamento));
}