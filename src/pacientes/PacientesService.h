#pragma once
#include "crow.h"
#include <fstream>

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
    static Paciente json2struct(const crow::json::rvalue &json)
    {
        Paciente p;
        p.nome = json["nome"].s();
        p.cpf = json["cpf"].s();
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
        std::string pacienteCsv = structPcsv(json2struct(body));
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
};