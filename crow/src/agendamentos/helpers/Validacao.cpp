#include "ValidacaoAgendamento.h"
#include "../../helpers/Common.h"
#include "HelpersAgendamento.h"

std::variant<bool, std::string> ValidacaoAgendamento::bodyCadastro(crow::json::rvalue &body)
{
    auto campos = {"cpf", "data", "horario", "medico", "especialidade"};
    for (auto campo : campos)
    {
        if (!body.has(campo))
            return (std::stringstream() << "Campo '" << campo << "' faltando").str();
        if (body[campo].t() != crow::json::type::String)
            return (std::stringstream() << "Campo '" << campo << "' não é uma string").str();
    }

    std::string cpf = body["cpf"].s();
    std::string data = body["data"].s();
    std::string horario = body["horario"].s();

    if (!Common::regexTelefoneECPF(cpf))
        return "CPF inválido (11 dígitos)";
    if (!Common::regexData(data))
        return "Data inválida (dd-mm-yyyy)";
    if (!HelpersAgendamento::regexHorario(horario))
        return "Horário inválido (hh:mm)";
    return true;
}