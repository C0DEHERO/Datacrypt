#include "datacrypt.h"
/*Definiert Funktionskonstanten um die Ver-/Entschluesselung zu verkuerzt schreiben zu koennen*/
#define VERSCHLUESSELUNG c += (wert + wert * wert + 79 * wert + wert * 54 * wert + 50 + 91 * wert * wert * 29 + wert)
#define ENTSCHLUESSELUNG c -= (wert + wert * wert + 79 * wert + wert * 54 * wert + 50 + 91 * wert * wert * 29 + wert)

typedef unsigned long int ULONG;

int dataencrypt( char *inputfilename, char *outputfilename, char *keyfilename )
{
    /*Geh�rt zur Fortschrittsanzeige*/
    int oneprocent;
    int progcount = 0;
    int progcount2 = 0;
    int oneprogbar = 0;
    int progbarcount = 0;
    int progbarcount2 = 0;
    int progbarcount3 = 0;
    /*Geh�rt zur Fortschrittsanzeige*/

    FILE *inputfile, *outputfile, *keyfile;
    ULONG wert;
    char c;

    if ( ( inputfile = fopen( inputfilename, "rb") ) == 0 )
    return -1;

    if ( ( outputfile = fopen( outputfilename, "w+b") ) == 0 )
    return -2;

    if ( ( keyfile = fopen( keyfilename, "r") ) == 0 )
    return -3;

    /*Geh�rt zur Fortschrittsanzeige*/
    oneprocent = datalength( inputfilename )/100;
    oneprogbar = datalength( inputfilename )/75;
    /*Geh�rt zur Fortschrittsanzeige*/

    while ( !feof(inputfile) )
    {
        c = fgetc( inputfile );
        fscanf( keyfile, " %ld", &wert );

        VERSCHLUESSELUNG;

        if ( !feof( inputfile ) )
        {
        fputc ( c, outputfile );
        fflush ( outputfile );
        }

        if ( feof( keyfile ) )
        rewind( keyfile );

        /*Geh�rt zur Fortschrittsanzeige*/
        if(progcount == oneprocent)
        {
            progcount2++;
            printf("\r%d%%|", progcount2);
            progcount = 0;
        }
        if(progbarcount3 == oneprogbar)
        {
            progbarcount++;
            while ( progbarcount != progbarcount2 )
            {
                printf(":");
                progbarcount2++;
            }
            progbarcount2 = 0;
            progbarcount3 = 0;
        }

        progcount++;
        progbarcount3++;
        /*Geh�rt zur Fortschrittsanzeige*/
    }

fclose( inputfile );
fclose( outputfile );
fclose( keyfile );

    return 0;

}



int datadecrypt( char *inputfilename, char *outputfilename, char *keyfilename)
{
    /*Geh�rt zur Fortschrittsanzeige*/
    int oneprocent;
    int progcount = 0;
    int progcount2 = 0;
    int oneprogbar = 0;
    int progbarcount = 0;
    int progbarcount2 = 0;
    int progbarcount3 = 0;
    /*Geh�rt zur Fortschrittsanzeige*/

    FILE *inputfile, *outputfile, *keyfile;
    ULONG wert;
    char c;

    if ( ( inputfile = fopen( inputfilename, "rb") ) == 0 )
    return -1;

    if ( ( outputfile = fopen( outputfilename, "w+b") ) == 0 )
    return -2;

    if ( ( keyfile = fopen( keyfilename, "r") ) == 0 )
    return -3;

    /*Geh�rt zur Fortschrittsanzeige*/
    oneprocent = datalength( inputfilename )/100;
    oneprogbar = datalength( inputfilename )/75;
    /*Geh�rt zur Fortschrittsanzeige*/

    while ( !feof(inputfile) )
    {
        c = fgetc( inputfile );
        fscanf( keyfile, " %ld", &wert );

        ENTSCHLUESSELUNG;

        if ( !feof( inputfile ) )
        {
        fputc ( c, outputfile );
        fflush ( outputfile );
        }

        if ( feof( keyfile ) )
        rewind( keyfile );

        /*Geh�rt zur Fortschrittsanzeige*/
        if(progcount == oneprocent)
        {
            progcount2++;
            printf("\r%d%%|", progcount2);
            progcount = 0;
        }
        if(progbarcount3 == oneprogbar)
        {
            progbarcount++;
            while ( progbarcount != progbarcount2 )
            {
                printf(":");
                progbarcount2++;
            }
            progbarcount2 = 0;
            progbarcount3 = 0;
        }

        progcount++;
        progbarcount3++;
        /*Geh�rt zur Fortschrittsanzeige*/
    }

fclose( inputfile );
fclose( outputfile );
fclose( keyfile );

return 0;

}



int pwdataencrypt( char *inputfilename, char *outputfilename, char *password )
{
    /*Geh�rt zur Fortschrittsanzeige*/
    int oneprocent;
    int progcount = 0;
    int progcount2 = 0;
    int oneprogbar = 0;
    int progbarcount = 0;
    int progbarcount2 = 0;
    int progbarcount3 = 0;
    /*Geh�rt zur Fortschrittsanzeige*/

    FILE *inputfile, *outputfile;
    ULONG wert;
    char c;
    int i = 0;

    if ( ( inputfile = fopen( inputfilename, "rb") ) == 0 )
    return -1;

    if ( ( outputfile = fopen( outputfilename, "w+b") ) == 0 )
    return -2;

    /*Geh�rt zur Fortschrittsanzeige*/
    oneprocent = datalength( inputfilename )/100;
    oneprogbar = datalength( inputfilename )/75;
    /*Geh�rt zur Fortschrittsanzeige*/

    while ( !feof(inputfile) )
    {
        c = fgetc( inputfile );
        wert = password[i];

        VERSCHLUESSELUNG;

        if ( !feof( inputfile ) )
        {
        fputc ( c, outputfile );
        fflush ( outputfile );
        i++;
        }

        if ( password[i] == EOS )
        i = 0;

        /*Geh�rt zur Fortschrittsanzeige*/
        if(progcount == oneprocent)
        {
            progcount2++;
            printf("\r%d%%|", progcount2);
            progcount = 0;
        }
        if(progbarcount3 == oneprogbar)
        {
            progbarcount++;
            while ( progbarcount != progbarcount2 )
            {
                printf(":");
                progbarcount2++;
            }
            progbarcount2 = 0;
            progbarcount3 = 0;
        }

        progcount++;
        progbarcount3++;
        /*Geh�rt zur Fortschrittsanzeige*/
    }

fclose( inputfile );
fclose( outputfile );

    return 0;
}


int pwdatadecrypt( char *inputfilename, char *outputfilename, char *password )
{
    /*Geh�rt zur Fortschrittsanzeige*/
    int oneprocent;
    int progcount = 0;
    int progcount2 = 0;
    int oneprogbar = 0;
    int progbarcount = 0;
    int progbarcount2 = 0;
    int progbarcount3 = 0;
    /*Geh�rt zur Fortschrittsanzeige*/

    FILE *inputfile, *outputfile;
    ULONG wert;
    char c;
    int i = 0;

    if ( ( inputfile = fopen( inputfilename, "rb") ) == 0 )
    return -1;

    if ( ( outputfile = fopen( outputfilename, "w+b") ) == 0 )
    return -2;

    /*Geh�rt zur Fortschrittsanzeige*/
    oneprocent = datalength( inputfilename )/100;
    oneprogbar = datalength( inputfilename )/75;
    /*Geh�rt zur Fortschrittsanzeige*/

    while ( !feof(inputfile) )
    {
        c = fgetc( inputfile );
        wert = password[i];

        ENTSCHLUESSELUNG;

        if ( !feof( inputfile ) )
        {
        fputc ( c, outputfile );
        fflush ( outputfile );
        i++;
        }

        if ( password[i] == EOS )
        i = 0;

        /*Geh�rt zur Fortschrittsanzeige*/
        if(progcount == oneprocent)
        {
            progcount2++;
            printf("\r%d%%|", progcount2);
            progcount = 0;
        }
        if(progbarcount3 == oneprogbar)
        {
            progbarcount++;
            while ( progbarcount != progbarcount2 )
            {
                printf(":");
                progbarcount2++;
            }
            progbarcount2 = 0;
            progbarcount3 = 0;
        }

        progcount++;
        progbarcount3++;
        /*Geh�rt zur Fortschrittsanzeige*/
    }

fclose( inputfile );
fclose( outputfile );

    return 0;
}



int chardataencrypt( char *inputfilename, char *outputfilename, char *keyfilename )
{
    /*Geh�rt zur Fortschrittsanzeige*/
    int oneprocent;
    int progcount = 0;
    int progcount2 = 0;
    int oneprogbar = 0;
    int progbarcount = 0;
    int progbarcount2 = 0;
    int progbarcount3 = 0;
    /*Geh�rt zur Fortschrittsanzeige*/

    FILE *inputfile, *outputfile, *keyfile;
    char c, wert;

    if ( ( inputfile = fopen( inputfilename, "rb") ) == 0 )
    return -1;

    if ( ( outputfile = fopen( outputfilename, "w+b") ) == 0 )
    return -2;

    if ( ( keyfile = fopen( keyfilename, "rb") ) == 0 )
    return -3;

    /*Geh�rt zur Fortschrittsanzeige*/
    oneprocent = datalength( inputfilename )/100;
    oneprogbar = datalength( inputfilename )/75;
    /*Geh�rt zur Fortschrittsanzeige*/

    while ( !feof(inputfile) )
    {
        c = fgetc( inputfile );
        wert = fgetc( keyfile );

        VERSCHLUESSELUNG;

        if ( !feof( inputfile ) )
        {
        fputc ( c, outputfile );
        fflush ( outputfile );
        }

        if ( feof( keyfile ) )
        rewind( keyfile );

        /*Geh�rt zur Fortschrittsanzeige*/
        if(progcount == oneprocent)
        {
            progcount2++;
            printf("\r%d%%|", progcount2);
            progcount = 0;
        }
        if(progbarcount3 == oneprogbar)
        {
            progbarcount++;
            while ( progbarcount != progbarcount2 )
            {
                printf(":");
                progbarcount2++;
            }
            progbarcount2 = 0;
            progbarcount3 = 0;
        }

        progcount++;
        progbarcount3++;
        /*Geh�rt zur Fortschrittsanzeige*/
    }

fclose( inputfile );
fclose( outputfile );
fclose( keyfile );

return 0;

}



int chardatadecrypt( char *inputfilename, char *outputfilename, char *keyfilename )
{
    /*Geh�rt zur Fortschrittsanzeige*/
    int oneprocent;
    int progcount = 0;
    int progcount2 = 0;
    int oneprogbar = 0;
    int progbarcount = 0;
    int progbarcount2 = 0;
    int progbarcount3 = 0;
    /*Geh�rt zur Fortschrittsanzeige*/

    FILE *inputfile, *outputfile, *keyfile;
    char c, wert;

    if ( ( inputfile = fopen( inputfilename, "rb") ) == 0 )
    return -1;

    if ( ( outputfile = fopen( outputfilename, "w+b") ) == 0 )
    return -2;

    if ( ( keyfile = fopen( keyfilename, "rb") ) == 0 )
    return -3;

    /*Geh�rt zur Fortschrittsanzeige*/
    oneprocent = datalength( inputfilename )/100;
    oneprogbar = datalength( inputfilename )/75;
    /*Geh�rt zur Fortschrittsanzeige*/

    while ( !feof(inputfile) )
    {
        c = fgetc( inputfile );
        wert = fgetc( keyfile );

        ENTSCHLUESSELUNG;

        if ( !feof( inputfile ) )
        {
        fputc ( c, outputfile );
        fflush ( outputfile );
        }

        if ( feof( keyfile ) )
        rewind( keyfile );

        /*Geh�rt zur Fortschrittsanzeige*/
        if(progcount == oneprocent)
        {
            progcount2++;
            printf("\r%d%%|", progcount2);
            progcount = 0;
        }
        if(progbarcount3 == oneprogbar)
        {
            progbarcount++;
            while ( progbarcount != progbarcount2 )
            {
                printf(":");
                progbarcount2++;
            }
            progbarcount2 = 0;
            progbarcount3 = 0;
        }

        progcount++;
        progbarcount3++;
        /*Geh�rt zur Fortschrittsanzeige*/
    }

fclose( inputfile );
fclose( outputfile );
fclose( keyfile );

return 0;

}



int chardataencryptandconvert( char *inputfilename, char *outputfilename, char *keyfilename, char *newkeyfilename )
{
    /*Geh�rt zur Fortschrittsanzeige*/
    int oneprocent;
    int progcount = 0;
    int progcount2 = 0;
    int oneprogbar = 0;
    int progbarcount = 0;
    int progbarcount2 = 0;
    int progbarcount3 = 0;
    /*Geh�rt zur Fortschrittsanzeige*/
    /*Geh�rt zur Fortschrittsanzeige*/
    int oneprocent2;
    int progcount12 = 0;
    int progcount22 = 0;
    int progcount32 = 0;
    int progcount42 = 0;
    /*Geh�rt zur Fortschrittsanzeige*/

    FILE *inputfile, *outputfile, *keyfile, *newkeyfile;
    char c;
    ULONG wert;

    if ( ( inputfile = fopen( inputfilename, "rb") ) == 0 )
    return -1;

    if ( ( outputfile = fopen( outputfilename, "w+b") ) == 0 )
    return -2;

    if ( ( keyfile = fopen( keyfilename, "r") ) == 0 )
    return -3;

    if ( ( newkeyfile = fopen( newkeyfilename, "w+b") ) == 0 )
    return -4;

    /*Geh�rt zur Fortschrittsanzeige*/
    oneprocent = datalength( inputfilename )/100; /*F�r die Eingabedatei*/
    oneprogbar = datalength( inputfilename )/75;
    /*Geh�rt zur Fortschrittsanzeige*/
   /*Geh�rt zur Fortschrittsanzeige*/
    oneprocent2 = datalength( keyfilename )/100; /*F�r die Eingabedatei*/
    progcount32 = oneprocent2;
    progcount42 = oneprocent2 * 2;
    /*Geh�rt zur Fortschrittsanzeige*/

    while ( !feof(keyfile) )
    {
        c = 0;
        fscanf( keyfile, " %ld", &wert );

        c += wert;

        if ( !feof( keyfile ) )
        {
        fputc ( c, newkeyfile );
        fflush ( newkeyfile );
        }

        /*Geh�rt zur Fortschrittsanzeige*//*F�r Key-File*/
        if( (progcount12 >= progcount32) && (progcount12 < progcount42) )
        {
            progcount22++;
            printf("\r%d%%|", progcount22);
            progcount32 += oneprocent2;
            progcount42 += oneprocent2;
        }
        progcount12 = ftell(keyfile);
        /*Geh�rt zur Fortschrittsanzeige*/
    }
    rewind (newkeyfile);

    while ( !feof(inputfile) )
    {
        c = fgetc( inputfile );
        wert = fgetc( newkeyfile );

        VERSCHLUESSELUNG;

        if ( !feof( inputfile ) )
        {
        fputc ( c, outputfile );
        fflush ( outputfile );
        }

        if ( feof( newkeyfile ) )
        rewind( newkeyfile );

        /*Geh�rt zur Fortschrittsanzeige*//*F�r inputfile*/
        if(progcount == oneprocent)
        {
            progcount2++;
            printf("\r%d%%|", progcount2);
            progcount = 0;
        }
        if(progbarcount3 == oneprogbar)
        {
            progbarcount++;
            while ( progbarcount != progbarcount2 )
            {
                printf(":");
                progbarcount2++;
            }
            progbarcount2 = 0;
            progbarcount3 = 0;
        }

        progcount++;
        progbarcount3++;
        /*Geh�rt zur Fortschrittsanzeige*/
    }

fclose( inputfile );
fclose( outputfile );
fclose( newkeyfile );
fclose( keyfile );

return 0;

}



int convert( char *keyfilename, char *newkeyfilename )
{
    /*Geh�rt zur Fortschrittsanzeige*/
    int oneprocent;
    int progcount = 0;
    int progcount2 = 0;
    int progcount3 = 0;
    int progcount4 = 0;
    /*Geh�rt zur Fortschrittsanzeige*/

    FILE *keyfile, *newkeyfile;
    ULONG wert;
    char c;

    if ( ( keyfile = fopen( keyfilename, "r") ) == 0 )
    return -1;

    if ( ( newkeyfile = fopen( newkeyfilename, "w+b") ) == 0 )
    return -2;

    /*Geh�rt zur Fortschrittsanzeige*/
    oneprocent = datalength( keyfilename )/100; /*F�r die Eingabedatei*/
    progcount3 = oneprocent;
    progcount4 = oneprocent * 2;
    /*Geh�rt zur Fortschrittsanzeige*/

    while ( !feof(keyfile) )
    {
        c = 0;
        fscanf( keyfile, " %ld", &wert );

        c += wert;

        if ( !feof( keyfile ) )
        {
        fputc ( c, newkeyfile );
        fflush ( newkeyfile );
        }

        /*Geh�rt zur Fortschrittsanzeige*/
        if( (progcount >= progcount3) && (progcount < progcount4) )
        {
            progcount2++;
            printf("\r%d%%|", progcount2);
            progcount3 += oneprocent;
            progcount4 += oneprocent;
        }
        progcount = ftell(keyfile);

        /*Geh�rt zur Fortschrittsanzeige*/
    }

fclose( keyfile );
fclose( newkeyfile );
    return 0;
}



long datalength( char *inputfilename )
{
    FILE *inputfile;
    long tell;

    if ( (inputfile = fopen( inputfilename, "rb") ) == 0 )
        return -1;

    fseek( inputfile, 0, SEEK_END );
    tell = ftell( inputfile );
    rewind( inputfile );

    fclose( inputfile );

    return ( tell );
}


int restoreformat( char *keyfilename, char *newkeyfilename )
{
    /*Geh�rt zur Fortschrittsanzeige*/
    int oneprocent;
    int progcount = 0;
    int progcount2 = 0;
    int oneprogbar = 0;
    int progbarcount = 0;
    int progbarcount2 = 0;
    int progbarcount3 = 0;
    /*Geh�rt zur Fortschrittsanzeige*/

    FILE *keyfile, *newkeyfile;
    char c = 5;
    ULONG wert;

    if ( ( keyfile = fopen( keyfilename, "r") ) == 0 )
    return -1;

    if ( ( newkeyfile = fopen( newkeyfilename, "w+") ) == 0 )
    return -2;

    /*Geh�rt zur Fortschrittsanzeige*/
    oneprocent = datalength( keyfilename )/100;
    oneprogbar = datalength( keyfilename )/75;
    /*Geh�rt zur Fortschrittsanzeige*/

    while ( !feof(keyfile) )
    {
        wert = 0;
        c = fgetc( keyfile );

        wert += c;

        if ( !feof( keyfile ) )
        {
        fprintf(newkeyfile," %ld", wert);
        fflush ( newkeyfile );
        }

        /*Geh�rt zur Fortschrittsanzeige*/
        if(progcount == oneprocent)
        {
            progcount2++;
            printf("\r%d%%|", progcount2);
            progcount = 0;
        }
        if(progbarcount3 == oneprogbar)
        {
            progbarcount++;
            while ( progbarcount != progbarcount2 )
            {
                printf(":");
                progbarcount2++;
            }
            progbarcount2 = 0;
            progbarcount3 = 0;
        }

        progcount++;
        progbarcount3++;
        /*Geh�rt zur Fortschrittsanzeige*/
    }

fclose( keyfile );
fclose( newkeyfile );
    return 0;
}
