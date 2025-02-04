/*
   I am writing this code for learning and research purposes.
   This file has the implementation of process management
*/

#ifndef _LINUX_SCHED_H
#define _LINUX_SCHED_H

/*
  Define 'struct task_struct' and provide the main scheduler
  APIs
*/

#include "/home/haider/linux-6.13.1/include/uapi/linux/sched.h"

#include "/home/haider/linux-6.13.1/include/asm-generic/current.h"
#include "/home/haider/linux-6.13.1/include/linux/thread_info.h"
#include "/home/haider/linux-6.13.1/include/linux/preempt.h"
#include "/home/haider/linux-6.13.1/include/linux/cpumask_types.h"

#include "/home/haider/linux-6.13.1/include/linux/cache.h"
#include "/home/haider/linux-6.13.1/include/linux/irqflags_types.h"
#include "/home/haider/linux-6.13.1/include/linux/smp_types.h"
#include "/home/haider/linux-6.13.1/include/linux/pid_types.h"
#include "/home/haider/linux-6.13.1/include/linux/sem_types.h"
#include "/home/haider/linux-6.13.1/include/linux/shm.h"
#include "/home/haider/linux-6.13.1/include/linux/kmsan_types.h"
#include "/home/haider/linux-6.13.1/include/linux/mutex_types.h"
#include "/home/haider/linux-6.13.1/include/linux/plist_types.h"
#include "/home/haider/linux-6.13.1/include/linux/hrtimer_types.h"
#include "/home/haider/linux-6.13.1/include/linux/timer_types.h"
#include "/home/haider/linux-6.13.1/include/linux/seccomp_types.h"
#include "/home/haider/linux-6.13.1/include/linux/nodemask_types.h"
#include "/home/haider/linux-6.13.1/include/linux/refcount_types.h"
#include "/home/haider/linux-6.13.1/include/linux/resource.h"
#include "/home/haider/linux-6.13.1/include/linux/latencytop.h"
#include "/home/haider/linux-6.13.1/include/linux/sched/prio.h"
#include "/home/haider/linux-6.13.1/include/linux/sched/types.h"
#include "/home/haider/linux-6.13.1/include/linux/signal_types.h"
#include "/home/haider/linux-6.13.1/include/linux/syscall_user_dispatch_types.h"
#include "/home/haider/linux-6.13.1/include/linux/mm_types_task.h"
#include "/home/haider/linux-6.13.1/include/linux/netdevice_xmit.h"
#include "/home/haider/linux-6.13.1/include/linux/task_io_accounting.h"
#include "/home/haider/linux-6.13.1/include/linux/posix-timers_types.h"
#include "/home/haider/linux-6.13.1/include/linux/restart_block.h"
#include "/home/haider/linux-6.13.1/include/uapi/linux/rseq.h"
#include "/home/haider/linux-6.13.1/include/linux/seqlock_types.h"
#include "/home/haider/linux-6.13.1/include/linux/kcsan.h"
#include "/home/haider/linux-6.13.1/include/linux/rv.h"
#include "/home/haider/linux-6.13.1/include/linux/livepatch_sched.h"
#include "/home/haider/linux-6.13.1/include/linux/uidgid_types.h"
#include "/home/haider/linux-6.13.1/include/asm-generic/kmap_size.h"


// task_struct memeber predeclarations

struct audit_context;
struct bio_list;
struct blk_plug;
struct bpf_local_storage;
struct bpf_run_ctx;
struct bpf_net_context;
struct capture_control;
struct cfs_rq;
struct fs_struct;
struct futex_pi_state;
struct io_context;
struct io_uring_task;
struct mempolicy;
struct nameidata;
struct nsproxy;
struct perf_event_context;
struct pid_namespace;
struct pipe_inode_info;
struct rcu_node;
struct reclaim_state;
struct robust_list_head;
struct root_domain;
struct rq;
struct sched_attr;
struct sched_dl_entity;
struct seq_file;
struct sighand_struct;
struct signal_struct;
struct task_delay_info;
struct task_group;
struct task_struct; // process/task descriptor
struct user_event_nm;


#endif
