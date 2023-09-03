#include <cs50.h>
#include <stdio.h>

int alt_digits(long card);
int mandsum(int ld);

int main(void)
{
    long card;
    do
    {
         card = get_long("Credit Card: ");
    }
    while(card <0);
    int sumf = alt_digits(card);
    if ((sumf%10) == 0)
    {
        printf("fodase\n");
    }
    else
    {
        printf("Invalid\n");
    }
}

int alt_digits(long card)
{
    int sum = 0;
    bool altd = false;
    while(card>0)
    {
        if (altd == true){
            int altdigit = card%10;
            sum += mandsum(altdigit);
        }
        else
        {
            int altdigit = card%10;
            sum += altdigit;
        }
        card = card /10;
        altd = !altd;

    }
    return sum;
}
int mandsum(int ld){
    int n=0;
    if(ld*2>10){
         while(ld>0){
            int ld2 = ld*2%10;
            n += ld2;
            ld = ld*2%100;
            }
    }
    else{
         n+=ld*2;
    }
    return n;
    }


