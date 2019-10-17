#ifndef QUEUE_INTERNAL_H
#define QUEUE_INTERNAL_H

#include <pthread.h>

#define Q_ERR_TIMEOUT (-2)

typedef struct element_t{
    struct element_t *next;
    void *data;
    int size;
} element_t;

typedef struct queue_t {
    element_t           *in;
    element_t           *out;
    int                 capacity;
    int                 size;
    pthread_mutex_t     mutex;
    pthread_cond_t      cond;
} queue_t;

extern queue_t* new_queue( int capacity );
extern int enqueue( queue_t *q, void *data, int size );
extern int dequeue( queue_t *q, void **data, int *outsize, int64_t timeout_ms );
extern int queue_get_size( queue_t *q );
extern int queue_lock( queue_t *q );
extern int queue_unlock( queue_t *q );

#endif  /*QUEUE_H*/
