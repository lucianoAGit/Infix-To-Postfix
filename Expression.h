#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "StackTemplate.h"
#include <cstring>
using namespace std;

class Expression 
{ public:
    Expression(string expression);
    void setInfix(string expression);
    string getInfix();
    string getPostfix();
    int getValue();

  private:
    string infix;   // expressao na notacao infixa, fornecida pelo usuario
    string postfix; // expressao infix convertida na notacao posfixa pelo Algoritmo 1
    int    value;   // valor da expressao posfix obtida pelo Algoritmo 2

    void infixToPostfix(); // Implementacao do Algoritmo 1
    void evalPostfix();    // Implementacao do Algoritmo 2
};

#endif /* EXPRESSION_H */
