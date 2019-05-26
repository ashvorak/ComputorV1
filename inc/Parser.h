#pragma once

#include <memory>
#include <map>
#include "ErrorManager.h"

using mQuadraticEquation = std::map<int, double>;

class Parser
{

    Parser();
    ~Parser();

    std::unique_ptr<ErrorManager> _errorManager;

	void ParseMonomial(const std::string& addend, bool isInverse, mQuadraticEquation& qEquation);
	void ParseMonomials(const std::string& equation, FormOfEquation formOfEquation, mQuadraticEquation& qEquation);
	void ShowReducedForm(FormOfEquation formOfEquation, mQuadraticEquation& qEquation);

public:

    static Parser* get();

	mQuadraticEquation Parse(const std::string& equation);
};