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

char *CheckInit(const char *path);
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
int CheckSage(char *Path)
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
    while ((fgets(Line , 4096 , StatusPath)) != NULL)
    {
        Line[strlen(Line) -1] = '/0';
        if (!strncmp( Line , Path , strlen(Path)))
        {
            Line[strlen(Line)] = '/n';
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
        mkdir(token, 0777);
        chdir(token);
        token = strtok(NULL, "/");
    }
    chdir(cwd);
}
void CreatConfig(int IsGlobal, char *mode, char *Data) {
    if (IsGlobal) 
    {
        char path[] = "/mnt/e/ffproject/.babyfitconfig"; // path chi bashe ?
        DIR *Direction = opendir(path);
        if (Direction == NULL) { // Fixed the syntax error here
            mkdir(path, 0777);     // sath dastresie error midad fix kardam
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
        char *path = (char *)malloc(strlen(cwd) + strlen("/.babygit") + 1);  // Allocate enough memory
        strcpy(path, cwd);
        path = CheckInit(cwd);

        if (path == NULL) {  // Fixed the syntax error here
            strcat(path, "/.babygit");
            if (strcmp(mode, "username") != 0) 
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
    }
}
void GitInit ()
{
char *cwd = CurrentWorkingDirectory();
if (CheckInit(cwd) != NULL)
{
            puts("repository reinitialized");
            system("rm -r ,babygit");
}

    mkdir(".babygit", 0777);
    mkdir(".babygit/branch", 0777);
    mkdir(".babygit/branch/master", 0777);
    mkdir(".babygit/commits", 0777);
    mkdir(".babygit/stage", 0777);
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
        if (NewPath[0] == "/") NewPath += 1;
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
void PerformCommit(int argc , char **argv)
{
    char *cwd = CurrentWorkingDirectory();
    char *RepositoryPath 
    = CheckInit(cwd);
    char *UserFilePath = (char *)malloc(4096); char *EmailFilePath = (char *)malloc(4096);
    sprintf(UserFilePath , "%s/.babygit/user.txt" , RepositoryPath)
    ;
    sprintf(EmailFilePath , "%s/.babygit/email.txt" , EmailFilePath);
    FILE *UserFile = fopen(UserFilePath , "r"); FILE *EmailFile = fopen(EmailFilePath , "r");
    if ( UserFile == NULL || EmailFile == NULL)
    {
        //check global config (faghat bara khoda, kar mide fek konam)
        char *GlobalUserFilePath = "/mnt/e/ffproject/.babygittconfig/user.txt";
        char *GlobalEmailFilePath = "/mnt/e/ffproject/.babygitconfig/email.txt";
        UserFile = fopen(GlobalUserFilePath , "r");
        EmailFile = fopen(GlobalEmailFilePath , "r");
        if (UserFile == NULL || EmailFile == NULL)
        {
            puts("what the hell are you doing ? set username and email first -_-");
            return;
        }
        //continue?
        char *UserName = (char *)malloc(4096);
        char *UserEmail = (char *)malloc(4096);
        fgets(UserName , 4096 , UserFile) ; fgets(UserEmail , 4096 , EmailFile);
        UserName[strlen(UserName) - 1] = '\0'; 
        UserEmail[strlen(UserEmail) - 1] = '\0';
        fclose(UserEmail); fclose(UserFile);

        char *BranchFilePath = mallo(4096);
        sprintf(BranchFilePath , "%s/.babygit/commits/branch.txt" , RepositoryPath);
        FILE *BranchFile =fopen(BranchFilePath , "r");
        char *BranchName = malloc(4096);
        fgets(BranchName , 4096 , BranchFile);
        BranchName[strlen(BranchName) - 1] = '/0';
        fclose(BranchFile);

        char *IdFilePath = malloc(4096);
        sprintf (IdFilePath , "%s/.babygit/commits/current-id.txt" , RepositoryPath );
        FILE *IdFile = fopen(IdFilePath , "r");
        char *CommitId = malloc(4096);
        fgets(CommitId , 4096 , IdFile);
        CommitId[strlen(CommitId) - 1] = "/0"; fclose(IdFile);

        char *PrevIdFilePath = malloc(4096);
        sprintf(PrevIdFilePath, "%s/.babygit/commits/prev-id.txt", RepositoryPath);
        FILE *prevIdFile = fopen(PrevIdFilePath, "r");
        char *prevCommitId = malloc(4096);
        fgets(prevCommitId, 4096 , prevIdFile);
        prevCommitId[strlen(prevCommitId) - 1] = '\0'; 
        fclose(prevIdFile);

         char *StagePath = malloc(4096);
        sprintf(StagePath, "%s/.babygit/stage", RepositoryPath);
        int FileCount = FileCounter(StagePath); //not made yet
        if(FileCount = 0) puts("there is nothing we can commit -_-"); return;

        CommitInfo *CommitInfo = malloc(sizeof(CommitInfo));
        CommitInfo->Id = atoi(CommitId) + 1;
        CommitInfo->prev = atoi(prevCommitId);
        CommitInfo->FileCount = FileCount; //add File counter function
        strcpy(CommitInfo->Branch , BranchName);
        strcpy(CommitInfo->Message , argv[3]); //nigakona error dared
        strcpy(CommitInfo->Author , UserName);
        strcpy(CommitInfo->AuthorEmail , UserEmail);
        printf("[%d %s] %s\n", CommitInfo->Id, CommitInfo->Message, CommitInfo->Branch);

        char *CommitPath = malloc(4096);
        sprintf(CommitPath , "%s/.babygit/branch/%s/%d" , RepositoryPath , CommitInfo->Branch);
        mkdir(CommitPath , 0777);

        char *CommitInfoPath = malloc(4096);
        if (CommitInfo->Id == 0)
        {
            char *StagePath = malloc(4096);
            sprintf(StagePath , "%s/.babygit/stage" , RepositoryPath);
            DIR *Direction = opendir(StagePath);
            struct dirent *entry;
            while( (entry = readdir(Direction)) != NULL)
            {
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".babygit") == 0) 
            {
                continue;
            }
            char *Path = malloc(4096);
            sprintf(Path, "%s/%s", StagePath, entry->d_name);

            char *cpCommand = malloc(4096); 
             if (entry->d_type == DT_DIR)
            {
                sprintf(cpCommand, "cp -r %s %s", Path, CommitPath);
            } 
            else if (entry->d_type == DT_REG) 
            {
                sprintf(cpCommand, "cp %s %s", Path, CommitPath);
            }
            system(cpCommand);
            }
        closedir(Direction);
        }
    else
    {
        char *PrevCommitPath ;
        sprintf(PrevCommitPath ,"%s/.babygit/branch/%s/%d" , RepositoryPath , CommitInfo->Branch , CommitInfo->prev);
        DIR *prevDir = opendir(PrevCommitPath);
        struct dirent *entryPrev;
        while ((entryPrev = readdir(prevDir)) != NULL)
        {
        if (strcmp(entryPrev->d_name, ".") == 0 || strcmp(entryPrev->d_name, "..") == 0 || strcmp(entryPrev->d_name, ".babygit") == 0)
        {
            continue;
        }
        if(entryPrev->d_type == DT_DIR)
        {
            char *PathPrev = malloc(4096);
            sprintf(PathPrev , "%s/%s" , PrevCommitPath , entryPrev->d_name);
            char *cpCommandPrev = malloc(4096);
            sprintf(cpCommandPrev , "cp -r %s %s" , PathPrev , CommitPath);
            system(cpCommandPrev); //hala halat badi
        }
        else if (entryPrev->d_type == DT_REG)
        {
            char *PathPrev = malloc(4096);
            sprintf(PathPrev , "%s/%s" , PrevCommitPath , entryPrev->d_name);
            char *cpCommandPrev = malloc(4096);
            sprintf(cpCommandPrev , "cp %s %s" , PathPrev , CommitPath);
            system(cpCommandPrev);
        }
        }
    closedir(prevDir);
    }

    char *LogPath = malloc(4096);
    sprintf(LogPath , "%s/.babygit/commits/log.txt" , RepositoryPath);
    FILE *LogFile = fopen(LogPath , "a");
    fprintf(LogFile , "%s/n" , CommitInfo->Author);
    fprintf(LogFile, "%d\n\"%s\"\n%s\n%d\n", CommitInfo->Id, CommitInfo->Message, CommitInfo->Branch, CommitInfo->FileCount); 
    //add time element if you want
    fclose(LogFile);

    FILE *PrevFile2 = fopen(PrevIdFilePath , "w");
    fprintf(PrevFile2 , "%d" , CommitInfo->Id);
    fclpse(PrevFile2);

    IdFile = fopen(IdFilePath , "w" );
    fprintf(IdFile , CommitInfo->Id);
    flose(IdFile);

    prevIdFile = fopen(prevIdFile, "w");  //Repository path ro mitoni bara fahm behtar eslah koni
    fprintf( prevIdFile , "%d", CommitInfo->Id);
    fclose(prevIdFile);

    sprintf( CommitInfoPath , "%s/.babygit/branch/%s/info%d.txt" , RepositoryPath , CommitInfo->Branch , CommitInfo->Id);
    FILE *CommitInfoFile = fopen(CommitInfoPath , "w");
    fprintf(CommitInfoFile , "%s/n" , CommitInfoPath);
    fprintf(CommitInfoFile, "%d\n%s\n%s\n%d\n", CommitInfo->Id, CommitInfo->Message, CommitInfo->Branch, CommitInfo->FileCount);
    fclose(CommitInfoFile);

    chdir(RepositoryPath);
    chdir(".babygit");
    system("rm -r stage");
    mkdir("stage" , 0777);
    system("rm status.txt && touch status.txt");
    system("rm add.txt && touch add.txt");
    system("rm reset.txt && touch reset.txt");
    return;
}
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
        while (fgets(Line , 4096 , LogFilePath) != NULL)
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
    while ( (fgets (CurrentLine , 4096 , LogFilePath)) != 0)
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
                printf("file count): %d\n", Commit[j].Branch);
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
            else if (!strcmp(argv[2], "-n"))
            {
                if (argc <= 3)
                {
                    puts("hey you ! enter your command correctly");
                    return 0;           //add n not add yet
                }
                int a = atoi(argv[3]);
                addn(a);
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
            if (!strcmp(argv[2], "-undo"))
            {
                undo(); //not made
            }
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
                    reset(FileDir(x), x);
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
        else if (!strcmp(argv[1], "checkout"))
        {
            CheckOut(argc, argv);
        }
        else if (!strcmp(argv[1], "branch"))
        {
            Branch(argc, argv); //lilil
        }
        else
        {
            puts("hey you ! enter your command correctly");
            return 0;

        }
    }
    return 0;
}