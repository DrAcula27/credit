#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>

long cc; //initializes values for main()
int length, digit1, digit2, digit_temp;

long ccluhn1, ccluhn2, check1, check2, total1, total2, total; //initializes values for luhn()

bool luhn(); //initializes functions used below main.
long cctype();

int main(void)
{
    do
    {
        cc = get_long("Enter a credit card number: "); //ask user for a credit card number.
    }
    while (cc <= 0); //do while loop forces user to input a postive non-zero number.

    length = floor(log10(labs(cc))) + 1; //determines length of cc.

    if (length == 13 || length == 15 || length == 16) //test if cc is a valid card number based on length.
    {
        if (luhn(cc) == true) //runs Luhn's Algorithm with cc as input.
        {

            if (length % 2 == 1) //reassigns digit1 and digit2 for odd length cc.
            {
                digit_temp = digit2;
                digit2 = digit1;
                digit1 = digit_temp;
            }

            if (length == 13 && digit1 == 4)
            {
                printf("VISA\n");
            }
            else if (length == 15 && digit1 == 3)
            {
                if (digit2 == 4 || digit2 == 7)
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else if (length == 16)
            {
                if (digit1 == 4)
                {
                    printf("VISA\n");
                }
                else if (digit1 == 5)
                {
                    if (digit2 == 1 || digit2 == 2 || digit2 == 3 || digit2 == 4 || digit2 == 5)
                    {
                        printf("MASTERCARD\n");
                    }
                    else
                    {
                        printf("INVALID\n");
                    }
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n"); //print INVALID\n if cc is correct length but fails luhn.
        }
    }
    else
    {
        printf("INVALID\n"); //if cc is the incorrect length, "INVALID\n" is printed to the screen.
    }
}

bool luhn() //checks if cc passes Luhn's Algorithm.
{
    ccluhn1 = cc / 10; //removes last digit from cc.
    while (ccluhn1 >= 1) //iterates thru ccluhn1
    {
        check1 = ccluhn1 % 10; //isolates last digit of ccluhn1 and assigns to check1.
        digit1 = check1; //assigns check1 to digit1.
        ccluhn1 /= 100; //divides ccluhn1 by 100 to skip to new second to last digit.
        check1 *= 2; //multiplies check1 by 2.
        if (check1 > 9) //determines if check1 is greater than 9 and if so adds the digits together.
        {
            total1 = total1 + (check1 % 10);
            total1 = total1 + ((check1 / 10) % 10);
        }
        else
        {
            total1 = total1 + check1;
        }
    }

    ccluhn2 = cc; //assigns cc to ccluhn2.
    while (ccluhn2 >= 1) //iterates thru ccluhn2.
    {
        check2 = ccluhn2 % 10; //isolates last digit of ccluhn2 and assigns to check2.
        digit2 = check2; //assigns check2 to digit2.
        ccluhn2 /= 100; //divides ccluhn2 by 100 to skip to new last digit.
        total2 = total2 + check2;
    }

    total = total1 + total2;

    if (total % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}