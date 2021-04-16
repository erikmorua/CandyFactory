
#ifndef __cplusplus
/*
 * This line is only needed if you are compiling with the 
 * C99 dialect although it should not hurt with previous
 * versions of C.
 * This line will expose the clock_gettime function and
 * associated structure timespec.
 */
#define _POSIX_C_SOURCE 199309L
#endif

#include <stdio.h>

#include <time.h>

#include "io.h"

/*
 * i/o functions - assumed to be called in a critical section
 */


/* Handle C++ namespaces, ignore if compiled in C 
 * C++ usually uses this #define to declare the C++ standard.
 * It will not be defined if a C compiler is used.
 */
#ifdef __cplusplus
using namespace std;
#endif

/*
 * Data section - names must align with the enumerated types
 * defined in production.h
 */

/* Names of producer threads and candies */
const char *ProducerNames[] = {"crunchy frog bite", "everlasting escargot sucker"};
const char *ProducerAbbrevs[] = {"CFB", "EES"};

/* Names of consumer threads */
const char *ConsumerNames[] = {"Lucy", "Ethel"};

/* double elapsed_s()
 * show seconds of wall clock time used by the process
 */

double elapsed_s() {
  const double ns_per_s = 1e9; /* nanoseconds per second */

  /* Initialize the first time we call this */
  static struct timespec start;
  static int firsttime = 1;

  struct timespec t;

  /* get elapsed wall clock time for this process
   * note:  use CLOCK_PROCESS_CPUTIME_ID for CPU time (not relevant here
   * as we will be sleeping a lot on the semaphores)
   */
  clock_gettime(CLOCK_REALTIME, &t);

  if (firsttime) {
    /* first time we've called the function, store the current
     * time.  This will not track the cost of the first item
     * produced, but is a reasonable approximation for the
     * whole process and avoids having to create an initialization
     * function.
     * (In C++, we'd just build a timer object and pass it around,
     *  but this approximation provides a simple interface for both
     *  C and C++.)
     */
    firsttime = 0;  /* don't do this again */
    start = t;  /* note when we started */
  }
  
  /* determine time delta from start and convert to s */
  double s = (t.tv_sec - start.tv_sec) + 
    (t.tv_nsec - start.tv_nsec) / ns_per_s ;
  return s;
}

void io_add_type(ProductType producer, int OnBelt[], int Produced[]) {
  int idx;
  int total;

  /* Show what is on the conveyer belt */
  printf("Belt: ");
  total = 0;  /* total produced */
  for (idx=0; idx < ProductTypeN; idx++) {
    if (idx > 0)
      printf(" + ");  /* separator */
    printf("%d %s", OnBelt[idx], ProducerAbbrevs[idx]);
    total += OnBelt[idx];
  }
  printf(" = %d. ", total);

  printf("Added %s.", ProducerNames[producer]);

  /* Show what has been produced */
  total = 0;
  printf(" Produced: ");
  for (idx=0; idx < ProductTypeN; idx++) {
    total += Produced[idx];  /* track total produced */
    if (idx > 0)
      printf(" + ");  /* separator */
    printf("%d %s", Produced[idx], ProducerAbbrevs[idx], Produced[idx]);
  }
  /* total produced over how long */
  printf(" = %d in %.3f s.\n", total, elapsed_s());

  /* This is not really needed, but will be helpful for making sure that you
   * see output prior to a segmentation vioilation.  This is not usually a
   * good practice as we want to avoid ending the CPU burst premaurely which
   * this will do, but it is a helpful technique.
   */
  fflush(stdout);  
};

/*
 * io_remove_type(ConsumerType consumer, ProductType product, 
 *     int OnBelt[], int Consumed[])
 * Show that an item has been removed from the belt and print the current
 * status of the candy factory production.
 * Expects:
 * consumer - Who removed the candy?
 * product:  What kind of product was removed?
 * OnBelt:  Array of number of candies of each type that are
 *   on the belt and have not yet been consumed.
 *   (OnBelt[FrogBite] and OnBelt[Escargot])
 * Consumed:  Array of number of candies of each type that have been
 *  consumed by consumer.
 *
 * Counts reflect numbers after the candy has been removed
 */
void io_remove_type(ConsumerType consumer, ProductType product,
		    int OnBelt[], int Consumed[]) {
  int idx;
  int total;

  /* Show what is on the conveyer belt */
  total = 0;
  printf("Belt: ");
  for (idx=0; idx < ProductTypeN; idx++) {
    if (idx > 0)
      printf(" + ");  /* separator */
    printf("%d %s", OnBelt[idx], ProducerAbbrevs[idx]);
    total += OnBelt[idx];
  }
  printf(" = %d. ", total);

  
  /* Show what has been consumed by consumer */
  printf("%s consumed %s.  %s totals: ",
	 ConsumerNames[consumer],
	 ProducerNames[product],
	 ConsumerNames[consumer]);
  total = 0;
  for (idx=0; idx < ProductTypeN; idx++) {
    if (idx > 0)
      printf(" + ");  /* separator */
    total += Consumed[idx];  /* track total consumed */
    printf("%d %s", Consumed[idx], ProducerAbbrevs[idx]);
  }
  /* total consumed over how long */
  printf(" = %d consumed in %.3f s.\n", total, elapsed_s());

  /* This is not really needed, but will be helpful for making sure that you
   * see output prior to a segmentation vioilation.  This is not usually a
   * good practice as we want to avoid ending the CPU burst premaurely which
   * this will do, but it is a helpful technique.
   */
  fflush(stdout);
};


/*
 * void io_production_report(int produced[], int *consumed[])
 * Show how many candies of each type produced.  Show how many candies consumed by
 * each consumer.
 * produced[] - count for each ProductType
 * *consumed[] - array of pointers to consumed arrays
 *    e.g. consumed[Lucy] points to an array that is indexed by product name
 */
void io_production_report(int produced[], int *consumed[]) {
  int p, c;  /* array indices */
  int total;

  printf("\nPRODUCTION REPORT\n----------------------------------------\n");

  /* show number produced for each producer / candy type */
  for (p=0; p < ProductTypeN; p++) {
    printf("%s producer generated %d candies\n",
	   ProducerNames[p], produced[p]);
  }
  
  /* show number consumed by each consumer */
  for (c=0; c < ConsumerTypeN; c++) {
    printf("%s consumed ", ConsumerNames[c]);
    total = 0;
    for (p=0; p < ProductTypeN; p++) {
      if (p > 0)
	printf(" + ");
      total += consumed[c][p];
      printf("%d %s", consumed[c][p], ProducerAbbrevs[p]);
    }
    printf(" = %d total\n", total);
  }

  printf("Elapsed time %.3f s\n", elapsed_s());
}
