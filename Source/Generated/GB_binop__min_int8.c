//------------------------------------------------------------------------------
// GB_binop:  hard-coded functions for each built-in binary operator
//------------------------------------------------------------------------------

// SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2021, All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

//------------------------------------------------------------------------------

// If this file is in the Generated/ folder, do not edit it (auto-generated).

#include "GB.h"
#ifndef GBCOMPACT
#include "GB_emult.h"
#include "GB_control.h"
#include "GB_ek_slice.h"
#include "GB_dense.h"
#include "GB_atomics.h"
#include "GB_bitmap_assign_methods.h"
#include "GB_binop__include.h"

// C=binop(A,B) is defined by the following types and operators:

// A+B function (eWiseAdd):         GB (_AaddB__min_int8)
// A.*B function (eWiseMult):       GB (_AemultB)
// A.*B function (eWiseMult):       GB (_AemultB_02__min_int8)
// A.*B function (eWiseMult):       GB (_AemultB_03__min_int8)
// A.*B function (eWiseMult):       GB (_AemultB_bitmap__min_int8)
// A*D function (colscale):         GB (_AxD__min_int8)
// D*A function (rowscale):         GB (_DxB__min_int8)
// C+=B function (dense accum):     GB (_Cdense_accumB__min_int8)
// C+=b function (dense accum):     GB (_Cdense_accumb__min_int8)
// C+=A+B function (dense ewise3):  GB (_Cdense_ewise3_accum__min_int8)
// C=A+B function (dense ewise3):   GB (_Cdense_ewise3_noaccum__min_int8)
// C=scalar+B                       GB (_bind1st__min_int8)
// C=scalar+B'                      GB (_bind1st_tran__min_int8)
// C=A+scalar                       GB (_bind2nd__min_int8)
// C=A'+scalar                      GB (_bind2nd_tran__min_int8)

// C type:   int8_t
// A type:   int8_t
// B,b type: int8_t
// BinaryOp: cij = GB_IMIN (aij, bij)

#define GB_ATYPE \
    int8_t

#define GB_BTYPE \
    int8_t

#define GB_CTYPE \
    int8_t

// true if the types of A and B are identical
#define GB_ATYPE_IS_BTYPE \
    1

// true if the types of C and A are identical
#define GB_CTYPE_IS_ATYPE \
    1

// true if the types of C and B are identical
#define GB_CTYPE_IS_BTYPE \
    1

// aij = Ax [pA]
#define GB_GETA(aij,Ax,pA,A_iso)  \
    int8_t aij = GBX (Ax, pA, A_iso)

// bij = Bx [pB]
#define GB_GETB(bij,Bx,pB,B_iso)  \
    int8_t bij = GBX (Bx, pB, B_iso)

// declare scalar of the same type as C
#define GB_CTYPE_SCALAR(t)  \
    int8_t t

// cij = Ax [pA]
#define GB_COPY_A_TO_C(cij,Ax,pA,A_iso) \
    cij = GBX (Ax, pA, A_iso)

// cij = Bx [pB]
#define GB_COPY_B_TO_C(cij,Bx,pB,B_iso) \
    cij = GBX (Bx, pB, B_iso)

#define GB_CX(p) Cx [p]

// binary operator
#define GB_BINOP(z,x,y,i,j) \
    z = GB_IMIN (x, y) ;

// true if the binop must be flipped
#define GB_BINOP_FLIP \
    0

// op is second
#define GB_OP_IS_SECOND \
    0

// do the numerical phases of GB_add and GB_emult
#define GB_PHASE_2_OF_2

// hard-coded loops can be vectorized
#define GB_PRAGMA_SIMD_VECTORIZE GB_PRAGMA_SIMD

// disable this operator and use the generic case if these conditions hold
#define GB_DISABLE \
    (GxB_NO_MIN || GxB_NO_INT8 || GxB_NO_MIN_INT8)

//------------------------------------------------------------------------------
// C += A+B, all 3 matrices dense
//------------------------------------------------------------------------------



// The op must be MIN, MAX, PLUS, MINUS, RMINUS, TIMES, DIV, or RDIV.

void GB (_Cdense_ewise3_accum__min_int8)
(
    GrB_Matrix C,
    const GrB_Matrix A,
    const GrB_Matrix B,
    const int nthreads
)
{ 
    #include "GB_dense_ewise3_accum_template.c"
}



//------------------------------------------------------------------------------
// C = A+B, all 3 matrices dense
//------------------------------------------------------------------------------

GrB_Info GB (_Cdense_ewise3_noaccum__min_int8)
(
    GrB_Matrix C,
    const GrB_Matrix A,
    const GrB_Matrix B,
    const int nthreads
)
{ 
    #if GB_DISABLE
    return (GrB_NO_VALUE) ;
    #else
    #include "GB_dense_ewise3_noaccum_template.c"
    return (GrB_SUCCESS) ;
    #endif
}

//------------------------------------------------------------------------------
// C += B, accumulate a sparse matrix into a dense matrix
//------------------------------------------------------------------------------

GrB_Info GB (_Cdense_accumB__min_int8)
(
    GrB_Matrix C,
    const GrB_Matrix B,
    const int64_t *B_ek_slicing, const int B_ntasks, const int B_nthreads
)
{
    #if GB_DISABLE
    return (GrB_NO_VALUE) ;
    #else
    
    { 
        #include "GB_dense_subassign_23_template.c"
    }
    
    return (GrB_SUCCESS) ;
    #endif
}

//------------------------------------------------------------------------------
// C += b, accumulate a scalar into a dense matrix
//------------------------------------------------------------------------------

GrB_Info GB (_Cdense_accumb__min_int8)
(
    GrB_Matrix C,
    const GB_void *p_bwork,
    const int nthreads
)
{
    #if GB_DISABLE
    return (GrB_NO_VALUE) ;
    #else
    
    { 
        // get the scalar b for C += b, of type int8_t
        int8_t bwork = (*((int8_t *) p_bwork)) ;
        #include "GB_dense_subassign_22_template.c"
        return (GrB_SUCCESS) ;
    }
    
    return (GrB_SUCCESS) ;
    #endif
}

//------------------------------------------------------------------------------
// C = A*D, column scale with diagonal D matrix
//------------------------------------------------------------------------------



GrB_Info GB (_AxD__min_int8)
(
    GrB_Matrix C,
    const GrB_Matrix A, bool A_is_pattern,
    const GrB_Matrix D, bool D_is_pattern,
    const int64_t *A_ek_slicing, const int A_ntasks, const int A_nthreads
)
{ 
    #if GB_DISABLE
    return (GrB_NO_VALUE) ;
    #else
    int8_t *restrict Cx = (int8_t *) C->x ;
    #include "GB_AxB_colscale_meta.c"
    return (GrB_SUCCESS) ;
    #endif
}



//------------------------------------------------------------------------------
// C = D*B, row scale with diagonal D matrix
//------------------------------------------------------------------------------



GrB_Info GB (_DxB__min_int8)
(
    GrB_Matrix C,
    const GrB_Matrix D, bool D_is_pattern,
    const GrB_Matrix B, bool B_is_pattern,
    int nthreads
)
{ 
    #if GB_DISABLE
    return (GrB_NO_VALUE) ;
    #else
    int8_t *restrict Cx = (int8_t *) C->x ;
    #include "GB_AxB_rowscale_meta.c"
    return (GrB_SUCCESS) ;
    #endif
}



//------------------------------------------------------------------------------
// eWiseAdd: C = A+B or C<M> = A+B
//------------------------------------------------------------------------------

GrB_Info GB (_AaddB__min_int8)
(
    GrB_Matrix C,
    const int C_sparsity,
    const GrB_Matrix M,
    const bool Mask_struct,
    const bool Mask_comp,
    const GrB_Matrix A,
    const GrB_Matrix B,
    const bool Ch_is_Mh,
    const int64_t *restrict C_to_M,
    const int64_t *restrict C_to_A,
    const int64_t *restrict C_to_B,
    const GB_task_struct *restrict TaskList,
    const int C_ntasks,
    const int C_nthreads,
    GB_Context Context
)
{ 
    #if GB_DISABLE
    return (GrB_NO_VALUE) ;
    #else
    GB_WERK_DECLARE (M_ek_slicing, int64_t) ;
    GB_WERK_DECLARE (A_ek_slicing, int64_t) ;
    GB_WERK_DECLARE (B_ek_slicing, int64_t) ;
    #include "GB_add_template.c"
    GB_FREE_WORK ;
    return (GrB_SUCCESS) ;
    #endif
}

//------------------------------------------------------------------------------
// eWiseMult: C = A.*B or C<M> = A.*B
//------------------------------------------------------------------------------

GrB_Info GB (_AemultB_01__min_int8)
(
    GrB_Matrix C,
    const int C_sparsity,
    const int ewise_method,
    const GrB_Matrix M,
    const bool Mask_struct,
    const bool Mask_comp,
    const GrB_Matrix A,
    const GrB_Matrix B,
    const int64_t *restrict C_to_M,
    const int64_t *restrict C_to_A,
    const int64_t *restrict C_to_B,
    const GB_task_struct *restrict TaskList,
    const int C_ntasks,
    const int C_nthreads,
    GB_Context Context
)
{ 
    #if GB_DISABLE
    return (GrB_NO_VALUE) ;
    #else
    #include "GB_emult_01_meta.c"
    return (GrB_SUCCESS) ;
    #endif
}

//------------------------------------------------------------------------------
// eWiseMult: C<#> = A.*B when A is sparse/hyper and B is bitmap/full
//------------------------------------------------------------------------------

GrB_Info GB (_AemultB_02__min_int8)
(
    GrB_Matrix C,
    const GrB_Matrix M,
    const bool Mask_struct,
    const bool Mask_comp,
    const GrB_Matrix A,
    const GrB_Matrix B,
    const bool flipxy,
    const int64_t *restrict Cp_kfirst,
    const int64_t *A_ek_slicing, const int A_ntasks, const int A_nthreads
)
{ 
    #if GB_DISABLE
    return (GrB_NO_VALUE) ;
    #else
    #if GB_BINOP_FLIP
        // The operator is not commutative, and does not have a flipped
        // variant.  For example z=atan2(y,x).
        if (flipxy)
        {
            // use fmult(y,x)
            #undef  GB_FLIPPED
            #define GB_FLIPPED 1
            #include "GB_emult_02_template.c"
        }
        else
        {
            // use fmult(x,y)
            #undef  GB_FLIPPED
            #define GB_FLIPPED 0
            #include "GB_emult_02_template.c"
        }
    #else
        // No need to handle the flip: the operator is either commutative, or
        // has been handled by changing z=div(y,x) to z=rdiv(x,y) for example.
        #undef  GB_FLIPPED
        #define GB_FLIPPED 0
        #include "GB_emult_02_template.c"
    #endif
    return (GrB_SUCCESS) ;
    #endif
}

//------------------------------------------------------------------------------
// eWiseMult: C<M> = A.*B, M sparse/hyper, A and B bitmap/full
//------------------------------------------------------------------------------

GrB_Info GB (_AemultB_03__min_int8)
(
    GrB_Matrix C,
    const GrB_Matrix M,
    const bool Mask_struct,
    const GrB_Matrix A,
    const GrB_Matrix B,
    const int64_t *restrict Cp_kfirst,
    const int64_t *M_ek_slicing, const int M_ntasks, const int M_nthreads
)
{ 
    #if GB_DISABLE
    return (GrB_NO_VALUE) ;
    #else
    #include "GB_emult_03_template.c"
    return (GrB_SUCCESS) ;
    #endif
}

//------------------------------------------------------------------------------
// eWiseMult: C=A.*B, C<M>=A.*B, C<!M>=A.*B where C is bitmap
//------------------------------------------------------------------------------

GrB_Info GB (_AemultB_bitmap__min_int8)
(
    GrB_Matrix C,
    const int ewise_method,
    const GrB_Matrix M,
    const bool Mask_struct,
    const bool Mask_comp,
    const GrB_Matrix A,
    const GrB_Matrix B,
    const int64_t *M_ek_slicing, const int M_ntasks, const int M_nthreads,
    const int C_nthreads,
    GB_Context Context
)
{ 
    #if GB_DISABLE
    return (GrB_NO_VALUE) ;
    #else
    #include "GB_bitmap_emult_template.c"
    return (GrB_SUCCESS) ;
    #endif
}

//------------------------------------------------------------------------------
// Cx = op (x,Bx):  apply a binary operator to a matrix with scalar bind1st
//------------------------------------------------------------------------------



GrB_Info GB (_bind1st__min_int8)
(
    GB_void *Cx_output,         // Cx and Bx may be aliased
    const GB_void *x_input,
    const GB_void *Bx_input,
    const int8_t *restrict Bb,
    int64_t bnz,
    int nthreads
)
{ 
    #if GB_DISABLE
    return (GrB_NO_VALUE) ;
    #else
    int8_t *Cx = (int8_t *) Cx_output ;
    int8_t   x = (*((int8_t *) x_input)) ;
    int8_t *Bx = (int8_t *) Bx_input ;
    int64_t p ;
    #pragma omp parallel for num_threads(nthreads) schedule(static)
    for (p = 0 ; p < bnz ; p++)
    {
        if (!GBB (Bb, p)) continue ;
        int8_t bij = GBX (Bx, p, false) ;
        Cx [p] = GB_IMIN (x, bij) ;
    }
    return (GrB_SUCCESS) ;
    #endif
}



//------------------------------------------------------------------------------
// Cx = op (Ax,y):  apply a binary operator to a matrix with scalar bind2nd
//------------------------------------------------------------------------------



GrB_Info GB (_bind2nd__min_int8)
(
    GB_void *Cx_output,         // Cx and Ax may be aliased
    const GB_void *Ax_input,
    const GB_void *y_input,
    const int8_t *restrict Ab,
    int64_t anz,
    int nthreads
)
{ 
    #if GB_DISABLE
    return (GrB_NO_VALUE) ;
    #else
    int64_t p ;
    int8_t *Cx = (int8_t *) Cx_output ;
    int8_t *Ax = (int8_t *) Ax_input ;
    int8_t   y = (*((int8_t *) y_input)) ;
    #pragma omp parallel for num_threads(nthreads) schedule(static)
    for (p = 0 ; p < anz ; p++)
    {
        if (!GBB (Ab, p)) continue ;
        int8_t aij = GBX (Ax, p, false) ;
        Cx [p] = GB_IMIN (aij, y) ;
    }
    return (GrB_SUCCESS) ;
    #endif
}



//------------------------------------------------------------------------------
// C = op (x, A'): transpose and apply a binary operator
//------------------------------------------------------------------------------



// cij = op (x, aij), no typecasting (in spite of the macro name)
#undef  GB_CAST_OP
#define GB_CAST_OP(pC,pA)                       \
{                                               \
    int8_t aij = GBX (Ax, pA, false) ;               \
    Cx [pC] = GB_IMIN (x, aij) ;        \
}

GrB_Info GB (_bind1st_tran__min_int8)
(
    GrB_Matrix C,
    const GB_void *x_input,
    const GrB_Matrix A,
    int64_t *restrict *Workspaces,
    const int64_t *restrict A_slice,
    int nworkspaces,
    int nthreads
)
{ 
    // GB_unop_transpose.c uses GB_ATYPE, but A is
    // the 2nd input to binary operator z=f(x,y).
    #undef  GB_ATYPE
    #define GB_ATYPE \
    int8_t
    #if GB_DISABLE
    return (GrB_NO_VALUE) ;
    #else
    int8_t x = (*((const int8_t *) x_input)) ;
    #include "GB_unop_transpose.c"
    return (GrB_SUCCESS) ;
    #endif
    #undef  GB_ATYPE
    #define GB_ATYPE \
    int8_t
}



//------------------------------------------------------------------------------
// C = op (A', y): transpose and apply a binary operator
//------------------------------------------------------------------------------



// cij = op (aij, y), no typecasting (in spite of the macro name)
#undef  GB_CAST_OP
#define GB_CAST_OP(pC,pA)                       \
{                                               \
    int8_t aij = GBX (Ax, pA, false) ;               \
    Cx [pC] = GB_IMIN (aij, y) ;        \
}

GrB_Info GB (_bind2nd_tran__min_int8)
(
    GrB_Matrix C,
    const GrB_Matrix A,
    const GB_void *y_input,
    int64_t *restrict *Workspaces,
    const int64_t *restrict A_slice,
    int nworkspaces,
    int nthreads
)
{ 
    #if GB_DISABLE
    return (GrB_NO_VALUE) ;
    #else
    int8_t y = (*((const int8_t *) y_input)) ;
    #include "GB_unop_transpose.c"
    return (GrB_SUCCESS) ;
    #endif
}



#endif

