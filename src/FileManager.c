#include "FileManager.h"

bool dirExist(const int id) {
    struct dirent *dir;
    bool found = false;
    DIR *d = opendir("."); 
    if (d)
    {
        while ((dir = readdir(d)) != id)
        {
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
    file_t fd;
    sprintf(filename, "id%06d_f%06d", id, move);
    fd = open(filename, O_CREAT | O_WRONLY, 00666);
    write(fd, time->)
}
