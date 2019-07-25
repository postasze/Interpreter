#include "Token.h"
#include "Source.h"
#include "Scanner.h"
#include "Parser.h"
#include "Interpreter.h"
#include <fstream>

int main() // main dla parsera
{
    //ofstream out("out.txt");
    //cout.rdbuf(out.rdbuf()); //redirect cout to out.txt!

    cout << "Interpreter" << endl;
    Source *source = new Source("/home/pawel/Desktop/projekty_Qt/Interpreter/plik.txt");
    Scanner *scanner = new Scanner(*source);
    Parser *parser = new Parser(*scanner);
    Interpreter *interpreter = new Interpreter(*parser);

    interpreter->Run();
    delete(interpreter);

    cout << "Interpretacja przebiegla pomyslnie" << endl;
    cout << "0 bledow" << endl;
    return 0;
}

/*int main() // main dla parsera
{
    cout << "Parser" << endl;
    Source *source = new Source("plik.txt");
    Scanner *scanner = new Scanner(*source);
    Parser *parser = new Parser(*scanner);

    parser->parseProgram();
    delete(parser);

    cout << "Parsowanie przebieglo pomyslnie" << endl;
    cout << "0 bledow" << endl;
    return 0;
}*/


/*int main() // main dla scannera
{
    ofstream outputStream;
    outputStream.open("plik_wyjsciowy.txt", std::ofstream::out);
    Token *token;
    cout << "Skaner" << endl;
    outputStream << "Skaner" << endl;
    Source *source = new Source("plik.txt");
    Scanner *scanner = new Scanner(*source);
    cout << "Wczytane tokeny:\n" << endl;
    outputStream << "Wczytane tokeny:\n" << endl;
    token = scanner->GetNextToken();
    while(token->GetCode() != EOT)
    {
        cout << "numer:\t" << token->GetCode() << "\tnazwa:\t" << TokenStrings[token->GetCode()];
        for(unsigned int i = 0; i < 20 - TokenStrings[token->GetCode()].length(); i++)
            cout << " ";
        cout << "linijka: " << token->GetTokenPosition().GetLineNumber() << "\t\tznak: " << token->GetTokenPosition().GetCharacterNumber() << endl;
        outputStream << "numer:\t" << token->GetCode() << "\tnazwa:\t" << TokenStrings[token->GetCode()];
        for(unsigned int i = 0; i < 20 - TokenStrings[token->GetCode()].length(); i++)
            outputStream << " ";
        outputStream << "linijka: " << token->GetTokenPosition().GetLineNumber() << "\t\tznak: " << token->GetTokenPosition().GetCharacterNumber() << endl;
        delete token;
        token = scanner->GetNextToken();
    }
    outputStream.close();
    return 0;
}*/
