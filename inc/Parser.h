#pragma once

#include <memory>
#include "ErrorManager.h"
#include "Computor.h"

class Parser
{

    Parser();
    ~Parser();

    std::unique_ptr<ErrorManager> _errorManager;

    void parseMonomial(std::string& monomial, mQuadraticEquation& qEquation, bool isReverse);

public:

    static Parser* get();

    void parse(std::string expression, mQuadraticEquation& qEquation);
};