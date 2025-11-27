#include "AgendamentosRepository.h"
#include <sstream>
#include <vector>
#include <filesystem>
int AgendamentosRepository::getId(std::fstream &file)
{
    ponteiroInicio(file);
    int id = 0;
    std::string linha, idStr;
    while (std::getline(file, linha))
    {
        std::stringstream ss(linha);
        std::getline(ss, idStr, ';');
        id = std::stoi(idStr);
    }
    return id + 1;
}

bool AgendamentosRepository::podeCadastrar(std::fstream &file)
{
    ponteiroInicio(file);
    int linhas = 0;
    std::string _;
    while (std::getline(file, _))
    {
        linhas++;
    }
    return linhas < AgendamentosRepository::max;
}

void AgendamentosRepository::criar(std::string agendamento, std::fstream &file)
{
    ponteiroFim(file);
    file << agendamento;
}

bool AgendamentosRepository::idValido(int id, std::fstream &file)
{
    ponteiroInicio(file);
    std::string linha, idLinhaStr;
    int idLinhaInt;
    while (std::getline(file, linha))
    {
        std::stringstream ss(linha);
        std::getline(ss, idLinhaStr, ';');
        idLinhaInt = std::stoi(idLinhaStr);
        if (idLinhaInt == id)
            return true;
    }
    return false;
}

HelpersAgendamento::Agendamento AgendamentosRepository::updateStatus(int id, std::string status, std::fstream &file)
{
    std::vector<std::string> linhas;
    std::string linha;
    ponteiroInicio(file);
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
            agendamento = a;
        }
    }
    ponteiroInicio(file);
    file.flush();
    std::filesystem::resize_file(AgendamentosRepository::path, 0);
    for (const auto &lin : linhas)
    {
        file << lin;
    }
    return agendamento;
}

std::optional<std::vector<HelpersAgendamento::Agendamento>> AgendamentosRepository::buscarPor(AgendamentosRepository::BuscarPor tipo, std::string valor, std::fstream &file)
{
    ponteiroInicio(file);
    std::vector<HelpersAgendamento::Agendamento> agendamentos;
    std::string linha;
    while (std::getline(file, linha))
    {
        HelpersAgendamento::Agendamento a;
        std::stringstream ss(linha);
        std::string linhaId;

        std::getline(ss, linhaId, ';');
        std::getline(ss, a.cpf, ';');
        std::getline(ss, a.data, ';');
        std::getline(ss, a.horario, ';');
        std::getline(ss, a.medico, ';');
        std::getline(ss, a.especialidade, ';');
        std::getline(ss, a.status, ';');
        a.id = std::stoi(linhaId);
        if (tipo == AgendamentosRepository::BuscarPor::CPF && a.cpf == valor)
            agendamentos.push_back(a);
        if (tipo == AgendamentosRepository::BuscarPor::Data && a.data == valor)
            agendamentos.push_back(a);
    }
    return !agendamentos.empty() ? std::make_optional(agendamentos) : std::nullopt;
}

std::optional<std::vector<HelpersAgendamento::Agendamento>> AgendamentosRepository::findAll(std::fstream &file)
{
    ponteiroInicio(file);
    std::vector<HelpersAgendamento::Agendamento> agendamentos;
    std::string linha;
    while (std::getline(file, linha))
    {
        HelpersAgendamento::Agendamento a;
        std::stringstream ss(linha);
        std::string linhaId;

        std::getline(ss, linhaId, ';');
        std::getline(ss, a.cpf, ';');
        std::getline(ss, a.data, ';');
        std::getline(ss, a.horario, ';');
        std::getline(ss, a.medico, ';');
        std::getline(ss, a.especialidade, ';');
        std::getline(ss, a.status, ';');
        a.id = std::stoi(linhaId);
        agendamentos.push_back(a);
    }
    return !agendamentos.empty() ? std::make_optional(agendamentos) : std::nullopt;
}