#ifndef DATACRYPT_H
#define DATACRYPT_H

#include <stdio.h>

#include "getpassunix.h"
#include "getpass.h"

int dataencrypt( char *inputfilename, char *outputfilename, char *keyfilename );
int datadecrypt( char *inputfilename, char *outputfilename, char *keyfilename );
int pwdataencrypt( char *inputfilename, char *outputfilename, char *password );
int pwdatadecrypt( char *inputfilename, char *outputfilename, char *password );
int chardataencrypt( char *inputfilename, char *outputfilename, char *keyfilename );
int chardatadecrypt( char *inputfilename, char *outputfilename, char *keyfilename );
int chardataencryptandconvert( char *inputfilename, char *outputfilename, char *keyfilename, char *newkeyfilename );
int convert( char *keyfilename, char *newkeyfilename );
long datalength( char *inputfilename );
int restoreformat( char *keyfilename, char *newkeyfilename );
#endif
