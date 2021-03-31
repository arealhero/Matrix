#pragma once

#include <gtest/gtest.h>

#include <Matrix.h>

#include "utils.h"

TEST(Matrix_ColsManipulations, Swap)
{
	const std::size_t rows = GenerateSize();
	const std::size_t cols = rand() % 40 + 15;

	const auto first = GenerateRandomMatrix<int>(rows, cols);
	auto second = first;

	const std::size_t firstCol = rand() % (cols / 2);
	const std::size_t secondCol = cols / 2 + rand() % (cols / 2);

	second.SwapCols(firstCol, secondCol);

	AssertEqualSize(first, second);

	for (std::size_t i = 0; i < first.Rows(); ++i)
	{
		ASSERT_EQ(first[i][firstCol], second[i][secondCol]);
		ASSERT_EQ(first[i][secondCol], second[i][firstCol]);
	}

	for (std::size_t i = 0; i < first.Rows(); ++i)
	{
		for (std::size_t j = 0; j < first.Cols(); ++j)
		{
			if (j == firstCol || j == secondCol) continue;

			ASSERT_EQ(first[i][j], second[i][j]);
		}
	}
}

TEST(Matrix_ColsManipulations, SwapItself)
{
	const auto first = GenerateRandomMatrix<int>();
	auto second = first;

	const std::size_t col = rand() % first.Cols();

	second.SwapCols(col, col);

	AssertEqual(first, second);
}

