#ifndef _PTHREAD_IMPL_H
#define _PTHREAD_IMPL_H

#include <azalea/syscall.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <limits.h>
#include "libc.h"
#include "atomic.h"
#include "futex.h"
#include <stdint.h>

#define pthread __pthread

struct pthread {
	/* Part 1 -- these fields may be external or
	 * internal (accessed via asm) ABI. Do not change. */
	struct pthread *self;
	void **dtv, *unused1, *unused2;
	uintptr_t sysinfo;
	uintptr_t canary, canary2;
	pid_t tid, pid;

	/* Part 2 -- implementation details, non-ABI. */
	int tsd_used, errno_val;
	volatile int cancel, canceldisable, cancelasync;
	int detached;
	unsigned char *map_base;
	size_t map_size;
	void *stack;
	size_t stack_size;
	void *start_arg;
	void *(*start)(void *);
	void *result;
	struct __ptcb *cancelbuf;
	void **tsd;
	volatile int dead;
	int unblock_cancel;
	volatile int timer_id;
	locale_t locale;
	volatile int killlock[1];
	volatile int exitlock[1];
	volatile int startlock[2];
	unsigned long sigmask[_NSIG/8/sizeof(long)];
	char *dlerror_buf;
	int dlerror_flag;
	void *stdio_locks;
	size_t guard_size;

	/* Part 3 -- the positions of these fields relative to
	 * the end of the structure is external and internal ABI. */
	uintptr_t canary_at_end;
	void **dtv_copy;
};

struct __timer {
	int timerid;
	pthread_t thread;
};

#define __SU (sizeof(size_t)/sizeof(int))

#define _a_stacksize __u.__s[0]
#define _a_guardsize __u.__s[1]
#define _a_stackaddr __u.__s[2]
#define _a_detach __u.__i[3*__SU+0]
#define _a_sched __u.__i[3*__SU+1]
#define _a_policy __u.__i[3*__SU+2]
#define _a_prio __u.__i[3*__SU+3]
#define _m_type __u.__i[0]
#define _m_lock __u.__vi[1]
#define _m_waiters __u.__vi[2]
/*#define _m_prev __u.__p[3]
#define _m_next __u.__p[4]*/
#define _m_count __u.__i[5]
#define _c_shared __u.__p[0]
#define _c_seq __u.__vi[2]
#define _c_waiters __u.__vi[3]
#define _c_clock __u.__i[4]
#define _c_lock __u.__vi[8]
#define _c_head __u.__p[1]
#define _c_tail __u.__p[5]
#define _rw_lock __u.__vi[0]
#define _rw_waiters __u.__vi[1]
#define _rw_shared __u.__i[2]
#define _b_lock __u.__vi[0]
#define _b_waiters __u.__vi[1]
#define _b_limit __u.__i[2]
#define _b_count __u.__vi[3]
#define _b_waiters2 __u.__vi[4]
#define _b_inst __u.__p[3]

#include "pthread_arch.h"

#ifndef CANARY
#define CANARY canary
#endif

#ifndef DTP_OFFSET
#define DTP_OFFSET 0
#endif

#ifndef tls_mod_off_t
#define tls_mod_off_t size_t
#endif

#define SIGTIMER 32
#define SIGCANCEL 33
#define SIGSYNCCALL 34

#define SIGALL_SET ((sigset_t *)(const unsigned long long [2]){ -1,-1 })
#define SIGPT_SET \
	((sigset_t *)(const unsigned long [_NSIG/8/sizeof(long)]){ \
	[sizeof(long)==4] = 3UL<<(32*(sizeof(long)>4)) })
#define SIGTIMER_SET \
	((sigset_t *)(const unsigned long [_NSIG/8/sizeof(long)]){ \
	 0x80000000 })

pthread_t __pthread_self_init(void);

int __clone(int (*)(void *), void *, int, void *, ...);
int __set_thread_area(void *);
int __libc_sigaction(int, const struct sigaction *, struct sigaction *);
int __libc_sigprocmask(int, const sigset_t *, sigset_t *);
void __lock(volatile int *);
void __unmapself(void *, size_t);

void __vm_wait(void);
void __vm_lock(void);
void __vm_unlock(void);

int __timedwait(volatile int *, int, clockid_t, const struct timespec *, int);
int __timedwait_cp(volatile int *, int, clockid_t, const struct timespec *, int);
void __wait(volatile int *, volatile int *, int, int);

/* Azalea deficiency: priv and cnt are ignored */
/* These are only defined outside of the kernel, since the only times they're called inside the kernel relate to the
   use of functions like vfprintf, that are themselves only used in situations where threading is an issue. Therefore
	 it's reasonable to just leave them blank. */
static inline void __wake(volatile void *addr, int cnt, int priv)
{
#ifndef __AZ_KERNEL__
	az_futex_op((volatile int *)addr, FUTEX_WAKE, 0, 0, 0, 0);
#endif
}
static inline void __futexwait(volatile void *addr, int val, int priv)
{
#ifndef __AZ_KERNEL__
	az_futex_op((volatile int *)addr, FUTEX_WAIT, val, 0, 0, 0);
#endif
}

void __acquire_ptc(void);
void __release_ptc(void);
void __inhibit_ptc(void);

void __block_all_sigs(void *);
void __block_app_sigs(void *);
void __restore_sigs(void *);

int32_t get_new_tid();
void release_tid(int32_t);

#define DEFAULT_STACK_SIZE 81920
#define DEFAULT_GUARD_SIZE 4096

#define __ATTRP_C11_THREAD ((void*)(uintptr_t)-1)

#endif
