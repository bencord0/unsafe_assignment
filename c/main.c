#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/random.h>

struct thread_info {
    pthread_t thread_id;
    int       value;
    int      *a;
};

int should_wait() {
    int s;
    u_int8_t buf = 0;

    s = getrandom(&buf, 1, 0);
    if (s == -1) {
        perror("getrandom");
        exit(EXIT_FAILURE);
    }

    return buf & 1;
}

static void *slow_assignment(void *arg) {
    struct thread_info *tinfo = arg;
    int value = tinfo->value;
    int *a = tinfo->a;

    if (should_wait()) {
        sleep(1);
    }

    *a = value;
}

void main() {
    int a = 0;
    int s;

    struct thread_info *tinfo;

    tinfo = calloc(2, sizeof(struct thread_info));
    if (tinfo == NULL) {
        perror("calloc tinfo");
        exit(EXIT_FAILURE);
    }

    tinfo[0].value = 1; tinfo[0].a = &a;
    tinfo[1].value = 2; tinfo[1].a = &a;


    for (int tnum = 0; tnum < 2; tnum++) {
        s = pthread_create(&tinfo[tnum].thread_id, NULL, &slow_assignment, &tinfo[tnum]);
        if (s != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for (int tnum = 0; tnum < 2; tnum++) {
        s = pthread_join(tinfo[tnum].thread_id, NULL);
        if (s != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    printf("%d\n", a);
 }
