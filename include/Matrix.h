#pragma once

#include <vector>
#include <iostream>

template<typename T>
class Matrix
{
public:
	Matrix(std::size_t rows, std::size_t cols, const T& value = T());
	Matrix(const Matrix<T>& other);
	Matrix(Matrix<T>&& other);

	Matrix<T>& operator=(const Matrix<T>& other);
	Matrix<T>& operator=(Matrix<T>&& other);

	Matrix<T> Transpose() const;
	Matrix<T> Inverse() const;
	T Determinant() const;

	Matrix<T>& operator+=(const T& value);
	Matrix<T>& operator-=(const T& value);
	Matrix<T>& operator*=(const T& value);
	Matrix<T>& operator/=(const T& value);

	Matrix<T>& operator+=(const Matrix<T>& other);
	Matrix<T>& operator-=(const Matrix<T>& other);

	std::vector<T>& operator[](std::size_t row);
	const std::vector<T>& operator[](std::size_t row) const;

	std::size_t Rows() const;
	std::size_t Cols() const;

	bool IsSquare() const;

	void SwapRows(std::size_t i, std::size_t j);
	void SwapCols(std::size_t i, std::size_t j);

	void AddRow(std::size_t srcIndex, std::size_t destIndex, const T& factor = 1);
	void SubtractRow(std::size_t srcIndex, std::size_t destIndex, const T& factor = 1);
	void MultiplyRow(std::size_t row, const T& value);
	void DivideRow(std::size_t row, const T& value);

	void AddCol(std::size_t srcIndex, std::size_t destIndex, const T& factor = 1);
	void SubtractCol(std::size_t srcIndex, std::size_t destIndex, const T& factor = 1);
	void MultiplyCol(std::size_t col, const T& value);
	void DivideCol(std::size_t col, const T& value);

	Matrix<T> Submatrix(const std::vector<std::size_t>& rows, const std::vector<std::size_t>& cols) const;

	friend Matrix<T> operator*(const T& value, const Matrix<T>& matrix)
	{
		Matrix<T> result(matrix.Rows(), matrix.Cols());

		for (std::size_t i = 0; i < matrix.Rows(); ++i)
		{
			for (std::size_t j = 0; j < matrix.Cols(); ++j)
			{
				result[i][j] = value * matrix[i][j];
			}
		}

		return result;
	}

	friend Matrix<T> operator*(const Matrix<T>& matrix, const T& value)
	{
		return value * matrix;
	}

	friend Matrix<T> operator/(const Matrix<T>& matrix, const T& value)
	{
		Matrix<T> result(matrix.Rows(), matrix.Cols());

		for (std::size_t i = 0; i < matrix.Rows(); ++i)
		{
			for (std::size_t j = 0; j < matrix.Cols(); ++j)
			{
				result[i][j] = matrix[i][j] / value;
			}
		}

		return result;
	}

	friend Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs)
	{
		if (lhs.Rows() != rhs.Rows() || lhs.Cols() != rhs.Cols())
		{
			throw std::runtime_error{ "Cannot add matrices: sizes do not match" };
		}

		Matrix<T> result(lhs.Rows(), lhs.Cols());

		for (std::size_t i = 0; i < result.Rows(); ++i)
		{
			for (std::size_t j = 0; j < result.Cols(); ++j)
			{
				result[i][j] = lhs[i][j] + rhs[i][j];
			}
		}

		return result;
	}

	friend Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs)
	{
		return lhs + (-1) * rhs;
	}

	friend Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs)
	{
		if (lhs.Cols() != rhs.Rows())
		{
			throw std::runtime_error{ "Cannot multiply matrices: sizes do not match" };
		}

		Matrix<T> result(lhs.Rows(), rhs.Cols());

		for (std::size_t i = 0; i < result.Rows(); ++i)
		{
			for (std::size_t j = 0; j < result.Cols(); ++j)
			{
				for (std::size_t k = 0; k < lhs.Cols(); ++k)
				{
					result[i][j] += lhs[i][k] * rhs[k][j];
				}
			}
		}

		return result;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Matrix<T>& matrix)
	{
		for (std::size_t i = 0; i < matrix.Rows(); ++i)
		{
			for (std::size_t j = 0; j < matrix.Cols(); ++j)
			{
				stream << matrix[i][j] << ' ';
			}

			stream << '\n';
		}

		return stream;
	}

	static Matrix<T> Identity(std::size_t n);

private:
	std::vector<std::vector<T>> data;
	std::size_t rows;
	std::size_t cols;
};

#include "../src/Matrix.cc"

