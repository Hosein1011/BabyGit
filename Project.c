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
int CheckSage(char *Path)
{
    char *StatusPath = malloc(4096);
    char *cwd = CurrentWorkingDirectory;
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
int FileCounter ( char * Path)
{
    int count = 0 ;
    struct dirent *fp;
    DIR *Direction = opendir(Path);
    while ((fp = readdir(Direction)) != NULL)
    {
        if (strcmp(fp->d_name , ".d") == 0 || strcmp(fp->d_name , ".." || strcmp(fp->d_name , ".babygit")))
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
void CreatConfig(int IsGlobal, char *mode, char *Data) {
    if (IsGlobal) {
        char path[] = "/mnt/e/ffproject/.babyfitconfig"; // path chi bashe ?
        DIR *Direction = opendir(path);
        if (Direction == NULL) { // Fixed the syntax error here
            mkdir(path, 0777);     // sath dastresie error midad fix kardam
            if (strcmp(mode, "username") != 0) {
                FILE *username = fopen("/mnt/e/ffproject/.babygitconfig/username.txt", "w"); // path eslah she
                fprintf(username, "%s", Data);  // Fixed the syntax error here
                fclose(username);
            } else {
                FILE *email = fopen("/mnt/e/ffproject/.babygitconfig/email.txt", "w"); // path
                fprintf(email, "%s", Data);  // Fixed the syntax error here
                fclose(email);
            }
        } else {
            if (strcmp(mode, "email") != 0) {
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
        sprintf(StagePath, "%s/.magit/stage", RepositoryPath);
        int FileCount = FileCounter(StagePath); //not made yet
        if(Filecount = 0) puts("there is nothing we can commit -_-"); return;

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
        if (strcmp(entryPrev->d_name, ".") == 0 || strcmp(entryPrev->d_name, "..") == 0 || strcmp(entryPrev->d_name, ".magit") == 0)
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



int main(int argc, char *argv[]) {  // Fixed the syntax error here
    if (argc < 2) {
        fprintf(stdout, "please enter a valid command");
        return 1;
    }

    return 0;
}
