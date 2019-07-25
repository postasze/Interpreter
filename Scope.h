#ifndef SCOPE_H
#define SCOPE_H

#include "header.h"

class Parser;
class IdentifierDescriptor;
class TypeDescriptor;
class Interpreter;
class BlockStatement;

class Scope
{
    public:
        Scope(string scopeName, Interpreter &interpreter, Scope *exteriorScope, BlockStatement *block): block(block),
            scopeName(scopeName), interpreter(interpreter), exteriorScope(exteriorScope), root(NULL)
        { }
        //Scope();
        virtual ~Scope();
        IdentifierDescriptor* Install(string name, unsigned kind, TypeDescriptor *typeDescriptor);
        IdentifierDescriptor* Search (string name, unsigned typeKinds);
        void PrintTree(IdentifierDescriptor *identifierDescriptorPointer, int currentDepth);
        BlockStatement *block;
        IdentifierDescriptor *root; // Korzeń drzewa nazw lokalnych

    protected:

    private:
        friend Interpreter;
        string scopeName;// "GLOBAL", "PROGRAM" albo nazwa procedury
        Interpreter &interpreter; // Związanie z parserem (obowiązkowe)
        Scope *exteriorScope; // Zasięg otaczający
};

#endif // SCOPE_H
