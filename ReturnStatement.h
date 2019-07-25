#ifndef RETURNSTATEMENT_H
#define RETURNSTATEMENT_H

#include "Statement.h"

class Expression;
class Value;

class ReturnStatement : public Statement
{
    public:
        ReturnStatement(Expression *expressionPointer, int statementPosition);
        ReturnStatement(const ReturnStatement& returnStatement);
        virtual ~ReturnStatement();

        Statement* clone() { return new ReturnStatement(*this); }
        void execute(Interpreter& interpreter);
        void setValue(Value* value);
        Value* getValue();
    protected:

    private:
        Expression *expressionPointer;
        Value *returnValue;
};

#endif // RETURNSTATEMENT_H
