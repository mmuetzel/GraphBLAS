//------------------------------------------------------------------------------
// GB_unop_shared_definitions.h: common macros for unop kernels
//------------------------------------------------------------------------------

// SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2023, All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

//------------------------------------------------------------------------------

// GB_unop_shared_definitions.h provides default definitions for all unop
// kernels, if the special cases have not been #define'd prior to #include'ing
// this file.  This file is shared by generic, factory, and both CPU and
// CUDA JIT kernels.

#include "GB_kernel_shared_definitions.h"

#ifndef GB_UNOP_SHARED_DEFINITIONS_H
#define GB_UNOP_SHARED_DEFINITIONS_H

// access C(i,j) in Cx [p]
#ifndef GB_CX
#define GB_CX(p) Cx [p]
#endif

// copy A(i,j) to C(i,j)
#ifndef GB_COPY_A_TO_C
#define GB_COPY_A_TO_C(Cx,pC,Ax,pA,A_iso) Cx [pC] = Ax [(A_iso) ? 0 : (pA)]
#endif

// copy B(i,j) to C(i,j)
#ifndef GB_COPY_B_TO_C
#define GB_COPY_B_TO_C(Cx,pC,Bx,pB,B_iso) Cx [pC] = Bx [(B_iso) ? 0 : (pB)]
#endif

#endif
