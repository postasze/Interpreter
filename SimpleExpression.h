#ifndef SIMPLEEXPRESSION_H
#define SIMPLEEXPRESSION_H

#include "header.h"

class TypeDescriptor;
class Term;
class Interpreter;
class Value;

class SimpleExpression
{
    public:
        SimpleExpression(TypeDescriptor *typeDescriptorPointer, vector<Term*> *termList,
            vector<TokenType> *additiveOperatorList, bool isNegative = false);
        SimpleExpression(const SimpleExpression& simpleExpression);
        virtual ~SimpleExpression();

        TypeDescriptor *typeDescriptorPointer;
        Value* evaluate(Interpreter& interpreter);
        void setValue(Value* value);
        Value* getValue();
    protected:

    private:
        bool isNegative;
        vector<Term*> *termList;
        vector<TokenType> *additiveOperatorList;
        Value *value;
};

#endif // SIMPLEEXPRESSION_H
