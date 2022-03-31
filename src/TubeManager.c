#include "TubeManager.h"

void createTubeManager(TubeManager *tm, stream_t **ts, const int tc, const int id) {
    int r=id, w=id+1;
    w = (w >= tc) ? 0 : w;
    tm->read = ts[r][0];
    tm->write = ts[w][1];
    tm->proc = 0;
}

stream_t** tubes(const int tc) {
    int i;
    stream_t **ts = (stream_t**) malloc(tc*sizeof(stream_t*));
    if(ts == NULL) return NULL;
    for(i=0; i<tc; i++) {
        ts[i] = (stream_t*) malloc(2*sizeof(stream_t));
        if(ts[i] == NULL) {
            freeTubes(ts, i);
            return NULL;
        }
    }
    for(i=0; i<tc; i++) pipe(ts[i]);
    return ts;
}

void closeTubes(stream_t **ts, const int tc, TubeManager *tm) {
    int i;
    for(i=0; i<tc; i++) {
        if(tm == NULL || (tm != NULL && ts[i][0] != tm->read))
            close(ts[i][0]);
        if(tm == NULL || (tm != NULL && ts[i][1] != tm->write))
            close(ts[i][1]);
    }
}

void freeTubes(stream_t **ts, const int tc) {
    int i;
    for(i=0; i<tc; i++) {
        free(ts[i]);
        ts[i] = NULL;
    }
    free(ts);
    ts = NULL;
}
