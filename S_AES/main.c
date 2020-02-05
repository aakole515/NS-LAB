#include <stdio.h>
#include <stdlib.h>
int plain_text[16]={1,1,0,1,0,1,1,1,0,0,1,0,1,0,0,0};
int cipher_text[16];
int public_key[16]={0,1,0,0,1,0,1,0,1,1,1,1,0,1,0,1};
int key[3];
//int w[6];
//int w0[8],w1[8],w2[8],w3[8],w4[8],w5[8];
const sbox_encryption[4][4]={
                            {0b1001,0b0100,0b1010,0b1011},
                            {0b1101,0b0001,0b1000,0b0101},
                            {0b0110,0b0010,0b0000,0b0011},
                            {0b1100,0b1110,0b1111,0b0111}
                            };

int ww[6][8];

void display()
{
    for(int i=0;i<6;i++)
    {printf("W[%d]\t",i);
        for(int j=0;j<8;j++)
            printf("%d",ww[i][j]);
    printf("\n");
    }
    printf("-----------------------------------------------\n");
}

void ex_or(int t1[8],int t2[8],int c)
{
    for(int i=0;i<8;i++)
        ww[c][i]=t1[i]^t2[i];
}


int rotate_nibble(int k[8],int c){
    printf("In rotate nibble----------k=------c=%d-------------------------------\n",c);
    for(int i=0;i<8;i++)
        printf("%d\t",k[i]);
    printf("\n-----------------------------------------------\n");
    for(int i=0;i<4;i++)
    {
        ww[c][i]=k[i+4];
        ww[c][i+4]=k[i];
       //k[i+4]=k[i];
    }
    for(int i=0;i<8;i++)
        printf("%d\t",ww[2][i]);
    printf("\n-----------------------------------------------\n");
    return k;
}


void sub_nibble(int k[8],int c)
{
    /*int t[8];
    for(int i =0 ;i<8 ;i++)
        t[i]=ww[2][i];*/
    int kk[8];
    kk[0]=ww[2][0];
    printf("\nIn substitute nibble\n");
        printf("----------k=------c=%d-------------------------------\n",c);
    for(int i=0;i<8;i++)
        printf("%d\t",ww[2][i]);
    printf("\n");
    for(int i=0;i<8;i++)
        printf("%d\t",kk[i]);

    for(int i=0;i<8;i=i+4)
    {

        int row=k[i]*2+k[i+1];
        int col=k[i+2]*2+k[i+3];
        printf("\n r=%d\tc=%d\n",row,col);
        int n=sbox_encryption[row][col];
        printf("\n n=%d\n",n);
        if(i==0)
        {
            for(int j=0;j<=3;j++)
            {
                int t1=n>>j;
                if(t1&1)
                    ww[c][3-j]=1;
               else
                    ww[c][3-j]=0;
            }
        }
        else
        {
           for(int j=0;j<=3;j++)
            {
                int t1=n>>j;
                if(t1&1)
                    ww[c][j+4]=1;
               else
                    ww[c][j+4]=0;
            }
        }
   }
}

void generate_key()
{
    int i;
    for(i=0;i<8;i++)
    {
        ww[0][i]=public_key[i];
        ww[1][i]=public_key[i+8];
    }
    for(i=2;i<3;i++)
    {
        if(i%2==0)
        {
            rotate_nibble(ww[i-1],i);
            display();
            sub_nibble(ww[i-1],i);
        }
        else
        {
            ex_or(ww[i-1],ww[i-2],i);
        }
    }

    display();

    /*for(int i=0;i<3;i++)
    {

    }*/


}

int main()
{
    printf("Hello world!\n");

    generate_key();
    /*for(int i=0;i<6;i++)
    {
        //for(int j=0;j<8;j++)
            printf("%d",w[i]);
    printf("\n");
    }*/
    return 0;
}
