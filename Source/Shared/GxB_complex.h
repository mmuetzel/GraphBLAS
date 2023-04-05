//------------------------------------------------------------------------------
// GxB_complex.h: definitions for the GraphBLAS complex types
//------------------------------------------------------------------------------

// SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2022, All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

//------------------------------------------------------------------------------

// If a user-defined operator needs access to the GraphBLAS complex types,
// GxB_FC32_t and GxB_FC64_t types, then this file can be #include'd in the
// defining string.  See Demo/Source/usercomplex.h for an example.

// See:
// https://www.drdobbs.com/complex-arithmetic-in-the-intersection-o/184401628#

#ifndef GXB_COMPLEX_H
#define GXB_COMPLEX_H

    #if defined ( __NVCC__ )

        // CUDA complex types (using the C++ variant)
        extern "C++"
        {
            #include <cuda/std/complex>
            typedef std::complex<float>  GxB_FC32_t ;
            typedef std::complex<double> GxB_FC64_t ;
        }
        #define GxB_CMPLXF(r,i) GxB_FC32_t(r,i)
        #define GxB_CMPLX(r,i)  GxB_FC64_t(r,i)

    #elif defined ( __cplusplus )

        // C++ complex types
        extern "C++"
        {
            #include <cmath>
            #include <complex>
            #undef I
            typedef std::complex<float>  GxB_FC32_t ;
            typedef std::complex<double> GxB_FC64_t ;
        }
        #define GxB_CMPLXF(r,i) GxB_FC32_t(r,i)
        #define GxB_CMPLX(r,i)  GxB_FC64_t(r,i)

    #elif ( _MSC_VER && !(__INTEL_COMPILER || __INTEL_CLANG_COMPILER) )

        // Microsoft Windows complex types for C
        #include <complex.h>
        #undef I
        typedef _Fcomplex GxB_FC32_t ;
        typedef _Dcomplex GxB_FC64_t ;
        #define GxB_CMPLXF(r,i) (_FCbuild (r,i))
        #define GxB_CMPLX(r,i)  ( _Cbuild (r,i))

    #else

        // ANSI C11 complex types
        #include <complex.h>
        #undef I
        typedef float  complex GxB_FC32_t ;
        typedef double complex GxB_FC64_t ;

        #ifndef CMPLX
            // gcc 6.2 on the the Mac doesn't #define CMPLX
            #define GxB_CMPLX(r,i) \
            ((GxB_FC64_t)((double)(r)) + (GxB_FC64_t)((double)(i) * _Complex_I))
        #else
            // use the ANSI C11 CMPLX macro
            #define GxB_CMPLX(r,i) CMPLX (r,i)
        #endif

        #ifndef CMPLXF
            // gcc 6.2 on the the Mac doesn't #define CMPLXF
            #define GxB_CMPLXF(r,i) \
            ((GxB_FC32_t)((float)(r)) + (GxB_FC32_t)((float)(i) * _Complex_I))
        #else
            // use the ANSI C11 CMPLXF macro
            #define GxB_CMPLXF(r,i) CMPLXF (r,i)
        #endif

    #endif
#endif
