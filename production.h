#ifndef PRODUCTION_H
#define PRODUCTION_H

/*
 * Arrays with producer and consumer names
 * These can be indexed with the enumerated types below
 * and are defined in io.c
 */
extern const char *ProducerNames[];
extern const char *ProducerAbbrevs[];  
extern const char *ConsumerNames[]; 

/*
 * Enumerated types to be used by the producers and consumers
 * These are expected in the input/output functions (io.h)
 * should be useful in your producer and consumer code.
 */

/*
 * Each producer only produces one type of product,
 * so ProductType is synomonous with the producer type
 */
typedef enum Products {
  FrogBite = 0,   // Crunch frog bites, my favorite!
  Escargot = 1,  // Escargot suckers, slimy yet satisfying...
  ProductTypeN = 2,   // Number of products
} ProductType;

typedef enum Consumers {
  Lucy = 0,
  Ethel = 1,
  ConsumerTypeN = 2,   // Number of consumers
} ConsumerType;


#endif
