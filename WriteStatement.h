#ifndef WRITESTATEMENT_H
#define WRITESTATEMENT_H

#include "header.h"
#include "Statement.h"

class Expression;

class WriteStatement : public Statement
{
    public:
        WriteStatement(vector<Expression*> *expressionList, int statementPosition);
        WriteStatement(const WriteStatement& writeStatement);
        virtual ~WriteStatement();

        Statement* clone() { return new WriteStatement(*this); }
        void execute(Interpreter& interpreter);

    protected:

    private:
        vector<Expression*> *expressionList;
};

#endif // WRITESTATEMENT_H
