#include "request_queue.h"

#include <assert.h>

#include "common.h"

/**
 * @brief Create a request queue object and associates it with the given mutex
 * and condition variable.
 * 
 * @param p_mutex the mutex for accessing the request queue
 * @param p_cond_var the condition variable for notifying threads 
 * @return struct request_queue* 
 */
struct request_queue* create_request_queue(pthread_mutex_t* p_mutex,
                                           pthread_cond_t* p_cond_var) {
    struct request_queue* req_queue = malloc(sizeof(struct request_queue));
    if (!req_queue) {
        handle_error("create_request_queue:malloc");
    }

    req_queue->mutex = p_mutex;
    req_queue->cond_var = p_cond_var;
    req_queue->is_closed = false;
    req_queue->tail = NULL;
    req_queue->num_requests = 0;
    req_queue->head = NULL;
    return req_queue;
}

/**
 * @brief Adds a request to the tail of the linked list.
 * Notifies all worker threads that a request was added to the queue.
 * Increments the request queue's num_requests.
 * 
 * @param req_queue the request queue
 * @param request_num the request number that is assigned to the new request
 */
void add_request(struct request_queue* req_queue, int request_num) {
    // TODO dynamically allocate memory for a request object
    struct request* new_req = malloc(sizeof(struct request));

    if (!new_req) {
        handle_error("add_request:malloc");
    }
    new_req->number = request_num;
    new_req->next = NULL;

    // TODO complete the code as described in the comments
    /*
        lock mtx
        put the new request at tail of queue
        increment the req_queue->num_requests by 1
        notify waiting theads by calling pthread_cond_broadcast
        unlock mtx
    */

    LOCK_MTX(req_queue->mutex);

    if (req_queue->tail) {
        req_queue->tail->next = new_req;
        req_queue->tail = new_req;
    } else {
        req_queue->tail = new_req;
        req_queue->head = new_req;
    }

    req_queue->num_requests++;
    pthread_cond_broadcast(req_queue->cond_var);
    UNLOCK_MTX(req_queue->mutex);
}

/**
 * @brief Waits for a request to come into the queue, if no requests are in the queue.
 * Otherwise, it returns the oldest (head) request in the queue.
 * The function returns a request when it becomes available.
 * It returns NULL if no requests are available and the queue is closed.
 * 
 * @param req_queue a pointer to the request queue 
 * @return struct request* a pointer to the request object 
 */
struct request* wait_for_request(struct request_queue* req_queue) {
    struct request* req = NULL;
    bool done = false;

    // TODO complete this function
    /*
        lock mtx
        while(!done)
            if there's a request on the head of queue
                take it off the queue
                adjust head pointer appropriately 
                req = the request that was at the head of the queue
                done = true
            else if req_queue is closed
                done = true
            else
                wait on the cond variable (pthread_cond_wait)
        unlock mtx
    */
   
    LOCK_MTX(req_queue->mutex);

    while (!done) {
        if (req_queue->head) {
            struct request* temp = req_queue->head;
            req_queue->head = temp->next;
            if (!req_queue->head) {
                req_queue->tail = NULL;
            }
            req_queue->num_requests--;
            req = temp;
            done = true;
        } else if (req_queue->is_closed) {
            done = true;
        } else {
            pthread_cond_wait(req_queue->cond_var, req_queue->mutex);
        }
    }

    UNLOCK_MTX(req_queue->mutex);

    return req;
}

/**
 * @brief Get the pending request count 
 * 
 * @param req_queue a pointer to the request queue
 * @return int the current pending request count
 */
int get_pending_request_count(struct request_queue* req_queue) {
    // Begin Critical Section
    LOCK_MTX(req_queue->mutex);

    int count = req_queue->num_requests;

    UNLOCK_MTX(req_queue->mutex);
    // End Critical Section
    return count;
}

void delete_request_queue(struct request_queue* req_queue) {
    close_request_queue(req_queue);
    free(req_queue);
}

/**
 * @brief Closes the request queue by setting the is_closed bool
 * attribute of the request queue to true.
 * Notifies all threads that the queue is closed.
 * 
 * @param req_queue a pointer to the request queue
 */
void close_request_queue(struct request_queue* req_queue) {
    // TODO complete this function
    LOCK_MTX(req_queue->mutex);
    req_queue->is_closed = true;
    int rval = pthread_cond_broadcast(req_queue->cond_var);
    if (rval) {
        perror("pthread_cond_broadcast");
    }
    UNLOCK_MTX(req_queue->mutex);
}

bool is_request_queue_closed(struct request_queue* req_queue) {
    // Begin Critical Section
    LOCK_MTX(req_queue->mutex);
    bool closed = req_queue->is_closed;
    UNLOCK_MTX(req_queue->mutex);
    // End Critical Section

    return closed;
}