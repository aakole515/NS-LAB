//Playfair cipher

#include <bits/stdc++.h>
#include <iostream>
using namespace std;

typedef struct{
	int row;
	int col;
}position;

char mat[5][5]; // Global Variable
int flag=0;
int flag1=0;
void generateMatrix(string key)
{
    /* flag keeps track of letters that are filled in matrix */
	/* flag = 0 -> letter not already present in matrix */
	/* flag = 1 -> letter already present in matrix */
    int flag[26] = {0};
    int x = 0, y = 0;

    /* Add all characters present in the key */
    for(int i=0; i<key.length(); i++)
    {
        if(key[i] == 'j') key[i] = 'i'; // replace j with i

        if(flag[key[i]-'a'] == 0)
        {
            mat[x][y++] = key[i];
            flag[key[i]-'a'] = 1;
        }
        if(y==5) x++, y=0;
    }

    /* Add remaining characters */
    for(char ch = 'a'; ch <= 'z'; ch++)
    {
        if(ch == 'j') continue; // don't fill j since j was replaced by i

        if(flag[ch - 'a'] == 0)
        {
            mat[x][y++] = ch;
            flag[ch - 'a'] = 1 ;
        }
        if(y==5) x++, y=0;
    }
}

/* function to add filler letter('z') */
string formatMessage(string msg)
{
    string s = "z";
    int len = msg.length();
    if(len % 2 != 0)
    {
        msg.append(s);
        flag1 =1;
    }
    return msg;
}

/* Returns the position of the character */
position getPosition(char c)
{
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
            if(c == mat[i][j])
            {
                position p = {i, j};
                return p;
            }
}

string encrypt(string message)
{
    string ctext;
    for(int i=0; i<message.length(); i+=2)    // i is incremented by 2 inorder to check for pair values
    {
		position p1 = getPosition(message[i]);
		position p2 = getPosition(message[i+1]);
        int x1 = p1.row; int y1 = p1.col;
        int x2 = p2.row; int y2 = p2.col;

        if( x1 == x2 ) // same row
        {
            ctext.append(1, mat[x1][(y1+1)%5]);
            ctext.append(1, mat[x2][(y2+1)%5]);
        }
        else if( y1 == y2 ) // same column
        {
            ctext.append(1, mat[ (x1+1)%5 ][ y1 ]);
            ctext.append(1, mat[ (x2+1)%5 ][ y2 ]);
        }
        else
        {
            ctext.append(1, mat[ x1 ][ y2 ]);
            ctext.append(1, mat[ x2 ][ y1 ]);
        }
    }
    return ctext;
}


string Decrypt(string message)
{
    string ptext;
    for(int i=0; i<message.length(); i+=2) // i is incremented by 2 inorder to check for pair values
    {
        position p1 = getPosition(message[i]);
		position p2 = getPosition(message[i+1]);
        int x1 = p1.row; int y1 = p1.col;
        int x2 = p2.row; int y2 = p2.col;

        if( x1 == x2 ) // same row
        {
            ptext.append(1, mat[x1][ --y1<0 ? 4: y1 ]);
            ptext.append(1, mat[x2][ --y2<0 ? 4: y2 ]);
        }
        else if( y1 == y2 ) // same column
        {
            ptext.append(1, mat[ --x1<0 ? 4: x1 ][y1]);
            ptext.append(1, mat[ --x2<0 ? 4: x2 ][y2]);
        }
        else
        {
            ptext.append(1, mat[ x1 ][ y2 ]);
            ptext.append(1, mat[ x2 ][ y1 ]);
        }
    }
    return ptext;
}

int main()
{
    string plaintext;
    cout << "Enter message : "; cin >> plaintext;

    int n; // number of keys
    //cout << "Enter number of keys : "; cin >> n;

    string key;
        cout<< "\nEnter key " << " : " <<endl;
        cin >> key;

        generateMatrix(key);

        cout << "Key  Matrix:" << endl;
        for(int k=0;k<5;k++)
        {
            for(int j=0;j<5;j++)
            {
                cout << mat[k][j] << "  ";
            }
            cout << endl;
        }

        cout << "Actual Message \t\t: " << plaintext << endl;

       string fmsg = formatMessage(plaintext);
       cout << "Formatted Message \t: " << fmsg << endl;
       int len = fmsg.length();
       cout<<len<<endl;

        string ciphertext = encrypt(fmsg);
        cout << "Encrypted Message \t: " << ciphertext << endl;

        string decryptmsg = Decrypt(ciphertext);
        if(flag1 == 1)
        {
            int t = decryptmsg.length();
            decryptmsg[--t]='\0';
        }
        cout<< "Decrypted Message \t: " << decryptmsg << endl;
}

/*
Enter message : welcome
Enter key  :vit
Key  Matrix:
v  i  t  a  b
c  d  e  f  g
h  k  l  m  n
o  p  q  r  s
u  w  x  y  z
Actual Message          : welcome
Formatted Message       : welcomez
8
Encrypted Message       : xdherhgx
Decrypted Message       : welcome
*/
