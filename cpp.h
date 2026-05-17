#ifndef CPP_H
#define CPP_H
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-macro-identifier"

/* cpp.h - Organized C Preprocessor Utility Macros
 * 
 * This header provides a collection of preprocessor macros for functional
 * programming patterns, string manipulation, and other utility operations.
 * 
 * MACRO NAMING CONVENTIONS:
 * 
 * Public macros: UPPERCASE or UPPERCASE_WITH_UNDERSCORES
 * Helper macros: _UPPERCASE_WITH_LEADING_UNDERSCORE (not intended for direct use)
 * 
 * To extend any of these macro families, add new helper macros following
 * the patterns described in the section comments below.
 */

/*******************************************************************************
 * Basic Function Composition Macros
 ******************************************************************************/

/* Identity function - returns its argument unchanged
 */
#define IDENTITY(x) x

/* Apply function f to arguments
 */
#define APPLY(x, ...) x(__VA_ARGS__)

/* Function composition macros - chain function calls
 */
#define COMPOSE(f, g, ...) f(g(__VA_ARGS__))
#define COMPOSE3(f, g, h, ...) f(g(h(__VA_ARGS__)))
#define COMPOSE4(f, g, h, i, ...) f(g(h(i(__VA_ARGS__))))

/*******************************************************************************
 * Argument Expansion Macros
 ******************************************************************************/

/* Expand arguments through other macros
 * 
 * Note: To add support for expanding through new macros, define a new
 * _EXPAND_ARG_MACRO_NAME helper that applies the corresponding macro.
 */
#define EXPAND_ARG(x) _EXPAND_ARG_ ## x
#define _EXPAND_ARG_APPLY(...) APPLY(__VA_ARGS__)
#define _EXPAND_ARG_CAT(...) CAT(__VA_ARGS__)
#define _EXPAND_ARG_CAT3(...) CAT3(__VA_ARGS__)
#define _EXPAND_ARG_HEAD(...) HEAD(__VA_ARGS__)
#define _EXPAND_ARG_SND(...) SND(__VA_ARGS__)
#define _EXPAND_ARG_SECOND(...) SECOND(__VA_ARGS__)
#define _EXPAND_ARG_TAIL(...) TAIL(__VA_ARGS__)
#define _EXPAND_ARG_DROP(x) _EXPAND_ARG_DROP_ ## x
#define _EXPAND_ARG_DROP_2(...) DROP(2)(__VA_ARGS__)
#define _EXPAND_ARG_EQUAL_INTER(...) EQUAL_INTER(__VA_ARGS__)

/*******************************************************************************
 * Tuple/Argument Manipulation Macros
 ******************************************************************************/

/* Extract elements from argument lists
 * 
 * Note: These are fundamental macros that other utility macros build upon.
 * To add additional extractors, follow the pattern shown below.
 */
#define HEAD(x, ...) x
#define TAIL(_, ...) __VA_ARGS__
#define SND(_, x, ...) x
#define THD(_, __, x, ...) x

/* Enumeration 2 tuple
 *
 * Note: Only works with 8 bit (<= 256) enums
 */
#define TUPLE(x, y) \
  ( ( ((int)(x) & 0x00FF) << 8 ) \
  | ( ((int)(y) & 0x00FF) << 0 ) \
  )

/* Enumeration 3 tuple
 *
 * Note: Only works with 5 bit (<= 32) enums
 */
#define TUPLE3(x, y, z) \
  ( ( ((int)(x) & 0x001F) << 10 ) \
  | ( ((int)(y) & 0x001F) <<  5 ) \
  | ( ((int)(z) & 0x001F) <<  0 ) \
  )

/* Enumeration 4 tuple
 *
 * Note: Only works with 6 bit (<= 16) enums
 */
#define TUPLE4(w, x, y, z) \
  ( ( ((int)(w) & 0x000F) << 12 ) \
  | ( ((int)(x) & 0x000F) <<  8 ) \
  | ( ((int)(y) & 0x000F) <<  4 ) \
  | ( ((int)(z) & 0x000F) <<  0 ) \
  )

#define FST4(x) (((x) >>  0) & 0x000F)
#define SND4(x) (((x) >>  4) & 0x000F)
#define THD4(x) (((x) >>  8) & 0x000F)
#define FTH4(x) (((x) >> 12) & 0x000F)

#define FST4_SET(x, y) ((((int)(x) & 0x000F) <<  0) | ((int)(y) & ~0x000F))
#define SND4_SET(x, y) ((((int)(x) & 0x000F) <<  4) | ((int)(y) & ~0x00F0))
#define THD4_SET(x, y) ((((int)(x) & 0x000F) <<  8) | ((int)(y) & ~0x0F00))
#define FTH4_SET(x, y) ((((int)(x) & 0x000F) << 12) | ((int)(y) & ~0xF000))

/* Alias macros for readability
 * 
 * Note: These macros need corresponding implementation helpers prefixed with underscore.
 * To extend, define both the alias and its helper with matching names.
 */
#define FIRST(f) _FIRST_ ## f
#define SECOND(f) _SECOND_ ## f

/* Drop elements from argument lists
 * 
 * Note: To add a new DROP macro for N elements, define:
 * #define DROP_N(...) a pattern with N underscores followed by __VA_ARGS__
 */
#define DROP(x) _DROP_ ## x
#define _DROP_2(_, __, ...) __VA_ARGS__

/* Reorder arguments
 */
#define FLIP(x, y, ...) y, x, __VA_ARGS__

/* Empty argument list
 */
#define EMPTY(...)

/*******************************************************************************
 * Concatenation and String Manipulation
 ******************************************************************************/

#define STRINGIFY(x) #x

#define NAME_CAT(x, y) _NAME_CAT(x, y)
#define _NAME_CAT(x, y) x ## y

/* Concatenation macros
 */
#define CAT(x, y) x y
#define CAT3(x, y, z) x y z

/* Prefix manipulation
 * 
 * Note: To add support for new prefixes, define a new PREFIX_X macro
 * where X is the name you want to support.
 */
#define PREFIX(x) _PREFIX_##x
#define _PREFIX_Log(x) _DEFER_STRING_CAT(Log, x)
#define _DEFER_STRING_CAT(x, y) x ## y

/* String copy with bounds checking
 * 
 * Note: To add support for new source/length combinations, define a new
 * _STRNCPY_source_length helper macro for each specific case.
 */
#define STRNCPY(from, n) _STRNCPY_ ## from ## _ ## n
#define _STRNCPY_path_PATH_MAX(to, ...) strncpy(to, path, PATH_MAX)

/*******************************************************************************
 * Operators and Expression Helpers
 ******************************************************************************/

/* Infix operator macros
 */
#define INTER(x) x ## _INTER
#define else_INTER(x, y, ...) x else y

#define COMMA_INTER(x, ...) x, __VA_ARGS__
#define AND_INTER(x, y)   ((x) && (y))
#define PLUS_INTER(x, y)  ((x) + (y))
#define EQUAL_INTER(x, y) x = (y)
#define STAR_INTER(x, y)  ((x) * (y))

/* Expression terminators
 */
#define END_EXPRESSION(x, ...) x;
#define END_EXPRESSION_INTER(x, y, ...) END_EXPRESSION(x) y

/* Switch case return macros
 * 
 * Note: These macros simplify common switch-case pattern implementations.
 * CASE_RETURN_STRINGIFIED converts an enum value to its string representation.
 * CASE_RETURN provides a shorthand for returning a specific value for a case.
 */
#define CASE_RETURN_STRINGIFIED(x) case x: return STRINGIFY(x)
#define CASE_RETURN(x, y, ...) case x: return y

/* Maximum value macro
 */
#ifdef CPP_DEV
#define MAX(x, y) max(x, y)
#else
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#endif

/* Minimum value macro
 */
#ifdef CPP_DEV
#define MIN(x, y) min(x, y)
#else
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#endif

/*******************************************************************************
 * Control Flow Helper Macros
 ******************************************************************************/

/* Switch case fallthrough annotation
 * 
 * Note: This macro explicitly indicates intentional fallthrough in switch 
 * statements to silence compiler warnings. It provides cross-compiler 
 * compatibility by selecting the appropriate implementation based on the
 * compiler and C/C++ standard version.
 *
 * Usage: Place at the end of a case block before the next case label:
 *   case 1:
 *     doSomething();
 *     FALLTHROUGH;
 *   case 2:
 *     doSomethingElse();
 */
#if defined(__cplusplus) && __cplusplus >= 201703L
  /* C++17 and later - use standard attribute */
  #define FALLTHROUGH [[fallthrough]]
#elif defined(__clang__)
  /* Clang - use clang-specific attribute */
  #define FALLTHROUGH __attribute__((fallthrough))
#elif defined(__GNUC__) && (__GNUC__ >= 7)
  /* GCC 7 and later - use GCC attribute */
  #define FALLTHROUGH __attribute__((fallthrough))
#else
  /* Other compilers - use comment style that GCC recognizes */
  #define FALLTHROUGH do {} while (0) /* fallthrough */
#endif

/*******************************************************************************
 * Argument Counting
 ******************************************************************************/

#define NARGS(...) _NARGS(__VA_ARGS__,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#define _NARGS(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,N,...) N

/*******************************************************************************
 * Folds
 ******************************************************************************/

#define MAP_REDUCE(reduce, map, constant, ...) APPLY(NAME_CAT(_MR, NARGS(__VA_ARGS__)), reduce, map, constant, __VA_ARGS__)
#define _MR1(  r, m, c, a)      m(c, a)
#define _MR2(  r, m, c, a, ...) r(m(c, a),  _MR1(r, m, c, __VA_ARGS__))
#define _MR3(  r, m, c, a, ...) r(m(c, a),  _MR2(r, m, c, __VA_ARGS__))
#define _MR4(  r, m, c, a, ...) r(m(c, a),  _MR3(r, m, c, __VA_ARGS__))
#define _MR5(  r, m, c, a, ...) r(m(c, a),  _MR4(r, m, c, __VA_ARGS__))
#define _MR6(  r, m, c, a, ...) r(m(c, a),  _MR5(r, m, c, __VA_ARGS__))
#define _MR7(  r, m, c, a, ...) r(m(c, a),  _MR6(r, m, c, __VA_ARGS__))
#define _MR8(  r, m, c, a, ...) r(m(c, a),  _MR7(r, m, c, __VA_ARGS__))
#define _MR9(  r, m, c, a, ...) r(m(c, a),  _MR8(r, m, c, __VA_ARGS__))
#define _MR10( r, m, c, a, ...) r(m(c, a),  _MR9(r, m, c, __VA_ARGS__))
#define _MR11( r, m, c, a, ...) r(m(c, a), _MR10(r, m, c, __VA_ARGS__))
#define _MR12( r, m, c, a, ...) r(m(c, a), _MR11(r, m, c, __VA_ARGS__))
#define _MR13( r, m, c, a, ...) r(m(c, a), _MR12(r, m, c, __VA_ARGS__))
#define _MR14( r, m, c, a, ...) r(m(c, a), _MR13(r, m, c, __VA_ARGS__))
#define _MR15( r, m, c, a, ...) r(m(c, a), _MR14(r, m, c, __VA_ARGS__))
#define _MR16( r, m, c, a, ...) r(m(c, a), _MR15(r, m, c, __VA_ARGS__))
#define _MR17( r, m, c, a, ...) r(m(c, a), _MR16(r, m, c, __VA_ARGS__))
#define _MR18( r, m, c, a, ...) r(m(c, a), _MR17(r, m, c, __VA_ARGS__))
#define _MR19( r, m, c, a, ...) r(m(c, a), _MR18(r, m, c, __VA_ARGS__))
#define _MR20( r, m, c, a, ...) r(m(c, a), _MR19(r, m, c, __VA_ARGS__))

/*******************************************************************************
 * Table Selection
 ******************************************************************************/

/* COLUMNS(table, col1, col2, ...)
 *
 * Extract columns by name from a table macro, in any order.
 *
 * Table definition format:
 *   #define <table-name>(cons, map, ...) \
 *     / *                  | <col1>  | <col2>  | <col3>  |* /\
 *     cons(map(__VA_ARGS__ , r1c1    , r1c2    , r1c3    ),  \
 *     cons(map(__VA_ARGS__ , r2c1    , r2c2    , r2c3    ),  \
 *          map(__VA_ARGS__ , r3c1    , r3c2    , r3c3    )   \
 *         ))
 *
 * Column index definitions:
 *   #define COLUMN_<table-name>_<column-name>  <column-index>
 *
 * Single column:
 *   <table-name>(CONS, APPLY, COLUMNS(<table-name>, <col1>))
 *
 * Multiple columns (requires COMPOSE and EXPAND_ARG to unpack):
 *   <table-name>(CONS, COMPOSE, EXPAND_ARG(COMBINER), APPLY, COLUMNS(<table-name>, <col2>, <col1>))
 */
#define COLUMNS(table, ...) _N_COLUMNS(NARGS(__VA_ARGS__)), MAP_REDUCE(COMMA_INTER, NAME_CAT, COLUMN_ ## table ## _, __VA_ARGS__)
#define _N_COLUMNS(n) _N_COLUMNS_(n)
#define _N_COLUMNS_(n) _ ## n ## _ ## COLUMNS

#define _N_COLUMNS_APPLY(x, ...) x(__VA_ARGS__)
#define _1_COLUMNS(a, ...) _N_COLUMNS_APPLY(_COLUMN_ ## a, __VA_ARGS__)
#define _2_COLUMNS(a, b, ...) _N_COLUMNS_APPLY(_COLUMN_ ## a, __VA_ARGS__), _N_COLUMNS_APPLY(_COLUMN_ ## b, __VA_ARGS__)
#define _3_COLUMNS(a, b, c, ...) _N_COLUMNS_APPLY(_COLUMN_ ## a, __VA_ARGS__), _2_COLUMNS(b, c, __VA_ARGS__)
#define _4_COLUMNS(a, b, c, d, ...) _N_COLUMNS_APPLY(_COLUMN_ ## a, __VA_ARGS__), _3_COLUMNS(b, c, d, __VA_ARGS__)

#define _COLUMN_1(...) HEAD(__VA_ARGS__,)
#define _COLUMN_2(x, ...) _COLUMN_1(__VA_ARGS__)
#define _COLUMN_3(x, ...) _COLUMN_2(__VA_ARGS__)
#define _COLUMN_4(x, ...) _COLUMN_3(__VA_ARGS__)

/* TABLE_LOOKUP(table, key_col_name, key, result_col_name, default_val)
 *
 * Look up a value from a table macro by selecting the row whose
 * key column equals key, returning the corresponding result
 * column. Produces a nested ternary chain that the compiler
 * constant-folds when key is a compile-time constant.
 * Evaluates to default_val if no row has a key equal to key.
 */
#define TABLE_LOOKUP(table, key_col_name, key, result_col_name, default_val) \
  table(CAT, _ROW_MATCH, key, COLUMNS(table, key_col_name, result_col_name)) (default_val)

#define _ROW_MATCH(key, _, key_col, val_col, ...) ((key) == (_1_COLUMNS(key_col, __VA_ARGS__))) ? (_1_COLUMNS(val_col, __VA_ARGS__)) :

/*******************************************************************************
 * Defintion Helpers
 ******************************************************************************/

#define ENUMERATORS(name_column, value_column, table) \
  table(COMMA_INTER, COMPOSE, EXPAND_ARG(EQUAL_INTER), APPLY, COLUMNS(table, name_column, value_column))

/*******************************************************************************
 * Pointer Type Helpers
 ******************************************************************************/

/* Pointer type shortcuts
 */
#define FP(x) const x *const
#define CP *const

/*******************************************************************************
 * Assignment Macros
 ******************************************************************************/

/* Value assignment macros
 * 
 * Note: To add new assignment types, define a new _ASSIGN_VALUE helper
 * where VALUE is the specific value or type to assign.
 */
#define ASSIGN(x, ...) _ASSIGN_##x
#define _ASSIGN_1(x, ...) x = 1
#define _ASSIGN_NULL(x, ...) x = NULL
#define _ASSIGN_INT_MIN(x, ...) x = INT_MIN
#define _ASSIGN_EMPTY(...)

/* Negated value assignment macros
 * 
 * Note: To add new negated assignments, define a new _ASSIGN_NEG_VALUE helper
 * where VALUE is the specific value to negate and assign.
 */
#define ASSIGN_NEG(x, ...) _ASSIGN_NEG_ ## x
#define _ASSIGN_NEG_1(x, ...) x = -1

/* Pointer dereferencing assignment
 * 
 * Note: To add new dereferencing assignments, define a new _ASSIGN_DEREF_VALUE helper
 * where VALUE is the specific value to assign through the pointer.
 */
#define ASSIGN_DEREF(x, ...) _ASSIGN_DEREF_##x
#define _ASSIGN_DEREF_0(x, ...) *x = 0

/*******************************************************************************
 * Structure Field Access
 ******************************************************************************/

/* Structure field access helpers
 * 
 * Note: To add support for dereferencing from new structures, define a new
 * _DREF_FROM_structvar helper where structvar is the structure variable name.
 */
#define DREF_FROM(x) _DREF_FROM_ ## x
#define _DREF_FROM_f(x) f-> x
#define _SECOND_DREF_FROM(f) _SECOND_DREF_FROM_ ## f
#define _SECOND__DREF_FROM_f(...) \
  EXPAND_ARG(HEAD)(__VA_ARGS__), \
  _DREF_FROM_f(EXPAND_ARG(SND)(__VA_ARGS__)), \
  EXPAND_ARG(DROP(2))(__VA_ARGS__)

/*******************************************************************************
 * Equivalence Testing
 ******************************************************************************/

/* Value comparison macros
 * 
 * Note: To add support for comparing with new values, define a new
 * _EQUIVALENT_VALUE helper where VALUE is the specific value to compare against.
 */
#define EQUIVALENT(x) _EQUIVALENT_ ## x
#define _EQUIVALENT_NULL(x, ...) NULL == (x)
#define _EQUIVALENT_INT_MIN(x, ...) INT_MIN == (x)
#define _EQUIVALENT_EMPTY(...) NULL == NULL

/* Pointer dereferencing comparison
 * 
 * Note: To add support for comparing dereferenced pointers with new values,
 * define a new _EQUIVALENT_DEREF_VALUE helper where VALUE is the value to compare.
 */
#define EQUIVALENT_DEREF(x) _EQUIVALENT_DEREF_ ## x
#define _EQUIVALENT_DEREF_0(x, ...) 0 == *(x)

/*******************************************************************************
 * Repeating a Macro Function
 ******************************************************************************/
#define REPEAT_N(n, cons, map, ...) APPLY(_REPEAT_ ## n, n, cons, map, __VA_ARGS__)
#define _REPEAT_1(  n, cons, map, ...)      map(__VA_ARGS__,  1, n)
#define _REPEAT_2(  n, cons, map, ...) cons(_REPEAT_1(  n, cons, map, __VA_ARGS__), map(__VA_ARGS__,  2, n))
#define _REPEAT_3(  n, cons, map, ...) cons(_REPEAT_2(  n, cons, map, __VA_ARGS__), map(__VA_ARGS__,  3, n))
#define _REPEAT_4(  n, cons, map, ...) cons(_REPEAT_3(  n, cons, map, __VA_ARGS__), map(__VA_ARGS__,  4, n))
#define _REPEAT_5(  n, cons, map, ...) cons(_REPEAT_4(  n, cons, map, __VA_ARGS__), map(__VA_ARGS__,  5, n))
#define _REPEAT_6(  n, cons, map, ...) cons(_REPEAT_5(  n, cons, map, __VA_ARGS__), map(__VA_ARGS__,  6, n))
#define _REPEAT_7(  n, cons, map, ...) cons(_REPEAT_6(  n, cons, map, __VA_ARGS__), map(__VA_ARGS__,  7, n))
#define _REPEAT_8(  n, cons, map, ...) cons(_REPEAT_7(  n, cons, map, __VA_ARGS__), map(__VA_ARGS__,  8, n))
#define _REPEAT_9(  n, cons, map, ...) cons(_REPEAT_8(  n, cons, map, __VA_ARGS__), map(__VA_ARGS__,  9, n))
#define _REPEAT_10( n, cons, map, ...) cons(_REPEAT_9(  n, cons, map, __VA_ARGS__), map(__VA_ARGS__, 10, n))
#define _REPEAT_11( n, cons, map, ...) cons(_REPEAT_10( n, cons, map, __VA_ARGS__), map(__VA_ARGS__, 11, n))
#define _REPEAT_12( n, cons, map, ...) cons(_REPEAT_11( n, cons, map, __VA_ARGS__), map(__VA_ARGS__, 12, n))
#define _REPEAT_13( n, cons, map, ...) cons(_REPEAT_12( n, cons, map, __VA_ARGS__), map(__VA_ARGS__, 13, n))
#define _REPEAT_14( n, cons, map, ...) cons(_REPEAT_13( n, cons, map, __VA_ARGS__), map(__VA_ARGS__, 14, n))
#define _REPEAT_15( n, cons, map, ...) cons(_REPEAT_14( n, cons, map, __VA_ARGS__), map(__VA_ARGS__, 15, n))
#define _REPEAT_16( n, cons, map, ...) cons(_REPEAT_15( n, cons, map, __VA_ARGS__), map(__VA_ARGS__, 16, n))
#define _REPEAT_17( n, cons, map, ...) cons(_REPEAT_16( n, cons, map, __VA_ARGS__), map(__VA_ARGS__, 17, n))
#define _REPEAT_18( n, cons, map, ...) cons(_REPEAT_17( n, cons, map, __VA_ARGS__), map(__VA_ARGS__, 18, n))
#define _REPEAT_19( n, cons, map, ...) cons(_REPEAT_18( n, cons, map, __VA_ARGS__), map(__VA_ARGS__, 19, n))
/* ... */

/* The C preprocessor will not recursively expand a macro that is currently
 * being expanded (§6.10.3.4). REPEAT_ALT is a duplicate of REPEAT_N with
 * a distinct name, allowing it to be used inside map functions passed to
 * REPEAT_N without being suppressed by the self-referential expansion guard.
 */
#define REPEAT_ALT_N(n, cons, map, ...) _APPLY_ALT(_REPEAT_ALT_ ## n, n, cons, map, __VA_ARGS__)
#define _APPLY_ALT(x, ...) x(__VA_ARGS__)
#define _REPEAT_ALT_1(  n, cons, map, ...)      map(__VA_ARGS__,  1, n)
#define _REPEAT_ALT_2(  n, cons, map, ...) cons(_REPEAT_ALT_1(  n, cons, map, __VA_ARGS__), map(__VA_ARGS__,  2, n))
#define _REPEAT_ALT_3(  n, cons, map, ...) cons(_REPEAT_ALT_2(  n, cons, map, __VA_ARGS__), map(__VA_ARGS__,  3, n))
#define _REPEAT_ALT_4(  n, cons, map, ...) cons(_REPEAT_ALT_3(  n, cons, map, __VA_ARGS__), map(__VA_ARGS__,  4, n))
#define _REPEAT_ALT_5(  n, cons, map, ...) cons(_REPEAT_ALT_4(  n, cons, map, __VA_ARGS__), map(__VA_ARGS__,  5, n))
#define _REPEAT_ALT_6(  n, cons, map, ...) cons(_REPEAT_ALT_5(  n, cons, map, __VA_ARGS__), map(__VA_ARGS__,  6, n))
#define _REPEAT_ALT_7(  n, cons, map, ...) cons(_REPEAT_ALT_6(  n, cons, map, __VA_ARGS__), map(__VA_ARGS__,  7, n))
#define _REPEAT_ALT_8(  n, cons, map, ...) cons(_REPEAT_ALT_7(  n, cons, map, __VA_ARGS__), map(__VA_ARGS__,  8, n))
#define _REPEAT_ALT_9(  n, cons, map, ...) cons(_REPEAT_ALT_8(  n, cons, map, __VA_ARGS__), map(__VA_ARGS__,  9, n))
#define _REPEAT_ALT_10( n, cons, map, ...) cons(_REPEAT_ALT_9(  n, cons, map, __VA_ARGS__), map(__VA_ARGS__, 10, n))
#define _REPEAT_ALT_11( n, cons, map, ...) cons(_REPEAT_ALT_10( n, cons, map, __VA_ARGS__), map(__VA_ARGS__, 11, n))
#define _REPEAT_ALT_12( n, cons, map, ...) cons(_REPEAT_ALT_11( n, cons, map, __VA_ARGS__), map(__VA_ARGS__, 12, n))
#define _REPEAT_ALT_13( n, cons, map, ...) cons(_REPEAT_ALT_12( n, cons, map, __VA_ARGS__), map(__VA_ARGS__, 13, n))
#define _REPEAT_ALT_14( n, cons, map, ...) cons(_REPEAT_ALT_13( n, cons, map, __VA_ARGS__), map(__VA_ARGS__, 14, n))
#define _REPEAT_ALT_15( n, cons, map, ...) cons(_REPEAT_ALT_14( n, cons, map, __VA_ARGS__), map(__VA_ARGS__, 15, n))
#define _REPEAT_ALT_16( n, cons, map, ...) cons(_REPEAT_ALT_15( n, cons, map, __VA_ARGS__), map(__VA_ARGS__, 16, n))
#define _REPEAT_ALT_17( n, cons, map, ...) cons(_REPEAT_ALT_16( n, cons, map, __VA_ARGS__), map(__VA_ARGS__, 17, n))
#define _REPEAT_ALT_18( n, cons, map, ...) cons(_REPEAT_ALT_17( n, cons, map, __VA_ARGS__), map(__VA_ARGS__, 18, n))
#define _REPEAT_ALT_19( n, cons, map, ...) cons(_REPEAT_ALT_18( n, cons, map, __VA_ARGS__), map(__VA_ARGS__, 19, n))
/* ... */

#pragma clang diagnostic pop
#endif /* CPP_H */
