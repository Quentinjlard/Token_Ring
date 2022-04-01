#include "FileManager.h"

bool dirExist(const int id) {
    bool cont = true;
    struct dirent *de;
    DIR *dir = opendir("./");
    char dirname[9] = {'0'};
    sprintf(dirname, "id%06d", id);
    if(dir == NULL) return false;
    while((de = readdir(dir)) != NULL && cont) {
        if(!strcmp(dirname, de->d_name)) cont = false;
    }
    closedir(dir);
    return !cont;
}

void createDir(const int id) {
    char dirname[9] = {'0'};
    sprintf(dirname, "id%06d", id);
    if(mkdir(dirname, S_IRWXU) == -1) {
        switch(errno) {
            case EACCES:
                printf("E: the parent directory does not allow writing\n");
                break;
            case EEXIST:
                printf("E: this pathname already exists\n");
                break;
            case ENAMETOOLONG:
                printf("E: the pathname is too long\n");
                break;
            default:
                printf("E: an error occurred\n");
        }
        die();
    }
}

void editTime(const int id, const int move, const int cur_ms, const int old_ms) {
    char filename[17] = {'0'};
    int microsec = cur_ms - old_ms;
    file_t fd;
    sprintf(filename, "id%06d/v%06d", id, move);
    fd = open(filename, O_CREAT | O_WRONLY, 00666);
    write(fd, &microsec, sizeof(int));
    close(fd);
}
