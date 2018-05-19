#ifndef PS_RAND_ERAND48_H
#define PS_RAND_ERAND48_H


double
pg_erand48(unsigned short xseed[3]);

long
pg_lrand48(void);

void
pg_srand48(long seed);


#endif


