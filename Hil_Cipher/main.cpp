#include <iostream>
using namespace std;
/*string text;
string key;
int text_len;
int keyMatrix[100][100];
char cipher[100];
int text_matrix[100];
int inveseMatrix[100][100];
//char cipher[100];
void encrypt()
{
    for(int i=0 ; i<text_len ; i++)
    {
        text_matrix[i] = text[i]%97;
    }
    /*for(int i=0 ; i<text_len ; i++)
    {
        cout << text_matrix[i] << " " ;
    }*//*
    int cnt=0;
    for(int i=0 ; i<text_len ;i++)
    {

       int temp =0;
        for(int j =0 ; j < text_len ; j++)
        {
            temp +=  text_matrix[j] * keyMatrix[j][i];
            //cout << "text[j]" << text_matrix[j] << "and " << keyMatrix[j][i] <<endl;
        }
        //cout <<"temp=" << temp <<endl;
        temp = temp % 26;
        cipher[cnt++] =temp + 97;
        temp = 0;
    }
    cout << cipher <<endl;
}

int main()
{
    cout << "Hello world!" << endl;
    cout << "Enter plain text" <<endl;
    cin >> text;
    text_len = text.length();

    cout << "Enter" << text_len << " *" <<text_len <<"key matrix" <<endl;
    //cin >> key ;
    for(int i=0 ; i< text_len ;i++)
    {
        for(int j=0 ; j<text_len ; j++)
            cin >> keyMatrix[i][j];
    }

    /*for(int i=0 ; i< text_len ;i++)
    {
        for(int j=0 ; j<text_len ; j++)
            cout << keyMatrix[i][j] << " ";
        cout <<endl;
    }*//*

    encrypt();
    determinent();

    return 0;
}*/

string text;
char cipher[2];
int keyMatrix[2][2];
int textMatrix[2];
int cipherMatrix[2];
void encryption()
{
    for(int i=0; i<2 ;i++)
        textMatrix[i] = text[i] % 97;
    int cnt =0;
    for(int i=0 ; i<2 ;i++)
    {

       int temp =0;
        for(int j =0 ; j < 2 ; j++)
        {
            temp +=  textMatrix[j] * keyMatrix[j][i];
            //cout << "text[j]" << textMatrix[j] << "and " << keyMatrix[j][i] <<endl;
        }
        //cout <<"temp=" << temp <<endl;
        temp = temp % 26;
        cipher[cnt++] =temp + 97;
        temp = 0;
    }
}

int modInverse(int a, int m)
{
    a = a%m;
    for (int x=1; x<m; x++)
       if ((a*x) % m == 1)
          return x;
}

void decryption()
{
    float det = (keyMatrix[0][0]*keyMatrix[1][1]) - (keyMatrix[0][1]*keyMatrix[1][0]);
    cout<<"det = "<<det <<endl;
    int adjMatrix[2][2];
    adjMatrix[0][0]=keyMatrix[1][1];
    adjMatrix[1][1]=keyMatrix[0][0];
    adjMatrix[0][1]= -keyMatrix[0][1];
    adjMatrix[1][0] = -keyMatrix[1][0];
   /* for(int i=0;i<2;i++)
        for(int j=0 ; j<2 ;j++)
            cout<<adjMatrix[i][j];*/
    int inverse = modInverse(det , 26);
    cout<<"Inverse = "<<inverse <<endl;
     for(int i=0;i<2;i++)
        for(int j=0 ; j<2 ;j++)
        {
            int t = adjMatrix[i][j];
            if(t<0)
                t+=26;
            adjMatrix[i][j]= (t* inverse) %26;
        }
    cout<<"Adjoint Matrix"<<endl;

    for(int i=0;i<2;i++)
    {
        for(int j=0 ; j<2 ;j++)
            cout<<adjMatrix[i][j]<<" ";
        cout<<endl;
    }

    for(int i=0; i<2 ;i++)
        cipherMatrix[i] = cipher[i] % 97;
    int cnt =0;
    cout <<"Decryption =";
    for(int i=0 ; i<2 ;i++)
    {

       int temp =0;
        for(int j =0 ; j < 2 ; j++)
        {
            temp +=  cipherMatrix[j] * adjMatrix[j][i];
            //cout << "text[j]" << cipherMatrix[j] << "and " << adjMatrix[j][i] <<endl;
        }

        temp = temp % 26;
        char ch =temp + 97;
        cout << ch;
        temp = 0;
    }



}

int main()
{
    cout<<"Hello World " <<endl;
    cout << "Enter string" <<endl;
    cin >> text ;
    //cout << text;
    cout << "Enter key matrix of [2][2]" <<endl;
    for(int i=0; i<2 ;i++)
    {
        for(int j=0; j<2 ; j++)
            cin>>keyMatrix[i][j];
    }

    encryption();
    cout <<"Cipher text =" <<cipher <<endl;
    decryption();

}
