#include "stream.hpp"
#include "inlineSIMDFunctions.hpp"

using namespace std;
using namespace cv;

namespace cp
{
	void streamCopy(const double* src, double* dst, const int size)
	{
		const int SIZE = get_simd_floor(size, 4);
		for (int i = 0; i < SIZE; i += 4)
		{
			_mm256_stream_pd(dst + i, _mm256_stream_load_pd(src + i));
		}
		for (int i = SIZE; i < size; i++)
		{
			dst[i] = src[i];
		}
	}

	void streamCopy(const float* src, float* dst, const int size)
	{
		const int SIZE = get_simd_floor(size, 8);
		for (int i = 0; i < SIZE; i += 8)
		{
			_mm256_stream_ps(dst + i, _mm256_stream_load_ps(src + i));
		}
		for (int i = SIZE; i < size; i++)
		{
			dst[i] = src[i];
		}
	}

	void streamCopy(const char* src, char* dst, const int size)
	{
		const int SIZE = get_simd_floor(size, 32);
		for (int i = 0; i < SIZE; i += 32)
		{
			_mm256_stream_si256((__m256i*)(dst + i), _mm256_stream_load_si256((__m256i*)(src + i)));
		}
		for (int i = SIZE; i < size; i++)
		{
			dst[i] = src[i];
		}
	}

	void streamCopy(const uchar* src, uchar* dst, const int size)
	{
		const int SIZE = get_simd_floor(size, 32);
		for (int i = 0; i < SIZE; i += 32)
		{
			_mm256_stream_si256((__m256i*)(dst + i), _mm256_stream_load_si256((__m256i*)(src + i)));
		}
		for (int i = SIZE; i < size; i++)
		{
			dst[i] = src[i];
		}
	}

	void streamCopy(const short* src, short* dst, const int size)
	{
		const int SIZE = get_simd_floor(size, 16);
		for (int i = 0; i < SIZE; i += 16)
		{
			_mm256_stream_si256((__m256i*)(dst + i), _mm256_stream_load_si256((__m256i*)(src + i)));
		}
		for (int i = SIZE; i < size; i++)
		{
			dst[i] = src[i];
		}
	}

	void streamCopy(const ushort* src, ushort* dst, const int size)
	{
		const int SIZE = get_simd_floor(size, 16);
		for (int i = 0; i < SIZE; i += 16)
		{
			_mm256_stream_si256((__m256i*)(dst + i), _mm256_stream_load_si256((__m256i*)(src + i)));
		}
		for (int i = SIZE; i < size; i++)
		{
			dst[i] = src[i];
		}
	}

	void streamCopy(const int* src, int* dst, const int size)
	{
		const int SIZE = get_simd_floor(size, 8);
		for (int i = 0; i < SIZE; i += 8)
		{
			_mm256_stream_si256((__m256i*)(dst + i), _mm256_stream_load_si256((__m256i*)(src + i)));
		}
		for (int i = SIZE; i < size; i++)
		{
			dst[i] = src[i];
		}
	}

	void streamCopy(cv::InputArray src, cv::OutputArray dst)
	{
		dst.create(src.size(), src.type());
		Mat s = src.getMat();
		Mat d = dst.getMat();
		const int size = (int)s.total();
		if (src.depth() == CV_8U) streamCopy(s.ptr<uchar>(), d.ptr<uchar>(), size);
		if (src.depth() == CV_8S) streamCopy(s.ptr<char>(), d.ptr<char>(), size);
		if (src.depth() == CV_16U) streamCopy(s.ptr<ushort>(), d.ptr<ushort>(), size);
		if (src.depth() == CV_16S) streamCopy(s.ptr<short>(), d.ptr<short>(), size);
		if (src.depth() == CV_32S) streamCopy(s.ptr<int>(), d.ptr<int>(), size);
		if (src.depth() == CV_32F) streamCopy(s.ptr<float>(), d.ptr<float>(), size);
		if (src.depth() == CV_64F) streamCopy(s.ptr<double>(), d.ptr<double>(), size);
	}

	void streamConvertTo8U(const char* src, uchar* dst, const int size)
	{
		const int SIZE = get_simd_floor(size, 32);
		for (int i = 0; i < SIZE; i += 32)
		{
			__m256i a = _mm256_max_epi8(_mm256_setzero_si256(), _mm256_stream_load_si256((__m256i*)(src + i)));
			_mm256_stream_si256((__m256i*)(dst + i), a);
		}
		for (int i = SIZE; i < size; i++)
		{
			dst[i] = saturate_cast<uchar>(src[i]);
		}
	}

	void streamConvertTo8U(const short* src, uchar* dst, const int size)
	{
		const int SIZE = get_simd_floor(size, 16);
		for (int i = 0; i < SIZE; i += 16)
		{
			__m256i a = _mm256_stream_load_si256((__m256i*)(src + i));
			_mm_stream_si128((__m128i*)(dst + i), _mm256_cvtepi16_epu8(a));

		}
		for (int i = SIZE; i < size; i++)
		{
			dst[i] = saturate_cast<uchar>(src[i]);
		}
	}

	void streamConvertTo8U(const int* src, uchar* dst, const int size)
	{
		const int SIZE = get_simd_floor(size, 16);
		for (int i = 0; i < SIZE; i += 16)
		{
			__m256i a = _mm256_stream_load_si256((__m256i*)(src + i));
			__m256i b = _mm256_stream_load_si256((__m256i*)(src + i + 8));
			_mm_stream_si128((__m128i*)(dst + i), _mm256_cvtepi32x2_epu8(a, b));

		}
		for (int i = SIZE; i < size; i++)
		{
			dst[i] = saturate_cast<uchar>(src[i]);
		}
	}

	void streamConvertTo8U(const float* src, uchar* dst, const int size)
	{
		const int SIZE = get_simd_floor(size, 16);
		for (int i = 0; i < SIZE; i += 16)
		{
			__m256 a = _mm256_stream_load_ps(src + i);
			__m256 b = _mm256_stream_load_ps(src + i + 8);
			_mm_stream_si128((__m128i*)(dst + i), _mm256_cvtpsx2_epu8(a, b));
		}
		for (int i = SIZE; i < size; i++)
		{
			dst[i] = saturate_cast<uchar>(src[i]);
		}
	}

	void streamConvertTo8U(const double* src, uchar* dst, const int size)
	{
		const int SIZE = get_simd_floor(size, 16);
		for (int i = 0; i < SIZE; i += 16)
		{
			__m256d a = _mm256_stream_load_pd(src + i);
			__m256d b = _mm256_stream_load_pd(src + i + 4);
			__m256d c = _mm256_stream_load_pd(src + i + 8);
			__m256d d = _mm256_stream_load_pd(src + i + 12);

			__m256 e = _mm256_cvtpdx2_ps(a, b);
			__m256 f = _mm256_cvtpdx2_ps(c, d);
			_mm_stream_si128((__m128i*)(dst + i), _mm256_cvtpsx2_epu8(e, f));
		}
		for (int i = SIZE; i < size; i++)
		{
			dst[i] = saturate_cast<uchar>(src[i]);
		}
	}

	void streamConvertTo8U(cv::InputArray src, cv::OutputArray dst)
	{
		dst.create(src.size(), CV_MAKETYPE(CV_8U, src.channels()));
		Mat s = src.getMat();
		Mat d = dst.getMat();
		const int size = (int)s.total();
		if (src.depth() == CV_8U) streamCopy(s.ptr<uchar>(), d.ptr<uchar>(), size);
		if (src.depth() == CV_8S) streamConvertTo8U(s.ptr<char>(), d.ptr<uchar>(), size);
		if (src.depth() == CV_16U) streamConvertTo8U(s.ptr<short>(), d.ptr<uchar>(), size);
		if (src.depth() == CV_16S) streamConvertTo8U(s.ptr<short>(), d.ptr<uchar>(), size);
		if (src.depth() == CV_32S) streamConvertTo8U(s.ptr<int>(), d.ptr<uchar>(), size);
		if (src.depth() == CV_32F) streamConvertTo8U(s.ptr<float>(), d.ptr<uchar>(), size);
		if (src.depth() == CV_64F) streamConvertTo8U(s.ptr<double>(), d.ptr<uchar>(), size);
	}
}