#ifndef TYPEDESCRIPTOR_H
#define TYPEDESCRIPTOR_H

#include "header.h"

class TypeDescriptor
{
    public:
        TypeDescriptor(TypeKind typeKind)
        {
            this->typeKind = typeKind;
            this->count = 0;
        }
        TypeDescriptor();
        virtual ~TypeDescriptor();
        static int TypeDescriptorCount;
        int Link()
        {
            return ++count;
        } // Dołącz "użytkownika"
        int Delink()
        {
            return --count;
        }// Odłącz
        TypeKind GetTypeKind() const
        {
            return typeKind;
        }
        virtual void Print()
        {
            cout<< TypeKindStrings[typeKind];// <<'(' << count << ')';
        }
        friend int Compatible(TypeDescriptor *t1, TypeDescriptor *t2);

    protected:
        TypeKind typeKind; // Rodzaj typu
        int count; // Liczba użytkowników deskryptora

    private:
};

#endif // TYPEDESCRIPTOR_H
