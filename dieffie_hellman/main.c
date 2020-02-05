#include <stdio.h>
#include<math.h>
#include<stdlib.h>
int *set;
int count=0;


int power(int x, int y, int p)
{
    int res =1;
    x=x%p;
    while(y>0)
    {
        if(y&1)
            res=(res*x)%p;
        y=y>>1;
        x=(x*x)%p;
    }
    return res;
}

void find_Prime_Factors(int n)
{
    /**(set+0)=1;
   printf("%d\n",*(set+0));*/
   while(n%2 == 0)
   {
       *(set+count)=2;
       count++;
       n=n/2;
   }

   for(int i=3;i<sqrt(n);i=i+2)
   {
       while(n%i==0)
       {
           *(set+count)=i;
           count++;
           n=n/i;
       }
   }

   if(n>2)
   {
        *(set+count)=n;
        count++;
   }
}



int find_Primitive(int n)
{
   set=(int *)malloc(10*sizeof(int));
   /*
   *(set+0)=1;
   printf("%d\n",*(set+0));
   */
   int phi = n-1;
   find_Prime_Factors(phi);
   for(int r=2;r<=phi;r++)
   {
       int flag=0;
       for(int j=0;j<count;j++)
       {
           if((power(r,phi/(*(set+j)),n)) == 1)
           {
               flag=1;
               break;
           }
       }

       if(flag==0)
        return r;
   }

}

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

void key_Exchange(int q, int alpha, int Xa, int Xb)
{
    int Ya,Yb;
    Ya=calc_mod(alpha,Xa,q);
    Yb=calc_mod(alpha,Xb,q);
    printf("Ya=%d\n",Ya);
    printf("Yb=%d\n",Yb);
    int key_a,key_b;
    key_a=calc_mod(Yb,Xa,q);
    key_b=calc_mod(Ya,Xb,q);
    printf("key_a=%d\n",key_a);
    printf("key_b=%d\n",key_b);
}

int main()
{
    printf("Hello World\n");
    int n;
    printf("Enter prime number(Alpha):\n");
    scanf("%d",&n);
    //finding primitive root of a prime number
    int root=find_Primitive(n);
    printf("Primitive root of prime (alpha) =%d\n",root);

    //key exchange
    printf("Enter Xa and Xb\n");
    int Xa, Xb;
    scanf("%d%d",&Xa,&Xb);
    key_Exchange(n,root,Xa,Xb);
    return 0;
}


//input
/*q=353
xa=97
xb=233*/
