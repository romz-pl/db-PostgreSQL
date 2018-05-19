#ifndef PS_GLOBAL_MACROS_H
#define PS_GLOBAL_MACROS_H


/* ----------------------------------------------------------------
  *              Section 7:  widely useful macros
  * ----------------------------------------------------------------
  */
 /*
  * Max
  *      Return the maximum of two numbers.
  */
 #define Max(x, y)       ((x) > (y) ? (x) : (y))

 /*
  * Min
  *      Return the minimum of two numbers.
  */
 #define Min(x, y)       ((x) < (y) ? (x) : (y))

 /*
  * Abs
  *      Return the absolute value of the argument.
  */
 #define Abs(x)          ((x) >= 0 ? (x) : -(x))

 /*
  * StrNCpy
  *  Like standard library function strncpy(), except that result string
  *  is guaranteed to be null-terminated --- that is, at most N-1 bytes
  *  of the source string will be kept.
  *  Also, the macro returns no result (too hard to do that without
  *  evaluating the arguments multiple times, which seems worse).
  *
  *  BTW: when you need to copy a non-null-terminated string (like a text
  *  datum) and add a null, do not do it with StrNCpy(..., len+1).  That
  *  might seem to work, but it fetches one byte more than there is in the
  *  text object.  One fine day you'll have a SIGSEGV because there isn't
  *  another byte before the end of memory.  Don't laugh, we've had real
  *  live bug reports from real live users over exactly this mistake.
  *  Do it honestly with "memcpy(dst,src,len); dst[len] = '\0';", instead.
  */
 #define StrNCpy(dst,src,len) \
     do \
     { \
         char * _dst = (dst); \
         Size _len = (len); \
 \
         if (_len > 0) \
         { \
             strncpy(_dst, (src), _len); \
             _dst[_len-1] = '\0'; \
         } \
     } while (0)


 /* Get a bit mask of the bits set in non-long aligned addresses */
 #define LONG_ALIGN_MASK (sizeof(long) - 1)

 /*
  * MemSet
  *  Exactly the same as standard library function memset(), but considerably
  *  faster for zeroing small word-aligned structures (such as parsetree nodes).
  *  This has to be a macro because the main point is to avoid function-call
  *  overhead.   However, we have also found that the loop is faster than
  *  native libc memset() on some platforms, even those with assembler
  *  memset() functions.  More research needs to be done, perhaps with
  *  MEMSET_LOOP_LIMIT tests in configure.
  */
 #define MemSet(start, val, len) \
     do \
     { \
         /* must be void* because we don't know if it is integer aligned yet */ \
         void   *_vstart = (void *) (start); \
         int     _val = (val); \
         Size    _len = (len); \
 \
         if ((((uintptr_t) _vstart) & LONG_ALIGN_MASK) == 0 && \
             (_len & LONG_ALIGN_MASK) == 0 && \
             _val == 0 && \
             _len <= MEMSET_LOOP_LIMIT && \
             /* \
              *  If MEMSET_LOOP_LIMIT == 0, optimizer should find \
              *  the whole "if" false at compile time. \
              */ \
             MEMSET_LOOP_LIMIT != 0) \
         { \
             long *_start = (long *) _vstart; \
             long *_stop = (long *) ((char *) _start + _len); \
             while (_start < _stop) \
                 *_start++ = 0; \
         } \
         else \
             memset(_vstart, _val, _len); \
     } while (0)

 /*
  * MemSetAligned is the same as MemSet except it omits the test to see if
  * "start" is word-aligned.  This is okay to use if the caller knows a-priori
  * that the pointer is suitably aligned (typically, because he just got it
  * from palloc(), which always delivers a max-aligned pointer).
  */
 #define MemSetAligned(start, val, len) \
     do \
     { \
         long   *_start = (long *) (start); \
         int     _val = (val); \
         Size    _len = (len); \
 \
         if ((_len & LONG_ALIGN_MASK) == 0 && \
             _val == 0 && \
             _len <= MEMSET_LOOP_LIMIT && \
             MEMSET_LOOP_LIMIT != 0) \
         { \
             long *_stop = (long *) ((char *) _start + _len); \
             while (_start < _stop) \
                 *_start++ = 0; \
         } \
         else \
             memset(_start, _val, _len); \
     } while (0)


 /*
  * MemSetTest/MemSetLoop are a variant version that allow all the tests in
  * MemSet to be done at compile time in cases where "val" and "len" are
  * constants *and* we know the "start" pointer must be word-aligned.
  * If MemSetTest succeeds, then it is okay to use MemSetLoop, otherwise use
  * MemSetAligned.  Beware of multiple evaluations of the arguments when using
  * this approach.
  */
 #define MemSetTest(val, len) \
     ( ((len) & LONG_ALIGN_MASK) == 0 && \
     (len) <= MEMSET_LOOP_LIMIT && \
     MEMSET_LOOP_LIMIT != 0 && \
     (val) == 0 )

 #define MemSetLoop(start, val, len) \
     do \
     { \
         long * _start = (long *) (start); \
         long * _stop = (long *) ((char *) _start + (Size) (len)); \
     \
         while (_start < _stop) \
             *_start++ = 0; \
     } while (0)


#endif


