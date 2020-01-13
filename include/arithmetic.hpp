#pragma once

#include "common.hpp"

namespace cp
{
	CP_EXPORT void pow_fmath(const float a, const cv::Mat&  src, cv::Mat& dest);
	CP_EXPORT void pow_fmath(const cv::Mat& src, const float a, cv::Mat& dest);
	CP_EXPORT void pow_fmath(const cv::Mat& src1, const cv::Mat&  src2, cv::Mat& dest);
	CP_EXPORT void compareRange(cv::InputArray src, cv::OutputArray destMask, const double validMin, const double validMax);
	CP_EXPORT void setTypeMaxValue(cv::InputOutputArray src);
	CP_EXPORT void setTypeMinValue(cv::InputOutputArray src);

	//a*x+b
	CP_EXPORT void fmadd(cv::Mat& a, cv::Mat& x, cv::Mat& b, cv::Mat& dest);
	//a*x-b
	CP_EXPORT void fmsub(cv::Mat& a, cv::Mat& x, cv::Mat& b, cv::Mat& dest);
	//-a*x+b
	CP_EXPORT void fnmadd(cv::Mat& a, cv::Mat& x, cv::Mat& b, cv::Mat& dest);
	//-a*x-b
	CP_EXPORT void fnmsub(cv::Mat& a, cv::Mat& x, cv::Mat& b, cv::Mat& dest);

	//dest=src>>shift, lostbit=src-dest<<shift
	CP_EXPORT void bitshiftRight(cv::InputArray src, cv::OutputArray dest, cv::OutputArray lostbit, const int shift);
	//src>>shift
	CP_EXPORT void bitshiftRight(cv::InputArray src, cv::OutputArray dest, const int shift);
}
