#include <stdio.h>
#include <stdlib.h>
#include<conio.h>

int const p10[10]={3,5,2,7,4,10,1,9,8,6};
int const p8[8]={6,3,7,4,8,5,10,9};
int const IP[8]={2,6,3,1,4,8,5,7};
int const IP_Inverse[8]={4,1,3,5,7,2,8,6};
int const EP[8]={4,1,2,3,2,3,4,1};
int const p4[4]={2,4,3,1};

int const s0[4][4]={{1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,3,2}};
int const s1[4][4]={{0,1,2,3},{2,0,1,3},{3,0,1,0},{2,1,0,3}};
int plain_text[8]={1,0,1,0,0,1,0,1};
int cipher_text[8];
int key[10]={0,0,1,0,0,1,0,1,1,1};
int AP10[10],AIP[10];
int LS_1[10],LS_2[10];
int key1[8];
int key2[8];
int EP4[8],S0S1[4],AP4[4];
int result1[8];


void display()
{


    //4.
    printf("\nAIP=");
    for(int i =0;i<8;i++)
        printf("%d ",AIP[i]);
    printf("\n");

    //5.
    printf("\nEP4=");
    for(int i =0;i<8;i++)
        printf("%d ",EP4[i]);
    printf("\n");

    //6.
    printf("\nResult1=");
    for(int i =0;i<8;i++)
        printf("%d ",result1[i]);
     printf("\n");


    //7.
    printf("\nS0S1=");
     for(int i =0;i<4;i++)
        printf("%d",S0S1[i]);
     printf("\n");

    //8.
    printf("\nAP4=");
     for(int i =0;i<4;i++)
        printf("%d ",AP4[i]);
     printf("\n");

     printf("-------------------------------------------------------------------------------------------------------");

}

//P10 Permutaiton
void permutation10()
{
    for(int i=0;i<10;i++)
    {
        AP10[i]=key[p10[i]-1];
    }
}
//LS1
void LS1()
{
    int temp1=AP10[0];
    int temp2=AP10[5];
    for(int i=0;i<5;i++)
    {
        AP10[i]=AP10[i+1];
        AP10[i+5]=AP10[i+6];

    }
    AP10[4]=temp1;
    AP10[9]=temp2;
    //Generate key1
    for(int i=0;i<8;i++)
    {
        key1[i]=AP10[p8[i]-1];
    }
}
//LS2

void LS2()
{
    int temp1=AP10[0];
    int temp2=AP10[1];
    int temp3=AP10[5];
    int temp4=AP10[6];
    for(int i=0;i<5;i++)
    {
        AP10[i]=AP10[i+2];
        AP10[i+5]=AP10[i+7];
    }
    AP10[3]=temp1;
    AP10[4]=temp2;
    AP10[8]=temp3;
    AP10[9]=temp4;

    //generating key2
    for(int i=0;i<8;i++)
    {
        key2[i]=AP10[p8[i]-1];
    }
}

void dec_to_binary(int temp,int i)
{
    int index=1;
    while(index>=0)
    {
        S0S1[i]=temp&1;
        index--;
        temp>>=1;
        i--;
    }
}
void expansion_permutation()
{
 //Expansion permutation of last 4 bit
    for(int i=0;i<8;i++)
    {
        EP4[i]=AIP[EP[i]-1+4];
    }

}

void calculate_S0S1()
{
    int num1=result1[0]*2+result1[3]*1;
    int num2=result1[1]*2+result1[2]*1;
    dec_to_binary(s0[num1][num2],1);
    num1=result1[4]*2+result1[7]*1;
    num2=result1[5]*2+result1[6]*1;
    dec_to_binary(s1[num1][num2],3);
}
//swap
void swap()
{
    for(int i=0;i<4;i++)
    {
        int temp1=AIP[i];
        int temp2=AIP[i+4];
        AIP[i]=temp2;
        AIP[i+4]=temp1;
    }
}

//permutation4
void permutation4()
{
    for(int i=0;i<4;i++)
    {

        AP4[i]=S0S1[p4[i]-1];
        AIP[i]=AIP[i]^AP4[i];
    }
}

//exor of expansion permutation with key1 or key2
void exor(int k[])
{
    for(int i=0;i<8;i++)
    {
        result1[i]=EP4[i]^k[i];
    }
}

//initial permutation
void initial_permutation()
{
    //Applying initial permutation
    for(int i=0;i<8;i++)
    {
        AIP[i]=plain_text[IP[i]-1];
    }

    for(int j=0;j<2;j++)
    {
        //expansion permutation
        expansion_permutation();
        //exor with key1 or 2
        if(j%2==0)
            exor(key1);
        else
            exor(key2);
        //calculate value by S0 and S1
        calculate_S0S1();
        //Apply permutation 4
        permutation4();
        if(j==0)
            swap();
        //display();
    }
}





void inverse()
{
    for(int i=0;i<8;i++)
        cipher_text[i]=AIP[IP_Inverse[i]-1];
}

void decryption()
{
     //Applying initial permutation
    /*for(int i=0;i<8;i++)
    {
        printf("ct=%d AIP[i]=%d IP=%d\n",cipher_text[i],AIP[i],IP[i]);
        AIP[i]=cipher_text[IP[i]-1];
    }*/
    //printf("\nIn decrpytion\nCipher Text=\n");
    int tmp[8];
    //expansion Permutation
    expansion_permutation();
    exor(key2);
    calculate_S0S1();
    permutation4();
    //display();
    printf("\n");
    swap();
    expansion_permutation();
    exor(key1);
    calculate_S0S1();
    permutation4();
    for(int i=0;i<8;i++)
        tmp[i]=AIP[IP_Inverse[i]-1];
    //display();
    printf("\nDecrypted Text =");
    for(int i=0;i<8;i++)
        printf("%d ",tmp[i]);
    printf("\n");

}

void keyGeneration()
{
   permutation10();
   LS1();//LS1 and generation of key1
   LS2();//LS2 and generation of key2
   //1.
    printf("\nAP10=");
    for(int i =0;i<10;i++)
        printf("%d ",AP10[i]);
    printf("\n");

    //2.
    printf("\nkey1=");
    for(int i =0;i<8;i++)
        printf("%d ",key1[i]);
    printf("\n");

    //3.
    printf("\nkey2=");
    for(int i =0;i<8;i++)
        printf("%d ",key2[i]);

     printf("\n");
     printf("-------------------------------------------------------------------------------------------------------\n");
}

int main()
{
   printf("Plain Text =");
   for(int i=0; i<8;i++)
        printf("%d ",plain_text[i]);
   printf("\nKey =");
   for(int i=0; i<8;i++)
        printf("%d ",key[i]);

   printf("\n");
   keyGeneration();
   //encryption
   initial_permutation();
   inverse();
   //display();
   printf("\nCipher Text=");
   for(int i=0;i<8;i++)
        printf("%d ",cipher_text[i]);
   printf("\n");

   decryption();
   return 0;
}
