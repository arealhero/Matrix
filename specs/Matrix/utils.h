#pragma once

#include <cstdlib>

#include <gtest/gtest.h>

#include <Matrix.h>

std::size_t GenerateSize()
{
	return rand() % 100 + 1;
}

template<typename T>
Matrix<T> GenerateRandomMatrix(const std::size_t rows, const std::size_t cols)
{
	Matrix<T> matrix(rows, cols);

	for (std::size_t i = 0; i < matrix.Rows(); ++i)
	{
		for (std::size_t j = 0; j < matrix.Cols(); ++j)
		{
			matrix[i][j] = rand() % 10000;
		}
	}

	return matrix;
}

template<typename T>
Matrix<T> GenerateRandomMatrix()
{
	const std::size_t rows = GenerateSize();
	const std::size_t cols = GenerateSize();
	return GenerateRandomMatrix<T>(rows, cols);
}

template<typename T>
Matrix<T> GenerateRandomSquareMatrix()
{
	const std::size_t n = GenerateSize();
	return GenerateRandomMatrix<T>(n, n);
}

template<typename T>
void AssertEqualSize(const Matrix<T>& expected, const Matrix<T>& actual)
{
	ASSERT_EQ(expected.Rows(), actual.Rows());
	ASSERT_EQ(expected.Cols(), actual.Cols());
}

template<typename T>
void AssertEqual(const Matrix<T>& expected, const Matrix<T>& actual)
{
	AssertEqualSize(expected, actual);

	for (std::size_t i = 0; i < expected.Rows(); ++i)
	{
		for (std::size_t j = 0; j < expected.Cols(); ++j)
		{
			ASSERT_EQ(expected[i][j], actual[i][j]);
		}
	}
}

