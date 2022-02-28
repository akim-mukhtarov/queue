#include <stddef.h>     // size_t
#include <stdlib.h>     // calloc, free
#include <assert.h>


#define NODE(value_t)\
Node_##value_t\
{\
        struct Node_##value_t *next;\
        value_t value;\
}

#define QUEUE(value_t)\
Queue_##value_t\
{\
        struct Node_##value_t *buf;\
        struct Node_##value_t *head;\
        struct Node_##value_t *tail;\
        size_t size;\
        size_t maxlen;\
}

#define MAKE_ROUND_LIST(head_p, size, entry_t)\
{\
    assert(size != 0);\
\
    entry_t *curr = head_p;\
    size_t offset = 0;\
\
    while (offset < (size - 1))\
    {\
        curr = head_p + offset;\
        curr->next = curr + 1;\
        ++offset;\
    }\
\
    curr = head_p + offset;\
    curr->next = head_p;\
}


#define QUEUE__CONS(value_t, queue_p, maxlen_)\
({\
    assert((queue_p) != NULL);\
\
    struct Node_##value_t *list = calloc(\
        maxlen_, sizeof(struct Node_##value_t));\
\
    if (list)\
    {\
        MAKE_ROUND_LIST(list, maxlen_, struct Node_##value_t);\
        (queue_p)->buf = list;\
        (queue_p)->head = list;\
        (queue_p)->tail = list;\
        (queue_p)->maxlen=maxlen_;\
    }\
})

// Push to tail
#define QUEUE__PUSH(queue_p, value)\
({\
    assert(queue_p != NULL);\
\
    (queue_p)->tail = (queue_p)->tail->next;\
    (queue_p)->value = value;\
\
    if (queue_p->size < queue->maxlen)\
        ++((queue_p)->size);\
})

// Pop from head
#define QUEUE__POP(queue_p, res_addr)\
({\
    assert(queue_p != NULL);\
\
    *(res_addr) = (queue_p)->head->value;\
    (queue_p)->head = (queue->head)->next;\
\
    if ((queue_p)->size < (queue_p)->maxlen)\
        --((queue_p)->size);\
})


#define QUEUE__FRONT(queue_p, res_addr)\
({\
    assert(queue_p != NULL);\
    *(res_addr) = (queue_p)->head->value;\
})


#define QUEUE__BACK(queue_p, res_addr)\
({\
    assert(queue_p != NULL);\
    *(res_addr) = (queue_p)->tail->value;\
})

// works only if mem is contiguos!
#define QUEUE__REPR(queue_p, repr)\
({\
    assert(queue_p != NULL);\
\
    for (size_t i = 0; i < (queue_p)->size; ++i)\
        repr((queue_p)->buf + i);\
})

#define QUEUE__DELETE(queue_p)\
({\
    assert(queue_p != NULL);\
    free((queue_p)->buf);\
    free(queue_p);\
})
