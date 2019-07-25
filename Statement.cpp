#include "Statement.h"

Statement::Statement()
{
    //ctor
}

Statement::~Statement()
{
    //dtor
}

int Statement::GetStatementPosition()
{
    return this->statementPosition;
}

void Statement::SetStatementPosition(int statementPosition)
{
    this->statementPosition = statementPosition;
}

void Statement::execute(Interpreter& interpreter)
{

}

Statement* Statement::clone()
{
    return new Statement(*this);
}
