#ifndef GETPASS_H
#define GETPASS_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


#define t_length const unsigned int
#define EOS '\0'


void getpass ( char *password, const unsigned int length, char pass_char );
#endif
