#ifndef PS_INCLUDE_GLOBAL_ASSERTIONS_H
#define PS_INCLUDE_GLOBAL_ASSERTIONS_H

/* ----------------------------------------------------------------
  *              Section 6:  assertions
  * ----------------------------------------------------------------
  */

 /*
  * USE_ASSERT_CHECKING, if defined, turns on all the assertions.
  * - plai  9/5/90
  *
  * It should _NOT_ be defined in releases or in benchmark copies
  */

 /*
  * Assert() can be used in both frontend and backend code. In frontend code it
  * just calls the standard assert, if it's available. If use of assertions is
  * not configured, it does nothing.
  */
 #ifndef USE_ASSERT_CHECKING

 #define Assert(condition)   ((void)true)
 #define AssertMacro(condition)  ((void)true)
 #define AssertArg(condition)    ((void)true)
 #define AssertState(condition)  ((void)true)
 #define AssertPointerAlignment(ptr, bndr)   ((void)true)
 #define Trap(condition, errorType)  ((void)true)
 #define TrapMacro(condition, errorType) (true)

 #elif defined(FRONTEND)

 #include <assert.h>
 #define Assert(p) assert(p)
 #define AssertMacro(p)  ((void) assert(p))
 #define AssertArg(condition) assert(condition)
 #define AssertState(condition) assert(condition)
 #define AssertPointerAlignment(ptr, bndr)   ((void)true)

 #else                           /* USE_ASSERT_CHECKING && !FRONTEND */

 /*
  * Trap
  *      Generates an exception if the given condition is true.
  */
 #define Trap(condition, errorType) \
     do { \
         if (condition) \
             ExceptionalCondition(CppAsString(condition), (errorType), \
                                  __FILE__, __LINE__); \
     } while (0)

 /*
  *  TrapMacro is the same as Trap but it's intended for use in macros:
  *
  *      #define foo(x) (AssertMacro(x != 0), bar(x))
  *
  *  Isn't CPP fun?
  */
 #define TrapMacro(condition, errorType) \
     ((bool) (! (condition) || \
              (ExceptionalCondition(CppAsString(condition), (errorType), \
                                    __FILE__, __LINE__), 0)))

 #define Assert(condition) \
         Trap(!(condition), "FailedAssertion")

 #define AssertMacro(condition) \
         ((void) TrapMacro(!(condition), "FailedAssertion"))

 #define AssertArg(condition) \
         Trap(!(condition), "BadArgument")

 #define AssertState(condition) \
         Trap(!(condition), "BadState")

 /*
  * Check that `ptr' is `bndr' aligned.
  */
 #define AssertPointerAlignment(ptr, bndr) \
     Trap(TYPEALIGN(bndr, (uintptr_t)(ptr)) != (uintptr_t)(ptr), \
          "UnalignedPointer")

 #endif                          /* USE_ASSERT_CHECKING && !FRONTEND */

 /*
  * Macros to support compile-time assertion checks.
  *
  * If the "condition" (a compile-time-constant expression) evaluates to false,
  * throw a compile error using the "errmessage" (a string literal).
  *
  * gcc 4.6 and up supports _Static_assert(), but there are bizarre syntactic
  * placement restrictions.  These macros make it safe to use as a statement
  * or in an expression, respectively.
  *
  * Otherwise we fall back on a kluge that assumes the compiler will complain
  * about a negative width for a struct bit-field.  This will not include a
  * helpful error message, but it beats not getting an error at all.
  */
 #ifdef HAVE__STATIC_ASSERT
 #define StaticAssertStmt(condition, errmessage) \
     do { _Static_assert(condition, errmessage); } while(0)
 #define StaticAssertExpr(condition, errmessage) \
     ({ StaticAssertStmt(condition, errmessage); true; })
 #else                           /* !HAVE__STATIC_ASSERT */
 #define StaticAssertStmt(condition, errmessage) \
     ((void) sizeof(struct { int static_assert_failure : (condition) ? 1 : -1; }))
 #define StaticAssertExpr(condition, errmessage) \
     StaticAssertStmt(condition, errmessage)
 #endif                          /* HAVE__STATIC_ASSERT */


 /*
  * Compile-time checks that a variable (or expression) has the specified type.
  *
  * AssertVariableIsOfType() can be used as a statement.
  * AssertVariableIsOfTypeMacro() is intended for use in macros, eg
  *      #define foo(x) (AssertVariableIsOfTypeMacro(x, int), bar(x))
  *
  * If we don't have __builtin_types_compatible_p, we can still assert that
  * the types have the same size.  This is far from ideal (especially on 32-bit
  * platforms) but it provides at least some coverage.
  */
 #ifdef HAVE__BUILTIN_TYPES_COMPATIBLE_P
 #define AssertVariableIsOfType(varname, typename) \
     StaticAssertStmt(__builtin_types_compatible_p(__typeof__(varname), typename), \
     CppAsString(varname) " does not have type " CppAsString(typename))
 #define AssertVariableIsOfTypeMacro(varname, typename) \
     ((void) StaticAssertExpr(__builtin_types_compatible_p(__typeof__(varname), typename), \
      CppAsString(varname) " does not have type " CppAsString(typename)))
 #else                           /* !HAVE__BUILTIN_TYPES_COMPATIBLE_P */
 #define AssertVariableIsOfType(varname, typename) \
     StaticAssertStmt(sizeof(varname) == sizeof(typename), \
     CppAsString(varname) " does not have type " CppAsString(typename))
 #define AssertVariableIsOfTypeMacro(varname, typename) \
     ((void) StaticAssertExpr(sizeof(varname) == sizeof(typename),       \
      CppAsString(varname) " does not have type " CppAsString(typename)))
 #endif                          /* HAVE__BUILTIN_TYPES_COMPATIBLE_P */


#endif

