#include "Helpers.h"
#include "regex"

bool Helpers::regexHorario(std::string horario)
{
    std::regex regexHorario(R"(^(?:[01]\d|2[0-3]):[0-5]\d$)");
    if (!std::regex_match(horario, regexHorario))
        return false;
    return true;
}