#include "DeclarationStatement.h"
#include "FunctionDeclaration.h"
#include "VariableDeclaration.h"
#include "IdentifierDescriptor.h"
#include "Interpreter.h"
#include "Scope.h"
#include "Function.h"
#include "Variable.h"
#include "Assignment.h"

DeclarationStatement::DeclarationStatement()
{
    //ctor
}

DeclarationStatement::DeclarationStatement(FunctionDeclaration *functionDeclaration, int statementPosition)
{
    this->typeDesriptor = functionDeclaration->typeDescriptorPointer;
    this->functionDeclaration = functionDeclaration;
    this->variableDeclarationList = nullptr;
    this->statementPosition = statementPosition;
}

DeclarationStatement::DeclarationStatement(vector<VariableDeclaration*> *variableDeclarationList, int statementPosition)
{
    this->typeDesriptor = variableDeclarationList->front()->typeDescriptorPointer;
    this->functionDeclaration = nullptr;
    this->variableDeclarationList = variableDeclarationList;
    this->statementPosition = statementPosition;
}

DeclarationStatement::DeclarationStatement(const DeclarationStatement& declarationStatement)
{
    this->typeDesriptor = declarationStatement.typeDesriptor;
    this->statementPosition = statementPosition;

    if(declarationStatement.functionDeclaration != nullptr)
        this->functionDeclaration = new FunctionDeclaration(*declarationStatement.functionDeclaration);
    else
        this->functionDeclaration = nullptr;

    if(declarationStatement.variableDeclarationList != nullptr)
    {
        this->variableDeclarationList = new vector<VariableDeclaration*>();

        for(unsigned int i = 0; i < declarationStatement.variableDeclarationList->size(); i++)
            this->variableDeclarationList->push_back(new VariableDeclaration(*declarationStatement.variableDeclarationList->at(i)));
    }
    else
        this->variableDeclarationList = nullptr;
}

DeclarationStatement::~DeclarationStatement()
{
    if(functionDeclaration != nullptr)
        delete functionDeclaration;
    if(variableDeclarationList != nullptr)
    {
        variableDeclarationList->clear();
        delete variableDeclarationList;
    }
}

void DeclarationStatement::execute(Interpreter& interpreter)
{
    IdentifierDescriptor *identifierDescriptorPointer = nullptr;

    if(functionDeclaration != nullptr)
    {
        identifierDescriptorPointer =
            interpreter.currentScope->Install(
                functionDeclaration->functionPointer->identifierName, ProcedureIdentifier, interpreter.procedureType); // dodajemy deskryptor funkcji do obecnego zasiegu (powinien byc global, w przeciwnym razie blad parsowania)
        identifierDescriptorPointer->functionPointer = functionDeclaration->functionPointer;
    }
    else if(variableDeclarationList != nullptr)
    {
        for(unsigned int i = 0; i < variableDeclarationList->size(); i++)
        {
            if(variableDeclarationList->at(i)->variablePointer != nullptr)
            {
                identifierDescriptorPointer = interpreter.currentScope->Install(
                    variableDeclarationList->at(i)->variablePointer->identifierName,
                    VariableIdentifier, variableDeclarationList->at(i)->variablePointer->typeDescriptorPointer);
                identifierDescriptorPointer->variablePointer = variableDeclarationList->at(i)->variablePointer;
            }
            else if(variableDeclarationList->at(i)->assignmentPointer != nullptr)
            {
                identifierDescriptorPointer = interpreter.currentScope->Install(
                        variableDeclarationList->at(i)->assignmentPointer->variablePointer->identifierName,
                        VariableIdentifier, variableDeclarationList->at(i)->assignmentPointer->variablePointer->typeDescriptorPointer);
                identifierDescriptorPointer->variablePointer = variableDeclarationList->at(i)->assignmentPointer->variablePointer;

                variableDeclarationList->at(i)->assignmentPointer->execute(interpreter);
            }
        }
    }
}

