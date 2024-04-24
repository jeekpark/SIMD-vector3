#pragma once
#include <smmintrin.h>
#include <iostream>

#include <cstdlib>

static const __m128 SIGNMASK = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));

void* malloc_simd(const size_t size)
{
#if defined WIN32
	return _aligned_malloc(size, 16);
#elif defined __linux__
	return memalign(16, size);
#elif defined __MACH__
	return malloc(size);
#else
	return valloc(size);
#endif
}

void free_simd(void* v)
{
#if defined WIN32
	return _aligned_free(v);
#else
	return free(v);
#endif
}


#ifdef __GNUC__
class __attribute__((aligned(16))) Vector3
#else
__MM_ALIGN16 class Vector3
#endif
{

	union
	{
		struct
		{
			float x, y, z;
		};
		__m128 mmvalue;
	};
};