#ifndef DECLARATIONSTATEMENT_H
#define DECLARATIONSTATEMENT_H

#include "header.h"
#include "Statement.h"

class TypeDescriptor;
class FunctionDeclaration;
class VariableDeclaration;
class Interpreter;
class IdentifierDescriptor;

class DeclarationStatement : public Statement
{
    public:
        DeclarationStatement(FunctionDeclaration *functionDeclaration, int statementPosition);
        DeclarationStatement(vector<VariableDeclaration*> *variableDeclarationList, int statementPosition);
        DeclarationStatement(const DeclarationStatement& declarationStatement);
        DeclarationStatement();
        virtual ~DeclarationStatement();

        Statement* clone() { return new DeclarationStatement(*this); }
        void execute(Interpreter& interpreter);
        TypeDescriptor *typeDesriptor;
        FunctionDeclaration *functionDeclaration;
        vector<VariableDeclaration*> *variableDeclarationList;
    protected:

    private:
};

#endif // DECLARATIONSTATEMENT_H
