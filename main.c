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
//Getparrent
char *CheckInit(char *path);
int CheckSage(char *Path);
int FileDir(char *path);
int FileCounter ( char * Path);
char  *CurrentWorkingDirectory();
char * FindCWD( char * Data);
char *ChangeDir(char *path);
void StageFolder(char *path);
void CreatConfig(int IsGlobal, char *mode, char *Data);
void GitInit ();
void GitAdd(int mode , char *Data);
void redo();
void Reset( int mode , char *FileName);
void PerformCommit(int argc , char **argv);
void DisplayCommit(int argc , char **argv);






char *CheckInit(char *path)
{
    DIR *dir = opendir(path);
    struct dirent *fp;
    while ((fp = readdir(dir)) != NULL)
    {
        if (!strcmp(fp->d_name, ".babygit"))
        {
            closedir(dir);
            return path;
        }
    }
    closedir(dir);
    char *parent = malloc(strlen(path) + 1);
    strcpy(parent, path);
    GetParent(parent);
    if (strcmp(parent, "/home")) //
    {
        CheckInit(parent);
    }
    else
    {
        return NULL;
    }
}
int CheckStage(char *Path)
{
    char *StatusPath = malloc(4096);
    char *cwd = malloc(4096);
    char buffer[4096];
    cwd = getcwd(buffer , 4096);
    char *Repository = CheckInit(cwd);
    sprintf(StatusPath , "%s/.babygit/status.txt" , Repository);
    FILE *StatusFile = fopen(StatusPath , "r");
    char *Line = malloc(4096); char *FolderPath = malloc(4096); char *Temp = malloc(4096);
    strcpy(Temp , Path);
    Temp = Temp + strlen(Repository);
    sprintf(FolderPath , "%s/.babygit/stage%s" , Repository , Temp);
    DIR *Direction = opendir(FolderPath);
    while ((fgets(Line , 4096 , StatusFile)) != NULL)
    {
        Line[strlen(Line) -1] = '\0';
        if (!strncmp( Line , Path , strlen(Path)))
        {
            Line[strlen(Line)] = '\n';
            return 1;
        }

    }
    if (Direction != NULL)
    {
        return 1;
    }
    return 0 ; 
}
int FileDir(char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    if (S_ISREG(path_stat.st_mode))
    {
        return 1;
    }
    else if (S_ISDIR(path_stat.st_mode))
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
int FileCounter ( char * Path)
{
    int count = 0 ;
    struct dirent *fp;
    DIR *Direction = opendir(Path);
    while ((fp = readdir(Direction)) != NULL)
    {
        if (strcmp(fp->d_name , ".d") == 0 || strcmp(fp->d_name , "..") ==0 || strcmp(fp->d_name , ".babygit") ==0)
        {
            continue;
        }
        if (fp->d_type == DT_REG)
        {
            count++;
        }
        else if (fp->d_type == DT_DIR)
        {
            char *Path2 = malloc(4096);
            sprintf(Path2 , "%s/%s" , Path , fp->d_name);
            count += FileCounter(Path2);
        }
        return count;

    }


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
//int copyFile(char *sourcePath, char *destinationPath)
//{
  ///  destinationPath = destinationPath + 1;
    //FILE *sourceFile = fopen(sourcePath, "rb");
    //if (sourceFile == NULL)
    //{
      //  printf("File does not exist\n");
        //return -1;
    // }
    // chdir("/");
    // chdir(destinationPath);
    // FILE *destinationFile = fopen(destinationPath, "r");
    // if (destinationFile != NULL)
    // {
    //     delete the file
    //    char *rm_path = malloc(4096);
    //     sprintf(rm_path, "rm %s", destinationPath);
    //     system(rm_path);
//     }
//     destinationFile = fopen(destinationPath, "wb");
//     char buffer[1024];
//     size_t size;
//     while ((size = fread(buffer, 1, 1024, sourceFile)) > 0)
//     {
//         fwrite(buffer, 1, size, destinationFile);
//     }
//     fclose(sourceFile);
//     return 0;
// }
char *ChangeDir(char *path)
{
    // take a directory and change directory to parent of it and tokenize the last part of path and return it
    char *LastSlash = strrchr(path, '/');
    if (LastSlash == NULL)
    {
        return path; 
    }
    *LastSlash = '\0';
    char *Token = strtok(path, "/");
    while (Token != NULL)
    {
        chdir(Token);
        Token = strtok(NULL, "/");
    }
    return LastSlash + 1;
}
void StageFolder(char *path)
{
    char NewPath[4096];
    strcpy(NewPath, path);
    char *cwd = CurrentWorkingDirectory();
    char *Repository = CheckInit(cwd);
    char *loc = strrchr(NewPath, '/');
    *loc = '\0';
    char *token = strtok(NewPath, "/");
    chdir("/");
    chdir(Repository);
    chdir("./stage");
    while (token != NULL)
    {
        mkdir(token , 0777);
        chdir(token);
        token = strtok(NULL, "/");
    }
    chdir(cwd);
}
void CreatConfig(int IsGlobal, char *mode, char *Data) { //;)
    if (IsGlobal) 
    {
        char path[] = "/mnt/e/ffproject/.babygitconfig"; // path chi bashe ?
        DIR *Direction = opendir(path);
        if (Direction == NULL) { // Fixed the syntax error here
            mkdir(path , 0777);     // sath dastresie error midad fix kardam
            if (strcmp(mode, "user.name") != 0) {
                FILE *username = fopen("/mnt/e/ffproject/.babygitconfig/username.txt", "w"); // path eslah she
                fprintf(username, "%s", Data);  // Fixed the syntax error here
                fclose(username);
            } else {
                FILE *email = fopen("/mnt/e/ffproject/.babygitconfig/email.txt", "w"); // path
                fprintf(email, "%s", Data);  // Fixed the syntax error here
                fclose(email);
            }
        } else {
            if (strcmp(mode, "user.email") != 0) {
                FILE *email = fopen("/mnt/e/ffproject/.babygitconfig/email.txt", "w"); // path
                fprintf(email, "%s", Data);  // Fixed the syntax error here
                fclose(email);
            } else {
                FILE *username = fopen("/mnt/e/ffproject/.babygitconfig/username.txt", "w"); // path
                fprintf(username, "%s", Data);  // Fixed the syntax error here
                fclose(username);
            }
        }
        closedir(Direction);
        return;  
    } 
    else 
    {
        char *cwd;
        char buffer[4096];
        cwd = getcwd(buffer, 4096);
        char *path = malloc(4096);  // Allocate enough memory
        strcpy(path, cwd);
        path = CheckInit(cwd);

        if (path == NULL) {  // Fixed the syntax error here
            strcat(path, "/.babygit");
            if (strcmp(mode, "user.name") != 0) 
            {
                strcat(path, "/username.txt");
                FILE *prevConfig = fopen(path, "w");  
                fprintf(prevConfig, "%s", Data);     // Fixed the syntax error here
                fclose(prevConfig);
            } 
            else
            {
                strcat(path, "/email.txt");
                FILE *prevConfig = fopen(path, "w"); 
                fprintf(prevConfig, "%s", Data);     // Fixed the syntax error here
                fclose(prevConfig);
            }
        } else {
            puts("This is not babygit's repository");
        }
        return;
    }
}
void GitInit () //;)
{
char *cwd = CurrentWorkingDirectory();
if (CheckInit(cwd) != NULL)
{
            puts("repository reinitialized");
            system("rm -r .babygit");
}

    mkdir(".babygit", 0777);
    mkdir(".babygit/branch" , 0777);
    mkdir(".babygit/branch/master" , 0777);
    mkdir(".babygit/commits" , 0777);
    mkdir(".babygit/stage" , 0777);
    fopen(".babygit/status.txt", "w");
    fopen(".babygit/reset.txt", "w");
    fopen(".babygit/add.txt", "w");
    FILE *branch = fopen(".babygit/commits/branch.txt", "w");
    FILE *previd = fopen(".babygit/commits/previd.txt", "w");
    FILE *last_id = fopen(".babygit/commits/last_id.txt", "w");
    FILE *log = fopen(".babygit/commits/log.txt", "w");
    FILE *prevbranch = fopen(".babygit/commits/prevbranch.txt", "w");
    FILE *list = fopen(".babygit/branch/master/list.txt", "w");
    fprintf(branch, "master");
    fprintf(prevbranch, "master");
    fprintf(previd, "0");
    fprintf(last_id, "-1");
    return;

}
void GitAdd(int mode , char *Data) //;)
{
    if (mode == -1) puts("This file or directory is invalid-_-"); return;
    char *cwd ;
    char buffer[4096];
    cwd = getcwd (buffer , 4096);
    char *Repository = CheckInit (cwd);
    char *PathStats = malloc(4096);
    sprintf(PathStats , "%s/.babygit/status.txt" , Repository); 
    if (mode == Zero) 
    {
        char *NewPath = malloc(4096);
        NewPath = FindCWD(Data);
        if (NewPath[0] == '/') NewPath += 1;
        chdir("/"); chdir(Repository); chdir(".babygit/stage");
        mkdir(NewPath , 0777 ); chdir(cwd);
        struct dirent *fp ;
        char *path = malloc(4096);
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
                GitAdd(Zero, fp->d_name); ///nn
                chdir(cwd);
                }
                else if (fp->d_type == DT_REG)
            {
                char path[4096];
                sprintf(path, "%s/%s", cwd, Data);
                chdir("/");
                chdir(path);
                GitAdd(True, fp->d_name); //check beshe/////////////////
                chdir(cwd);
            }
            else
            {
                printf("%s pleas enter a valid type :(\n", fp->d_name); 
            }
        }
                char abs_path[4096];
        sprintf(abs_path, "%s/%s", cwd, Data);
        FILE *status = fopen(PathStats, "a"); 
        fprintf(status, "%s\n", abs_path);
        fclose(status);
        return;
    }
else
{
    char FileNAme[4096];
    sprintf(FileNAme , "%s/%s" , cwd , Data);
    FILE *file = fopen(FileNAme , "r");
    if ( file == NULL ) puts("can not finde the file"); return;
    char *path =(char *)malloc(4096);
    path = FindCWD(Data);
    char *Copydest = (char *)malloc(4096);
    char PathStats[4096];
    char PathABS[4096];
    sprintf(PathABS , "%s/%s" , cwd , Data);
    sprintf(PathStats , "%s/.babygit/status.txt" , Repository);
    FILE *stats = fopen(PathStats , "a");
    fprintf(stats , "%s/n" , PathABS);
    sprintf(Copydest , "%s/.babygit/stage%s" , Repository , path);
    (FileNAme , Copydest); //benevis
    fclose(file);
    fclose(stats);

}
}
void redo() //;)
{
    char *ResetFilePath = malloc(4096);
    char *cwd = CurrentWorkingDirectory();
    char *Repository = CheckInit(cwd);
    sprintf(ResetFilePath , "%s/.babygit/reset.txt" , Repository);
    FILE *ResetFile = fopen(ResetFilePath , "r");
    char *line = malloc(4096) ; char FileText[1024][4096];
    int count = 0;
    while (fgets(line , 4096 , ResetFile) != NULL)
    {
        int length = strlen(line) - 1 ; 
        line[length] = '\0';
        strcpy( FileText[count] ,line );
        count += 1;
    }
    for( int k = count -1 ; k >= 0 ; k--)
    {
        char *Command = malloc(4096);
        sprintf(Command , "babygit add %s" , FileText[k]);
        system(Command); //?
    }
   fclose(ResetFile); 
    ResetFile = fopen(ResetFilePath , "w");
    fclose(ResetFile);
}
void Reset( int mode  , char *FileName) //;)
{
    //Remove file from stage
    char *cwd = CurrentWorkingDirectory();
    char *RepositoryPath = CheckInit(cwd);
    if ( mode == Zero )
    {
        char *RemovePath = malloc(4096) ; char *FullPath = malloc(4096);
        char *RelativePath = malloc(4096);
        sprintf(FullPath , "%s/%s" , cwd , FileName);
        strcpy(RelativePath , FullPath);
        if(!CheckStage(FullPath))
        {
            printf("%s is not staged |:/n" , FileName); return;
        }
        RelativePath += strlen(RepositoryPath); //Removing newline path
        sprintf(RemovePath , "rm -r %s/.babygit/stage%s" , RepositoryPath , RelativePath );
        system(RemovePath);
        char *StatusPath = malloc(4096);
        sprintf(StatusPath , "%s/.babygit/status.txt" , RepositoryPath);
        FILE *StatusFile = fopen(StatusPath , "r");
        char *Line = malloc(4096);
        char FileText[1024][4096]; int index = 0;
        while (fgets (Line , 4096 , StatusFile))
        {
            int length = strlen(Line) - 1;
            Line[length] = '\0';
            // Skip the line if it matches the removed file
            if (!strncmp(Line  ,FullPath, strlen(FullPath))) //lililili
            {
            Line[strlen(Line)] = '\n';
            continue;
            }
            Line[strlen(Line)] = '\n';
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
            char *RemovePath = malloc(4096);char *Fullpath = malloc(4096);
            char *RelativePath = malloc(4096);
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
                Line[length] = '\0';
                if (!strcmp(Line , Fullpath))
                {
                    Line[length + 1] = '\n';
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
typedef struct 
{
    int Id;
    char Message[72]; 
    char Branch[100];  
    char Author[100];
    char AuthorEmail[100];
    int prev;
    int FileCount; 
    
} CommitInfo;
void PerformCommit( int argc , char **argv)
{
    int mode;
    char *cwd = CurrentWorkingDirectory();
    char *Repository = CheckInit(cwd);
    chdir(Repository);
    chdir(".babygit");
    char user[] = "user.txt";
    char email[] = "email.txt";
    FILE *ModeFile = fopen("commits/mode.txt", "r");
    if (ModeFile == NULL)
    {
        mode = 1;
    }
    else
    {
        mode = 0;
    }
    FILE *UserFile = fopen(user, "r");
    FILE *EmailFile = fopen(email, "r");
    if (UserFile == NULL || EmailFile == NULL)
    {
        // check global config
        chdir("/");
        chdir("/mnt/d/FOP.babygitconfig");
        UserFile = fopen(user, "r");
        EmailFile = fopen(email, "r");
        chdir(cwd);
        if (UserFile == NULL || EmailFile == NULL)
        {
            puts("you must set user name and email before Commititting");
            return;
        }
    }
    chdir(cwd);
    char *UserName = malloc(4096);
    char *UserEmail = malloc(4096);
    fgets(UserName, 4096, UserFile);
    fgets(UserEmail, 4096, EmailFile);
    UserName[strlen(UserName)] = '\0';
    UserEmail[strlen(UserEmail)] = '\0';
    fclose(UserFile);
    fclose(EmailFile);

    // branch name get
    char *BranchPath = malloc(4096);
    sprintf(BranchPath, "%s/.babygit/commits/branch.txt", Repository);
    FILE *branch_file = fopen(BranchPath, "r");
    char *branch_name = malloc(4096);
    fgets(branch_name, 4096, branch_file);
    branch_name[strlen(branch_name)] = '\0';
    fclose(branch_file);

    // Commitit id get
    char *IdPath = malloc(4096);
    sprintf(IdPath, "%s/.babygit/commits/last_id.txt", Repository);
    FILE *IdFile = fopen(IdPath, "r");
    char *id = malloc(4096);
    fgets(id, 4096, IdFile);
    id[strlen(id)] = '\0';

    // Commitit prev get
    char *PrevPath = malloc(4096);
    sprintf(PrevPath, "%s/.babygit/commits/previd.txt", Repository);
    FILE *PrevFile = fopen(PrevPath, "r");
    char *prev = malloc(4096);
    fgets(prev, 4096, PrevFile);
    prev[strlen(prev)] = '\0';

    // file count get
    char *StagePath = malloc(4096);
    sprintf(StagePath, "%s/.babygit/stage", Repository);
    int file_count = FileCounter(StagePath);
    if (file_count == 0)
    {
        puts("nothing to Commitit");
        return;
    }

    CommitInfo *Commit = malloc(sizeof(CommitInfo));
    Commit->Id = atoi(id) + 1;
    Commit->prev = atoi(prev);
    Commit->FileCount = file_count; //FileCount
    strcpy(Commit->Branch, branch_name);
    strcpy(Commit->Message, argv[3]);
    strcpy(Commit->Author, UserName);
    strcpy(Commit->AuthorEmail, UserEmail);
    printf("[%d %s] %s\n", Commit->Id, Commit->Message, Commit->Branch);
    char *CommitPath = malloc(4096);
    sprintf(CommitPath, "%s/.babygit/branch/%s/%d", Repository, Commit->Branch, Commit->Id);
    mkdir(CommitPath, 0777);
    char *CommitInfoPath = malloc(4096);

    // copy all from stage to CommitPath
    if (Commit->Id == 0)
    {
        char *StagePath = malloc(4096);
        sprintf(StagePath, "%s/.babygit/stage", Repository);
        char *cp_Commitad = malloc(4096);
        DIR *dir = opendir(StagePath);
        struct dirent *fp;
        dir = opendir(StagePath);
        while ((fp = readdir(dir)) != NULL)
        {
            if (strcmp(fp->d_name, ".") == 0 || strcmp(fp->d_name, "..") == 0 || strcmp(fp->d_name, ".babygit") == 0)
            {
                continue;
            }
            if (fp->d_type == DT_DIR)
            {
                char *path = malloc(4096);
                sprintf(path, "%s/%s", StagePath, fp->d_name);
                char *cp_Commitad = malloc(4096);
                sprintf(cp_Commitad, "cp -r %s %s", path, CommitPath);
                system(cp_Commitad);
            }
            else if (fp->d_type == DT_REG)
            {
                char *path = malloc(4096);
                sprintf(path, "%s/%s", StagePath, fp->d_name);
                char *cp_Commitad = malloc(4096);
                sprintf(cp_Commitad, "cp %s %s", path, CommitPath);
                system(cp_Commitad);
            }
        }
    }
    else
    {
        if (mode == 1)
        {
            // check if list.txt has any Commitit inside if not read prev Commitit from head.txt
            char *ListPath = malloc(4096);
            sprintf(ListPath, "%s/.babygit/branch/%s/list.txt", Repository, Commit->Branch);
            FILE *list_file = fopen(ListPath, "r");
            char *line = malloc(4096);
            char *PrevPath = malloc(4096); //prevbranch
            int i = 0;
            while (fgets(line, 4096, list_file) != NULL)
            {
                i++;
            }
            fclose(list_file);
            char *PrevBranchPath = malloc(4096);
            int PrevId;
            if (i == 0)
            {
                sprintf(PrevBranchPath, "%s/.babygit/branch/%s/head.txt", Repository, Commit->Branch);
                FILE *PrevBranchFile = fopen(PrevBranchPath, "r");
                char *line = malloc(4096);
                fgets(line, 4096, PrevBranchFile);
                PrevId = atoi(line);
                fgets(line, 4096, PrevBranchFile);
                strcpy(PrevPath, line);
                fclose(PrevBranchFile);
            }
            else
            {
                PrevId = atoi(line);
                strcpy(PrevPath, Commit->Branch);
            }

            char *PrevCommitPath = malloc(4096);
            sprintf(PrevCommitPath, "%s/.babygit/branch/%s/%d", Repository, PrevPath, PrevId);
            char *cp_Commitad = malloc(4096);
            // copy all from PrevCommitPath to CommitPath
            DIR *dir = opendir(PrevCommitPath);
            struct dirent *fp;
            dir = opendir(PrevCommitPath);
            while ((fp = readdir(dir)) != NULL)
            {
                if (strcmp(fp->d_name, ".") == 0 || strcmp(fp->d_name, "..") == 0 || strcmp(fp->d_name, ".babygit") == 0)
                {
                    continue;
                }
                if (fp->d_type == DT_DIR)
                {
                    char *path = malloc(4096);
                    sprintf(path, "%s/%s", PrevCommitPath, fp->d_name);
                    char *cp_Commitad = malloc(4096);
                    sprintf(cp_Commitad, "cp -r %s %s", path, CommitPath);
                    system(cp_Commitad);
                }
                else if (fp->d_type == DT_REG)
                {
                    char *path = malloc(4096);
                    sprintf(path, "%s/%s", PrevCommitPath, fp->d_name);
                    char *cp_Commitad = malloc(4096);
                    sprintf(cp_Commitad, "cp %s %s", path, CommitPath);
                    system(cp_Commitad);
                }
            }
            // copy all from stage to CommitPath
            char *StagePath = malloc(4096);
            sprintf(StagePath, "%s/.babygit/stage", Repository);
            char *cp_Commitad2 = malloc(4096);
            DIR *dir2 = opendir(StagePath);
            struct dirent *fp2;
            dir2 = opendir(StagePath);
            while ((fp2 = readdir(dir2)) != NULL)
            {
                if (strcmp(fp2->d_name, ".") == 0 || strcmp(fp2->d_name, "..") == 0 || strcmp(fp2->d_name, ".babygit") == 0)
                {
                    continue;
                }
                if (fp2->d_type == DT_DIR)
                {
                    char *path = malloc(4096);
                    sprintf(path, "%s/%s", StagePath, fp2->d_name);
                    char *cp_Commitad = malloc(4096);
                    sprintf(cp_Commitad, "cp -r %s %s", path, CommitPath);
                    system(cp_Commitad);
                }
                else if (fp2->d_type == DT_REG)
                {
                    char *path = malloc(4096);
                    sprintf(path, "%s/%s", StagePath, fp2->d_name);
                    char *cp_Commitad = malloc(4096);
                    sprintf(cp_Commitad, "cp %s %s", path, CommitPath);
                    system(cp_Commitad);
                }
            }
        }
        else
        {
            // copy all files from cwd into CommitPath
            DIR *dir = opendir(Repository);
            struct dirent *fp;
            while ((fp = readdir(dir)) != NULL)
            {
                if (strcmp(fp->d_name, ".") == 0 || strcmp(fp->d_name, "..") == 0 || strcmp(fp->d_name, ".babygit") == 0)
                {
                    continue;
                }
                if (fp->d_type == DT_DIR)
                {
                    char *path = malloc(4096);
                    sprintf(path, "%s/%s", Repository, fp->d_name);
                    char *cp_Commitad = malloc(4096);
                    sprintf(cp_Commitad, "cp -r %s %s", path, CommitPath);
                    system(cp_Commitad);
                }
                else if (fp->d_type == DT_REG)
                {
                    char *path = malloc(4096);
                    sprintf(path, "%s/%s", Repository, fp->d_name);
                    char *cp_Commitad = malloc(4096);
                    sprintf(cp_Commitad, "cp %s %s", path, CommitPath);
                    system(cp_Commitad);
                }
            }
            // copy all files from stage into CommitPath
            char *StagePath = malloc(4096);
            sprintf(StagePath, "%s/.babygit/stage", Repository);
            DIR *dir2 = opendir(StagePath);
            struct dirent *fp2;
            while ((fp2 = readdir(dir2)) != NULL)
            {
                if (strcmp(fp2->d_name, ".") == 0 || strcmp(fp2->d_name, "..") == 0 || strcmp(fp2->d_name, ".babygit") == 0)
                {
                    continue;
                }
                if (fp2->d_type == DT_DIR)
                {
                    char *path = malloc(4096);
                    sprintf(path, "%s/%s", StagePath, fp2->d_name);
                    char *cp_Commitad = malloc(4096);
                    sprintf(cp_Commitad, "cp -r %s %s", path, CommitPath);
                    system(cp_Commitad);
                }
                else if (fp2->d_type == DT_REG)
                {
                    char *path = malloc(4096);
                    sprintf(path, "%s/%s", StagePath, fp2->d_name);
                    char *cp_Commitad = malloc(4096);
                    sprintf(cp_Commitad, "cp %s %s", path, CommitPath);
                    system(cp_Commitad);
                }
            }
        }
    }

    // update branch head
    char *ListPath = malloc(4096);
    sprintf(ListPath, "%s/.babygit/branch/%s/list.txt", Repository, Commit->Branch);
    FILE *list_file = fopen(ListPath, "a");
    fprintf(list_file, "%d\n", Commit->Id);
    fclose(list_file);

    // update text files like id last id and log
    char *log_path = malloc(4096);
    sprintf(log_path, "%s/.babygit/commits/log.txt", Repository);
    FILE *log_file = fopen(log_path, "a");
    fprintf(log_file, "%s\n", Commit->Author);
    fprintf(log_file, "%d\n\"%s\"\n%s\n%d\n", Commit->Id, Commit->Message, Commit->Branch, Commit->FileCount);//FileCounter
    fclose(log_file);
    FILE *PrevFile2 = fopen(PrevPath, "w");
    fprintf(PrevFile2, "%d", Commit->Id);
    fclose(PrevFile2);
    IdFile = fopen(IdPath, "w");
    fprintf(IdFile, "%d", Commit->Id);
    fclose(IdFile);
    PrevFile = fopen(PrevPath, "w");
    fprintf(PrevFile, "%d", Commit->Id);
    fclose(PrevFile);

    // Commitit info creation
    sprintf(CommitInfoPath, "%s/.babygit/branch/%s/info%d.txt", Repository, Commit->Branch, Commit->Id);
    FILE *CommitInfoFile = fopen(CommitInfoPath, "w");
    fprintf(CommitInfoFile, "%s\n", Commit->Author);
    fprintf(CommitInfoFile, "%d\n%s\n%s\n%d\n", Commit->Id, Commit->Message, Commit->Branch, Commit->FileCount);//FileCount

    chdir(Repository);
    chdir(".babygit");
    system("rm -r stage");
    mkdir("stage", 0777);
    system("rm status.txt && touch status.txt");
    system("rm add.txt && touch add.txt");
    system("rm reset.txt && touch reset.txt");
    return;
}

void DisplayCommit(int argc , char **argv)
{
    char *cwd = CurrentWorkingDirectory();
    char *RepositoryPath = CheckInit(cwd);
    char *LogFilePath = malloc(4096); 
    sprintf(LogFilePath , "%s/.babygit/ommits/log.txt" , RepositoryPath );
    if (argc = 2)
    {
        char CommitLog[1024][4096];
        FILE *LogFile = fopen(LogFilePath , "r");
        char *Line = malloc(4096);
        int CommitCount = 0;
        while (fgets(Line , 4096 , LogFile) != NULL)
        {
            strcpy(CommitLog[CommitCount] , Line );
            CommitCount++;
        }
        CommitInfo CommitInfoArray[CommitCount]; //making an array of structs
            int CommitInfoIndex = 0;
        for (int i = 0 ; i < CommitCount ; i++)
        {
            //i = log index
            if ( i %  6 == 0)
            {
                strcpy(CommitInfoArray[CommitInfoIndex].Author, CommitLog[i]);
                CommitInfoArray[CommitInfoIndex].Id = atoi(CommitLog[i + 1]);
                strcpy(CommitInfoArray[CommitInfoIndex].Message, CommitLog[i + 2]);
                strcpy(CommitInfoArray[CommitInfoIndex].Branch, CommitLog[i + 3]);
                CommitInfoArray[CommitInfoIndex].FileCount = atoi(CommitLog[i + 4]);
                CommitInfoIndex++;
            }
        }
        for (int j = CommitInfoIndex - 1 ; CommitInfoIndex >= 0 ; j--)
        {
        printf ("Author |: %s" , CommitInfoArray[j].Author);
        printf ("Commit ID :) %d/n" , CommitInfoArray[j].Id);
        printf ("Message /: %s" , CommitInfoArray[j].Message);
        printf ("Branch ): %s" , CommitInfoArray[j].Branch);
        printf ("File Count :) %d/n" , CommitInfoArray[j].FileCount);
        }
    }
   else if(argc == 4 && !strcmp(argv[2] , '-n')) 
   {
    char CommitLog[1024][4096];
    FILE *LogFile = fopen(LogFilePath , "r");
    char *Line = malloc(4096);
    int LogIntryCount = 0;
    int RequestedEntries = atoi(argv[3]); //niga kon
    while (fgets(Line ,  4096 , LogFile) != NULL)
    {
        strcpy(CommitLog[LogIntryCount] , Line);
        LogIntryCount++;
    }
    CommitInfo Commits[LogIntryCount];
    int CommitIndex = 0;
    for(int i = 0 ; i <LogIntryCount ; i++)
    {
                if (i % 5 == 0)
        {
            strcpy(Commits[CommitIndex].Author, CommitLog[i]);
            Commits[CommitIndex].Id = atoi(CommitLog[i + 1]);////
            strcpy(Commits[CommitIndex].Message, CommitLog[i + 2]);
            strcpy(Commits[CommitIndex].Branch, CommitLog[i + 3]);
            Commits[CommitIndex].FileCount = atoi(CommitLog[i + 5]);
            CommitIndex++;
        }
   }
   if(RequestedEntries > CommitIndex) RequestedEntries = CommitIndex;
       for (int j = CommitIndex - 1; j >= CommitIndex - RequestedEntries; j--)
    {
        printf("Author:) %s", Commits[j].Author);
        printf("Commit ID:/ %d\n", Commits[j].Id);
        printf("Message:| %s", Commits[j].Message);
        printf("Branch:( %s\n", Commits[j].Branch);
        printf("File Count-: %d\n", Commits[j].FileCount);
        printf("\n");

    }
   }
   else if(argc == 4 && !strcmp(argv[2] , "-branch") == 0)
   {
    char CommitLog[1024][4096];
    FILE *LogFile = fopen(LogFilePath , "R");
    char *CurrentLine = malloc(4096);
    int NumberOfLines = 0;
    int n = atoi(argv[2]);
    while ( (fgets (CurrentLine , 4096 , LogFile)) != 0)
    {
    strcpy( CommitLog[NumberOfLines] , CurrentLine);
    NumberOfLines++;
    }
    CommitInfo CommitInfoArray[NumberOfLines];
    int NumberOfCommits = 0;
    for ( int i = 0 ; i < NumberOfLines ; i++)
    {
            strcpy(CommitInfoArray[NumberOfCommits].Author, CommitLog[i]);
            CommitInfoArray[NumberOfCommits].Id = atoi(CommitLog[i + 1]);
            strcpy(CommitInfoArray[NumberOfCommits].Message, CommitLog[i + 2]);
            strcpy(CommitInfoArray[NumberOfCommits].Branch, CommitLog[i + 3]);
            CommitInfoArray[NumberOfCommits].FileCount = atoi(CommitLog[i + 5]);
            NumberOfCommits++;
    }
            if (n > NumberOfCommits) n = NumberOfCommits;
             for (int j = NumberOfCommits - 1; j >= NumberOfCommits - n; j--)
        {
            printf("author:) %s", CommitInfoArray[j].Author);
            printf("commit id |: %d\n", CommitInfoArray[j].Id);
            printf("message /: %s", CommitInfoArray[j].Message);
            printf("branch ): %s\n", CommitInfoArray[j].Branch);
            printf("file count-: %d\n", CommitInfoArray[j].FileCount);
            printf("\n");
        }
   }
    else if (argc == 4 && !strcmp(argv[2], "-author"))
    {
        char log[1000][4096];
        FILE *LogFile = fopen(LogFilePath, "r");
        char *line = malloc(4096);
        int i = 0;
        while (fgets(line, 4096, LogFile) != NULL)
        {
            strcpy(log[i], line);
            i++;
        }
        CommitInfo CommitInfoArray[i];
        int k = 0;
        for (int j = 0; j < i; j++)
        {
            if (j % 5 == 0)
            {
                strcpy(CommitInfoArray[k].Author, log[j]);
                CommitInfoArray[k].Id = atoi(log[j + 1]);
                strcpy(CommitInfoArray[k].Message, log[j + 2]);
                strcpy(CommitInfoArray[k].Branch, log[j + 3]);
                CommitInfoArray[k].FileCount = atoi(log[j + 5]);
                k++;
            }
        }
        for (int j = k - 1; j >= 0; j--)
        {
            
            if (!strncmp(CommitInfoArray[j].Author, argv[3], strlen(argv[3])))
            {
                printf("author:) %s", CommitInfoArray[j].Author);
                printf("commit id|: %d\n", CommitInfoArray[j].Id);
                printf("message:() %s", CommitInfoArray[j].Message);
                printf("branch:/ %s", CommitInfoArray[j].Branch);
                printf("file count-: %d\n", CommitInfoArray[j].FileCount);
                printf("\n");
            }
        }           //debug shode ?
    }
        else if (argc == 5 && !strcmp(argv[2], "-since"))
    {
        char log[1024][4096];
        FILE *FileLog = fopen(LogFilePath, "r");
        char *Line = malloc(4096);
        int i = 0;
        int n = atoi(argv[3]);
        while (fgets(Line, 4096, FileLog) != NULL)
        {
            strcpy(log[i], Line);
            i++;
        }
        CommitInfo Commit[i];
        int k = 0;
        for (int j = 0; j < i; j++)
        {
            if (j % 5 == 0)
            {
                strcpy(Commit[k].Author, log[j]);
                Commit[k].Id = atoi(log[j + 1]);
                strcpy(Commit[k].Message, log[j + 2]);
                strcpy(Commit[k].Branch, log[j + 3]);
                Commit[k].FileCount = atoi(log[j + 5]);
                k++;
            }
        }
        if (n > k)
        {
            n = k;
        }
        for (int j = k - 1; j >= k - n; j--)
        {
            {
                printf("author -: %s", Commit[j].Author);
                printf(" Commit /: id: %d\n", Commit[j].Id);
                printf("message:| %s", Commit[j].Message);
                printf("branch:) %s", Commit[j].Branch);
                printf("file count): %s\n", Commit[j].Branch);
                printf("\n");
            }
        }
    }

}

int main(int argc, char *argv[]) 
{  // Fixed the syntax error here
    if (!strcmp(argv[1] , "config"))
        {
        if (argc != 4 && argc != 5)                {
                    puts("what the hell are you doing ? enter a valid command");
                    return 0;
                }
            if(!strcmp(argv[2] , "--global"))
                {
                    if(!strcmp(argv[3] , "user.name"))
                        {
                            CreatConfig(1 , argv[3] , argv[4]);
                        }
                    else if(!strcmp(argv[2] , "user.email"))
                        {
                             CreatConfig(1 , argv[3] , argv[4]);
                        }
                    else
                        {
                            puts("hey you ! enter your command correctly");
                            return 0;
                        }
                }
    
            else
                {
                    if (!strcmp(argv[2] , "user.name"))
                        {
                            CreatConfig(0 , argv[2] , argv[3]);
                        }
                    else if (!strcmp(argv[2] , "user.email"))
                        {
                            CreatConfig(0 , argv[2] , argv[3]);
                        }
                    else
                        {
                            puts("hey you ! enter your command correctly");
                            return 0;
                        }
                }        

        
    
             return 0;
        }
        
    else if (!strcmp(argv[1], "init"))
    {
        if (argc != 2)
        {
            puts("hey you ! enter your command correctly");
            return 0;
        }
        GitInit();
        return 0;
    }
    else
    {
        char *cwd = CurrentWorkingDirectory();
        char *Repository = CheckInit(cwd);
        if (Repository == NULL)
        {
            puts("This is not a babygit repository");
            return 0;
        }
        else if (!strcmp(argv[1], "add"))
        {
            char *AddPath = malloc(4096);
            sprintf(AddPath, "%s/.babygit/add.txt", Repository);
            FILE *AddFile = fopen(AddPath, "a");
            if (argc <= 2)
            {
                puts("hey you ! enter your command correctly");
                return 0;
            }
            if (!strcmp(argv[2], "-redo"))
            {
                redo();
            }

            else if (!strcmp(argv[2], "-f"))
            {
                if (argc <= 3)
                {
                    puts("hey you ! enter your command correctly");
                    return 0;
                }

                for (int i = 3; i < argc; i++)
                {
                    char *absPath = malloc(4096);
                    sprintf(absPath, "%s/%s", cwd, argv[i]);
                    if (CheckStage(absPath))
                    {
                        // delete from stage folder
                        char *path = malloc(4096);
                        path = FindCWD(argv[2]);
                        char *rm_path = malloc(4096);
                        sprintf(rm_path, "rm -r %s/.babygit/stage%s", Repository, path);
                        system(rm_path);
                    }
                    char TempPath[4096];
                    strcpy(TempPath, argv[i]);
                    char *x = ChangeDir(argv[i]);
                    char *newcwd = CurrentWorkingDirectory();
                    if (strcmp(Repository, newcwd))
                    {
                        char *path = malloc(4096);
                        path = FindCWD(argv[2]);
                        StageFolder(path);
                    }
                    GitAdd(FileDir(x), ChangeDir(x));
                    fprintf(AddFile, "%s ", TempPath);
                    chdir(cwd);
                }
                fprintf(AddFile, "\n");
                return 0;
            }
            else
            {
                for (int i = 2; i < argc; i++)
                {
                    char TempPath[4096];
                    strcpy(TempPath, argv[i]);
                    char *absPath = malloc(4096);
                    sprintf(absPath, "%s/%s", cwd, argv[i]);
                    if (CheckStage(absPath))
                    {
                        // delete from stage folder
                        char *path = malloc(4096);
                        path = FindCWD(argv[2]);
                        char *rm_path = malloc(4096);
                        sprintf(rm_path, "rm -r %s/.babygit/stage%s", Repository, path);
                        system(rm_path);
                    }
                    char *x = ChangeDir(argv[i]);
                    char *newcwd = CurrentWorkingDirectory();
                    if (strcmp(Repository, newcwd))
                    {
                        char *path = malloc(4096);
                        path = FindCWD(argv[2]);
                        StageFolder(path);
                    }
                    fprintf(AddFile, "%s ", TempPath);
                    GitAdd(FileDir(x), x);
                    chdir(cwd);
                }
                fprintf(AddFile, "\n");
                return 0;
            }
        }
        else if (!strcmp(argv[1], "reset"))
        {
            char *ResetPath = malloc(4096);
            sprintf(ResetPath, "%s/.babygit/reset.txt", Repository);
            FILE *resetfile = fopen(ResetPath, "a");
            if (argc <= 2)
            {
                puts("hey you ! enter your command correctly");
                return 0;
            }
           // if (!strcmp(argv[2], "-undo"))
            // {
            //     undo(); //not made
            // }
            else if (!strcmp(argv[2], "-f"))
            {
                for (int i = 3; i < argc; i++)
                {
                    char TempPath[4096];
                    strcpy(TempPath, argv[i]);
                    char *x = ChangeDir(argv[i]);
                    char *newcwd = malloc(4096);
                    char buffer[4096];
                    newcwd = getcwd(buffer, 4096);
                    char *absPath = malloc(4096);
                    sprintf(absPath, "%s/%s", newcwd, x);
                    if (!CheckStage(absPath))
                    {
                        printf("%s is not staged\n", x);
                        continue;
                    }
                    fprintf(resetfile, "%s ", TempPath);
                    Reset(FileDir(x), x);
                    chdir(cwd);
                }
                fprintf(resetfile, "\n");
                return 0;
            }
            else
            {
                for (int i = 2; i < argc; i++)
                {
                    char TempPath[4096];
                    strcpy(TempPath, argv[i]);
                    char *x = ChangeDir(argv[i]);
                    char *newcwd = malloc(4096);
                    char buffer[4096];
                    newcwd = getcwd(buffer, 4096);
                    char *absPath = malloc(4096);
                    sprintf(absPath, "%s/%s", newcwd, x);
                    if (!CheckStage(absPath))
                    {
                        printf("%s is not staged\n", x);
                        continue;
                    }
                    fprintf(resetfile, "%s ", TempPath);
                    Reset(FileDir(x), x);
                    chdir(cwd);
                }
                fprintf(resetfile, "\n");
                return 0;
            }
        }
        else if (!strcmp(argv[1], "commit"))
        {
            if (!strcmp(argv[2], "-m"))
            {
                if (argc <= 3)
                {
                    puts("hey you ! enter your command correctly");
                    return 0;
                }
                if (strlen(argv[3]) > 72)
                {
                    puts("commit message must be less than 72 characters");
                    return 0;
                }
                PerformCommit(argc, argv);
            }
            else
            {
                puts("hey you ! enter your command correctly");
                return 0;
            }
        }
        else if (!strcmp(argv[1], "log"))
        {
            DisplayCommit(argc, argv); //log
        }
        else
        {
            puts("hey you ! enter your command correctly");
            return 0;

        }
    }
    return 0;
}