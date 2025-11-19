#include "Validacao.h"
#include "../../helpers/Common.h"
#include "Helpers.h"

bool ValidacaoAgendamento::bodyCadastro(crow::json::rvalue &body)
{
    auto campos = {"cpf", "data", "horario", "medico", "especialidade"};
    for (auto campo : campos)
    {
        if (!body.has(campo))
            return false;
        if (body[campo].t() != crow::json::type::String)
            return false;
    }

    std::string cpf = body["cpf"].s();
    std::string data = body["data"].s();
    std::string horario = body["horario"].s();

    if (!Common::regexTelefoneECPF(cpf) || !Common::regexData(data) || !Helpers::regexHorario(horario))
        return false;
    return true;
}