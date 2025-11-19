#pragma once
#include "crow.h"
#include <fstream>
#include <vector>

class PacientesService
{
    struct Paciente
    {
        std::string nome;
        std::string cpf;
        std::string nascimento;
        std::string telefone;
        std::string convenio;
    };

private:
    static Paciente json2struct(const crow::json::rvalue &json, std::string cpf)
    {
        Paciente p;
        p.nome = json["nome"].s();
        p.cpf = cpf;
        p.nascimento = json["nascimento"].s();
        p.telefone = json["telefone"].s();
        p.convenio = json["convenio"].s();
        return p;
    }

private:
    static std::string structPcsv(const Paciente &p)
    {
        std::ostringstream ss;
        ss << p.nome << ";"
           << p.cpf << ";"
           << p.nascimento << ";"
           << p.telefone << ";"
           << p.convenio << "\n";
        return ss.str();
    }

public:
    static crow::response
    cadastrarPaciente(const crow::json::rvalue &body)
    {
        std::string pacienteCsv = structPcsv(json2struct(body, body["cpf"].s()));
        std::fstream file("/app/dados/pacientes.txt", std::ios::in | std::ios::out | std::ios::app);

        if (!file.is_open())
            return crow::response(500, crow::json::wvalue({{"mensagem", "Erro ao abrir arquivo"}}));

        std::string linha;
        int linhas = 0;
        while (std::getline(file, linha))
        {
            std::stringstream ss(linha);
            std::string _, cpf;

            std::getline(ss, _, ';');
            std::getline(ss, cpf, ';');

            if (cpf == body["cpf"].s())
                return crow::response(422, crow::json::wvalue({{"mensagem", "CPF já cadastrado"}}));
            linhas++;
        }
        if (linhas >= 100)
            return crow::response(403, crow::json::wvalue({{"mensagem", "Limite de 100 pacientes atingido"}}));

        file.clear();
        file.seekp(0, std::ios::end);
        file << pacienteCsv;
        file.close();
        return crow::response(200, crow::json::wvalue({{"mensagem", "Paciente cadastrado"}}));
    }

public:
    static crow::response getPacientes()
    {
        std::ifstream file("/app/dados/pacientes.txt");
        if (!file.is_open())
            return crow::response(500, crow::json::wvalue({{"mensagem", "Erro ao abrir arquivo"}}));
        std::string linha;
        std::vector<Paciente> pacientes;

        int linhas = 0;
        while (std::getline(file, linha))
        {
            Paciente p;
            std::stringstream ss(linha);

            std::getline(ss, p.nome, ';');
            std::getline(ss, p.cpf, ';');
            std::getline(ss, p.nascimento, ';');
            std::getline(ss, p.telefone, ';');
            std::getline(ss, p.convenio, ';');

            pacientes.push_back(p);
            linhas++;
        }
        if (linhas == 0)
            return crow::response(404, crow::json::wvalue({{"mensagem", "Nenhum paciente cadastrado"}}));
        file.close();
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

        return crow::response(200, resposta);
    }

public:
    static crow::response getPaciente(std::string cpf)
    {
        std::ifstream file("/app/dados/pacientes.txt");
        if (!file.is_open())
            return crow::response(500, crow::json::wvalue({{"mensagem", "Erro ao abrir arquivo"}}));
        std::string linha;

        Paciente paciente;
        bool encontrado = false;
        while (std::getline(file, linha))
        {
            Paciente p;
            std::stringstream ss(linha);

            std::getline(ss, p.nome, ';');
            std::getline(ss, p.cpf, ';');
            std::getline(ss, p.nascimento, ';');
            std::getline(ss, p.telefone, ';');
            std::getline(ss, p.convenio, ';');
            if (cpf == p.cpf)
            {
                paciente = p;
                encontrado = true;
                break;
            }
        }
        if (!encontrado)
            return crow::response(404, crow::json::wvalue({{"mensagem", "Paciente não encontrado"}}));

        crow::json::wvalue resposta;
        resposta["nome"] = paciente.nome;
        resposta["cpf"] = paciente.cpf;
        resposta["nascimento"] = paciente.nascimento;
        resposta["telefone"] = paciente.telefone;
        resposta["convenio"] = paciente.convenio;

        return crow::response(200, resposta);
    }

public:
    static crow::response deletarPaciente(std::string cpf)
    {
        std::ifstream file("/app/dados/pacientes.txt");
        if (!file.is_open())
            return crow::response(500, crow::json::wvalue({{"mensagem", "Erro ao abrir arquivo"}}));

        std::vector<std::string> linhas;
        std::string linha;
        bool encontrado = false;
        while (std::getline(file, linha))
        {
            std::stringstream ss(linha);
            std::string _, linhaCpf;

            std::getline(ss, _, ';');
            std::getline(ss, linhaCpf, ';');

            if (linhaCpf != cpf)
            {
                linhas.push_back(linha);
            }
            else
            {
                encontrado = true;
            }
        }
        file.close();
        if (!encontrado)
            return crow::response(404, crow::json::wvalue({{"mensagem", "Paciente não encotrado"}}));

        std::ofstream fileSaida("/app/dados/pacientes.txt", std::ios::trunc);

        for (const auto &lin : linhas)
            fileSaida << lin << "\n";

        fileSaida.close();
        return crow::response(200, crow::json::wvalue({{"mensagem", "Paciente excluido"}}));
    }

public:
    static crow::response alterarPaciente(std::string cpf, const crow::json::rvalue &body)
    {
        std::ifstream file("/app/dados/pacientes.txt");
        if (!file.is_open())
            return crow::response(500, crow::json::wvalue({{"mensagem", "Erro ao abrir arquivo"}}));

        std::vector<std::string> linhas;
        std::string linha;
        bool encontrado = false;
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
                std::string pacienteCsv = structPcsv(json2struct(body, cpf));
                linhas.push_back(pacienteCsv);
                encontrado = true;
            }
        }
        file.close();
        if (!encontrado)
            return crow::response(404, crow::json::wvalue({{"mensagem", "Paciente não encotrado"}}));

        std::ofstream fileSaida("/app/dados/pacientes.txt", std::ios::trunc);
        if (!fileSaida.is_open())
            return crow::response(500, crow::json::wvalue({{"mensagem", "Erro ao abrir arquivo"}}));

        for (const auto &lin : linhas)
            fileSaida << lin;

        fileSaida.close();
        return crow::response(200, crow::json::wvalue({{"mensagem", "Paciente alterado"}}));
    }
};