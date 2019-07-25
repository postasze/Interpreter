#ifndef BLOCKSTATEMENT_H
#define BLOCKSTATEMENT_H

#include "header.h"
#include "TypeDescriptor.h"
#include "Statement.h"

class Variable;
class Value;

class BlockStatement : public Statement
{
    public:
        BlockStatement(string name, queue<Statement*>* statementList, TypeDescriptor *returnType);
        BlockStatement(string name, queue<Statement*>* statementList, vector<Variable*>* argumentList);
        BlockStatement(BlockStatement& blockStatement);
        virtual ~BlockStatement();

        Statement* clone() { return new BlockStatement(*this); }
        void NextStatement(Interpreter& interpreter);
        void execute(Interpreter& interpreter);
        TypeDescriptor *returnType;
        Value* getReturnValue();
        void setReturnValue(Value* returnValue);
        Statement *currentStatement;
        vector<Variable*>* argumentList;
        queue<Statement*>* statementList;

    protected:

    private:
        string name;
        Value *returnValue;
};

#endif // BLOCKSTATEMENT_H
