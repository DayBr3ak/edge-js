#ifndef __CORECLR_EDGE_H
#define __CORECLR_EDGE_H

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string>
#include <stdio.h>
#include <utility>
#include <map>

typedef int BOOL;

#include <pal/pal.h>

// From http://stackoverflow.com/questions/5919996/how-to-detect-reliably-mac-os-x-ios-linux-windows-in-c-preprocessor
#ifdef _WIN64
   // Windows 64
#define EDGE_PLATFORM_WINDOWS 1
#elif _WIN32
   // Windows 32
#define EDGE_PLATFORM_WINDOWS 1
#elif __APPLE__
   // OSX
#define EDGE_PLATFORM_APPLE 1
#elif __linux
    // linux
#define EDGE_PLATFORM_NIX 1
#elif __unix // all unices not caught above
    // Unix
#define EDGE_PLATFORM_NIX 1
#elif __posix
    // POSIX
#define EDGE_PLATFORM_NIX 1
#endif

#ifndef EDGE_PLATFORM_WINDOWS
#include <stdlib.h>
#include <string.h>
#define __cdecl
#endif

#ifndef EDGE_PLATFORM_WINDOWS
#ifdef FALSE
#undef FALSE
#endif
#define FALSE 0
#ifdef TRUE
#undef TRUE
#endif
#define TRUE  1
#endif

#ifdef EDGE_PLATFORM_WINDOWS
#define ABORT_TODO() do { printf("%s (%d): %s\n", __FILE__, __LINE__, __FUNCTION__); abort(); } while (0)
#elif EDGE_PLATFORM_APPLE
#define ABORT_TODO() do { printf("%s (%d): %s\n", __FILE__, __LINE__, __func__); abort(); } while (0)
#else
#define ABORT_TODO() do { printf("%s (%d): %s\n", __FILE__, __LINE__, __func__); exit(1); } while (0)
#endif

#endif