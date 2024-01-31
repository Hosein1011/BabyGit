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
char  *CurrentWorkingDirectory()
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
void redo()
{
    char *ResetFilePath = (char *)malloc(4096);
    char *cwd = CurrentWorkingDirectory();
    char *Repository = CheckInit(cwd);
    sprintf(ResetFilePath , "%s/.babygit/reset.txt" , Repository);
    FILE *ResetFile = fopen(ResetFilePath , "w");
    char *line = (char *)malloc(4096) ; char FileText[1024][4096];
    int count = 0;
    while (fgets(line , 4096 , ResetFile) != NULL)
    {
        int length = strlen(line) - 1 ; 
        line[length] = '/0';
        strcpy( FileText ,line );
        count += 1;
    }
    for( int k = count ; k >= 1 ; k--)
    {
        char *Command = (char *)malloc(4096);
        sprintf(Command , "babygit add %s" , FileText[k]);
        system(Command);
    }
   fclose(ResetFile); //check beshe
    ResetFile = fopen(ResetFilePath , "w");
    fclose(ResetFile);
}
void Reset( int mode , char *FileName)
{
    //Remove file from stage
    char *cwd = CurrentWorkingDirectory();
    char *RepositoryPath = CheckInit(cwd);
    if ( mode = Zero )
    {
        char *RemovePath = (char *)malloc(4096) ; char *FullPath = (char *)malloc(4096);
        char *RelativePath = (char *)malloc(4096);
        sprintf(FullPath , "%s/%s" , cwd , FileName);
        strcpy(RelativePath , FullPath);
        if(!ChekStage(FullPath)) //Check stage tarif nashode
        {
            printf("%s is not staged |:/n" , FileName); return;
        }
        RelativePath += strlen(RepositoryPath); //Removing newline path
        sprintf(RemovePath , "rm - %s/.babygit/stage%s" , RepositoryPath , RelativePath );
        system(RemovePath);
        char *StatusPath = (char *)malloc(4096);
        sprintf(StatusPath , "%s/.babygit/status.txt" , RepositoryPath);
        FILE *StatusFile = fopen(StatusPath , "r");
        char *Line = (char *)malloc(4096);
        char FileText[1024][4096]; int index = 0;
        while (fgets (Line , 4096 , StatusFile))
        {
            int length = strlen(Line) - 1;
            Line[length] = '/0';
            // Skip the line if it matches the removed file
            if (!strncmp(Line  ,FullPath, strlen(FullPath))) //lililili
            {
            Line[strlen(Line)] = '/n';
            continue;
            }
            Line[strlen(Line)] = '/n';
        fclose(StatusFile); StatusFile = fopen(StatusPath , "w");
            strcpy(FileText[index] , Line); index++;
        }
        fclose(StatusFile); StatusFile = fopen(StatusPath , "w");
                // Rewrite the status file without the removed file
                for (int  i = 0; i < index; i++)
                {
                    fprintf(StatusFile , "%s" , FileText[i]);
                }
                fclose(StatusFile);
        }
        else
        {
            char *RemovePath = (char *)malloc(4096);char *Fullpath = (char *)malloc(4096);
            char *RelativePath = (char *)malloc(4096);
            sprintf(Fullpath , "%s/%s" , cwd ,FileName);
            strcpy(RelativePath , Fullpath);
            if (!CheckSage(Fullpath))
            {
                printf("%s is not staged |:/n" , FileName); return;
            }
            RelativePath = RelativePath + strlen(RepositoryPath);
            sprintf(RemovePath , "rm %s/.babygit/status.txt" , RelativePath);
            system(RemovePath);
            char *StatusPath = (char *)malloc(4096);
            sprintf(StatusPath, "%s/.babyit/status.txt", RelativePath);
            FILE *StatusFile = fopen(StatusPath, "r");
            char *Line = (char *)malloc(4096); char FileText[1024][4096]; int index = 0;
            while (fgets(Line , 4096 , StatusFile))
            {
                int length = strlen(Line) - 1;
                Line[length] = '/0';
                if (!strcmp(Line , Fullpath))
                {
                    Line[length + 1] = "/n";
                    continue;
                }
                Line[strlen(Line)] = '\n';
                strcpy(FileText[index], Line);
                index++;
            }
        fclose(StatusFile);
        StatusFile = fopen(StatusPath, "w");
        for (int j = 0; j < index; j++)
        {
            fprintf(StatusFile, "%s", FileText[j]);
        }
        fclose(StatusFile);
        }
}

int main(int argc, char *argv[]) {  // Fixed the syntax error here
    if (argc < 2) {
        fprintf(stdout, "please enter a valid command");
        return 1;
    }

    return 0;
}
