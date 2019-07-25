#include "ReadStatement.h"
#include "Value.h"
#include "Interpreter.h"
#include "Scope.h"
#include "Variable.h"
#include "IdentifierDescriptor.h"

ReadStatement::ReadStatement(vector<Variable*> *variableList, int statementPosition)
{
    this->variableList = variableList;
    this->statementPosition = statementPosition;
}

ReadStatement::ReadStatement(const ReadStatement& readStatement)
{
    this->statementPosition = statementPosition;

    if(readStatement.variableList != nullptr)
    {
        this->variableList = new vector<Variable*>();

        for(unsigned int i = 0; i < readStatement.variableList->size(); i++)
            this->variableList->push_back(new Variable(*readStatement.variableList->at(i)));
    }
    else
        this->variableList = nullptr;
}

ReadStatement::~ReadStatement()
{

}

void ReadStatement::execute(Interpreter& interpreter)
{
    IdentifierDescriptor *identifierDescriptorPointer;
    int intValue;
    bool boolValue;
    Value *value;

    cout << "Instrukcja wczytywania:" << endl;

    for(unsigned int i = 0; i < variableList->size(); i++)
    {
        value = new Value();
        identifierDescriptorPointer = interpreter.currentScope->Search(
            variableList->at(i)->identifierName, VariableIdentifier);

        if(variableList->at(i) != identifierDescriptorPointer->variablePointer)
        {   // przypadek gdy mamy do czynienia po raz pierwszy z odwolaniem sie do danej zmiennej z instrukcji spoza deklaracji zmiennej
            delete variableList->at(i);
            variableList->at(i) = identifierDescriptorPointer->variablePointer;
        }

        if(variableList->at(i)->typeDescriptorPointer == interpreter.integerType)
        {
            cout << "Podaj wartosc typu int" << endl;
            cin >> intValue;
            value->SetIntValue(intValue);
            variableList->at(i)->setValue(value);
        }
        else if(variableList->at(i)->typeDescriptorPointer == interpreter.booleanType)
        {
            cout << "Podaj wartosc typu bool" << endl;
            cin >> boolValue;
            value->SetBoolValue(boolValue);
            variableList->at(i)->setValue(value);
        }
        delete value;
    }
}
