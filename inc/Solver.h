#pragma once

#include "Computor.h"

class Solver
{
    Solver();
    ~Solver();

public:

    static Solver* get();

    void  resolve(mQuadraticEquation& qEquation);

};