#pragma once

#include <gtest/gtest.h>

#include <Matrix.h>

#include "utils.h"

TEST(Matrix_DefaultConstructor, ShoudAcceptNumberOfRowsAndColumns)
{
	Matrix<int> matrix(10, 20);

	EXPECT_EQ(matrix.Rows(), 10);
	EXPECT_EQ(matrix.Cols(), 20);
}

TEST(Matrix_DefaultConstructor, ShouldDefaultInitWithZeros)
{
	Matrix<int> matrix(10, 20);

	for (std::size_t i = 0; i < matrix.Rows(); ++i)
	{
		for (std::size_t j = 0; j < matrix.Cols(); ++j)
		{
			ASSERT_EQ(matrix[i][j], 0);
		}
	}
}

TEST(Matrix_DefaultConstructor, ShouldAcceptInitValue)
{
	Matrix<int> matrix(10, 20, 3);

	for (std::size_t i = 0; i < matrix.Rows(); ++i)
	{
		for (std::size_t j = 0; j < matrix.Cols(); ++j)
		{
			ASSERT_EQ(matrix[i][j], 3);
		}
	}
}

TEST(Matrix, ShouldHaveCopyConstructor)
{
	Matrix<int> first = GenerateRandomMatrix<int>();
	Matrix<int> second(first);

	AssertEqual(first, second);
}

TEST(Matrix, ShouldHaveMoveConstructor)
{
	Matrix<int> first = GenerateRandomMatrix<int>();
	Matrix<int> copy(first);

	Matrix<int> second(std::move(copy));

	AssertEqual(first, second);
}

TEST(Matrix, ShouldHaveCopyAssignmentOperator)
{
	Matrix<int> first = GenerateRandomMatrix<int>();
	Matrix<int> second = first;

	AssertEqual(first, second);
}

TEST(Matrix, ShouldHaveMoveAssignmentOperator)
{
	Matrix<int> first = GenerateRandomMatrix<int>();
	Matrix<int> copy = first;
	Matrix<int> second = std::move(copy);

	AssertEqual(first, second);
}

