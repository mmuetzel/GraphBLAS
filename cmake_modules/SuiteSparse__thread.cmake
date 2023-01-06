#-------------------------------------------------------------------------------
# GraphBLAS/cmake_modules/SuiteSparse__thread.cmake
#-------------------------------------------------------------------------------

# Copyright (c) 2017-2023, Timothy A. Davis.  All Rights Reserved.
# SPDX-License-Identifier: Apache-2.0

#-------------------------------------------------------------------------------

# determine if the __thread keyword is available, which is an extension by
# gcc but supported by many compilers, to indicate thread-local-storage.

include ( CheckCSourceRuns )

set ( thread_src
"   #include <stdio.h>
    __thread int x = 1 ;
    int main (void)
    {
        x = 0 ;
        return (x) ;
    }
" )

set ( declspec_thread_src
"   #include <stdio.h>
    __declspec ( thread ) int x = 1 ;
    int main (void)
    {
        x = 0 ;
        return (x) ;
    }
" )

check_c_source_runs ( "${declspec_thread_src}" HAVE_KEYWORD__DECLSPEC_THREAD )

check_c_source_runs ( "${thread_src}" HAVE_KEYWORD__THREAD )

if ( HAVE_KEYWORD__DECLSPEC_THREAD )
    add_compile_definitions ( HAVE_KEYWORD__DECLSPEC_THREAD )
    message ( STATUS "__declspec(thread) keyword: available" )
else ( )
    message ( STATUS "__declspec(thread) keyword: not available" )
endif ( )

if ( HAVE_KEYWORD__THREAD )
    add_compile_definitions ( HAVE_KEYWORD__THREAD )
    message ( STATUS "__thread keyword: available" )
else ( )
    message ( STATUS "__thread keyword: not available" )
endif ( )
