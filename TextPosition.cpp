#include "TextPosition.h"

//TextPosition::TextPosition()
//{
    //ctor
//}

TextPosition::~TextPosition()
{
    //dtor
}

int TextPosition::GetLineNumber()
{
    return this->lineNumber;
}

int TextPosition::GetCharacterNumber()
{
    return this->characterNumber;
}

void TextPosition::SetLineNumber(int number)
{
    this->lineNumber = number;
}

void TextPosition::SetCharacterNumber(int number)
{
    this->characterNumber = number;
}
