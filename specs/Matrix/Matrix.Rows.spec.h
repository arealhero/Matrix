#pragma once

#include <gtest/gtest.h>

#include <Matrix.h>

#include "utils.h"

// TODO: remove code duplication (refactor)

TEST(Matrix_RowsManipulations, Swap)
{
	const std::size_t rows = rand() % 40 + 15;
	const std::size_t cols = GenerateSize();

	const auto first = GenerateRandomMatrix<int>(rows, cols);
	auto second = first;

	const std::size_t firstRow = rand() % (rows / 2);
	const std::size_t secondRow = rows / 2 + rand() % (rows / 2);

	second.SwapRows(firstRow, secondRow);

	AssertEqualSize(first, second);

	for (std::size_t i = 0; i < first.Cols(); ++i)
	{
		ASSERT_EQ(first[firstRow][i], second[secondRow][i]);
		ASSERT_EQ(first[secondRow][i], second[firstRow][i]);
	}

	for (std::size_t i = 0; i < first.Rows(); ++i)
	{
		if (i == firstRow || i == secondRow) continue;

		for (std::size_t j = 0; j < first.Cols(); ++j)
		{
			ASSERT_EQ(first[i][j], second[i][j]);
		}
	}
}

TEST(Matrix_RowsManipulations, SwapItself)
{
	const auto first = GenerateRandomMatrix<int>();
	auto second = first;

	const std::size_t row = rand() % first.Rows();

	second.SwapRows(row, row);

	AssertEqual(first, second);
}

TEST(Matrix_RowsManipulations, Add)
{
	const auto first = GenerateRandomMatrix<int>();
	auto second = first;

	const std::size_t rows = first.Rows();
	const std::size_t srcRow = rand() % (rows / 2);
	const std::size_t destRow = rows / 2 + rand() % (rows / 2);

	second.AddRow(srcRow, destRow);

	AssertEqualSize(first, second);

	for (std::size_t i = 0; i < first.Cols(); ++i)
	{
		ASSERT_EQ(first[srcRow][i] + first[destRow][i], second[destRow][i]);
	}

	for (std::size_t i = 0; i < first.Rows(); ++i)
	{
		if (i == destRow) continue;

		for (std::size_t j = 0; j < first.Cols(); ++j)
		{
			ASSERT_EQ(first[i][j], second[i][j]);
		}
	}
}

TEST(Matrix_RowsManipulations, AddItself)
{
	const auto first = GenerateRandomMatrix<int>();
	auto second = first;

	const std::size_t row = rand() % first.Rows();

	second.AddRow(row, row);

	AssertEqualSize(first, second);

	for (std::size_t i = 0; i < first.Cols(); ++i)
	{
		ASSERT_EQ(2 * first[row][i], second[row][i]);
	}

	for (std::size_t i = 0; i < first.Rows(); ++i)
	{
		if (i == row) continue;

		for (std::size_t j = 0; j < first.Cols(); ++j)
		{
			ASSERT_EQ(first[i][j], second[i][j]);
		}
	}
}

TEST(Matrix_RowsManipulations, AddWithFactor)
{
	const auto first = GenerateRandomMatrix<int>();
	auto second = first;

	const std::size_t rows = first.Rows();
	const std::size_t srcRow = rand() % (rows / 2);
	const std::size_t destRow = rows / 2 + rand() % (rows / 2);
	const std::size_t factor = rand() % 100 + 5;

	second.AddRow(srcRow, destRow, factor);

	AssertEqualSize(first, second);

	for (std::size_t i = 0; i < first.Cols(); ++i)
	{
		ASSERT_EQ(factor * first[srcRow][i] + first[destRow][i], second[destRow][i]);
	}

	for (std::size_t i = 0; i < first.Rows(); ++i)
	{
		if (i == destRow) continue;

		for (std::size_t j = 0; j < first.Cols(); ++j)
		{
			ASSERT_EQ(first[i][j], second[i][j]);
		}
	}
}

TEST(Matrix_RowsManipulations, AddItselfWithFactor)
{
	const auto first = GenerateRandomMatrix<int>();
	auto second = first;

	const std::size_t row = rand() % first.Rows();
	const int factor = rand() % 100 + 5;

	second.AddRow(row, row, factor);

	AssertEqualSize(first, second);

	for (std::size_t i = 0; i < first.Cols(); ++i)
	{
		ASSERT_EQ((factor + 1) * first[row][i], second[row][i]);
	}

	for (std::size_t i = 0; i < first.Rows(); ++i)
	{
		if (i == row) continue;

		for (std::size_t j = 0; j < first.Cols(); ++j)
		{
			ASSERT_EQ(first[i][j], second[i][j]);
		}
	}
}

TEST(Matrix_RowsManipulations, Subtract)
{
	const auto first = GenerateRandomMatrix<int>();
	auto second = first;

	const std::size_t rows = first.Rows();
	const std::size_t srcRow = rand() % (rows / 2);
	const std::size_t destRow = rows / 2 + rand() % (rows / 2);

	second.SubtractRow(srcRow, destRow);

	AssertEqualSize(first, second);

	for (std::size_t i = 0; i < first.Cols(); ++i)
	{
		ASSERT_EQ(first[destRow][i] - first[srcRow][i], second[destRow][i]);
	}

	for (std::size_t i = 0; i < first.Rows(); ++i)
	{
		if (i == destRow) continue;

		for (std::size_t j = 0; j < first.Cols(); ++j)
		{
			ASSERT_EQ(first[i][j], second[i][j]);
		}
	}
}

TEST(Matrix_RowsManipulations, SubtractItself)
{
	const auto first = GenerateRandomMatrix<int>();
	auto second = first;

	const std::size_t row = rand() % first.Rows();

	second.SubtractRow(row, row);

	AssertEqualSize(first, second);

	for (std::size_t i = 0; i < first.Cols(); ++i)
	{
		ASSERT_EQ(0, second[row][i]);
	}

	for (std::size_t i = 0; i < first.Rows(); ++i)
	{
		if (i == row) continue;

		for (std::size_t j = 0; j < first.Cols(); ++j)
		{
			ASSERT_EQ(first[i][j], second[i][j]);
		}
	}
}

TEST(Matrix_RowsManipulations, SubtractWithFactor)
{
	const auto first = GenerateRandomMatrix<int>();
	auto second = first;

	const std::size_t rows = first.Rows();
	const std::size_t srcRow = rand() % (rows / 2);
	const std::size_t destRow = rows / 2 + rand() % (rows / 2);
	const std::size_t factor = rand() % 100 + 5;

	second.SubtractRow(srcRow, destRow, factor);

	AssertEqualSize(first, second);

	for (std::size_t i = 0; i < first.Cols(); ++i)
	{
		ASSERT_EQ(first[destRow][i] - factor * first[srcRow][i], second[destRow][i]);
	}

	for (std::size_t i = 0; i < first.Rows(); ++i)
	{
		if (i == destRow) continue;

		for (std::size_t j = 0; j < first.Cols(); ++j)
		{
			ASSERT_EQ(first[i][j], second[i][j]);
		}
	}
}

TEST(Matrix_RowsManipulations, SubtractItselfWithFactor)
{
	const auto first = GenerateRandomMatrix<int>();
	auto second = first;

	const std::size_t row = rand() % first.Rows();
	const int factor = rand() % 100 + 5;

	second.SubtractRow(row, row, factor);

	AssertEqualSize(first, second);

	for (std::size_t i = 0; i < first.Cols(); ++i)
	{
		ASSERT_EQ((1 - factor) * first[row][i], second[row][i]);
	}

	for (std::size_t i = 0; i < first.Rows(); ++i)
	{
		if (i == row) continue;

		for (std::size_t j = 0; j < first.Cols(); ++j)
		{
			ASSERT_EQ(first[i][j], second[i][j]);
		}
	}
}

