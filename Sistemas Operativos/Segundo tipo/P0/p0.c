#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#define MAX_INPUT 1024
#define MAX_TOKENS 100
#define LINE_LEN 80 
#include "list.h"
/* ========= FUNCIONES DE NUESTRO SHELL ============ */

int trocear(char *string, char *parts[])
{
    int i = 1;
    if ((parts[0] = strtok(string, " \n\t")) == NULL)
        return 0;
    while ((parts[i] = strtok(NULL, " \n\t")) != NULL)
        i++;
    return i;
}

int cmd_authors(char *trozos[], int ntrozos) 
{
    int l = 0;
    int n = 0;
    if (ntrozos > 2)
    {
        printf(" ERROR. TOO MANY ARGUMENTS.\n");
        return 0;
    }
    if (ntrozos > 1)
    {
        if (strcmp(trozos[0], "-l") == 0)
        {
            l = 1;
        }
        else if (strcmp(trozos[0], "-n") == 0)
        {
            n = 1;
        }
        else
        {
            printf("Command unknown %s\n", trozos[0]);
            return 0;
        }
    }
    char *nombre1 = "Andrea Lama Muiño";
    char *nombre2 = "Pablo Longueira Failde";
    char *login1 = "a.lama1";
    char *login2 = "pablo.longueira.failde";

    if (n)
    {
        printf("%s\n%s\n", nombre1, nombre2);
    }
    else if (l)
    {
        printf("%s\n%s", login1, login2);
    }
    else
    {
        printf("NAMES: \n%s\n%s\nLOGINS: \n%s\n%s\n", nombre1, nombre2, login1, login2);
    }
    return 0;
}

int cmd_getpid(char *trozos[], int ntrozos)
{
    printf("Process : %d\n", getpid());
    return 0;
}

int cmd_getppid(char *trozos[], int ntrozos)
{
    printf("Parent Process :  %d\n", getppid());
    return 0;
}

int cmd_pwd(char *trozos[], int ntrozos)
{
    char buffer[MAX_INPUT];
    if (getcwd(buffer, MAX_INPUT) == NULL)
    {
        printf("ERROR. Directory bigger than MAX_INPUT\n");
    }
    else
        printf("%s\n", buffer);
    return 0;
}

int cmd_chdir(char *trozos[], int ntrozos) 
{
    char dir[MAX_INPUT];
    strcpy(dir, "");
    if (ntrozos > 2)
    {
        printf("ERROR. TOO MANY ARGUMENTS.\n");
        return 0;
    }
    if (ntrozos > 1)
    {
        strcpy(dir, trozos[0]);
        if (chdir(dir) != 0)
        {
            perror("ERROR");
        }
    }
    else
    {
        char buffer[MAX_INPUT];
        chdir(buffer);
        printf("%s\n", buffer);
    }
    return 0;
}
int cmd_date(char *trozos[], int ntrozos)
{
    time_t tiempo_actual;
    struct tm *tiempo_info;
    char timeString[13];
    int arraysize = sizeof(timeString);
    time(&tiempo_actual);
    tiempo_info = localtime(&tiempo_actual);
    strftime(timeString, arraysize, "%d/%m/%C", tiempo_info);
    puts(timeString);
    return 0;
}

int cmd_time(char *trozos[], int ntrozos)
{
    time_t current_time;
    struct tm *time_info;
    char timeString[9]; // space for "HH:MM:SS\0"
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(timeString, sizeof(timeString), "%T", time_info);
    puts(timeString);
    return 0;
}
/*
int cmd_historic(char *trozos[], int ntrozos) //ni idea de como hacerlo
{   
    lista l=  crearlista();
    char option[MAX_INPUT];
    if (ntrozos> 4)
    {
        printf("ERROR. TOO MANY ARGUMENTS.\n");
        return 0;
    } if (strcmp(trozos[0],"-c")==0)
    {
        removeElement(l,l->sig,ntrozos);
        return 0;
    } if (strcmp(trozos[0],"-")==0)
    {
        
    }if (strcmp(trozos[0],"-rN")==0)
    {
        
    }else
    {
        
    }
    return 0;
}
*/
int cmd_exit(char *trozos[], int ntrozos)
{
    printf("Bye!!!\n");
    return 1;
}

void printPrompt()
{
    printf("\n$\t");
}

int procesar(char *trozos[], int ntrozos)
{
    struct
    {
        char *cmd_name;
        int (*func)(char *trozos[], int ntrozos);
    } cmds[] = {
        {"authors", cmd_authors},
        {"date", cmd_date},
        {"time", cmd_time},
       // {"historic", cmd_historic},
        {"pwd", cmd_pwd},
        {"chdir", cmd_chdir},
        {"getpid", cmd_getpid},
        {"getppid", cmd_getppid},
        {"exit", cmd_exit},
        {"end", cmd_exit},
        {"quit", cmd_exit},
        {NULL, NULL}

    };

    for (int i = 0; cmds[i].cmd_name != NULL; i++)
    {
        if (strcmp(trozos[0], cmds[i].cmd_name) == 0)
        {
            return cmds[i].func((trozos + 1), ntrozos);
        }
    }
    printf("Command does not exist\n");
    return 0;
}

/* ============== MAIN ================= */
int main()
{
    char input[MAX_INPUT];
    int ntrozos;
    char *trozos[MAX_TOKENS];

    printf("WELCOME!\n");
    printf("\n");

    int running_shell = 0;

    while (!running_shell)
    {
        printPrompt();
        fgets(input, MAX_INPUT, stdin);
        ntrozos = trocear(input, trozos);
        if (ntrozos > 0)
        {
            running_shell = procesar(trozos, ntrozos);
            
        }
    }
}