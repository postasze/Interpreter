#include "WriteStatement.h"
#include "Expression.h"
#include "Interpreter.h"
#include "Value.h"
#include "MatrixType.h"

WriteStatement::WriteStatement(vector<Expression*> *expressionList, int statementPosition)
{
    this->expressionList = expressionList;
    this->statementPosition = statementPosition;
}

WriteStatement::WriteStatement(const WriteStatement& writeStatement)
{
    this->statementPosition = statementPosition;

    if(writeStatement.expressionList != nullptr)
    {
        this->expressionList = new vector<Expression*>();

        for(unsigned int i = 0; i < writeStatement.expressionList->size(); i++)
            this->expressionList->push_back(new Expression(*writeStatement.expressionList->at(i)));
    }
    else
        this->expressionList = nullptr;
}

WriteStatement::~WriteStatement()
{
    if(expressionList != nullptr)
    {
        expressionList->clear();
        delete expressionList;
    }
}

void WriteStatement::execute(Interpreter& interpreter)
{
    cout << "Instrukcja wypisywania:" << endl;

    for(unsigned int i = 0; i < expressionList->size(); i++)
    {
        expressionList->at(i)->evaluate(interpreter);

        if(expressionList->at(i)->typeDescriptorPointer == interpreter.integerType)
            cout << "zmienna typu int: " << expressionList->at(i)->getValue()->GetIntValue() << endl;
        else if(expressionList->at(i)->typeDescriptorPointer == interpreter.booleanType)
            cout << "zmienna typu bool: " << expressionList->at(i)->getValue()->GetBoolValue() << endl;
        else
        {
            MatrixType *matrixType = (MatrixType*) expressionList->at(i)->typeDescriptorPointer;
            vector<int> *matrixValue = expressionList->at(i)->getValue()->GetMatrixValue();
            cout << "zmienna typu macierzowego: " << endl;
            for(int i = 0; i < matrixType->firstRange; i++)
            {
                for(int j = 0; j < matrixType->secondRange; j++)
                    cout << matrixValue->at(i*matrixType->firstRange+j) << '\t';
                cout << endl;
            }
        }
    }
}
