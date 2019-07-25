#include "Token.h"

Token::Token(TokenCategory tokenCategory, TokenType tokenType,
            TextPosition tokenPosition, string stringValue, int intValue)
{
    this->tokenCategory = tokenCategory;
    this->tokenType = tokenType;
    this->tokenPosition = tokenPosition;
    this->stringValue = stringValue;
    this->intValue = intValue;
}

Token::Token()
{
    //ctor
}

Token::~Token()
{
    //dtor
}

TokenType Token::GetTokenCode()
{
    return this->tokenType;
}

TokenCategory Token::GetTokenCategoryCode()
{
    return this->tokenCategory;
}

TextPosition Token::GetTokenPosition()
{
    return this->tokenPosition;
}

int Token::GetIntValue()
{
    return this->intValue;
}

string Token::GetStringValue()
{
    return this->stringValue;
}
