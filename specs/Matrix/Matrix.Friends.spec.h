#pragma once

#include <gtest/gtest.h>

#include <Matrix.h>

#include "utils.h"

TEST(Matrix_Friends, Addition)
{
	const std::size_t rows = GenerateSize();
	const std::size_t cols = GenerateSize();

	auto first = GenerateRandomMatrix<int>(rows, cols);
	auto second = GenerateRandomMatrix<int>(rows, cols);

	auto sum = first + second;

	ASSERT_EQ(rows, sum.Rows());
	ASSERT_EQ(cols, sum.Cols());

	for (std::size_t i = 0; i < sum.Rows(); ++i)
	{
		for (std::size_t j = 0; j < sum.Cols(); ++j)
		{
			ASSERT_EQ(first[i][j] + second[i][j], sum[i][j]);
		}
	}
}

TEST(Matrix_Friends, Addition_ShouldThrowIfSizesDiffer)
{
	const std::size_t firstRows = GenerateSize();
	const std::size_t firstCols = GenerateSize();

	const std::size_t secondRows = firstRows + rand() % 10 + 1;
	const std::size_t secondCols = secondRows + rand() % 10 + 1;

	auto first = GenerateRandomMatrix<int>(firstRows, firstCols);
	auto second = GenerateRandomMatrix<int>(secondRows, secondCols);

	ASSERT_THROW(auto third = first + second, std::runtime_error);
}

TEST(Matrix_Friends, Subtraction)
{
	const std::size_t rows = GenerateSize();
	const std::size_t cols = GenerateSize();

	auto first = GenerateRandomMatrix<int>(rows, cols);
	auto second = GenerateRandomMatrix<int>(rows, cols);

	auto difference = first - second;

	ASSERT_EQ(rows, difference.Rows());
	ASSERT_EQ(cols, difference.Cols());

	for (std::size_t i = 0; i < rows; ++i)
	{
		for (std::size_t j = 0; j < cols; ++j)
		{
			ASSERT_EQ(first[i][j] - second[i][j], difference[i][j]);
		}
	}

	AssertEqual(first, difference + second);
}

TEST(Matrix_Friends, Subtraction_ShouldThrow_IfSizesDiffer)
{
	const std::size_t firstRows = GenerateSize();
	const std::size_t firstCols = GenerateSize();

	const std::size_t secondRows = firstRows + rand() % 10 + 1;
	const std::size_t secondCols = secondRows + rand() % 10 + 1;

	auto first = GenerateRandomMatrix<int>(firstRows, firstCols);
	auto second = GenerateRandomMatrix<int>(secondRows, secondCols);

	ASSERT_THROW(auto third = first - second, std::runtime_error);
}

TEST(Matrix_Friends, Multiplication)
{
	const std::size_t firstRows = GenerateSize();
	const std::size_t firstCols = GenerateSize();

	const std::size_t secondRows = firstCols;
	const std::size_t secondCols = GenerateSize();

	auto first = GenerateRandomMatrix<int>(firstRows, firstCols);
	auto second = GenerateRandomMatrix<int>(secondRows, secondCols);

	auto product = first * second;

	ASSERT_EQ(first.Rows(), product.Rows());
	ASSERT_EQ(second.Cols(), product.Cols());

	for (std::size_t i = 0; i < product.Rows(); ++i)
	{
		for (std::size_t j = 0; j < product.Cols(); ++j)
		{
			int sum = 0;

			for (std::size_t k = 0; k < first.Cols(); ++k)
			{
				sum += first[i][k] * second[k][j];
			}

			ASSERT_EQ(sum, product[i][j]);
		}
	}
}

TEST(Matrix_Friends, Multiplication_ShouldThrow_IfSizesDiffer)
{
	const std::size_t firstRows = GenerateSize();
	const std::size_t firstCols = GenerateSize();

	const std::size_t secondRows = firstRows + rand() % 10 + 1;
	const std::size_t secondCols = secondRows + rand() % 10 + 1;

	auto first = GenerateRandomMatrix<int>(firstRows, firstCols);
	auto second = GenerateRandomMatrix<int>(secondRows, secondCols);

	ASSERT_THROW(auto third = first * second, std::runtime_error);
}

TEST(Matrix_Friends, ScalarMultiplication_Left)
{
	auto first = GenerateRandomMatrix<int>();
	int scalar = rand() % 1500 + 1;

	auto second = scalar * first;

	ASSERT_EQ(first.Rows(), second.Rows());
	ASSERT_EQ(first.Cols(), second.Cols());

	for (std::size_t i = 0; i < first.Rows(); ++i)
	{
		for (std::size_t j = 0; j < first.Cols(); ++j)
		{
			ASSERT_EQ(scalar * first[i][j], second[i][j]);
		}
	}
}

TEST(Matrix_Friends, ScalarMultiplication_Right)
{
	auto first = GenerateRandomMatrix<int>();
	int scalar = rand() % 1500 + 1;

	auto second = first * scalar;

	ASSERT_EQ(first.Rows(), second.Rows());
	ASSERT_EQ(first.Cols(), second.Cols());

	for (std::size_t i = 0; i < first.Rows(); ++i)
	{
		for (std::size_t j = 0; j < first.Cols(); ++j)
		{
			ASSERT_EQ(first[i][j] * scalar, second[i][j]);
		}
	}
}

TEST(Matrix_Friends, ScalarDivision)
{
	auto first = GenerateRandomMatrix<int>();
	int scalar = rand() % 1500 + 1;

	auto second = first / scalar;

	ASSERT_EQ(first.Rows(), second.Rows());
	ASSERT_EQ(first.Cols(), second.Cols());

	for (std::size_t i = 0; i < first.Rows(); ++i)
	{
		for (std::size_t j = 0; j < first.Cols(); ++j)
		{
			ASSERT_EQ(first[i][j] / scalar, second[i][j]);
		}
	}
}

