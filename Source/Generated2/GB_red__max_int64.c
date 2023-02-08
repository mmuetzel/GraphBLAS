//------------------------------------------------------------------------------
// GB_red:  hard-coded functions for reductions
//------------------------------------------------------------------------------

// SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2023, All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

//------------------------------------------------------------------------------

// If this file is in the Generated2/ folder, do not edit it
// (it is auto-generated from Generator/*).

#include "GB.h"
#ifndef GBCUDA_DEV
#include "GB_control.h" 
#include "GB_red__include.h"

// The reduction is defined by the following types and operators:

// Reduce to scalar:   GB (_red__max_int64)

// A type:   int64_t
// Z type:   int64_t

// Update:   if (y > z) { z = y ; }
// Add func: z = GB_IMAX (x, y)
// Identity: INT64_MIN

#define GB_A_TYPE \
    int64_t

#define GB_Z_TYPE \
    int64_t

// declare a scalar and set it equal to the monoid identity value

    #define GB_DECLARE_MONOID_IDENTITY(modifier,z) \
        modifier int64_t z = INT64_MIN

// reduction operator:

    // declare aij as ztype (= atype since no typecasting is done here)
    #define GB_DECLAREA(aij)  \
        int64_t aij

    // aij = Ax [pA]
    #define GB_GETA(aij,Ax,pA,A_iso)  \
        aij = Ax [pA]

    // z += y, update
    #define GB_UPDATE(z,y) \
        if (y > z) { z = y ; }

    // z = x+y, additive function
    #define GB_ADD(z,x,y) \
        z = GB_IMAX (x, y)

    // s += (ztype) Ax [p], no typecast here however
    #define GB_GETA_AND_UPDATE(s,Ax,p)              \
        GB_UPDATE (s, Ax [p])

// monoid terminal condition, if any:

#define GB_MONOID_IS_TERMINAL 1
#define GB_TERMINAL_CONDITION(z,zterminal) (z == INT64_MAX)
#define GB_IF_TERMINAL_BREAK(z,zterminal) if (z == INT64_MAX) { break ; }
#define GB_DECLARE_MONOID_TERMINAL(modifier,zterminal) modifier int64_t zterminal = INT64_MAX

// panel size for built-in operators

    #define GB_PANEL                                \
        16

// disable this operator and use the generic case if these conditions hold
#define GB_DISABLE \
    (GxB_NO_MAX || GxB_NO_INT64 || GxB_NO_MAX_INT64)

#include "GB_monoid_shared_definitions.h"

//------------------------------------------------------------------------------
// reduce to a non-iso matrix to scalar, for monoids only
//------------------------------------------------------------------------------

GrB_Info GB (_red__max_int64)
(
    int64_t *result,
    const GrB_Matrix A,
    GB_void *restrict W_space,
    bool *restrict F,
    int ntasks,
    int nthreads
)
{ 
    #if GB_DISABLE
    return (GrB_NO_VALUE) ;
    #else
    int64_t z = (*result) ;
    int64_t *restrict W = (int64_t *) W_space ;
    if (A->nzombies > 0 || GB_IS_BITMAP (A))
    {
        #include "GB_reduce_to_scalar_template.c"
    }
    else
    {
        #include "GB_reduce_panel.c"
    }
    (*result) = z ;
    return (GrB_SUCCESS) ;
    #endif
}

#endif
