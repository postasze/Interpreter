#ifndef READSTATEMENT_H
#define READSTATEMENT_H

#include "header.h"
#include "Statement.h"

class Variable;

class ReadStatement : public Statement
{
    public:
        ReadStatement(vector<Variable*> *variableList, int statementPosition);
        ReadStatement(const ReadStatement& readStatement);
        virtual ~ReadStatement();

        Statement* clone() { return new ReadStatement(*this); }
        void execute(Interpreter& interpreter);

    protected:

    private:
        vector<Variable*> *variableList;
};

#endif // READSTATEMENT_H
