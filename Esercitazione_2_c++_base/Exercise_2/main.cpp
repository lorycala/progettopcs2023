#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

/// \brief ImportText import the text for encryption
/// \param inputFilePath: the input file path
/// \param text: the resulting text
/// \return the result of the operation, true is success, false is error
bool ImportText(const string& inputFilePath,
                string& text);

/// \brief Encrypt encrypt the text
/// \param text: the text to encrypt
/// \param password: the password for encryption
/// \param encryptedText: the resulting encrypted text
/// \return the result of the operation, true is success, false is error
bool Encrypt(const string& text,
             const string& password,
             string& encryptedText);

/// \brief Decrypt decrypt the text
/// \param text: the text to decrypt
/// \param password: the password for decryption
/// \param decryptedText: the resulting decrypted text
/// \return the result of the operation, true is success, false is error
bool Decrypt(const string& text,
             const string& password,
             string& decryptedText);

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        cerr<< "Password shall passed to the program"<< endl;
        return -1;
    }
    string password = argv[1];   //la password la scrivo nell command line (project- command line)

    string inputFileName = "./text.txt", text;
    if (!ImportText(inputFileName, text))
    {
        cerr<< "Something goes wrong with import"<< endl;
        return -1;
    }
    else
        cout<< "Import successful: result= "<< text<< endl;

    string encryptedText;
    if (!Encrypt(text, password, encryptedText))
    {
        cerr<< "Something goes wrong with encryption"<< endl;
        return -1;
    }
    else
        cout<< "Encryption successful: result= "<< encryptedText<< endl;

    string decryptedText;
    if (!Decrypt(encryptedText, password, decryptedText) || text != decryptedText)
    {
        cerr<< "Something goes wrong with decryption"<< endl;
        return -1;
    }
    else
        cout<< "Decryption successful: result= "<< decryptedText<< endl;

    return 0;
}

bool ImportText(const string& inputFilePath,
                string& text)
{
    ifstream file;
    file.open(inputFilePath);
    string line;                          // qua sulla carta apro il file leggo e converto la stringa in text
    getline(file, line);

    text=line;
    file.close();

    return true;
}

bool Encrypt(const string& text,
             const string& password,
             string& encryptedText)

{
    unsigned int lett; // numero lettera del testo da leggere

    unsigned int j = 0; // sostanzialmente mi fa mantenere la password tutta attaccata, non considerando gli spazi, inftati j la uso nella line 99
    for (unsigned int i = 0; i < text.length(); i++)
    {      //for che mi legge il testo e lo encripta
        if (text[i] != ' ')
        {
            //si applica l'algoritmo di Vigenère -> wikipedia
            unsigned int testolettere = (text[i] - 65); //trasforma il testo shiftato in un numero da 0 a 25
            unsigned int testopassword = (password[(i-j) % password.length()] - 65); //trasforma la password shiftato in un numero da 0 a 25
            lett = ((testolettere + testopassword) % 26) + 65;  //la lettera diventa quetsa
        }
        else
            lett = ' ', j++;
        encryptedText += lett;  //scrivo l 'encrypted come lett
    }

    return true;                            //poi creo un testo nullo e aggiungo caratteri facendo la comversione alla fine del for




    return false;
}

bool Decrypt(const string& text,
             const string& password,
             string& decryptedText)     //qua fgaccio stessa cosa di encrypted ma al contrario

{
    unsigned int lett = int(' ');

    unsigned int j = 0; // inizializzo un contatore da utilizzare nel ciclo
    for (unsigned int i = 0; i < text.length(); i++)
    {
        if (text[i] != ' ')
        {
            //si applica l'algoritmo di Vigenère -> wikipedia
            unsigned int testolettere = (text[i] - 65); //trasforma il testo shiftato in un numero da 0 a 25
            unsigned int testopassword = (password[(i-j) % password.length()] - 65); //trasforma la password shiftato in un numero da 0 a 25
            lett = ((testolettere - testopassword + 26) % 26) + 65;   //% mi fa divisione modulo
        }
        else
            lett = ' ', j++;
        decryptedText += lett;
    }
    return  true;
}
