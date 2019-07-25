#ifndef TERM_H
#define TERM_H

#include "header.h"

class TypeDescriptor;
class Factor;
class Interpreter;
class Value;

class Term
{
    public:
        Term(TypeDescriptor *typeDescriptorPointer, vector<Factor*> *factorList,
            vector<TokenType> *multiplicativeOperatorList);
        Term(const Term& term);
        virtual ~Term();

        TypeDescriptor *typeDescriptorPointer;
        Value* evaluate(Interpreter& interpreter);
        void setValue(Value* value);
        Value* getValue();
    protected:

    private:
        vector<Factor*> *factorList;
        vector<TokenType> *multiplicativeOperatorList;
        Value *value;
};

#endif // TERM_H
