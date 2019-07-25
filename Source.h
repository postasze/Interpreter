#ifndef SOURCE_H
#define SOURCE_H

#include "header.h"
#include "TextPosition.h"

class Source
{
    public:
        Source();
        Source(string fileName);
        ~Source();
        void Error(int errorCode , TextPosition &textPosition, string mt = "", string at = "");
        int NextChar();
        const TextPosition& GetCurrentPosition() const { return currentTextPosition; }
        char Peek();

    protected:

    private:
        string fileName; // Nazwa pliku
        FILE *filePointer;
        TextPosition currentTextPosition; // Bieżąca pozycja w pliku
        int errorsTotal, errorsInLine; // Liczniki błędów
        void PrintLine(); // Druk bieżącego wiersza
        int NextLine(); // Następny wiersz
        bool bufferFilled;
        char bufferedCharacter;
};

#endif // SOURCE_H
