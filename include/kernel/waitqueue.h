#ifndef __WAITQUEUE_H__
#define __WAITQUEUE_H__

#include <types.h>
#include <kernel/lock.h>

struct waitqueue_head_t {
	spinlock_t lock;
	struct list_t list;
};

#define INIT_WAIT_HEAD(head) { \
	INIT_SPINLOCK(head.lock); \
	list_link_init(&head.list); \
}

struct waitqueue_t {
	struct task_t *task;
	struct list_t link;
};

#define WQ_EXCLUSIVE	1
#define WQ_ALL		0x7fffffff

#define DEFINE_WAIT(name) \
	struct waitqueue_t name = { \
		.task = current, \
		.link = INIT_LIST_HEAD((name).link), \
	}

extern inline void wq_wait(struct waitqueue_head_t *q, struct waitqueue_t *wait);
extern inline void wq_wake(struct waitqueue_head_t *head, int nr_task);

#endif /* __WAITQUEUE_H__ */