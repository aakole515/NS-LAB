#include <iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

char mat[26][26];
char temp='a';

void create_matrix()
{
    for(int i=0; i<26; i++)
    {
        char temp2 = temp;
        for(int j=0; j<26; j++)
        {
            if(temp2 > 'z')
                temp2 ='a';
            mat[i][j]= temp2++;
        }
        temp++;
    }
    /*for(int i=0; i<26; i++)
    {
        //char temp2 = temp;
        for(int j=0; j<26; j++)
        {
            cout<<mat[i][j]<<" ";
        }
        cout<<endl;
    }*/
}

string encryption(string text ,string key)
{
    //cout<<text<<endl<<key<<endl;
    //string cipher;
    char * cipher ;
    cipher = (char *) malloc (sizeof(char));
    int text_len = text.length();
    //cout<<"Text Len" << text_len<<endl;
    int key_len = key.length();
    //cout<< "Key Len" <<key_len<<endl;
    int cnt =0;
    int i=0;
    for(i =0 ; i < text_len ; i++)
    {
        int t1 = text[i];
        //cout<<"t1= " <<t1<<endl;
        if(cnt == key_len)
            cnt = 0;
        int t2 = key[cnt++];
        *(cipher + i) = mat[t1-97][t2-97];
        //cout<<i;
    }
    cipher[i]='\0';
//    cout<<"Cipher len" <<cipher.length();
    return cipher;
}

void decryption(string cipher ,string key)
{
    //string text[];
    int cipher_len = cipher.length();
    int key_len = key.length();
    int cnt =0;
    int i=0;
    cout<<"\nDecrypted Text:";
   for(i =0 ; i < cipher_len ; i++)
    {
        int t1 = cipher[i];
        if(cnt == key_len)
            cnt = 0;
        int t2 = key[cnt++];
        t1=t1-t2;
        if(t1<0)
            t1=t1+26;
        cout<<mat[t1][0];
    }
}

int main()
{
    cout << "Hello world!" << endl;
    string text;
    string key;
    string cipher;
    create_matrix();
    cout << "Enter text: " << endl;
    cin >> text;
    cout << "Enter key:" <<endl;
    cin >> key;
    cipher = encryption(text , key);
    cout << "\nEncrypted Text:" << cipher;
    decryption(cipher ,key);

    return 0;
}

//hello
//hi
