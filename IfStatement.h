#ifndef IFSTATEMENT_H
#define IFSTATEMENT_H

#include "Statement.h"

class Expression;
class Statement;

class IfStatement : public Statement
{
    public:
        IfStatement(Expression *conditionExpression, Statement* thenStatement,
                    Statement* elseStatement, int statementPosition);
        IfStatement(const IfStatement& ifStatement);
        virtual ~IfStatement();

        Statement* clone() { return new IfStatement(*this); }
        void execute(Interpreter& interpreter);

    protected:

    private:
        Expression *conditionExpression;
        Statement *thenStatement;
        Statement *elseStatement;
};

#endif // IFSTATEMENT_H
