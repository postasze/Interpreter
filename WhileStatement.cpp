#include "WhileStatement.h"
#include "Expression.h"
#include "Value.h"

WhileStatement::WhileStatement(Expression *conditionExpression, Statement* statement, int statementPosition)
{
    this->conditionExpression = conditionExpression;
    this->statement = statement;
    this->statementPosition = statementPosition;
}

WhileStatement::WhileStatement(const WhileStatement& whileStatement)
{
    this->conditionExpression = new Expression(*whileStatement.conditionExpression);
    this->statement = whileStatement.statement->clone();
    this->statementPosition = statementPosition;
}

WhileStatement::~WhileStatement()
{
    if(conditionExpression != nullptr)
        delete conditionExpression;
    if(statement != nullptr)
        delete statement;
}

void WhileStatement::execute(Interpreter& interpreter)
{
    conditionExpression->evaluate(interpreter);

    while(conditionExpression->getValue()->GetBoolValue())
    {
        statement->execute(interpreter);
        conditionExpression->evaluate(interpreter);
    }
}
