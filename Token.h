#ifndef TOKEN_H
#define TOKEN_H

#include "header.h"
#include "TextPosition.h"

class Token
{
    public:
        Token(TokenCategory tokenCategory, TokenType tokenType,
            TextPosition tokenPosition, string stringValue = "", int intValue = 0);
        Token();
        ~Token();
        TokenType GetTokenCode();
        TokenCategory GetTokenCategoryCode();
        TextPosition GetTokenPosition();
        int GetIntValue();
        string GetStringValue();
    protected:

    private:
        TokenCategory tokenCategory; // kod kategorii tokenow leksykalnych
        TokenType tokenType; // kod tokenu leksykalnego
        TextPosition tokenPosition;
        string stringValue; // przechowuje wartosc tokena jesli string/identifier
        int intValue; // przechowuje watosc tokena jesli integer
};

#endif // TOKEN_H
