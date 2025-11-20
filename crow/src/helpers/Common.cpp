#include "Common.h"
#include <regex>

bool Common::regexTelefoneECPF(std::string telefoneOuCpf)
{
    std::regex telefone_regex(R"(^\d{11}$)");
    if (!std::regex_match(telefoneOuCpf, telefone_regex))
        return false;
    return true;
}

bool Common::regexData(std::string data)
{
    std::regex dataRegex(R"(^(0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[0-2])-\d{4}$)");
    if (!std::regex_match(data, dataRegex))
        return false;
    return true;
}

crow::json::wvalue Common::json(std::string mensagem)
{
    return crow::json::wvalue({{"mensagem", mensagem}});
}

crow::response Resposta::notFound(std::string mensagem)
{
    return crow::response(404, Common::json(mensagem));
}

crow::response Resposta::unprocessableEntity(std::string mensagem)
{
    return crow::response(422, Common::json(mensagem));
}

crow::response Resposta::internalServerError(std::string mensagem)
{
    return crow::response(500, Common::json(mensagem));
}

crow::response Resposta::forbidden(std::string mensagem)
{
    return crow::response(403, Common::json(mensagem));
}

crow::response Resposta::badRequest(std::string mensagem)
{
    return crow::response(400, Common::json(mensagem));
}

crow::response Resposta::ok(std::string mensagem)
{
    return crow::response(200, Common::json(mensagem));
}

crow::response Resposta::okJson(crow::json::wvalue json)
{
    return crow::response(200, json);
}

crow::response Resposta::created(std::string mensagem)
{
    return crow::response(201, Common::json(mensagem));
}

crow::response Resposta::createdJson(crow::json::wvalue json)
{
    return crow::response(201, json);
}