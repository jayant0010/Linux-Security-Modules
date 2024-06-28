/*
 * OSS Linux Security Module
 *
 * Author: Saijayanth chidirala <saijayan.chidira@ufl.edu>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2, as
 * published by the Free Software Foundation.
 *
 */

#include <linux/lsm_hooks.h>
#include <linux/sysctl.h>
#include <linux/ptrace.h>
#include <linux/prctl.h>
#include <linux/ratelimit.h>
#include <linux/workqueue.h>
#include <linux/string_helpers.h>
#include <linux/task_work.h>
#include <linux/sched.h>
#include <linux/spinlock.h>

#include <linux/time.h>
#include <linux/cred.h>


/*Assignment 4 Define the hook function for settimeofday system call */

static int oss_settime(const struct timespec *ts, const struct timezone *tz)
{
    struct timespec now;
    getnstimeofday(&now);

    if(!ts){
      return -EFAULT;
    }

/* Check if the time is set to a value earlier than the current system time */
    if (timespec_compare(ts, &now) < 0) {
        pr_info("OSS: Assignment 4 Attempt to set time to an earlier value rejected\n");
        return -EPERM;
    }

	pr_info("OSS: Assignment 4 Attempt to set time allowed\n");
    /* Allow the time to be set */
    return 0;
}


static struct security_hook_list oss_hooks[] __lsm_ro_after_init = {
	LSM_HOOK_INIT(settime, oss_settime),
};


void __init oss_add_hooks(void)
{
	pr_info("OSS: Assignment 4 calling security_add_hooks.\n");
	security_add_hooks(oss_hooks, ARRAY_SIZE(oss_hooks), "oss-lsm");
}
