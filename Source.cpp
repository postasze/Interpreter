#include "Source.h"

Source::Source()
{
    //ctor
}

Source::Source(string fileName)
{
    //strcpy(fileName = new char[strlen(fileName)+1], fileName);
    this->fileName = fileName;
    filePointer = fopen(fileName.c_str(), "r");
    if(!filePointer)
    {
        cout << "nie można otworzyć pliku o nazwie:\"" << fileName << "\"\n";
        exit(1);
    }
    cout << "Raport kompilacji dla pliku: \"" << fileName << "\"\n\n";
    errorsTotal = errorsInLine = 0;
    bufferFilled = false;
}

Source::~Source()
{
    cout << "\n koniec raportu. Wykrytych błędów: " << errorsTotal << endl;
    fclose(filePointer);
}

void Source::Error(int errorCode, TextPosition &textPosition, string message, string token)
{
    //errorsTotal++;
    //if(errorsInLine == 0)// Błąd #1 w wierszu
    cout << "Blad w linijce: " << textPosition.GetLineNumber()
        << " i w znaku: " << textPosition.GetCharacterNumber() << endl;
    //errorsInLine = 1;
    //cout << ScanErrors[errorCode] << endl;
    cout << message << token << endl;
}

int Source::NextChar()
{
    int character;
    if(bufferFilled)
    {
        character = bufferedCharacter;
        bufferFilled = false;
    }
    else
        character = getc(filePointer);
    if(character == 10) // LF - Line Feed - nowa linia
    {
        currentTextPosition.SetLineNumber(currentTextPosition.GetLineNumber() + 1);
        currentTextPosition.SetCharacterNumber(0);
    }
    else
        currentTextPosition.SetCharacterNumber(currentTextPosition.GetCharacterNumber() + 1);
    return character; // tutaj moze byc tez zwrocony EOF
}

char Source::Peek()
{
    bufferedCharacter = NextChar();
    bufferFilled = true;
    return bufferedCharacter;
}
