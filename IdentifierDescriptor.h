#ifndef IDENTIFIERDESCRIPTOR_H
#define IDENTIFIERDESCRIPTOR_H

#include "header.h"

class TypeDescriptor;
class Variable;
class Function;

class IdentifierDescriptor
{
    public:
        IdentifierDescriptor(string name, unsigned typeKind, TypeDescriptor *identifierType,
            Variable *variablePointer = nullptr, Function *functionPointer = nullptr):
                name(name), typeKind(typeKind), identifierType(identifierType),
                variablePointer(variablePointer), functionPointer(functionPointer)
        {
            leftSubTree = nullptr;
            rightSubTree = nullptr;
        }
        IdentifierDescriptor();
        virtual ~IdentifierDescriptor();
        static int IdDescriptorCount;
        void Print();
        friend
        ostream& operator<<(ostream& os, const IdentifierDescriptor &identifierDescriptor);
        string name; // Nazwa
        unsigned typeKind; // Rodzaj identyfikatora (wg IdentifierKind)
        TypeDescriptor *identifierType; // Typ identyfikatora
        IdentifierDescriptor *leftSubTree, *rightSubTree; // Lewe i prawe poddrzewa
        Variable *variablePointer;
        Function *functionPointer;

    protected:

    private:
};

#endif // IDENTIFIERDESCRIPTOR_H
