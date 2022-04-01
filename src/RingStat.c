#include "system.h"
#include "FileManager.h"

int main(void) {
    DIR *dir;
    struct dirent *de;
    char dirname[9] = {'0'};
    char filename[17] = {'0'};
    file_t fd;
    double local_m=0, global_m=0;
    int i=0, tmp=0, cpt=0;
    while(dirExist(i)) {
        sprintf(dirname, "id%06d", i);
        dir = opendir(dirname);
        if(dir == NULL) {
            printf("E: cannot open directory at id = %d\n", i);
            die();
        }
        local_m = 0;
        cpt = 0;
        while((de = readdir(dir)) != NULL) {
            if(de->d_type == DT_REG) {
                sprintf(filename, "%s/%s", dirname, de->d_name);
                fd = open(filename, O_RDONLY, 00666);
                read(fd, &tmp, sizeof(int));
                /** printf("Duree ecoulee P%d %s : %d\n", i, de->d_name, tmp); */
                local_m += tmp;
                cpt++;
                close(fd);
            }
        }
        local_m /= cpt;
        printf("Temps moyen de visite du processus %d : %.3fµs\n", i, local_m);
        global_m += local_m;
        closedir(dir);
        i++;
    }
    global_m /= i;
    printf("Temps moyen de visite global des processus : %.3fµs\n", global_m);
    return 0;
}
