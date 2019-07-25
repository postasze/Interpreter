#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "header.h"

class Parser;
class Scope;
class TypeDescriptor;
class IdentifierDescriptor;
class Statement;
class BlockStatement;

class Interpreter
{
    public:
        Interpreter(Parser& parser);
        virtual ~Interpreter();
        void SemanticError(int errorCode, bool displayStatementPosition);
        void Run();

        TypeDescriptor *integerType, *booleanType, *matrixType, *procedureType;
        IdentifierDescriptor *VariableDummy, *ConstantDummy, *TypeDummy, *ProcedureDummy;
        Scope *currentScope; // Zasieg biezacy
        void OpenScope(string scopeName, BlockStatement *block);
        void CloseScope();
    protected:

    private:
        friend Scope;

        Statement *currentStatement;
        queue<Statement*> *statementList;
        Parser& parser; // Modul parsera

        void NextStatement();
};

#endif // INTERPRETER_H
