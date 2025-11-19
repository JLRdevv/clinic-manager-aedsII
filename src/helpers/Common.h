#include "crow.h"

class Common
{
public:
    static bool regexTelefoneECPF(std::string telefoneOuCpf);
    static bool regexData(std::string data);
    static crow::json::wvalue json(std::string mensagem);
};

class Resposta
{
public:
    static crow::response notFound(std::string mensagem);
    static crow::response unprocessableEntity(std::string mensagem);
    static crow::response internalServerError(std::string mensagem);
    static crow::response forbidden(std::string mensagem);
    static crow::response badRequest(std::string mensagem);
    static crow::response ok(std::string mensagem);
    static crow::response okJson(crow::json::wvalue json);
    static crow::response created(std::string mensagem);
    static crow::response createdJson(crow::json::wvalue json);
};