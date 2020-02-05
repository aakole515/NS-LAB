//Playfair cipher
#include <iostream>
using namespace std;

string encrypt(string text, int s)
{
	string result = "";
	for (int i=0;i<text.length();i++)
	{
		if (isupper(text[i]))
			result += char(int(text[i]+s-65)%26 +65);
        else
            result += char(int(text[i]+s-97)%26 +97);
	}

	return result;
}

string decrypt(string text , int s)
{
    string result = "";
	for (int i=0;i<text.length();i++)
	{
		if (isupper(text[i]))
			result += char(int(text[i]-s-65)%26 +65);
        else
            result += char(int(text[i]-s-97)%26 +97);
	}

	return result;
}
int main()
{
	string text;;
	int key;
	cout << "Enter text\n";
	cin  >> text;
	cout << "Enter key"<<endl;
	cin  >> key;
	cout << "Text : " << text;
	cout << "\nShift: " << key;
	string cipher =encrypt(text, key);
	cout << "\nCipher Text: " << cipher<<endl;
	cout << "Decrypted Text:" << decrypt(cipher,key);
	return 0;
}
