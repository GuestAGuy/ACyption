#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <cstdio>


using namespace std;


//This function turn an array of char bits into a char
char BtC( char* bin)
{
    int x = 0;
    for (int i = 0; i < 8; i++)
    {
        if (bin[i] == '1')
            x += pow(2,7-i);
    }
    return char(x);
}

//this function turn a char into an array of char bits.
char* CtB(char* bin, char aChar)
{
    int val = int(uint8_t(aChar));
    for(int i = 7; i>= 0 ; i--)
    {
        (val % 2) ? bin[i]= '1' : bin[i]= '0';
        val /= 2;
    }
    return bin;
}


// This function takes in a string as key, and a size 8 array of char simulating a byte, It reorders the bits based on the key. 
char* enCodeS(string key, char* bin)
{
    int key1 = key.length();
    int key2 = key[key1 - 1] % 2;
    if (key2 == 1)
    {
        for (int j = 0; j < key1; j++)
        {
            char temp = bin[0];
            for (int i = 0; i < 7; i++)
            {
                bin[i] = bin[i+1];
            }
            bin[7] = temp;
        }
    }
    if (key2 == 0)
    {
        for (int j = 0; j < key1; j++)
        {
            char temp = bin[7];
            for (int i = 7; i > 0; i--)
            {
                bin[i] = bin[i-1];
            }
            bin[0] = temp;
        }
    }
    return bin;
}

//this function decode the binary char bits back to its orignial order by the opposite process of enCodeS
char* deCodeS(string key, char* bin)
{
    int key1 = key.length();
    int key2 = key[key1 - 1] % 2;
    if (key2 == 0)
    {
        for (int j = 0; j < key1; j++)
        {
            char temp = bin[0];
            for (int i = 0; i < 7; i++)
            {
                bin[i] = bin[i + 1];
            }
            bin[7] = temp;
        }
    }
    if (key2 == 1)
    {
        for (int j = 0; j < key1; j++)
        {
            char temp = bin[7];
            for (int i = 7; i > 0; i--)
            {
                bin[i] = bin[i - 1];
            }
            bin[0] = temp;
        }
    }
    return bin;
}

//this function open two text file, take in the data from the target file,  and call the CtB function to turn chars into bits 
// that are storaged in an size 8 char array, which then being encrypted by the enCodeS function.
// then it the bits into the other text file.
void enCryptS(string key, string file_name, string eFile_name)
{ 
    ifstream file;
    ofstream eFile;
    file.open(file_name);
    eFile.open(eFile_name);
    char aChar;
    char bin[8];
    while (file >> noskipws >> aChar)
    {
        CtB(bin, aChar);
        enCodeS(key, bin);
        eFile << BtC(bin);
    }
    cout << "Encrypt Finished!" << endl;
}

//this function open two text file, take in the data from the encryped file, and decrypt by storing the bits char into an size 8 char array
//it then call the deCodeS function to decrypt the binary bits, then call the BtC function to translate the bits into a char.
//after that storage them at the other text file.
void deCryptS(string key, string eFile_name, string file_name)
{
    ofstream file;
    ifstream eFile;
    file.open(file_name);
    eFile.open(eFile_name);
    char aChar;
    string x;
    char bin[8];
    int i = 0;
    while (eFile >> noskipws >> aChar)
    {
        CtB(bin, aChar);
        file << BtC(deCodeS(key, bin));
    }
    cout << "Decrypt Finished!" << endl;
}


// driver code for encrypt
void encrypt()
{
    string responds, file_name1, file_name2, key;
    ifstream infile;
    ifstream infile2;
    cout << "\nEnter the file you want to encrypt: ";
    do
    {
        cin.ignore();
        getline(cin, file_name1);
        infile.open(file_name1);
        if (!infile)
        {
            cout << "\nUnable to locate that file, please retry. \n(enter q to leave)" << endl;
        }
    } while (file_name1 != "q" && !infile);
    infile.close();
    cout << "\nEnter the file you want to save the encrypted data in: " << endl;
    do
    {
        cin >> file_name2;
        cin.ignore();
        infile2.open(file_name2);
        if (!infile2)
        {
            cout << "\nUnable to locate that file, do you want to create a new one with that name? \n(Y/N)";
            cin >> responds;
            if (responds == "Y" || responds == "y")
            {
                ofstream file{ file_name2 };
            }
        }
    } while (file_name2 != "q" && !infile2);
    infile2.close();
    if (responds != "q")
    {
        cout << "\nEnter the key you want to use \n(you need this key to decrypt): ";
        cin >> key;
        cin.ignore();
        enCryptS(key, file_name1, file_name2);
    }
}


//driver code for decrypt.
void decrypt()
{
    string responds, file_name1, file_name2, key;
    ifstream infile;
    ifstream infile2;
    cout << "\nEnter the file you want to decrypt: ";
    do
    {
        cin.ignore();
        getline(cin, file_name1);
        infile.open(file_name1);
        if (!infile)
        {
            cout << "\nUnable to locate that file, please retry. \n(enter q to leave) :" << endl;
        }
    } while (responds != "q" && !infile);
    infile.close();
    cout << "\nEnter the file you want to save the decrypted data in: " << endl;
    do
    {
        cin >> file_name2;
        cin.ignore();
        infile2.open(file_name2);
        if (!infile2)
        {
            cout << "\nUnable to locate that file, do you want to create a new one with that name? \n(Y/N)";
            cin >> responds;
            if (responds == "Y" || responds == "y")
            {
                ofstream file{ file_name2 };
            }
        }
    } while (responds != "q" && !infile2);
    infile2.close();
    if (responds != "q")
    {
        cout << "\nEnter the key you want to use \n(the key you used to encrypt): ";
        cin >> key;
        cin.ignore();
        deCryptS(key, file_name1, file_name2);
    }
}
void driver()
{
    string responds;
    while (responds != "q")
    {
        cout << "\n\nHello, welcome to use my A Cryption app!\nDo you want to encrypt a file or decrypt a file?\n" <<
            "if you just want to leave, enter q (E/D):  ";
        cin >> responds;
        if (responds == "E" || responds == "e")
        {
            encrypt();
        }
        if (responds == "D" || responds == "d")
        {
            decrypt();
        }
    }
}


int main()
{
    enCryptS("SKey", "deText.txt", "eText.txt");
    deCryptS("FKey", "eText.txt", "deText.txt");
    //driver();      
}

