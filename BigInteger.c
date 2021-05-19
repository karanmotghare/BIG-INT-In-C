#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 10

typedef struct big
{
    int number[SIZE];
    int sign;
}bigInteger;

void Init(bigInteger* big)
{
    int i;
    for(i=0;i<SIZE;i++)
    {
        big->number[i]=0;
    }
}

int lengthOfString(char* s)
{
    int i=0;
    while(s[i]!='\0')
    {
        i++;
    }
    return i;
}

int lengthOfArray(int* s)
{
    int i=0;
    while(s[i]!='\0')
    {
        i++;
    }
    return i;
}
int similarBigInt(bigInteger op1,bigInteger op2,int size)
{
   int retval,i,flag=0;
   for(i=0;i<size && flag==0;i++)
   {
       if(op1.number[i]!=op2.number[i])
       {
           flag=1;
       }
   }
   if(flag==1)
   {
       retval=0;
   }
   else{
       retval=1;
   }
   return retval;

}


void readBigInt(bigInteger* bigInt)
{
    char bigIntString[SIZE+1];
    printf("Enter large integer\n");
    scanf("%s",bigIntString);
    if(bigIntString[0]=='-')
    {
     bigInt->sign=0;   
    }
    else{
        bigInt->sign=1;
    }
    int i=strlen(bigIntString)-1;
    int j=0;
    while (i>0)
    {
        bigInt->number[SIZE-1-j]=bigIntString[i]-'0';
        i--;
        j++;
    }
    
}
void printBigInt(bigInteger* big,int size)
{
    if(big->sign==0)
    {
        printf("-");
    }
    else if(big->sign==1)
    {
        printf("+");
    }
    int i=0;
    while(big->number[i]==0)
    {
        i++;
    }
    for(;i<size;i++)
    {
        printf("%d",big->number[i]);
        
    }
    printf("\n");
}

bigInteger biggerInt(bigInteger b1,bigInteger b2,int size){
    int i=0,flag=0;
    bigInteger retval;
    
        for(i=0;i<size && flag==0;i++)
        {
            if(b1.number[i]>b2.number[i])
            {
                retval=b1;
                flag=1;
            }
            else if(b1.number[i]<b2.number[i])
            {
                retval=b2;
                flag=1;
            }
        }
    return retval;
}

void subBigInt(bigInteger* op1,bigInteger* op2,bigInteger* res,int size);



void addBigInt(bigInteger* op1,bigInteger* op2,bigInteger* res,int size){
    int i,sum,carry=0,borrow=0,diff;
    bigInteger b,temp;
    if((op1->sign==0 && op2->sign==0))
    {
        for(i=size-1;i>=0;i--)
        {
            sum=op1->number[i]+op2->number[i]+carry;
            if(sum>9)
            {
                carry=1;
                res->number[i]=sum%10;
            }
            else
            {
                res->number[i]=sum;
                carry=0;
            }
        }
        res->sign=0;

    }

    else if((op1->sign==1 && op2->sign==1))
    {
        for(i=size-1;i>=0;i--)
        {
            sum=op1->number[i]+op2->number[i]+carry;
            if(sum>9)
            {
                carry=1;
                res->number[i]=sum%10;
            }
            else
            {
                res->number[i]=sum;
                carry=0;
            }
        }
        res->sign=1;
    }
    else
    {
        b=biggerInt(*op1,*op2,SIZE);
        res->sign=b.sign;
        if(b.sign!=op1->sign)
        {
            temp=*op1;
            *op1=*op2;
            *op2=temp;

        }

        

        for(i=size-1;i>=0;i--)
        {
            if(borrow==1)
            {
                op1->number[i]--;
            }
            diff=op1->number[i]-op2->number[i];
            if(diff<0)
            {
                borrow=1;
                res->number[i]=op1->number[i] + 10 - op2->number[i];
            }
            else
            {
                res->number[i]=diff;;
                borrow=0;
            }
        }

    }



}


void subBigInt(bigInteger* op1,bigInteger* op2,bigInteger* res,int size){
    int i,diff,borrow=0;
    bigInteger big,temp;

    if((op1->sign==1 && op2->sign==0))
    {   
        op2->sign=1;
        addBigInt(op1,op2,res,SIZE);
        res->sign=1;
    }

    else if((op1->sign==0 && op2->sign==0))
    {
        addBigInt(op1,op2,res,SIZE);
        res->sign=0;
    }
    else{
        big=biggerInt(*op1,*op2,SIZE);
        if(!similarBigInt(*op1,big,SIZE))
        {
            temp=*op1;
            *op1=*op2;
            *op2=temp;
            res->sign=0;
        }
        else{
            res->sign=1;
        }

        for(i=size-1;i>=0;i--)
        {
            if(borrow==1)
            {
                op1->number[i]--;
            }
            diff=op1->number[i]-op2->number[i];
            if(diff<0)
            {
                borrow=1;
                res->number[i]=op1->number[i] + 10 - op2->number[i];
            }
            else
            {
                res->number[i]=diff;;
                borrow=0;
            }
        }
    

    }

}

void multiplyBigInt(bigInteger* b1,bigInteger* b2,bigInteger* res,int size){
    int j,i,prod,carry=0,k=0,z1=0,z2=0;
    bigInteger temp;
    Init(&temp);
    temp.sign=1;
    if(b1->sign==b2->sign)
    {
        res->sign=1;
    }
    else
    {
        res->sign=0;
    }
    for(i=size-1;i>=0;i--)
    {
        
        for(j=size-1;j>=0;j--)
        {
            prod=b1->number[j]*b2->number[i]+ carry;
            if(prod>9)
            {
                temp.number[j]=prod%10;
                carry=prod/10;
            }
            else{
                temp.number[j]=prod;
                carry=0;
            }   

        }

        //--------------------STEP 2----------------


        for(j=size-1;j>=k;j--)
        {   
            int sum=temp.number[j]+res->number[j-k]+carry;
            if(sum>9)
            {
                carry=1;
                res->number[j-k]=sum%10;
            }
            else
            {
                res->number[j-k]=sum;
                carry=0;
            }
        }
        k++;


        

    }
}

int main() {
    bigInteger big;
    bigInteger big2;
    bigInteger result;
    Init(&big);
    Init(&big2);
    Init(&result);
    readBigInt(&big);
    readBigInt(&big2);
    addBigInt(&big,&big2,&result,SIZE);
    printBigInt(&result,SIZE);
    return 0;
}