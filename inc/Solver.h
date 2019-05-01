#pragma once

#include "Parser.h"

class Solver
{
    Solver();
    ~Solver();

public:

    static Solver* get();

    void  Resolve(const std::string& equation);

};