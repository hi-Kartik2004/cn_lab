#include <stdio.h>
#include <math.h>
void genhamcode();
void makeerror();
void correcterror();
int h[12];
int main()
{
    int i, ch;
    printf("\n enter the message in bits\n");
    for (i = 1; i < 12; i++)
        if (i == 3 || i == 5 || i == 6 || i == 7 || i == 9 || i == 10 || i == 11)
            scanf("%d", &h[i]);
    for (i = 1; i < 12; i++)
        printf("%d", h[i]);
    genhamcode();
    printf("\n do you want to make error\n(0 or 1)\n");
    scanf("%d", &ch);
    if (ch)
    {
        makeerror();
        correcterror();
    }
    else
        printf("\n no error");
    return (0);
}
void genhamcode()
{
    int temp, i;
    temp = h[3] + h[5] + h[7] + h[9] + h[11];
    (temp % 2 != 0) ? (h[1] = 1) : (h[1] = 0);
    temp = h[3] + h[6] + h[7] + h[10] + h[11];
    (temp % 2 != 0) ? (h[2] = 1) : (h[2] = 0);
    temp = h[5] + h[6] + h[7];
    (temp % 2 != 0) ? (h[4] = 1) : (h[4] = 0);
    temp = h[9] + h[10] + h[11];
    (temp % 2 != 0) ? (h[8] = 1) : (h[8] = 0);
    printf("\n transmitted codeword is:\n");
    for (i = 1; i < 12; i++)
        printf(" %d ", h[i]);
}
void makeerror()
{
    int pos, i;
    printf("\n enter the position you want to make error\n");
    scanf("%d", &pos);
    if (h[pos] == 1)
        h[pos] = 0;
    else
        h[pos] = 1;
    printf("\n Error occured and the error codeword is\n");
    for (i = 1; i < 12; i++)
        printf(" %d ", h[i]);
}
void correcterror()
{
    int r1, r2, r4, r8, i, errpos;
    r1 = (h[1] + h[3] + h[5] + h[7] + h[9] + h[11]) % 2;
    r2 = (h[2] + h[3] + h[6] + h[7] + h[10] + h[11]) % 2;
    r4 = (h[4] + h[5] + h[6] + h[7]) % 2;
    r8 = (h[8] + h[9] + h[10] + h[11]) % 2;
    errpos = r8 * 8 + r4 * 4 + r2 * 2 + r1 * 1;
    printf("\n Error occured in pos %d\n", errpos);
    printf("\n\n............ correction starts now........\n");
    if (h[errpos] == 1)
        h[errpos] = 0;
    else
        h[errpos] = 1;
    printf("\n Original codeword is :");
    for (i = 1; i < 12; i++)
        printf(" %d ", h[i]);
}