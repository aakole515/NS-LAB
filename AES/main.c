#include <stdio.h>
#include <stdlib.h>
#include<math.h>
int plain_text[16]={1,1,0,1,0,1,1,1,0,0,1,0,1,0,0,0};
int cipher_text[16];
int public_key[16]={0,1,0,0,1,0,1,0,1,1,1,1,0,1,0,1};
int key0[16],key1[16],key2[16];
int temp[16];
int const1[8]={1,0,0,0,0,0,0,0};
int me[2][2]={{0b0001,0b0100},{0b0100,0b0001}};
int mix_column_metrix[2][2];
//int const1[8]=[0,0,1,1,0,0,0,0];
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
    {
        printf("W[%d]\t",i);
        for(int j=0;j<8;j++)
            printf("%d ",ww[i][j]);
        printf("\n");
    }
    printf("-----------------------------------------------\n");
}

void ex_or(int t1[8],int t2[8],int c)
{
    for(int i=0;i<8;i++)
        ww[c][i]=t1[i]^t2[i];
}
 int binary[4];
int  convert_to_binary(int n1,int n2,int w_count)
{

    for(int i=3;i>=0;i--)
    {
        int t1=n1>>i;
        int t2=n2>>i;
        if(t1&1)
             ww[w_count][3-i]=1;
             //binary[3-i]=1;
        else
            ww[w_count][3-i]=0;
           // binary[3-i]=0;
        if(t2&1)
             ww[w_count][7-i]=1;
             //binary[3-i]=1;

        else
            ww[w_count][7-i]=0;
          // binary[3-i]=0;
    }
    //printf("\n n = %d",n);
    return binary;
}


int substitute_nibble(int temp[])
{
    int temp3[4]={0,0,0,0};
    int temp2[16];
    printf("\n IN substitute nibble\n");
    for(int i=0;i<16;i=i+4)
    {
        int t1 = temp[i];
        int t2 = temp[i+1];
        int t3 = temp[i+2];
        int t4 = temp[i+3];
       // printf("t1=%d , t2=%d ,t3=%d, t4=%d\n",t1,t2,t3,t4);
        int row = t1*2+t2*1;
        int col = t3*2+t4*1;
        //printf("row = %d col=%d ",row ,col);
        int temp1 = sbox_encryption[row][col];
        printf("Temp 1 = %d\n",temp1);
        int cnt =0;
        //printf("i=%d",i);
        for (int c = 3; c >= 0; c--)
        {
            int k = temp1 >> c;

            if (k & 1)
            {
                //printf("1");
                temp3[cnt]=1;
                temp2[cnt]=1;
            }

            else
            {
                //printf("0");
                temp3[cnt]=0;
                temp2[cnt]=0;
                //temp[4-i+1]=0;
            }
            cnt++;
           // printf("Count = %d\n",cnt);
        }
        for(int i=0;i<4;i++)
            printf("%d ",temp3[i]);
        printf("\n");
        printf("\n");
    }

   printf("Temmp2\n");
        for(int i=0 ;i<16 ;i++)
            printf("%d ",temp2[i]);
        printf("\n");
    return temp;
}

void key_generator()
{
    //int counter=2;

    for(int i=0;i<8;i++)
    {

        ww[0][i]=public_key[i];
        ww[1][i]=public_key[i+8];
    }
    for(int i=2;i<6;i++)
    {
        if(i%2==0)
        {
            int j=0;
            int row=ww[i-1][j+4]*2+ww[i-1][j+5];
            int col=ww[i-1][j+6]*2+ww[i-1][j+7];
            int n1=sbox_encryption[row][col];
            row=ww[i-1][j]*2+ww[i-1][j+1];
            col=ww[i-1][j+2]*2+ww[i-1][j+3];
            int n2=sbox_encryption[row][col];
            printf("\nn1=%d,n2=%d\n",n1,n2);
            convert_to_binary(n1,n2,i);
            /*for(j=0;j<4;j++)
                ww[i][j]=binary[j];*/
            ex_or(const1,ww[i],i);
            ex_or(ww[i-2],ww[i],i);
            const1[0]=0;const1[2]=1;const1[3]=1;
        }
        else
            ex_or(ww[i-1],ww[i-2],i);

    }
    display();
    for(int i=0;i<8;i++)
    {
        key0[i]=ww[0][i];
        key0[i+8]=ww[1][i];
        key1[i]=ww[2][i];
        key1[i+8]=ww[3][i];
        key2[i]=ww[4][i];
        key2[i+8]=ww[5][i];
    }
    /*for(int i=0;i<16;i++)
        printf("%d ",key2[i]);*/
}

int add_round_key(int t1[],int t2[])
{
    for(int i=0;i<16;i++)
        temp[i]=t1[i]^t2[i];
    return temp;
}



void display_temp()
{
    for(int i=0;i<16;i++)
        printf("%d ",temp[i]);
}

void shift_row(int temp[])
{
    for(int i=0;i<4;i++)
    {
        int t=temp[i+4];
        temp[i+4]=temp[i+12];
        temp[i+12]=t;
    }
}

void mix_column()
{
    int count=0;
    int temp2=3;
    int no[4]={0,0,0,0};
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            no[i]=no[i]+pow(2,temp2--)*temp[count++];
        }
        printf("\n%d\n",no[i]);
        temp2=3;
    }
    mix_column_metrix[0][0]=no[0];
    mix_column_metrix[1][0]=no[1];
    mix_column_metrix[0][1]=no[2];
    mix_column_metrix[1][1]=no[3];
    printf("\nMix Column=");
   for(int i=0;i<2;i++)
    {
       for(int j=0;j<2;j++)
       {
           mix_column_metrix[i][j]=me[i][j]* mix_column_metrix[i][j];
           printf("%d ",mix_column_metrix[i][j]);
       }
    }
    printf("\n");
    for(int i=0;i<2;i++)
    {
       for(int j=0;j<2;j++)
       {
           //multiplication is greater than 15
           if((me[i][j]* mix_column_metrix[i][j])>0b1111)
           {
                printf("> thena 1111");
           }

           else
                printf("%d ",mix_column_metrix[i][j]);
       }
    }
}

int main()
{
    key_generator();
    add_round_key(plain_text,key0);
    printf("Add round key=");
    for(int i=0 ;i<16 ;i++)
        printf("%d ",temp[i]);
    printf("\n");
    printf("Substitute Nibble=");
    substitute_nibble(temp);
     for(int i=0 ;i<16 ;i++)
        printf("%d ",temp[i]);
    printf("\n");
    printf("Shift Row");
    shift_row(temp);
    printf("\nTemp=");
    display_temp();
    mix_column();
    printf("Hello world!\n");
    return 0;
}
