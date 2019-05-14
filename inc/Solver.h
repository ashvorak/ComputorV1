#pragma once

#include "Parser.h"

class Solver
{
    Solver();
    ~Solver();

    void CalculateRoots(double discriminate, mQuadraticEquation& qEquation);

public:

    static Solver* get();

    void  Resolve(const std::string& equation);

};