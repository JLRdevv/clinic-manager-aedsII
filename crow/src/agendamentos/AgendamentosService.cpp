#include "AgendamentosService.h"
#include "helpers/HelpersAgendamento.h"
#include "../helpers/Common.h"
#include "AgendamentosRepository.h"
#include "../pacientes/PacientesRepository.h"

crow::response AgendamentosService::criarAgendamento(crow::json::rvalue &body)
{
    std::fstream pacientes(PacientesRepository::path, std::ios::in);
    std::fstream agendamentos(AgendamentosRepository::path, std::ios::in | std::ios::out);
    if (!pacientes.is_open() || !agendamentos.is_open())
        return Resposta::internalServerError("Erro ao abrir arquivo");

    if (!PacientesRepository::findByCpf(body["cpf"].s(), pacientes))
        return Resposta::forbidden("Paciente não encontrado");
    pacientes.close();

    if (!AgendamentosRepository::podeCadastrar(agendamentos))
        return Resposta::forbidden("Limite de agendamentos atingido");

    int id = AgendamentosRepository::getId(agendamentos);
    std::string agendamentoCsv = HelpersAgendamento::structPcsv(HelpersAgendamento::json2struct(body, id));
    AgendamentosRepository::criar(agendamentoCsv, agendamentos);
    agendamentos.close();
    return HelpersAgendamento::createdComId(body, id);
};

crow::response AgendamentosService::alterarStatus(std::string status, int id)
{
    std::fstream file(AgendamentosRepository::path, std::ios::in | std::ios::out);
    if (!file.is_open())
        return Resposta::internalServerError("Erro ao abrir arquivo");

    if (!AgendamentosRepository::idValido(id, file))
        return Resposta::notFound("Agendamento não encontrado");

    HelpersAgendamento::Agendamento agendamento = AgendamentosRepository::updateStatus(id, status, file);
    file.close();
    return Resposta::okJson(HelpersAgendamento::struct2json(agendamento));
}

crow::response AgendamentosService::buscaPor(AgendamentosRepository::BuscarPor tipo, std::string valor)
{
    std::fstream file("/app/dados/agendamentos.txt", std::ios::in);
    if (!file.is_open())
        return Resposta::internalServerError("Erro ao abrir arquivo");
    AgendamentosRepository::BuscarPor tipoBusca = tipo == AgendamentosRepository::BuscarPor::Data ? AgendamentosRepository::BuscarPor::Data : AgendamentosRepository::BuscarPor::CPF;
    auto agendamentos = AgendamentosRepository::buscarPor(tipoBusca, valor, file);
    file.close();

    if (!agendamentos)
        return Resposta::notFound("Nenhum agendamento encontrado");

    crow::json::wvalue resposta = HelpersAgendamento::structVector2jsonArray(agendamentos.value());
    return Resposta::okJson(resposta);
}

crow::response AgendamentosService::getAll()
{
    std::fstream file("/app/dados/agendamentos.txt", std::ios::in);
    if (!file.is_open())
        return Resposta::internalServerError("Erro ao abrir arquivo");

    auto agendamentos = AgendamentosRepository::findAll(file);
    file.close();
    if (!agendamentos)
        return Resposta::notFound("Nenhum agendamento encontrado");

    crow::json::wvalue resposta = HelpersAgendamento::structVector2jsonArray(agendamentos.value());
    return Resposta::okJson(resposta);
}