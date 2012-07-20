/****************************************************************************
**
**  Name:       gki_int.h
**
**  Function:   this file contains constant definitions for GKI internal
**
**
**  Copyright (c) 1999-2011, Broadcom Corp., All Rights Reserved.
**  Broadcom Bluetooth Core. Proprietary and confidential.
**
*****************************************************************************/
#ifndef GKI_INT_H
#define GKI_INT_H

#include "gki_common.h"
#include <pthread.h>

/**********************************************************************
** OS specific definitions
*/
#ifdef ANDROID
#include <sys/times.h>
#endif

typedef struct
{
    pthread_mutex_t     GKI_mutex;
    pthread_t           thread_id[GKI_MAX_TASKS];
    pthread_mutex_t     thread_evt_mutex[GKI_MAX_TASKS];
    pthread_cond_t      thread_evt_cond[GKI_MAX_TASKS];
    pthread_mutex_t     thread_timeout_mutex[GKI_MAX_TASKS];
    pthread_cond_t      thread_timeout_cond[GKI_MAX_TASKS];
    int                 no_timer_suspend;   /* 1: no suspend, 0 stop calling GKI_timer_update() */
    pthread_mutex_t     gki_timer_mutex;
    pthread_cond_t      gki_timer_cond;
    int                 gki_timer_wake_lock_on;
#if (GKI_DEBUG == TRUE)
    pthread_mutex_t     GKI_trace_mutex;
#endif
} tGKI_OS;

/* condition to exit or continue GKI_run() timer loop */
#define GKI_TIMER_TICK_RUN_COND 1
#define GKI_TIMER_TICK_STOP_COND 0
#define GKI_TIMER_TICK_EXIT_COND 2

extern void gki_system_tick_start_stop_cback(BOOLEAN start);

/* Contains common control block as well as OS specific variables */
typedef struct
{
    tGKI_OS     os;
    tGKI_COM_CB com;
} tGKI_CB;


#ifdef __cplusplus
extern "C" {
#endif

#if GKI_DYNAMIC_MEMORY == FALSE
GKI_API extern tGKI_CB  gki_cb;
#else
GKI_API extern tGKI_CB *gki_cb_ptr;
#define gki_cb (*gki_cb_ptr)
#endif

#ifdef __cplusplus
}
#endif

#endif

