//
//  PlatformCompat.hh
//  Fleece
//
//  Created by Jens Alfke on 9/8/16.
//  Copyright © 2016 Couchbase. All rights reserved.
//

#pragma once


#ifdef _MSC_VER

    #define _usuallyTrue(VAL)               (VAL)
    #define _usuallyFalse(VAL)              (VAL)
    #define NOINLINE                        __declspec(noinline)

    #define __has_extension(X)              0
    #define __has_feature(F)                0
    #define __func__                        __FUNCTION__

    #define random()                        rand()
    #define srandom(s)                      srand(s)

    #define localtime_r(a, b)               localtime_s(b, a)

    #include <BaseTsd.h>
    typedef SSIZE_T ssize_t;

    #define MAXFLOAT FLT_MAX

    #define __printflike(A, B) 

    // MSVC doesn't support C99 so it doesn't have variable-length C arrays.
    // WARNING: sizeof() will not work on this array since it's actually declared as a pointer.
    #define StackArray(NAME, TYPE, SIZE)    TYPE* NAME = (TYPE*)_malloca(sizeof(TYPE)*(SIZE))

    #define MKDIR(PATH, MODE) ::_mkdir(PATH)
    #define chmod  ::_chmod
    #define fdopen ::_fdopen
    #define fseeko fseek
    #define ftello ftell

#else

    #define _usuallyTrue(VAL)               __builtin_expect(VAL, true)
    #define _usuallyFalse(VAL)              __builtin_expect(VAL, false)
    #define NOINLINE                        __attribute((noinline))

    #ifndef __printflike
    #define __printflike(fmtarg, firstvararg) __attribute__((__format__ (__printf__, fmtarg, firstvararg)))
    #endif
    #ifndef __unused
    #define __unused __attribute((unused))
    #endif

    #define StackArray(NAME, TYPE, SIZE)    TYPE NAME[(SIZE)]

    #define MKDIR(PATH, MODE) ::mkdir(PATH, (mode_t)MODE)

#endif
