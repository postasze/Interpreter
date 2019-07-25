#include "FunctionCallStatement.h"
#include "Value.h"
#include "Interpreter.h"
#include "Scope.h"
#include "IdentifierDescriptor.h"
#include "Function.h"
#include "BlockStatement.h"
#include "Expression.h"
#include "Variable.h"

FunctionCallStatement::FunctionCallStatement(TypeDescriptor *typeDescriptorPointer,
    string identifierName, vector<Expression*> *parameterList)
{
    this->typeDescriptorPointer = typeDescriptorPointer;
    this->identifierName = identifierName;
    this->parameterList = parameterList;
    this->returnValue = nullptr;
    this->blockStatement = nullptr;
}

FunctionCallStatement::FunctionCallStatement(string identifierName,
    vector<Expression*> *parameterList, int statementPosition)
{
    this->typeDescriptorPointer = nullptr;
    this->identifierName = identifierName;
    this->parameterList = parameterList;
    this->statementPosition = statementPosition;
    this->returnValue = nullptr;
    this->blockStatement = nullptr;
}

FunctionCallStatement::FunctionCallStatement(const FunctionCallStatement& functionCallStatement)
{
    this->typeDescriptorPointer = functionCallStatement.typeDescriptorPointer;
    this->identifierName = functionCallStatement.identifierName;
    this->statementPosition = statementPosition;
    this->returnValue = nullptr;

    if(functionCallStatement.blockStatement != nullptr)
        this->blockStatement = new BlockStatement(*functionCallStatement.blockStatement);
    else
        this->blockStatement = nullptr;

    if(functionCallStatement.parameterList != nullptr)
    {
        this->parameterList = new vector<Expression*>();

        for(unsigned int i = 0; i < functionCallStatement.parameterList->size(); i++)
            this->parameterList->push_back(new Expression(*functionCallStatement.parameterList->at(i)));
    }
    else
        this->parameterList = nullptr;
}

FunctionCallStatement::~FunctionCallStatement()
{
    if(blockStatement != nullptr)
        delete blockStatement;

    if(parameterList != nullptr)
    {
        parameterList->clear();
        delete parameterList;
    }
}

void FunctionCallStatement::execute(Interpreter& interpreter)
{
    IdentifierDescriptor *identifierDescriptorPointer;

    identifierDescriptorPointer = interpreter.currentScope->Search(
        identifierName, ProcedureIdentifier);

    if(this->parameterList->size() != identifierDescriptorPointer->functionPointer->argumentList->size())
        interpreter.SemanticError(WrongNumberOfFunctionParameters, true);

    this->blockStatement = (BlockStatement*) identifierDescriptorPointer->functionPointer->blockStatement->clone();

    for(unsigned int i = 0; i < this->parameterList->size(); i++)
    {
        this->parameterList->at(i)->evaluate(interpreter);
        if(this->parameterList->at(i)->typeDescriptorPointer != identifierDescriptorPointer->functionPointer->argumentList->at(i)->typeDescriptorPointer)
            interpreter.SemanticError(WrongTypeForFunctionParameter, true);

        this->blockStatement->argumentList->at(i)->setValue(this->parameterList->at(i)->getValue());
    }

    this->blockStatement->execute(interpreter);

    if(this->blockStatement->getReturnValue() == nullptr)
        interpreter.SemanticError(NoReturnValue, true);

    this->typeDescriptorPointer = this->blockStatement->returnType;

    if(!(Compatible(this->typeDescriptorPointer, identifierDescriptorPointer->functionPointer->typeDescriptorPointer)))
            interpreter.SemanticError(WrongTypesForFunctionAndReturnValue, true);

    this->setReturnValue(this->blockStatement->getReturnValue());
}

void FunctionCallStatement::setReturnValue(Value* returnValue)
{
    if(this->returnValue == nullptr)
        this->returnValue = new Value();

    this->returnValue->SetBoolValue(returnValue->GetBoolValue());
    this->returnValue->SetIntValue(returnValue->GetIntValue());
    this->returnValue->SetMatrixValue(returnValue->GetMatrixValue());
}

Value* FunctionCallStatement::getReturnValue()
{
    return this->returnValue;
}
