#include "VariableDeclaration.h"
#include "Variable.h"
#include "Assignment.h"

VariableDeclaration::VariableDeclaration()
{
    //ctor
}

VariableDeclaration::VariableDeclaration(Assignment *assignmentPointer)
{
    this->typeDescriptorPointer = assignmentPointer->typeDescriptorPointer;
    this->assignmentPointer = assignmentPointer;
    this->variablePointer = nullptr;
}

VariableDeclaration::VariableDeclaration(Variable *variablePointer)
{
    this->typeDescriptorPointer = variablePointer->typeDescriptorPointer;
    this->assignmentPointer = nullptr;
    this->variablePointer = variablePointer;
}

VariableDeclaration::VariableDeclaration(const VariableDeclaration& variableDeclaration)
{
    this->typeDescriptorPointer = variableDeclaration.typeDescriptorPointer;
    if(variableDeclaration.assignmentPointer != nullptr)
        this->assignmentPointer = new Assignment(*variableDeclaration.assignmentPointer);
    else
        this->assignmentPointer = nullptr;
    if(variableDeclaration.variablePointer != nullptr)
        this->variablePointer = new Variable(*variableDeclaration.variablePointer);
    else
        this->variablePointer = nullptr;
}

VariableDeclaration::~VariableDeclaration()
{
    //dtor
}
