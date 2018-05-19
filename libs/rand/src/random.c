/*-------------------------------------------------------------------------
 *
 * random.c
 *	  random() wrapper
 *
 * Portions Copyright (c) 1996-2017, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 *
 * IDENTIFICATION
 *	  src/port/random.c
 *
 *-------------------------------------------------------------------------
 */

// #include "c.h"

#include "erand48.h"


long
random()
{
	return pg_lrand48();
}
