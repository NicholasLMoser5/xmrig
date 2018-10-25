#ifndef SSE2ALTIVEC_H
#define SSE2ALTIVEC_H

#include <altivec.h>
#undef bool

typedef __vector unsigned char __m128i;
typedef __vector double __m128d;
typedef __vector unsigned long long __m128ll;

typedef float __m128 __attribute__ ((__vector_size__ (16), __may_alias__));

// From GCC
// https://patchwork.ozlabs.org/patch/827215/
static inline __m128d _mm_set1_pd (double __F)
{
  return __extension__ (__m128d){ __F, __F };
}

static inline __m128i _mm_load_si128(__m128i const *a)
{
  return *a;
}

static inline void _mm_store_si128(__m128i *a, __m128i b)
{
  vec_st(b, 0, a);
}

static inline __m128i _mm_set_epi64x(long long __q1, long long __q0)
{
  return (__m128i)(__vector long long){ __q0, __q1 };
}

static inline __m128i _mm_cvtsi64_si128 (long long __A)
{
  return (__m128i)(__vector long long){ __A, 0LL };
}

static inline __m128i _mm_add_epi64 (__m128i __A, __m128i __B)
{
  return (__m128i) ((__vector unsigned long long)__A + (__vector unsigned long long)__B);
}

static inline __m128d _mm_castsi128_pd(__m128i __A)
{
  return (__m128d) __A;
}

static inline __m128 _mm_cvtsi64_ss (__m128 __A, long long __B)
{
  float temp = __B;
  __A[0] = temp;

  return __A;
}

extern __inline __m128 _mm_castsi128(__m128i __A)
{
  return (__m128) __A;
}

extern __inline __m128 _mm_setzero_ps(void)
{
  return __extension__ (__m128){ 0.0f, 0.0f, 0.0f, 0.0f };
}

static inline __m128d _mm_setzero_pd(void)
{
  return (__m128d) vec_splats(0);
}

static inline __m128d _mm_setr_pd (double __W, double __X)
{
  return (__m128d){ __W, __X };
}

static inline __m128d _mm_sqrt_sd (__m128d __A, __m128d __B)
{
  __vector double c;
  c = vec_sqrt ((__vector double ) _mm_set1_pd (__B[0]));
  return (__m128d ) _mm_setr_pd (c[0], __A[1]);
}

static inline __m128i _mm_castpd_si128(__m128d __A)
{
  return (__m128i) __A;
}

static inline long long _mm_cvtsi128_si64 (__m128i __A)
{
  return ((__vector long long)__A)[0];
}

static inline __m128d _mm_cvtsi64_sd (__m128d __A, long long __B)
{
  __vector double result = (__vector double)__A;
  double db = __B;
  result [0] = db;
  return (__m128d)result;
}

static inline __m128i _mm_bsrli_si128 (__m128i __A, const int __N)
{
  __vector unsigned char result;
  const __vector unsigned char zeros =
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  if (__N < 16)
    if (__builtin_constant_p(__N))
      {
	/* Would like to use Vector Shift Left Double by Octet
	   Immediate here to use the immediate form and avoid
	   load of __N * 8 value into a separate VR.  */
	result = vec_sld (zeros, (__vector unsigned char) __A, (16 - __N));
      }
    else
      {
	__vector unsigned char shift = vec_splats((unsigned char)(__N*8));
	result = vec_sro ((__vector unsigned char)__A, shift);
      }
    else
    result = zeros;

  return (__m128i) result;
}

static inline __m128i _mm_srli_si128 (__m128i __A, const int __N)
{
  return _mm_bsrli_si128 (__A, __N);
}

static inline __m128i _mm_setzero_si128 (void)
{
  return (__m128i)(__vector int){ 0, 0, 0, 0 };
}
// End from GCC

#if defined(__GNUC__) || defined(__clang__)
#	pragma pop_macro("ALIGN_STRUCT")
#	pragma pop_macro("FORCE_INLINE")
#endif

#endif