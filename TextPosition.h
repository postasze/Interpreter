#ifndef TEXTPOSITION_H
#define TEXTPOSITION_H

#include "header.h"

class TextPosition
{
    public:
        TextPosition(int lineNumber = 1, int characterNumber = 1)
            : lineNumber(lineNumber), characterNumber(characterNumber) {}
        //TextPosition();
        ~TextPosition();
        int GetLineNumber();
        int GetCharacterNumber();
        void SetLineNumber(int number);
        void SetCharacterNumber(int number);
    protected:

    private:
        int lineNumber; // numer wiersza (od 1)
        int characterNumber; // Numer znaku (od 1)
};

#endif // TEXTPOSITION_H
