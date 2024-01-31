#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#define True 1
#define Zero 0
char *CheckInit(const char *path) {
    DIR *dir = opendir(path);
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".babygit") == 0) {
            closedir(dir);
            return path;
        }
    }
    closedir(dir);
    return NULL;
}
void CurrentWorkingDirectory(char *cwd)
{
    char *cwd;      //in voide check beshe
    char buffer[4096];
    cwd = getcwd(buffer , 4096);
    return cwd;
}
char * FindCWD( char * Data)
{
    char *fcwd = (char *)malloc(4096);
    char buffer[4096];
    char * path = (char *)malloc(4096);
    path = CheckInit(fcwd);
    fcwd = fcwd + strlen(path);////////oyyyyyyyyy
    sprintf(fcwd , "%s%s" , fcwd , Data);//
    return fcwd ;
}
void CreatConfig(int IsGlobal, char *mode, char *Data) {
    if (IsGlobal) {
        char path[] = "/mnt/e/ffproject/"; // path chi bashe ?
        DIR *Direction = opendir(path);
        if (Direction == NULL) { // Fixed the syntax error here
            mkdir(path, 0777);     // sath dastresie error midad fix kardam
            if (strcmp(mode, "username") != 0) {
                FILE *username = fopen("/mnt/e/ffproject/username.txt", "w"); // path eslah she
                fprintf(username, "%s", Data);  // Fixed the syntax error here
                fclose(username);
            } else {
                FILE *email = fopen("/mnt/e/ffproject/email.txt", "w"); // path
                fprintf(email, "%s", Data);  // Fixed the syntax error here
                fclose(email);
            }
        } else {
            if (strcmp(mode, "email") != 0) {
                FILE *email = fopen("/mnt/e/ffproject/email.txt", "w"); // path
                fprintf(email, "%s", Data);  // Fixed the syntax error here
                fclose(email);
            } else {
                FILE *username = fopen("/mnt/e/ffproject/username.txt", "w"); // path
                fprintf(username, "%s", Data);  // Fixed the syntax error here
                fclose(username);
            }
        }
        closedir(Direction);
        return;  // ?
    } else {
        char *cwd;
        char buffer[4096];
        cwd = getcwd(buffer, 4096);
        char *path = (char *)malloc(strlen(cwd) + strlen("/.babygit") + 1);  // Allocate enough memory
        strcpy(path, cwd);
        path = CheckInit(cwd);

        if (path == NULL) {  // Fixed the syntax error here
            strcat(path, "/.babygit");
            if (strcmp(mode, "username") != 0) {
                strcat(path, "/username.txt");
                FILE *prevConfig = fopen(path, "w");  // path.txt nis ?
                fprintf(prevConfig, "%s", Data);     // Fixed the syntax error here
                fclose(prevConfig);
            } else {
                strcat(path, "/email.txt");
                FILE *prevConfig = fopen(path, "w");  // path.txt?
                fprintf(prevConfig, "%s", Data);     // Fixed the syntax error here
                fclose(prevConfig);
            }
        } else {
            puts("This is not babygit's repository");
        }
    }
}
void GitInit (int mode , char *Data)
{
    char *cwd;
    char buffer[4096];
    cwd = getcwd (buffer , 4096);
if (CheckInit(cwd) != NULL)
{
    puts("This is already a  babygit repository :)");
    return;
}
else
{
    mkdir(".babygit" , "0777");
    //mkdir(".babygit/branch", 0777);
    //mkdir(".babygit/branch/master", 0777);
    //mkdir(".babygit/commits", 0777);
    //mkdir(".babygit/stage", 0777);
    //fopen(".babygit/status.txt", "w");
    //fopen(".babygit/branch/master/reset.txt", "w");
    return;
}
}
void GitAdd(int mode , char *Data)
{
    if (mode == -1) puts("This file or directory is invalid"); return;
    char *cwd ;
    char buffer[4096];
    cwd = getcwd (buffer , 4096);
    char *Repository = CheckInit (cwd);
    char *PathStats = (char *)malloc(4096);
    sprintf(PathStats , "%s/.babygit/status.txt" , Repository); //status.txt?why
    if (mode == Zero) //masir nadarim bayad ijad she
    {
        char *NewPath = (char *)malloc(4096);
        NewPath = FindCWD(Data);
        if (NewPath[0] = "/") NewPath += 1;
        chdir("/"); chdir(Repository); //chdir(".babygit/stage")
        mkdir(NewPath , 0777); chdir(cwd);
        struct dirent *fp ;
        char *path = (char *)malloc(4096);
        path = FindCWD(Data);
        DIR *direction = opendir(Data);
        if (direction == NULL) puts("directory not found :("); return;
        while ((fp = readdir(direction)) != NULL)
        {
                if (strcmp(fp->d_name , ".") == 0 ||strcmp(fp->d_name , "..") == 0)
                {
                    continue;
                }
                if (fp->d_type == DT_DIR)
                {
                    char path[4096];
                    sprintf(path , "%s/%s" , cwd , Data);
                    chdir("/");
                chdir(path);
                add(Zero, fp->d_name);
                chdir(cwd);
                }
                else if (fp->d_type == DT_REG)
            {
                char path[4096];
                sprintf(path, "%s/%s", cwd, Data);
                chdir("/");
                chdir(path);
                add(True, fp->d_name); //check beshe
                chdir(cwd);
            }
            else
            {
                printf("%s pleas enter a valid type :(\n", fp->d_name); //chera puts nis?
            }
        }
                char abs_path[4096];
        sprintf(abs_path, "%s/%s", cwd, Data);
        FILE *status = fopen(PathStats, "a"); //txt?
        fprintf(status, "%s\n", abs_path);
        fclose(status);
        return;
    }
else
{
    char FileNAme[4096];
    sprintf(FileNAme , "%s%s" , cwd , Data);
    FILE *file = fopen(FileNAme , "r");
    if ( file = NULL ) puts("can not finde the file"); return;
    char *path =(char *)malloc(4096);
    path = FindCWD(Data);
    char *Copydest = (char *)malloc(4096);
    char PathStats[4096];
    char PathABS[4096];
    sprintf(PathABS , "%s%s" , cwd , Data);
    sprintf(PathStats , "%s/.babygit/status.txt" , Repository);
    FILE *stats = fopen(PathStats , "a");
    fprintf(stats , "%s/n" , PathABS);
    sprintf(Copydest , "%s/.babygit/stage%s" , Repository , path);
    //copyfile(FileNAme , Copydest);
    Copydest = Copydest + 1 ;
    FILE *sourcefile = fopen("FileNAme.txt" , "rb");
    if (sourcefile == NULL) puts("right now your file does not exist :("); return -1; //or -1
    chdir("/"); chdir("copydest");
    FILE *Copydest = fopen("Copydest" ,  "wb");
    char buffer[1024]; size_t size;
    while ((size = fread(buffer , 1 , size , FileNAme)) > 0 )
    {
        fwrite(buffer , 1 , size , Copydest);
    }
    fclose(Copydest);
    fclose(file);
    fclose(stats);

}

}

int main(int argc, char *argv[]) {  // Fixed the syntax error here
    if (argc < 2) {
        fprintf(stdout, "please enter a valid command");
        return 1;
    }

    return 0;
}
