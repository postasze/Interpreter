#include "Scanner.h"
#include "Source.h"
#include "Token.h"

Scanner::Scanner(Source &source) : source(source)
{
    NextCharacter();
}

//Scanner::Scanner()
//{
    //ctor
//}

Scanner::~Scanner()
{
    //dtor
}

void Scanner::NextCharacter()
{
    character = source.NextChar();
}

bool Scanner::SkipWhiteSpace()
{
    if(isspace(character))
    {
        NextCharacter();
        return true;
    }
    else
        return false;
}

bool Scanner::SkipComment()
{
    if(character == '/') // obsluga komentarzy
    {
        char bufferedCharacter = source.Peek();
        if(bufferedCharacter == '/') // komentarz jednolinijkowy //
            {
                NextCharacter();
                while(character != '\n')
                {
                    if(character == EOF)
                    {
                        ScanError(WrongComment);
                        return false;
                    }
                    NextCharacter();
                }
                return true;
            }
            else if(bufferedCharacter == '*') // komentarz wielolinijkowy /* */
            {
                NextCharacter();
                NextCharacter();
                while(character != '*')
                {
                    if(character == EOF)
                    {
                        ScanError(WrongComment);
                        return false;
                    }
                    NextCharacter();
                }
                NextCharacter();
                if(character != '/')
                {
                    ScanError(WrongComment);
                    return false;
                }
                else
                {
                    NextCharacter();
                    return true;
                }
            }
            else
                return false;
    }
    return false;
}

void Scanner::SkipWhiteSpacesAndComments()
{
    while(SkipWhiteSpace() || SkipComment());
}

Token* Scanner::IdentifierOrKeyWord()
{
    unsigned int hashCode;
    identifier = "";
    while(isalnum(character) || character == '_')
    {
        if(identifier.length() > MAX_IDENTIFIER_LENGTH)
        {
            ScanError(WrongIdentifier);
            return nullptr;
        }
        identifier += character;
        NextCharacter();
    }
    hashCode = hashFunction(identifier);
    if(identifier.compare(KeyWordsMap[hashCode].second) == 0)
    {
        if(identifier == "integer" || identifier == "boolean" || identifier == "matrix")
            return new Token(TypeToken, KeyWordsMap[hashCode].first, tokenPosition);
        else if(identifier == "read" || identifier == "write" ||
                identifier == "while" || identifier == "if")
            return new Token(StatementToken, KeyWordsMap[hashCode].first, tokenPosition);
        else if(identifier == "or")
            return new Token(AdditiveOperatorToken, KeyWordsMap[hashCode].first, tokenPosition);
        else if(identifier == "div" || identifier == "mod" || identifier == "and")
            return new Token(MultiplicativeOperatorToken, KeyWordsMap[hashCode].first, tokenPosition);
        else
            return new Token(OtherToken, KeyWordsMap[hashCode].first, tokenPosition);
    }
    else
        return new Token(OtherToken, Identifier, tokenPosition, identifier);
}

Token* Scanner::LiteralConstantToken()
{
    if(character != '"')
    {
        ScanError(WrongLiteralConstant);
        return nullptr;
    }
    NextCharacter();
    while(character != '"')
    {
        if(character == EOF)
        {
            ScanError(WrongLiteralConstant);
            return nullptr;
        }
        if(character == '\\') // jeden backslash
        {
            NextCharacter();
            if(character == '"')
                literalConstant += '"';
            else if(character == '\\')
                literalConstant += '\\';
            else
                literalConstant += '\\' + character;
        }
        else
            literalConstant += character;
        NextCharacter();
    }
    return new Token(OtherToken, LiteralConstant, tokenPosition, literalConstant);
}

Token* Scanner::NaturalNumberToken()
{
    long number = 0;
    bool tooBig = false;
    while(isdigit(character) && !tooBig)
    {
        number = number * 10 + (character - '0');
        tooBig = number > INT_MAX;
        NextCharacter();
    }
    if(tooBig)
    {
        ScanError(NaturalNumberTooBig);
        return nullptr;
    }
    NaturalNumber = number;
    return new Token(OtherToken, NaturalNumberConstant, tokenPosition, "", number);
}

Token* Scanner::GetNextToken() // Główna usługa scanera
{
    SkipWhiteSpacesAndComments();
    if(character == EOF)
        return new Token(OtherToken, EOT, source.GetCurrentPosition());

    tokenPosition = source.GetCurrentPosition();

    //---IDENTYFIKATOR LUB SŁOWO KLUCZOWE
    if(isalpha(character))
        return IdentifierOrKeyWord();

    if(character == '"') //---STAŁA ZNAKOWA
        return LiteralConstantToken();

    else if(isdigit(character)) //---STAŁA CAŁKOWITA (moze byc czescia ciagu liczb w macierzy)
        return NaturalNumberToken();

    switch(character)
    {
    case '+':
        NextCharacter();
        return new Token(AdditiveOperatorToken, Plus, tokenPosition);
    case '-':
        NextCharacter();
        return new Token(AdditiveOperatorToken, Minus, tokenPosition);
    case '<':
        NextCharacter();
        if(character == '=')
        {
            NextCharacter();
            return new Token(RelativeOperatorToken, LesserOrEqualOperator, tokenPosition);
        }
        else
            return new Token(RelativeOperatorToken, LesserThanOperator, tokenPosition);
    case '>':
        NextCharacter();
        if(character == '=')
        {
            NextCharacter();
            return new Token(RelativeOperatorToken, GreaterOrEqualOperator, tokenPosition);
        }
        else
            return new Token(RelativeOperatorToken, GreaterThanOperator, tokenPosition);
    case '!':
        NextCharacter();
        if(character == '=')
        {
            NextCharacter();
            return new Token(RelativeOperatorToken, InequityOperator, tokenPosition);
        }
        else
            return new Token(OtherToken, ExclamationMark, tokenPosition);
    case '=':
        NextCharacter();
        if(character == '=')
        {
            NextCharacter();
            return new Token(RelativeOperatorToken, EquationOperator, tokenPosition);
        }
        else
            return new Token(OtherToken, AssignmentOperator, tokenPosition);
    case '(':
        NextCharacter();
        return new Token(OtherToken, LeftParenthesis, tokenPosition);
    case ')':
        NextCharacter();
        return new Token(OtherToken, RightParenthesis, tokenPosition);
    case '[':
        NextCharacter();
        return new Token(OtherToken, LeftBracket, tokenPosition);
    case ']':
        NextCharacter();
        return new Token(OtherToken, RightBracket, tokenPosition);
    case '{':
        NextCharacter();
        return new Token(OtherToken, LeftCurlyBrace, tokenPosition);
    case '}':
        NextCharacter();
        return new Token(OtherToken, RightCurlyBrace, tokenPosition);
    case '*':
        NextCharacter();
        return new Token(MultiplicativeOperatorToken, Multiplication, tokenPosition);
    case '/':
        NextCharacter();
        return new Token(MultiplicativeOperatorToken, Division, tokenPosition);
    case '^':
        NextCharacter();
        return new Token(MultiplicativeOperatorToken, Exponentiation, tokenPosition);
    case ':':
        NextCharacter();
        return new Token(PunctuationToken, Colon, tokenPosition);
    case ';':
        NextCharacter();
        return new Token(PunctuationToken, Semicolon, tokenPosition);
    case '.':
        NextCharacter();
        return new Token(PunctuationToken, Period, tokenPosition);
    case ',':
        NextCharacter();
        return new Token(PunctuationToken, Comma, tokenPosition);
    case '@':
        NextCharacter();
        return new Token(OtherToken, At, tokenPosition);
    case '$':
        NextCharacter();
        return new Token(OtherToken, Dollar, tokenPosition);
    case '%':
        NextCharacter();
        return new Token(MultiplicativeOperatorToken, Percent, tokenPosition);
    default:
        NextCharacter();
        return new Token(OtherToken, Others, tokenPosition);
    }
}

void Scanner::ScanError(int errorCode, string message, string token)
{
    if(message.length() > 0)
        source.Error(errorCode, tokenPosition, message, token);
    else
        source.Error(errorCode, tokenPosition, ScanErrors[errorCode]);
}
