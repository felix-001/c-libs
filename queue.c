#include "public.h"
#include "queue.h"

#define QUEUE_LOGI(args...) LOGI("QUEUE",args)
#define QUEUE_LOGE(args...) LOGE("QUEUE",args)
#define QUEUE_LOGT(args...) LOGT("QUEUE",args)

queue_t* new_queue( int capacity )
{
    queue_t *q = NULL;

    CALLOC_STRUCT( q, queue_t );
    q->size = 0;
    q->capacity = capacity;
    q->in = q->out = NULL;
    QUEUE_LOGI("size : %d", q->size );
    pthread_mutex_init( &q->mutex, NULL );
    pthread_cond_init( &q->cond, NULL );

err:
    return q;
}

int enqueue( queue_t *q, void *data, int size )
{
    element_t *elem = NULL;
    int ret = -1;

    PARAM_CHECK( !q || !data );

    pthread_mutex_lock( &q->mutex );
    if ( q->size >= q->capacity ) {
        QUEUE_LOGE("queue full");
        goto err;
    }
    CALLOC_STRUCT( elem, element_t );
    elem->data = data;
    elem->size = size;
    if ( q->size == 0 ) {
        q->in = q->out = elem;
    } else {
        q->in->next = elem;
        q->in = elem;
    }
    q->size ++;
    QUEUE_LOGT("q size: %d", q->size );
    pthread_cond_signal( &q->cond );
    pthread_mutex_unlock( &q->mutex );

    return 0;
err:
    pthread_mutex_unlock( &q->mutex );
    return ret;
}

int dequeue( queue_t *q, void **data, int *outsize, int64_t timeout_ms )
{
    element_t *elem = NULL;

    PARAM_CHECK( !q || !data );

    pthread_mutex_lock( &q->mutex );

    while ( q->size == 0 ) {
        int ret = 0;
        struct timeval now;
        struct timespec timeout;

        gettimeofday(&now, NULL);
        timeout.tv_sec = now.tv_sec + (now.tv_usec + timeout_ms) / 1000000;
        timeout.tv_nsec = ((now.tv_usec + timeout_ms) % 1000000)*1000;
        ret = pthread_cond_timedwait( &q->cond, &q->mutex, &timeout );
        if ( ret == ETIMEDOUT ) {
            pthread_mutex_unlock( &q->mutex );
            return Q_ERR_TIMEOUT;
        }
    }

    if ( !q->out ) {
        QUEUE_LOGE("check queue out error");
        goto err;
    }
    elem = q->out;
    *data = elem->data;
    if ( q->size > 1 ) {
        q->out = elem->next;
    } else {
        q->in = q->out = NULL;
    }
    free( elem);
    q->size--;
    if ( outsize )
        *outsize = elem->size;

    pthread_mutex_unlock( &q->mutex );

    return 0;

err:
    return -1;
}

int queue_get_size( queue_t *q )
{
    return q->size;
}

int queue_lock( queue_t *q )
{
    pthread_mutex_lock( &q->mutex );

    return 0;
}

int queue_unlock( queue_t *q )
{
    pthread_mutex_unlock( &q->mutex );

    return 0;
}
