#include "getpassunix.h"

void getpassunix ( char *password, const unsigned int length )
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
    password[i] = c;

    if (i > 0)
    if (c == '\b')
    i -= 2;

    }

    if (password[i] != EOS)
    password[i] = EOS;
    #undef MAX

}
