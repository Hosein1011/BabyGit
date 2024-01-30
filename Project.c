#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

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
void GitInit ()
{
    char *cwd;
    char buffer[4096];
    getcwd (buffer , 4096);
if (CheckInit(cwd) != NULL)
{
    puts("This is already a  babygit repository :)");
    return;
}
else
{

}
}

int main(int argc, char *argv[]) {  // Fixed the syntax error here
    if (argc < 2) {
        fprintf(stdout, "please enter a valid command");
        return 1;
    }

    return 0;
}
