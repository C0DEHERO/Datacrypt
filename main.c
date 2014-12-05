#ifdef __unix__
   #define clrscr() printf("\x1B[2J")
#elif __BORLANDC__ && __MSDOS__
   #include <conio.h>
#elif __WIN32__ || _MSC_VER
   #define clrscr() system("cls")
#else
   #define clrscr() printf("clrscr() - Fehler!!\n")
#endif

#include "datacrypt.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define t_length const unsigned int


void remove_newline( char* buffer, t_length laenge )
{
    int i = 0;

    while( i <= laenge )
    {
        if(buffer[i] == '\n')
        {
            buffer[i] = 0; break;
        }
        i++;
    }
}


enum option{OFF, ON};

int main(void)
{
    int bgcolor, txtcolor;
    FILE *settings;
    if ( ( settings = fopen( "settings.cfg", "r") ) == 0 )
    {
    perror("settings.cfg konnte nicht geoeffnet werden!!!\nDie Standard Einstellungen werden jetzt benutzt");
    bgcolor = 0;
    txtcolor = 7;
    }
    else
    fscanf(settings ,"%d,%d", &bgcolor, &txtcolor);

    /*Aussehen der Konsole*/
    CONSOLE_CURSOR_INFO ci = {10,FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE) , &ci);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , bgcolor*16+txtcolor);
    /*******************************************************************************/

    t_length length = 50;
    t_length laenge = 100;
    char inputfilename[laenge], outputfilename[laenge], keyfilename[laenge], newkeyfilename[laenge], password[length];
    char choice, pass_char = '*';
    int rw, clear_screen = ON;
    int show_pass_char = OFF;
    long rw2;

    puts("#############");
    puts("##Datacrypt##");
    puts("#############");

while ( 1 )
{
    printf(" Copyright danny_bautista@operamail.com \n\n");
    puts(" Waehlen Sie aus was Sie tun wollen:");
    puts(" 1 -> Encrypt (Verschluesseln)");
    puts(" 2 -> Decrypt (Entschluesseln)");
    puts(" 3 -> Encrypt with password");
    puts(" 4 -> Decrypt with password");
    puts(" 5 -> Encrypt with converted Key-File");
    puts(" 6 -> Decrypt with converted Key-File");
    puts(" 7 -> Encrypt + Convert");
    puts(" 8 -> Convert Key-File (Key-Datei konvertieren)");
    puts(" 9 -> Dateilaenge herausfinden");
    puts(" 0 -> Restore old Key-File Format");
    puts(" A -> Clear Screen ON - OFF");
    puts(" B -> Show Pass_Char ON - OFF");
    puts(" C -> Define Pass_Char");
    puts(" D -> Exit");

    choice = getch();
    fflush( stdin );

    switch(choice)
{
        case '1':
        {
            puts(" Geben Sie den Pfad der zu Verschluesselnden Datei ein:");
            fgets( inputfilename, laenge, stdin );
            fflush( stdin );
            puts(" Geben Sie den Pfad der Ausgangsdatei ein:");
            fgets( outputfilename, laenge, stdin );
            fflush( stdin );
            puts(" Geben Sie den Pfad der Key-Datei (Schluessel-Datei) ein:");
            fgets( keyfilename, laenge, stdin );
            fflush( stdin );

            remove_newline(inputfilename, laenge);
            remove_newline(outputfilename, laenge);
            remove_newline(keyfilename, laenge);

            rw = dataencrypt( inputfilename, outputfilename, keyfilename );


            if ( rw == 0 )
            puts("Datei erfolgreich Verschluesselt.");

            if ( rw == -1 )
            perror("\a\a\a!!! Fehler beim Zugriff auf die Eingabedatei !!! (1. Datei)\n");

            if ( rw == -2 )
            perror("\a\a\a!!! Fehler beim Zugriff auf die Ausgabedatei !!! (2. Datei)\n");

            if ( rw == -3 )
            perror("\a\a\a!!! Fehler beim Zugriff auf die Key-Datei !!! (3. Datei)\n");
            break;
        }
        case '2':
        {
            puts(" Geben Sie den Pfad der zu Entschluesselnden Datei ein:");
            fgets( inputfilename, laenge, stdin );
            fflush( stdin );
            puts(" Geben Sie den Pfad der Ausgangsdatei ein:");
            fgets( outputfilename, laenge, stdin );
            fflush( stdin );
            puts(" Geben Sie den Pfad der Key-Datei (Schluessel-Datei) ein:");
            fgets( keyfilename, laenge, stdin );
            fflush( stdin );

            remove_newline(inputfilename, laenge);
            remove_newline(outputfilename, laenge);
            remove_newline(keyfilename, laenge);

            rw = datadecrypt( inputfilename, outputfilename, keyfilename );

            if ( rw == 0 )
            puts("Datei erfolgreich Entschluesselt.");

            if ( rw == -1 )
            perror("\a\a\a!!! Fehler beim Zugriff auf die Eingabedatei !!! (1. Datei)\n");

            if ( rw == -2 )
            perror("\a\a\a!!! Fehler beim Zugriff auf die Ausgabedatei !!! (2. Datei)\n");

            if ( rw == -3 )
            perror("\a\a\a!!! Fehler beim Zugriff auf die Key-Datei !!! (3. Datei)\n");
            break;
        }
        case '3':
        {
            puts(" Geben Sie den Pfad der zu Verschluesselnden Datei ein:");
            fgets( inputfilename, laenge, stdin );
            fflush( stdin );
            puts(" Geben Sie den Pfad der Ausgangsdatei ein:");
            fgets( outputfilename, laenge, stdin );
            fflush( stdin );
            puts(" Geben Sie das zu benutzende Passwort ein:");
            if (show_pass_char == OFF)
            getpassunix( password, length );
            else
            if (show_pass_char == ON)
            getpass( password, length, pass_char );
            else
            {
            perror("Fehler: unzulaessiger Zustand des show_pass_char Schalters.\nBenachrichtigen Sie bitte den Autor dieser Software.");
            puts("Betaetigen Sie irgendeine Taste zum Fortfahren.");
            getch();
            }

            remove_newline(inputfilename, laenge);
            remove_newline(outputfilename, laenge);

            rw = pwdataencrypt( inputfilename, outputfilename, password );

            if ( rw == 0 )
            puts("\nDatei erfolgreich Verschluesselt.");

            if ( rw == -1 )
            perror("\n\a\a\a!!! Fehler beim Zugriff auf die Eingabedatei !!! (1. Datei)\n");

            if ( rw == -2 )
            perror("\n\a\a\a!!! Fehler beim Zugriff auf die Ausgabedatei !!! (2. Datei)\n");
            break;
        }
        case '4':
        {
            puts(" Geben Sie den Pfad der zu Entschluesselnden Datei ein:");
            fgets( inputfilename, laenge, stdin );
            fflush( stdin );
            puts(" Geben Sie den Pfad der Ausgangsdatei ein:");
            fgets( outputfilename, laenge, stdin );
            fflush( stdin );
            puts(" Geben Sie das zu benutzende Passwort ein:");
            if (show_pass_char == OFF)
            getpassunix( password, length );
            else
            if (show_pass_char == ON)
            getpass( password, length, pass_char );
            else
            {
            perror("Fehler: unzulaessiger Zustand des show_pass_char Schalters.\nBenachrichtigen Sie bitte den Autor dieser Software.");
            puts("Betaetigen Sie irgendeine Taste zum Fortfahren.");
            getch();
            }

            remove_newline(inputfilename, laenge);
            remove_newline(outputfilename, laenge);

            rw = pwdatadecrypt( inputfilename, outputfilename, password );

            if ( rw == 0 )
            puts("\nDatei erfolgreich Verschluesselt.");

            if ( rw == -1 )
            perror("\n\a\a\a!!! Fehler beim Zugriff auf die Eingabedatei !!! (1. Datei)\n");

            if ( rw == -2 )
            perror("\n\a\a\a!!! Fehler beim Zugriff auf die Ausgabedatei !!! (2. Datei)\n");
            break;
        }
        case '5':
        {
            puts(" Geben Sie den Pfad der zu Verschluesselnden Datei ein:");
            fgets( inputfilename, laenge, stdin );
            fflush( stdin );
            puts(" Geben Sie den Pfad der Ausgangsdatei ein:");
            fgets( outputfilename, laenge, stdin );
            fflush( stdin );
            puts(" Geben Sie den Pfad der Key-Datei (Schluessel-Datei) ein:");
            fgets( keyfilename, laenge, stdin );
            fflush( stdin );

            remove_newline(inputfilename, laenge);
            remove_newline(outputfilename, laenge);
            remove_newline(keyfilename, laenge);

            rw = chardataencrypt( inputfilename, outputfilename, keyfilename );

            if ( rw == 0 )
            puts("Datei erfolgreich Verschluesselt.");

            if ( rw == -1 )
            perror("\a\a\a!!! Fehler beim Zugriff auf die Eingabedatei !!! (1. Datei)\n");

            if ( rw == -2 )
            perror("\a\a\a!!! Fehler beim Zugriff auf die Ausgabedatei !!! (2. Datei)\n");

            if ( rw == -3 )
            perror("\a\a\a!!! Fehler beim Zugriff auf die Key-Datei !!! (3. Datei)\n");
            break;
        }
        case '6':
        {
            puts(" Geben Sie den Pfad der zu Entschluesselnden Datei ein:");
            fgets( inputfilename, laenge, stdin );
            fflush( stdin );
            puts(" Geben Sie den Pfad der Ausgangsdatei ein:");
            fgets( outputfilename, laenge, stdin );
            fflush( stdin );
            puts(" Geben Sie den Pfad der Key-Datei (Schluessel-Datei) ein:");
            fgets( keyfilename, laenge, stdin );
            fflush( stdin );

            remove_newline(inputfilename, laenge);
            remove_newline(outputfilename, laenge);
            remove_newline(keyfilename, laenge);

            rw = chardatadecrypt( inputfilename, outputfilename, keyfilename );

            if ( rw == 0 )
            puts("Datei erfolgreich Entschluesselt.");

            if ( rw == -1 )
            perror("\a\a\a!!! Fehler beim Zugriff auf die Eingabedatei !!! (1. Datei)\n");

            if ( rw == -2 )
            perror("\a\a\a!!! Fehler beim Zugriff auf die Ausgabedatei !!! (2. Datei)\n");

            if ( rw == -3 )
            perror("\a\a\a!!! Fehler beim Zugriff auf die Key-Datei !!! (3. Datei)\n");
            break;
        }
        case '7':
        {
            puts(" Geben Sie den Pfad der zu Verschluesselnden Datei ein:");
            fgets( inputfilename, laenge, stdin );
            fflush( stdin );
            puts(" Geben Sie den Pfad der Ausgangsdatei ein:");
            fgets( outputfilename, laenge, stdin );
            fflush( stdin );
            puts(" Geben Sie den Pfad der Key-Datei (Schluessel-Datei) ein:");
            fgets( keyfilename, laenge, stdin );
            puts(" Gebem Sie den Pfad der neuen Key-Datei (schluessel-Datei) ein:");
            fgets( newkeyfilename, laenge, stdin );
            fflush( stdin );

            remove_newline(inputfilename, laenge);
            remove_newline(outputfilename, laenge);
            remove_newline(keyfilename, laenge);
            remove_newline(newkeyfilename, laenge);

            rw = chardataencryptandconvert( inputfilename, outputfilename, keyfilename, newkeyfilename );

            if ( rw == 0 )
            puts("Datei erfolgreich Verschluesselt.");

            if ( rw == -1 )
            perror("\a\a\a!!! Fehler beim Zugriff auf die Eingabedatei !!! (1. Datei)\n");

            if ( rw == -2 )
            perror("\a\a\a!!! Fehler beim Zugriff auf die Ausgabedatei !!! (2. Datei)\n");

            if ( rw == -3 )
            perror("\a\a\a!!! Fehler beim Zugriff auf die Key-Datei !!! (3. Datei)\n");

            if ( rw == -4 )
            perror("\a\a\a!!! Fehler beim Zugriff auf die neue Key-Datei !!! (4. Datei)\n");
            break;
        }
        case '8':
        {
            puts(" Geben Sie den Pfad der Key-Datei (Schluessel-Datei) ein:");
            fgets ( keyfilename, laenge, stdin );
            puts(" Geben Sie den Pfad der neuen Key-Datei (Schluessel-Datei) ein:");
            fgets ( newkeyfilename, laenge, stdin );

            remove_newline(keyfilename, laenge);
            remove_newline(newkeyfilename, laenge);

            rw = convert( keyfilename, newkeyfilename );

            if ( rw == 0 )
            puts("Vorgang erfolgreich abgeschlossen.");

            if ( rw == -1 )
            perror("\a\a\a!!! Fehler beim Zugriff auf die Key-Datei !!!\n");

            if ( rw == -2 )
            perror("\a\a\a!!! Fehler beim Zugriff auf die Key-Datei !!!\n");

            break;
        }
        case '9':
        {
            puts(" Geben Sie den Pfad der Datei ein:");
            fflush(stdin);
            fgets( inputfilename, laenge, stdin );

            remove_newline(inputfilename, laenge);

            rw2 = datalength( inputfilename );

            if ( rw2 == -1 )
            perror("\a\a\a!!! Fehler beim Zugriff auf die Eingabedatei !!!\n");

            printf("%ld\n", rw2);
            break;
        }
        case '0':
        {
            puts(" Geben Sie den Pfad der Key-Datei (Schluessel-Datei) ein:");
            fgets ( keyfilename, laenge, stdin );
            puts(" Geben Sie den Pfad der neuen Key-Datei (Schluessel-Datei) ein:");
            fgets ( newkeyfilename, laenge, stdin );

            remove_newline(keyfilename, laenge);
            remove_newline(newkeyfilename, laenge);

            rw = restoreformat( keyfilename, newkeyfilename );

            if ( rw == 0)
            puts("Vorgang erfolgreich abgeschlossen.");

            if ( rw == -1 )
            perror("\a\a\a!!! Fehler beim Zugriff auf die Key-Datei !!!\n");

            if ( rw == -2 )
            perror("\a\a\a!!! Fehler beim Zugriff auf die neue Key-Datei!!!\n");

            break;
        }
        case 'a':
        {
            if ( clear_screen == ON )
            clear_screen = OFF;
                else
            if ( clear_screen == OFF )
            clear_screen = ON;
                else
            {
            perror("Fehler: unzulaessiger Zustand des clear_screen Schalters.\nBenachrichtigen Sie bitte den Autor dieser Software.");
            puts("Betaetigen Sie irgendeine Taste zum Fortfahren.");
            getch();
            break;
            }

            clrscr();
            continue;
        }
        case 'b':
        {
           if ( show_pass_char == ON )
            show_pass_char = OFF;
                else
            if ( show_pass_char == OFF )
            show_pass_char = ON;
                else
            {
            perror("Fehler: unzulaessiger Zustand des show_pass_char Schalters.\nBenachrichtigen Sie bitte den Autor dieser Software.");
            puts("Betaetigen Sie irgendeine Taste zum Fortfahren.");
            getch();
            }
            if ( clear_screen == ON )
            clrscr();
                else
            if ( clear_screen == OFF );
                else
            {
            perror("Fehler: unzulaessiger Zustand des clear_screen Schalters.\nBenachrichtigen Sie bitte den Autor dieser Software.");
            puts("Betaetigen Sie irgendeine Taste zum Fortfahren.");
            getch();
            break;
            }
            continue;
        }
        case 'c':
        {
            puts("Geben Sie das pass_char Zeichen ein. \n(Das Zeichen, dass waerend der Passworteingabe erscheint z.B.: *)");
            pass_char = getch();
            fflush(stdin);

            if (show_pass_char == OFF)
            {
            puts("Sie haben die pass_char zeigen Option auf OFF,\ndiese Aenderungen werden sich erst zeigen, wenn Sie diese einschalten.");
            puts("Betaetigen Sie irgendeine Taste zum Fortfahren.");
            getch();
            }
            if ( clear_screen == ON )
            clrscr();
                else
            if ( clear_screen == OFF );
                else
            {
            perror("Fehler: unzulaessiger Zustand des clear_screen Schalters.\nBenachrichtigen Sie bitte den Autor dieser Software.");
            puts("Betaetigen Sie irgendeine Taste zum Fortfahren.");
            getch();
            break;
            }
            continue;
        }
        case 'd':
        {
            return 0;
        }
        default:
        {
            perror("\a\a\aSie haben keine gueltige Auswahl getroffen.");
            break;
        }

puts("Druecken Sie irgendeine Taste um fortzufahren.");
getch();

}

if (clear_screen == ON)
clrscr();
    else
if (clear_screen == OFF);
    else
perror("Fehler: unzulaessiger Zustand des clear_screen Schalters.\nBenachrichtigen Sie bitte den Autor dieser Software.");


}
puts("\a !!!Programm beendet!!!");
return 0;
}
