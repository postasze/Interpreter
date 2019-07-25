#ifndef STATEMENT_H
#define STATEMENT_H

#include "TextPosition.h"

class Scope;
class Interpreter;

class Statement
{
    public:
        Statement();
        virtual ~Statement();

        virtual Statement* clone();
        virtual void execute(Interpreter& interpreter);
        void SetStatementPosition(int statementPosition);
        int GetStatementPosition();
    protected:
        int statementPosition;

    private:
};

#endif // STATEMENT_H
