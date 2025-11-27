#pragma once
#include "helpers/HelpersPaciente.h"
#include <optional>
#include <vector>
class PacientesRepository
{
public:
    inline static std::string path = "/app/dados/pacientes.txt";
    inline static int max = 100;
    static std::optional<HelpersPaciente::Paciente> findByCpf(const std::string& cpf, std::fstream& file);
    static std::optional<std::vector<HelpersPaciente::Paciente>> findAll(std::fstream& file);
    static void updateByCpf(std::string cpf, std::fstream& file, const crow::json::rvalue& body);
    static void deleteByCpf(std::string cpf, std::fstream& file);
    static bool podeCadastrar(std::fstream& file);
    static void criar(std::string paciente, std::fstream& file);
private:
    static void ponteiroInicio(std::fstream& file);
    static void ponteiroFim(std::fstream& file);
};