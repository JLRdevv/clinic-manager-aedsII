#include <fstream>
#include <vector>
#include "helpers/HelpersPaciente.h"
#include "PacientesService.h"
#include "../helpers/Common.h"
#include "PacientesRepository.h"

crow::response PacientesService::cadastrarPaciente(const crow::json::rvalue &body)
{
    std::string pacienteCsv = HelpersPaciente::structPcsv(HelpersPaciente::json2struct(body, body["cpf"].s()));
    std::fstream file(PacientesRepository::path, std::ios::in | std::ios::out);
    if (!file.is_open())
        return Resposta::internalServerError("Erro ao abrir arquivo");

    if (PacientesRepository::findByCpf(body["cpf"].s(), file))
        return Resposta::unprocessableEntity("CPF já cadastrado!");

    if (!PacientesRepository::podeCadastrar(file))
        return Resposta::forbidden("Limite de 100 pacientes atingido");

    PacientesRepository::criar(pacienteCsv, file);
    file.close();
    return Resposta::createdJson(body);
}

crow::response PacientesService::getPacientes()
{
    std::fstream file(PacientesRepository::path, std::ios::in);
    if (!file.is_open())
        return Resposta::internalServerError("Erro ao abrir arquivo");

    auto pacientesOpt = PacientesRepository::findAll(file);
    file.close();

    if (!pacientesOpt)
        return Resposta::notFound("Nenhum paciente cadastrado");

    auto pacientes = pacientesOpt.value();
    crow::json::wvalue resposta;

    for (size_t i = 0; i < pacientes.size(); ++i)
    {
        const auto &p = pacientes[i];
        resposta[i]["nome"] = p.nome;
        resposta[i]["cpf"] = p.cpf;
        resposta[i]["nascimento"] = p.nascimento;
        resposta[i]["telefone"] = p.telefone;
        resposta[i]["convenio"] = p.convenio;
    }
    return Resposta::okJson(resposta);
}

crow::response PacientesService::getPaciente(std::string cpf)
{
    std::fstream file(PacientesRepository::path, std::ios::in);
    if (!file.is_open())
        return Resposta::internalServerError("Erro ao abrir arquivo");
    auto pacienteOpt = PacientesRepository::findByCpf(cpf, file);
    file.close();

    if (!pacienteOpt)
        return Resposta::notFound("Paciente não encontrado");

    crow::json::wvalue resposta = HelpersPaciente::struct2json(pacienteOpt.value());
    return Resposta::okJson(resposta);
}

crow::response PacientesService::alterarPaciente(std::string cpf, const crow::json::rvalue &body)
{
    std::fstream file(PacientesRepository::path, std::ios::in | std::ios::out);
    if (!file.is_open())
        return Resposta::internalServerError("Erro ao abrir arquivo");

    if (!PacientesRepository::findByCpf(cpf, file))
        return Resposta::notFound("Paciente não encontrado");

    PacientesRepository::updateByCpf(cpf, file, body);
    file.close();
    return Resposta::okJson(body);
}

crow::response PacientesService::deletarPaciente(std::string cpf)
{
    std::fstream file(PacientesRepository::path, std::ios::in | std::ios::out);
    if (!file.is_open())
        Resposta::internalServerError("Erro ao abrir arquivo");

    if (!PacientesRepository::findByCpf(cpf, file))
        return Resposta::notFound("Paciente não encontrado");

    PacientesRepository::deleteByCpf(cpf, file);

    return Resposta::ok("Paciente excluido");
}