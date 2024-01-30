
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
void CreatConfig(int IsGlobal , char*mode , char*Data)
    {
        if (IsGlobal)
        {
            char path[]= ; // path chi bashe ?
            DIR *Direction = opendir(path);
            if (Direction = NULL)
            {
                mkdir(path);
                if(strcmp( mode , "usrename") != 0) 
                {
                FILE *username = fopen(path/username.txt) //path eslah she
                fprintf(username.txt , %s , Data);
                fclose(username);
                }
            }

        }

    }

int main(argc , char *argv[])
{
    if ( argc < 2)
    {
        fprintf(stdout , "please enter a valid command");
        return 1;
    }


    return 0;
}