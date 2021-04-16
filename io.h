#include "production.h"

/*
 * io_add_type(ProductType product, int OnBelt[], int Produced[])
 * Show that an item has been added to the belt and print the current
 * status of the candy factory production.
 * Expects:
 * product:  What kind of product was  produced?
 * OnBelt:  Array of number of candies of each type that are
 *   on the belt and have not yet been consumed.
 *   (OnBelt[FrogBite] and OnBelt[Escargot])
 * Produced:  Array of number of candies of each type that have been
 *   produced
 *
 * OnBelt and Produced reflect numbers *after* adding the current candy. 
 */
void io_add_type(ProductType, int OnBelt[], int Produced[]); 

/*
 * io_remove_type(Consumers consumer, ProductType product_type, 
 *     int OnBelt[], int Consumed[])
 * Show that an item has been removed from the belt and print the current
 * status of the candy factory production.
 * Expects:
 * consumer - Who removed the candy?
 * product_type:  What kind of product was removed?  As each producer produces
 *   one tyhpe of candy, this is the same as the producer.
 * OnBelt:  Array of number of candies of each type that are
 *   on the belt and have not yet been consumed.
 *   (OnBelt[FrogBite] and OnBelt[Escargot])
 * Consumed:  Array of number of candies of each type that have been
 *  consumed.
 *
 * Counts reflect numbers *after* the candy has been removed
 */
void io_remove_type(ConsumerType, ProductType, int OnBelt[], int Consumed[]);



/*
 * void io_production_report(int produced[], int *consumed[])
 * Show how many candies of each type produced.  Show how many candies consumed by
 * each consumer.
 * produced[] - count for each ProductType
 * *consumed[] - array of pointers to consumed arrays for each consumer
 *    e.g. consumed[Lucy] points to an array that is indexed by product name
 *         (consumed[Lucy][FrogBite] is the number for crunchy frog bites that Lucy consumed)
 */
void io_production_report(int produced[], int *consumed[]);
