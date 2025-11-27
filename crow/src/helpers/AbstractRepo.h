#pragma once
#include <fstream>

class AbstractRepo {
protected:
    static void ponteiroInicio(std::fstream& file);
    static void ponteiroFim(std::fstream& file);
};