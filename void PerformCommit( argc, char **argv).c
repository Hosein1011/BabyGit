void PerformCommit( argc, char **argv)
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
    int file_count = filecounter(StagePath);
    if (file_count == 0)
    {
        puts("nothing to Commitit");
        return;
    }

    CommitInfo *Commit = malloc(sizeof(CommitInfo));
    Commit->Id = atoi(id) + 1;
    Commit->prev = atoi(prev);
    Commit->filecount = file_count; //filecount
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
    if (Commit->id == 0)
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
            char *PrevPath = malloc(4096);
            int i = 0;
            while (fgets(line, 4096, list_file) != NULL)
            {
                i++;
            }
            fclose(list_file);
            char *PrevBranchPath = malloc(4096);
            int PrevPath;
            if (i == 0)
            {
                sprintf(PrevBranchPath, "%s/.babygit/branch/%s/head.txt", Repository, Commit->Branch);
                FILE *PrevBranchFile = fopen(PrevBranchPath, "r");
                char *line = malloc(4096);
                fgets(line, 4096, PrevBranchFile);
                PrevPath = atoi(line);
                fgets(line, 4096, PrevBranchFile);
                strcpy(PrevPath, line);
                fclose(PrevBranchFile);
            }
            else
            {
                PrevPath = atoi(line);
                strcpy(PrevPath, Commit->branch);
            }

            char *PrevCommitPath = malloc(4096);
            sprintf(PrevCommitPath, "%s/.babygit/branch/%s/%d", Repository, PrevPath, PrevPath);
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
    fprintf(log_file, "%d\n\"%s\"\n%s\n%d\n", Commit->Id, Commit->Message, Commit->Branch, Commit->filecount);//filecounter
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
    fprintf(CommitInfoFile, "%s\n", Commit->author);
    fprintf(CommitInfoFile, "%d\n%s\n%s\n%d\n", Commit->Id, Commit->Message, Commit->Branch, Commit->filecount);//filecount

    chdir(Repository);
    chdir(".babygit");
    system("rm -r stage");
    mkdir("stage", 0777);
    system("rm status.txt && touch status.txt");
    system("rm add.txt && touch add.txt");
    system("rm reset.txt && touch reset.txt");
    return;
}