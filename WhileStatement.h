#ifndef WHILESTATEMENT_H
#define WHILESTATEMENT_H

#include "Statement.h"

class Expression;
class Statement;

class WhileStatement : public Statement
{
    public:
        WhileStatement(Expression *conditionExpression, Statement* statement, int statementPosition);
        WhileStatement(const WhileStatement& whileStatement);
        virtual ~WhileStatement();

        Statement* clone() { return new WhileStatement(*this); }
        void execute(Interpreter& interpreter);

    protected:

    private:
        Expression *conditionExpression;
        Statement *statement;
};

#endif // WHILESTATEMENT_H
