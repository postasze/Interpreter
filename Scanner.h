#ifndef SCANNER_H
#define SCANNER_H

#include "header.h"
#include "TextPosition.h"

class Source;
class Token;

class Scanner
{
    public:
        Scanner(Source &source);
        //Scanner();
        ~Scanner();
        Token* GetNextToken();// Następny token
        void ScanError(int errorCode, string mtxt = nullptr, string atxt = nullptr);
        int GetLastNaturalNumber() { return NaturalNumber; }
        string GetLastIdentifier(){ return identifier; }
    protected:

    private:
        TextPosition tokenPosition; // Pozycja tokenu w tekscie
        enum { FirstLexerError = 0 };
        Source& source; // Strumień znaków
        int character; // Aktualny znak z src
        int NaturalNumber; // ostatnia stała liczbowa
        string literalConstant; // ostatnia stala znakowa
        string identifier;
        //char identifier[MAX_IDENTIFIER_LENGTH + 1];// Ostatni ident
        void NextCharacter();
        bool SkipWhiteSpace();
        bool SkipComment();
        void SkipWhiteSpacesAndComments();
        Token* IdentifierOrKeyWord();
        Token* LiteralConstantToken();
        Token* NaturalNumberToken();
};

#endif // SCANNER_H
