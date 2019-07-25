#ifndef FUNCTIONCALLSTATEMENT_H
#define FUNCTIONCALLSTATEMENT_H

#include "header.h"
#include "Statement.h"

class TypeDescriptor;
class Expression;
class Value;
class BlockStatement;

class FunctionCallStatement : public Statement
{
    public:
        FunctionCallStatement(TypeDescriptor *typeDescriptorPointer,
            string identifierName, vector<Expression*> *parameterList);
        FunctionCallStatement(string identifierName,
            vector<Expression*> *parameterList, int statementPosition);
        FunctionCallStatement(const FunctionCallStatement& functionCallStatement);
        virtual ~FunctionCallStatement();

        Statement* clone() { return new FunctionCallStatement(*this); }
        void execute(Interpreter& interpreter);
        TypeDescriptor *typeDescriptorPointer;
        void setReturnValue(Value* value);
        Value* getReturnValue();
    protected:

    private:
        string identifierName;
        vector<Expression*> *parameterList;
        Value *returnValue;
        BlockStatement *blockStatement;
};

#endif // FUNCTIONCALLSTATEMENT_H
