#include "FileManager.h"

bool dirExist(const int id) {
    struct dirent *dir;
    bool found = false;
    DIR *d = opendir("."); 
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if(dir->d_name == id && found != false)
                found = true;
        }
        closedir(d);
    }
    return found;
}

void createDir(const int id) {

}

void editTime(const int id, const int move, const struct timespec *time) {
    char filename[16] = {'0'};
    int microsec = time->tv_nsec * 1000;
    file_t fd;
    sprintf(filename, "id%06d/v%06d", id, move);
    fd = open(filename, O_CREAT | O_WRONLY, 00666);
    write(fd, &microsec, sizeof(int));
    close(fd);
}
