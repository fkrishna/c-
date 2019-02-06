/*
    KRISHNA FARVIL

    CREDIT CARD COMPANY IDENTIFIER DETECTION
    This program can only detect 3 types of card numbers: VISA, AMEX, MASTER CARD

    Problem set from the CS50 course
    source: https://lab.cs50.io/cs50/labs/2018/fall/credit/

    NB: this code is using the CS50 library
    source: https://github.com/cs50/libcs50
*/

#include <stdio.h>
#include <math.h>
#include <cs50.h>

int checksum(long);
int getNumberOfDigits(long);
int getBIN(long);

bool isValid(long);
char* getCardProvider(long);

int main()
{
    long card_number = 0;

    card_number = get_long("CARD NUMBER: ");

    if(isValid(card_number))
        printf("%s \n", getCardProvider(card_number));
    else
        printf("\nINVALID CARD NUMBER\n");

    return 0;
}


/*
    Credit Card numbers have some structure to them.
    - American Express numbers start with 34 or 37;
    - Most MasterCard numbers start with 51, 52, 53, 54, or 55;
    - Visa numbers start with 4.
*/
char* getCardProvider(long number)
{
    int ndigit = getNumberOfDigits(number);
    int nprefix = getBIN(number);
    char *provider = NULL;

    if((ndigit == 13 || ndigit == 16) && ((nprefix / 10) == 4))
        provider = "VISA";
    else if(ndigit == 16 && (nprefix >= 51 && nprefix <= 55))
        provider = "MASTER CARD";
    else if(ndigit == 15 && (nprefix == 34 || nprefix == 37))
        provider = "AMERICAN EXPRESS";
    else
        provider = "CARD PROVIDER UNKOWN";

    return provider;
}


/*
    Get the BIN (BANK IDENTIFICATION NUMBER)
    which is the leading 6 digits of the number, but
    in this program we'll only be getting the first 2 digits
    e.g: 378282246310005
    The BIN IS 37
*/
int getBIN(long number)
{
    long base = 0;
    const int PREFIX_DIGIT = 2;
    int ndigit = getNumberOfDigits(number);

    base = pow(10, (ndigit - PREFIX_DIGIT) );

    return number / base;
}

/*
    To determine if a card is valid or not will use LUHN'S ALGORITHM
    According to Luhn’s algorithm, you can determine if a credit card number
    is syntactically valid as follows:
    - Multiply every other digit by 2, starting with the number’s second-to-last digit
    - Then add those products’ digits together.
    - Add the sum to the sum of the digits that weren’t multiplied by 2.
    - If the total modulo 10 is 0, the number is valid!

    e.g: VISA: 4003600000000014

    let’s put every other digit in parenthesis, starting with the number’s second-to-last digit:

    (4) 0 (0) 3 (6) 0 (0) 0 (0) 0 (0) 0 (0) 0 (1) 4

    - let’s multiply each of digits in parentesis by 2:
      1•2 + 0•2 + 0•2 + 0•2 + 0•2 + 6•2 + 0•2 + 4•2

    - let’s add those products’ digits (i.e., not the products themselves) together:
      2 + 0 + 0 + 0 + 0 + 1 + 2 + 0 + 8 = 13

    - let’s add that sum (13) to the sum of the digits that weren’t multiplied by 2
      (starting from the end):
      13 + 4 + 0 + 0 + 0 + 0 + 0 + 3 + 0 = 20

      the last digit in that sum (20) is a 0, so the credit card is legit!
*/

int checksum(long number)
{
    int i, sum = 0, product = 0;
    long base = 1;
    int n = getNumberOfDigits(number);

    for(i = 0; i < n / 2; i++)
    {
        base *= 100;
        product = ((number % base) / (base / 10)) * 2;
        sum += (product / 10) + (product % 10);
    }

    base = 1;
    n = (int) round( (double) n / 2.0);

    for(i = 0; i < n; i++)
    {
        base = pow(10, i+1) * pow(10, i);
        sum += (number % base) / (base / 10);
    }

    return sum;
}

/*
    According to LUNH's ALGORITHM if the
    checksum modulo 10 is 0, the number is valid!
*/
bool isValid(long number)
{
    return (checksum(number) % 10 == 0);
}

int getNumberOfDigits(long number)
{
    return log10(number) + 1;
}

