#include <stdint.h>
#include <sys/types.h>
#ifdef LONG
#undef LONG
#endif
#ifndef BYTE
typedef uint8_t BYTE;
#endif
#ifndef WORD
typedef uint16_t WORD;
#endif
#include "rar.hpp"

#if defined(ALLOW_SSE)

static __m128i blake2s_IV_0_3, blake2s_IV_4_7;

static void blake2s_init_sse()
{
  static bool InitDone = false;
  if (InitDone)
    return;
  blake2s_IV_0_3 = _mm_setr_epi32( 0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A );
  blake2s_IV_4_7 = _mm_setr_epi32( 0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19 );
  InitDone = true;
}

#endif