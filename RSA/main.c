#include <stdio.h>
#include <stdlib.h>

int gcd(int num1, int num2)
{
    int result;
    for(int i=1;i<=num1&&i<=num2;i++)
    {
        if(num1%i==0 && num2%i==0)
            result=i;
    }

    printf("Gcd of %d and %d is %d\n",num1,num2,result);
    return result;
}

//finding value of e such that gcd(e,phi)=1
int find_e(int e, int phi)
{
    for(e=2;e<phi;e++)
        if(gcd(e,phi)==1)
            break;
    return e;
}

//for finding value of d
int modular_multiplicative_inverse(int no, int mod)
{
    no=no%mod;
    for(int i=1;i<mod;i++)
        if((no*i)%mod==1)
            return i;
}

//modular arithmetic
int calc_mod(int m, int e, int n)
{
    int  x=1,y=m;
    while(e>0)
    {
        if (e % 2 == 1)
			x = (x * y) % n;
		y = (y * y) % n;
		e /= 2;
    }
    return x%n;
}

int main()
{
    printf("Hello world\n");
    int p,q,n,phi, e, m,d;
    printf("Enter two  prime numbers\n");
    scanf("%d%d",&p,&q);
    printf("Enter message\n");
    scanf("%d",&m);
    n=p*q;
    phi=(p-1)*(q-1);

    //determing e
    e=find_e(e,phi);

    //finding e using modular multiplicative inverse method
    d=modular_multiplicative_inverse(e,phi);

    //encryption
    int cipher_text= calc_mod(m,e,n);
    //decryption
    int plain_text=calc_mod(cipher_text,d,n);

    printf("n=%d,phi=%d\n",n,phi);
    printf("Encrypted data=%d\n",cipher_text);
    printf("Decrypted data=%d\n",plain_text);
}
/*
17
11
88
*/
