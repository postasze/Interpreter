#include "BlockStatement.h"
#include "IdentifierDescriptor.h"
#include "Interpreter.h"
#include "Scope.h"
#include "Variable.h"
#include "Value.h"

BlockStatement::BlockStatement(string name, queue<Statement*>* statementList, TypeDescriptor *returnType)
{
    this->name = name;
    this->statementList = statementList;
    this->returnType = returnType;
    this->returnValue = nullptr;
}

BlockStatement::BlockStatement(string name, queue<Statement*>* statementList, vector<Variable*>* argumentList)
{
    this->name = name;
    this->statementList = statementList;
    this->argumentList = argumentList;
    this->returnValue = nullptr;
}

BlockStatement::BlockStatement(BlockStatement& blockStatement)
{
    Statement *statementPointer;
    this->name = blockStatement.name;
    this->returnValue = nullptr;

    if(blockStatement.statementList != nullptr)
    {
        this->statementList = new queue<Statement*>();

        for(unsigned int i = 0; i < blockStatement.statementList->size(); i++)
        {
            statementPointer = blockStatement.statementList->front();
            blockStatement.statementList->pop();
            this->statementList->push(statementPointer->clone());
            blockStatement.statementList->push(statementPointer);
        }
    }
    else
        this->statementList = nullptr;

    if(blockStatement.argumentList != nullptr)
    {
        this->argumentList = new vector<Variable*>();

        for(unsigned int i = 0; i < blockStatement.argumentList->size(); i++)
            this->argumentList->push_back(new Variable(*blockStatement.argumentList->at(i)));
    }
    else
        this->argumentList = nullptr;
}

BlockStatement::~BlockStatement()
{
    if(statementList != nullptr)
    {
        while(!statementList->empty())
            statementList->pop();
        delete statementList;
    }
    if(argumentList != nullptr)
    {
        argumentList->clear();
        delete argumentList;
    }
}

void BlockStatement::NextStatement(Interpreter& interpreter)
{
    currentStatement = statementList->front();
    statementList->pop();
    currentStatement->execute(interpreter);
}

void BlockStatement::execute(Interpreter& interpreter)
{
    IdentifierDescriptor *identifierDescriptorPointer;

    // Utworz zasieg lokalny bloku
    interpreter.OpenScope(this->name, this);

    if(argumentList != nullptr)
    {
        for(unsigned int i = 0; i < argumentList->size(); i++)
        {
            identifierDescriptorPointer = interpreter.currentScope->Install(
                argumentList->at(i)->identifierName, VariableIdentifier, argumentList->at(i)->typeDescriptorPointer);
            identifierDescriptorPointer->variablePointer = argumentList->at(i);
        }
    }

    if(statementList != nullptr)
        while(!statementList->empty())
            NextStatement(interpreter);

    interpreter.CloseScope(); // Zamknij zakres lokalny bloku
}

Value* BlockStatement::getReturnValue()
{
    return this->returnValue;
}

void BlockStatement::setReturnValue(Value* returnValue)
{
    if(this->returnValue == nullptr)
        this->returnValue = new Value();

    this->returnValue->SetBoolValue(returnValue->GetBoolValue());
    this->returnValue->SetIntValue(returnValue->GetIntValue());
    this->returnValue->SetMatrixValue(returnValue->GetMatrixValue());
}
