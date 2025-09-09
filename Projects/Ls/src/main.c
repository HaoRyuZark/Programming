#include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>

int main() {
    
    DIR* dir;
    struct dirent* entry; 
    struct stat file_stat;

    char time_str[20];
    int total_files = 0;

    dir = opendir(".");
    if (dir == NULL) {
        perror("Could not open directory");
        return 1;
    }

    printf("Name\t\tSize\t\tModified\t\tType\n");
    printf("-----\t\t-----\t\t-----\t\t-----\n");
    
    while ((entry = readdir(dir)) != NULL) {

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 ) {
            continue;
        }

        if (stat(entry->d_name, &file_stat) == 0) {
            
            strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M", localtime(&file_stat.st_mtime));

            printf("%-15s\t", entry->d_name);
            printf("%-8ld\t", (long)file_stat.st_size);
            printf("%s\t", time_str);

            if (S_ISDIR(file_stat.st_mode)) {
                printf("DIR\n");
            } else if (S_ISREG(file_stat.st_mode)) {
                printf("FILE\n");
            } else if (S_ISLNK(file_stat.st_mode)) {
                printf("LINK\n");
            } else {
                printf("OTHERS\n");
            }

            total_files++;
        }
    }
    
    printf("\nTotal files: %d\n", total_files);
    closedir(dir);
    return 0;
}
