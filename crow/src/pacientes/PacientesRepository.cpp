#include "PacientesRepository.h"
#include <fstream>
#include <filesystem>
std::optional<HelpersPaciente::Paciente> PacientesRepository::findByCpf(const std::string &cpf, std::fstream &file)
{
    ponteiroInicio(file);
    std::string linha;
    while (std::getline(file, linha))
    {
        HelpersPaciente::Paciente p;
        std::stringstream ss(linha);

        std::getline(ss, p.nome, ';');
        std::getline(ss, p.cpf, ';');
        std::getline(ss, p.nascimento, ';');
        std::getline(ss, p.telefone, ';');
        std::getline(ss, p.convenio, ';');
        if (p.cpf == cpf)
        {
            return p;
        }
    }
    return std::nullopt;
}

bool PacientesRepository::podeCadastrar(std::fstream &file)
{
    ponteiroInicio(file);
    std::string _;
    int linhas = 0;
    while (std::getline(file, _))
    {
        linhas++;
    }
    return linhas < PacientesRepository::max;
}

std::optional<std::vector<HelpersPaciente::Paciente>> PacientesRepository::findAll(std::fstream &file)
{
    std::vector<HelpersPaciente::Paciente> pacientes;
    std::string linha;
    ponteiroInicio(file);
    while (std::getline(file, linha))
    {
        HelpersPaciente::Paciente p;
        std::stringstream ss(linha);

        std::getline(ss, p.nome, ';');
        std::getline(ss, p.cpf, ';');
        std::getline(ss, p.nascimento, ';');
        std::getline(ss, p.telefone, ';');
        std::getline(ss, p.convenio, ';');

        pacientes.push_back(p);
    }
    return !pacientes.empty() ? std::make_optional(pacientes) : std::nullopt;
}

void PacientesRepository::criar(std::string paciente, std::fstream &file)
{
    ponteiroFim(file);
    file << paciente;
}

void PacientesRepository::updateByCpf(std::string cpf, std::fstream &file, const crow::json::rvalue &body)
{
    ponteiroInicio(file);
    std::vector<std::string> linhas;
    std::string linha;
    while (std::getline(file, linha))
    {
        std::stringstream ss(linha);
        std::string _, linhaCpf;

        std::getline(ss, _, ';');
        std::getline(ss, linhaCpf, ';');

        if (linhaCpf != cpf)
        {
            linhas.push_back(linha + "\n");
        }
        else
        {
            std::string pacienteCsv = HelpersPaciente::structPcsv(HelpersPaciente::json2struct(body, cpf));
            linhas.push_back(pacienteCsv);
        }
    }

    ponteiroInicio(file);
    file.flush();
    std::filesystem::resize_file(PacientesRepository::path, 0);
    for (const auto &lin : linhas)
    {
        file << lin;
    }
}

void PacientesRepository::deleteByCpf(std::string cpf, std::fstream &file)
{
    ponteiroInicio(file);
    std::vector<std::string> linhas;
    std::string linha;
    while (std::getline(file, linha))
    {
        std::stringstream ss(linha);
        std::string _, linhaCpf;

        std::getline(ss, _, ';');
        std::getline(ss, linhaCpf, ';');

        if (linhaCpf != cpf)
        {
            linhas.push_back(linha + "\n");
        }
    }

    ponteiroInicio(file);
    file.flush();
    std::filesystem::resize_file(PacientesRepository::path, 0);
    for (const auto &lin : linhas)
    {
        file << lin;
    }
}