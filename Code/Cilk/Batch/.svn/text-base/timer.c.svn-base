#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "timer.h"

/* =================================================== */
/* 
 * Timing functions 
 */
#if !defined(HAVE_TIMER) && defined(_POSIX_TIMERS)
#  define TIMER_DESC "clock_gettime"

#define USE_STD_CREATE
#define USE_STD_DESTROY
#define USE_STD_START
#define USE_STD_STOP
#define USE_STD_ELAPSED

#include <time.h>

struct stopwatch_t
{
  struct timespec t_start_;
  struct timespec t_stop_;
  int is_running_;
};

static
long double
ELAPSED (struct timespec start, struct timespec stop)
{
  return (long double)((stop.tv_sec * 1000000000ll + stop.tv_nsec) - (start.tv_sec * 1000000000ll + start.tv_nsec)) * 1e-9; /* ns to s */
}

#define DECL_RAW(T)     struct timespec T
#define STAMP_RAW(T)    clock_gettime (CLOCK_MONOTONIC, &(T));
#define READ_START(T)   (T).t_start_
#define READ_STOP(T)    (T).t_stop_
#define STAMP_START(T)  { STAMP_RAW (READ_START (T)) ; (T).is_running_ = 1; }
#define STAMP_STOP(T)   { STAMP_RAW (READ_STOP (T)) ; (T).is_running_ = 0; }
#define IS_RUNNING(T)   ((T).is_running_ != 0)

void
stopwatch_init (void)
{
 // fprintf (stderr, "Timer: %s\n", TIMER_DESC);
  //fprintf (stderr, "Timer resolution: %d ns\n", clock_getres ());
  fflush (stderr);
}

#  define HAVE_TIMER 1
#elif !defined(HAVE_TIMER)
#  define TIMER_DESC "gettimeofday"

#define USE_STD_CREATE
#define USE_STD_DESTROY
#define USE_STD_START
#define USE_STD_STOP
#define USE_STD_ELAPSED

#include <sys/time.h>

struct stopwatch_t
{
  struct timeval t_start_;
  struct timeval t_stop_;
  int is_running_;
};

#define DECL_RAW(T)     struct timeval T
#define STAMP_RAW(T)    gettimeofday (&(T), 0)
#define READ_START(T)   (T).t_start_
#define READ_STOP(T)    (T).t_stop_
#define STAMP_START(T)  { STAMP_RAW (READ_START (T)) ; (T).is_running_ = 1; }
#define STAMP_STOP(T)   { STAMP_RAW (READ_STOP (T)) ; (T).is_running_ = 0; }
#define IS_RUNNING(T)   ((T).is_running_ != 0)

static
long double
ELAPSED (struct timeval start, struct timeval stop)
{
  return (long double)(stop.tv_sec - start.tv_sec)
    + (long double)(stop.tv_usec - start.tv_usec)*1e-6;
}

void
stopwatch_init (void)
{
  //fprintf (stderr, "Timer: %s\n", TIMER_DESC);
  //fprintf (stderr, "Timer resolution: ~ 1 us (?)\n");
  fflush (stderr);
}

#  define HAVE_TIMER 1
#endif

#if defined(USE_STD_CREATE)
struct stopwatch_t *
stopwatch_create (void)
{
  struct stopwatch_t* new_timer =
    (struct stopwatch_t *)malloc (sizeof (struct stopwatch_t));
  if (new_timer)
    memset (new_timer, 0, sizeof (struct stopwatch_t));
  return new_timer;
}
#endif

#if defined(USE_STD_DESTROY)
void
stopwatch_destroy (struct stopwatch_t* T)
{
  if (T) {
    stopwatch_stop (T);
    free (T);
  }
}
#endif

#if defined (USE_STD_ELAPSED)
long double
stopwatch_elapsed (const struct stopwatch_t* T)
{
  long double dt = 0;
  if (T) {
    if (IS_RUNNING (*T)) {
      DECL_RAW (stop);
      STAMP_RAW (stop);
      dt = ELAPSED (READ_START (*T), stop);
    } else {
      dt = ELAPSED (READ_START (*T), READ_STOP (*T));
    }
  }
  return dt;
}
#endif


#if defined (USE_STD_START)
void
stopwatch_start (struct stopwatch_t* T)
{
  assert (T);
  STAMP_START (*T);
}
#endif

#if defined (USE_STD_STOP)
long double
stopwatch_stop (struct stopwatch_t* T)
{
  long double dt = 0;
  if (T) {
    if (IS_RUNNING (*T))
      STAMP_STOP (*T);
    dt = stopwatch_elapsed (T);
  }
  return dt;
}
#endif

/* =================================================== */



