#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "header.h"

#include "Statement.h"

class TypeDescriptor;
class Variable;
class Expression;

class Assignment : public Statement
{
    public:
        Assignment(Variable *variablePointer, Expression *expressionPointer);
        Assignment(string identifierName, Expression *expressionPointer, int statementPosition);
        Assignment(const Assignment& assignment);
        virtual ~Assignment();

        Statement* clone() { return new Assignment(*this); }
        void execute(Interpreter& interpreter);
        TypeDescriptor *typeDescriptorPointer;
        Variable *variablePointer;

    protected:

    private:
        string identifierName;
        Expression *expressionPointer;
};

#endif // ASSIGNMENT_H
