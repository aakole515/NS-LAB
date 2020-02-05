#include <stdio.h>
#include <stdlib.h>

int Ep=23,EPx=9,EPy=17,Gx=14,Gy=14,*Point_x,*Point_y,Px=16,Py=5,Pcount=0,k=0;

int modInverse(int a, int m)
{
	a = a%m;
	for (int x=1; x<m; x++)
	if ((a*x) % m == 1)
		return x;
}

void calculate()
{
    int count=2;
    int temp_x,temp_y;
    int delta,calc_x,calc_y;
    do
    {
        int temp=count/2;
        if(count%2==0)//2P 4P 6P 8P//P+P
        {
            int t=*(Point_x+Pcount-temp);
            calc_x=((3*t*t)+EPx)%Ep;
            calc_y=2*(*(Point_y+Pcount-temp));
           // printf("Calc_x=%d\tcalc_y=%d\n",calc_x,calc_y);
            if(calc_y<Ep)
               calc_y = modInverse(calc_y,Ep);
            else
                calc_y=calc_y% Ep;
            delta=calc_x*calc_y%Ep;
           // printf("Delta=%d\n",delta);
        }
        else
        {
            //printf("in else block\n");
            int prev_x,prev_y;
            prev_x=*(Point_x+Pcount-1);//x2
            prev_y=*(Point_y+Pcount-1);//y2
            //printf("Previous=%d\tx=%d\ty=%d\n",Pcount,prev_x,prev_y);
            int y=prev_y-Py;
            int x=prev_x-Px;
           // printf("y2-y1=%d\tx=%d\ty=%d\n",Pcount,x,y);
            //if(y>0 && y< Ep)
                //y = modInverse(y,Ep);
            //else
            //{
                y=y%Ep;
                y= y<0?y+Ep:y;
            //}
            x=modInverse(x,Ep);
            delta=x*y%Ep;
        }
        temp_x=delta*delta-(*(Point_x+Pcount-temp))- (*(Point_x+0));
        temp_y=delta*((*(Point_x+Pcount-1))-temp_x)-(*(Point_y+Pcount-1));

        temp_x=temp_x%Ep;
        temp_x= temp_x<0?temp_x+Ep:temp_x;

        temp_y=temp_y%Ep;
        temp_y= temp_y<0?temp_y+Ep:temp_y;

        printf("Point=%d\tx=%d\ty=%d\n",Pcount,temp_x,temp_y);

        *(Point_x+Pcount)=temp_x;
        *(Point_y+Pcount)=temp_y;
        Pcount++;
        count++;
        printf("count=%d\n",count);
    }while(temp_x!=Gx && temp_y!=Gy);//while(Pcount<3);

    k=count-1;
}

void key_generation()
{
    int nA,nB;
    /*printf("Generating private key for nA and nB (should be < than Ep)");
    printf("Enter nA, nB");
    scanf("%d%d",&nA,&nB);*/
    nA=9,nB=14;
    int Pa=nA*k;
    int Pb=nB*k;
    int key1=nA*Pb;
    int key2=nB*Pa;
    printf("key=%d\tkey=%d\t\n",key1,key2);
}

int main()
{
    printf("Hello world!\n");
    /*printf("Enter prime number");
    scanf("%d",&Ep);
    printf("Enter Points on the curve Ep(X,Y)\n");
    scanf("%d%d",&EPx,&EPy);
    printf("Enter Gx and Gy");
    scanf("%d%d",&Gx,&Gy);
    printf("Enter  base point P(x,y)\n");
    scanf("%d%d",&Px,&Py);*/
    //we have to find kP=Q
    printf("P=%d\tEPx=%d\tEPy=%d\tGx=%d\tGy=%d\t\n",Ep,EPx,EPy,Gx,Gy);
    Point_x=(int *)malloc(10*sizeof(int));
    Point_y=(int *)malloc(10*sizeof(int));
    *(Point_x+0)=16;
    *(Point_y+0)=5;
    //Pcount_x++;Pcount_Y++;
    Pcount++;
    calculate();


    for(int i=0;i<Pcount;i++)
    {
        printf("X=%d\t",*(Point_x+i));
        printf("Y=%d\t",*(Point_y+i));
        printf("\n");
    }

    printf("k=%d\n",k);

    key_generation();

    return 0;
}
