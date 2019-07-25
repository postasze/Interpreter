#include "IfStatement.h"
#include "Expression.h"
#include "Value.h"

IfStatement::IfStatement(Expression *conditionExpression, Statement* thenStatement,
                    Statement* elseStatement, int statementPosition)
{
    this->conditionExpression = conditionExpression;
    this->thenStatement = thenStatement;
    this->elseStatement = elseStatement;
    this->statementPosition = statementPosition;
}

IfStatement::IfStatement(const IfStatement& ifStatement)
{
    this->conditionExpression = new Expression(*ifStatement.conditionExpression);
    this->thenStatement = ifStatement.thenStatement->clone();
    if(ifStatement.elseStatement != nullptr)
        this->elseStatement = ifStatement.elseStatement->clone();
    else
        this->elseStatement = nullptr;
    this->statementPosition = ifStatement.statementPosition;
}

IfStatement::~IfStatement()
{
    if(conditionExpression != nullptr)
        delete conditionExpression;
    if(thenStatement != nullptr)
        delete thenStatement;
    if(elseStatement != nullptr)
        delete elseStatement;
}

void IfStatement::execute(Interpreter& interpreter)
{
    conditionExpression->evaluate(interpreter);

    if(conditionExpression->getValue()->GetBoolValue())
        thenStatement->execute(interpreter);
    else if(elseStatement != nullptr)
        elseStatement->execute(interpreter);
}
