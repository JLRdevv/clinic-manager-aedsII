#include "AbstractRepo.h"

void AbstractRepo::ponteiroInicio(std::fstream &file)
{
    file.clear();
    file.seekg(0, std::ios::beg);
    file.seekp(0, std::ios::beg);
}

void AbstractRepo::ponteiroFim(std::fstream &file)
{
    file.clear();
    file.seekg(0, std::ios::end);
    file.seekp(0, std::ios::end);
}