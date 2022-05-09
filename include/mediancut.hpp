#pragma once

#include "common.hpp"

namespace cp
{
	enum class MedianCutMethod
	{
		MEDIAN,
		MIN,
		MAX
	};
	void mediancut(cv::InputArray src, const int K, cv::OutputArray destLabels, cv::OutputArray destColor, const MedianCutMethod cmethod = MedianCutMethod::MEDIAN);
}

