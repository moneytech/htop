
#include "XAlloc.h"
#include "RichString.h"

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <assert.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>

/*{
#include <stdlib.h>
}*/

static inline void fail() {
   curs_set(1);
   endwin();
   err(1, NULL);
}

void* xMalloc(size_t size) {
   void* data = malloc(size);
   if (!data && size > 0) {
      fail();
   }
   return data;
}

void* xCalloc(size_t nmemb, size_t size) {
   void* data = calloc(nmemb, size);
   if (!data && nmemb > 0 && size > 0) {
      fail();
   }
   return data;
}

void* xRealloc(void* ptr, size_t size) {
   void* data = realloc(ptr, size);
   if (!data && size > 0) {
      fail();
   }
   return data;
}

#undef xStrdup
#undef xStrdup_
#ifdef NDEBUG
# define xStrdup_ xStrdup
#else
# define xStrdup(str_) (assert(str_), xStrdup_(str_))
#endif

#if ((__GNUC__ > 3) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 3))
char* xStrdup_(const char* str) __attribute__((nonnull));
#endif // GNU C 3.3 or later

char* xStrdup_(const char* str) {
   char* data = strdup(str);
   if (!data) {
      fail();
   }
   return data;
}
