#include "getpass.h"

void getpass ( char *password, const unsigned int length, char pass_char )
{
    #define MAX (length -1)
    int i = 0;
    char c = 0;
    for (  ;( (c != ' ') && (c != 13) ) && (i < MAX); i++)
    {

    c = getch();
    if ( (c == ' ') || (c == 13) || (c == '\n') )
    password[i] = EOS;
    else
    if (c != '\b')
    {
    password[i] = c;
    printf("%c", pass_char);
    }

    if (i > 0)
    if (c == '\b')
    {
    i -= 2;
    printf("\b");
    printf(" ");
    printf("\b");
    }

    }

    if (password[i] != EOS)
    password[i] = EOS;
    #undef MAX

}
