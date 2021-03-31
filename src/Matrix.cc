#include "Matrix.h"

#include <stdexcept>
#include <algorithm>

template<typename T>
class Matrix;

template<typename T>
Matrix<T>::Matrix(std::size_t rows, std::size_t cols, const T& value)
	: rows(rows)
	, cols(cols)
{
	data.reserve(rows);

	for (std::size_t i = 0; i < rows; ++i)
	{
		data.emplace_back(cols, value);
	}
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& other)
	: data(other.data)
	, rows(other.rows)
	, cols(other.cols)
{}

template<typename T>
Matrix<T>::Matrix(Matrix<T>&& other)
	: data(std::move(other.data))
	, rows(other.rows)
	, cols(other.cols)
{}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
{
	data = other.data;
	rows = other.rows;
	cols = other.cols;

	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other)
{
	data = std::move(other.data);
	rows = other.rows;
	cols = other.cols;

	return *this;
}

template<typename T>
Matrix<T> Matrix<T>::Transpose() const
{
	Matrix<T> result(cols, rows);
	for (std::size_t i = 0; i < cols; ++i)
	{
		for (std::size_t j = 0; j < rows; ++j)
		{
			result[i][j] = data[j][i];
		}
	}
	return result;
}

template<typename T>
Matrix<T> Matrix<T>::Inverse() const
{
	if (!IsSquare())
	{
		throw std::runtime_error{ "Cannot invert matrix: rows != cols" };
	}

	const std::size_t n = rows;

	Matrix<T> inverse = Matrix<T>::Identity(n);
	Matrix<T> copy = *this;

	for (std::size_t col = 0; col < n; ++col)
	{
		std::size_t row = col;

		while (row < n)
		{
			if (copy.data[row][col] != 0)
			{
				break;
			}

			++row;
		}

		if (row == n)
		{
			throw std::runtime_error{ "Cannot invert matrix: det = 0" };
		}

		inverse.SwapRows(col, row);
		copy.SwapRows(col, row);

		inverse.DivideRow(col, copy.data[col][col]);
		copy.DivideRow(col, copy.data[col][col]);

		++row;

		while (row < n)
		{
			inverse.SubtractRows(col, row, copy.data[row][col]);
			copy.SubtractRows(col, row, copy.data[row][col]);

			++row;
		}
	}

	for (std::size_t col = 0; col < n; ++col)
	{
		for (std::size_t row = col + 1; row < n; ++row)
		{
			const std::size_t i = n - col - 1;
			const std::size_t j = n - row - 1;

			inverse.SubtractRows(i, j, copy.data[j][i]);
			copy.SubtractRows(i, j, copy.data[j][i]);
		}
	}

	return inverse;
}

template<typename T>
T Matrix<T>::Determinant() const
{
	if (!IsSquare())
	{
		throw std::runtime_error{ "Cannot find determinant: rows != cols" };
	}

	const std::size_t n = rows;

	T det = 1;
	T sign = 1;

	Matrix<T> copy = *this;

	for (std::size_t col = 0; col < n; ++col)
	{
		std::size_t row = col;

		while (row < n)
		{
			if (copy.data[row][col] != 0)
			{
				break;
			}

			++row;
		}

		if (row == n)
		{
			return 0;
		}

		if (col != row)
		{
			copy.SwapRows(col, row);
			sign *= -1;
		}

		++row;

		while (row < n)
		{
			copy.SubtractRow(col, row, copy.data[row][col] / copy.data[col][col]);
			++row;
		}

		det *= copy[col][col];
	}

	return sign * det;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const T& value)
{
	for (std::size_t i = 0; i < rows; ++i)
	{
		for (std::size_t j = 0; j < cols; ++j)
		{
			data[i][j] += value;
		}
	}

	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const T& value)
{
	for (std::size_t i = 0; i < rows; ++i)
	{
		for (std::size_t j = 0; j < cols; ++j)
		{
			data[i][j] -= value;
		}
	}

	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const T& value)
{
	for (std::size_t i = 0; i < rows; ++i)
	{
		for (std::size_t j = 0; j < cols; ++j)
		{
			data[i][j] *= value;
		}
	}

	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator/=(const T& value)
{
	for (std::size_t i = 0; i < rows; ++i)
	{
		for (std::size_t j = 0; j < cols; ++j)
		{
			data[i][j] /= value;
		}
	}

	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other)
{
	if (rows != other.rows || cols != other.cols)
	{
		throw std::runtime_error{ "Cannot add matrices: sizes do not match" };
	}

	for (std::size_t i = 0; i < rows; ++i)
	{
		for (std::size_t j = 0; j < cols; ++j)
		{
			data[i][j] += other.data[i][j];
		}
	}

	return data;
}

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other)
{
	if (rows != other.rows || cols != other.cols)
	{
		throw std::runtime_error{ "Cannot subtract matrices: sizes do not match" };
	}

	for (std::size_t i = 0; i < rows; ++i)
	{
		for (std::size_t j = 0; j < cols; ++j)
		{
			data[i][j] -= other.data[i][j];
		}
	}

	return data;
}

template<typename T>
std::vector<T>& Matrix<T>::operator[](std::size_t row)
{
	return data[row];
}

template<typename T>
const std::vector<T>& Matrix<T>::operator[](std::size_t row) const
{
	return data[row];
}

template<typename T>
std::size_t Matrix<T>::Rows() const
{
	return rows;
}

template<typename T>
std::size_t Matrix<T>::Cols() const
{
	return cols;
}

template<typename T>
bool Matrix<T>::IsSquare() const
{
	return Rows() == Cols();
}

template<typename T>
void Matrix<T>::SwapRows(std::size_t i, std::size_t j)
{
	using std::swap;

	for (std::size_t col = 0; col < cols; ++col)
	{
		swap(data[i][col], data[j][col]);
	}
}

template<typename T>
void Matrix<T>::SwapCols(std::size_t i, std::size_t j)
{
	using std::swap;

	for (std::size_t row = 0; row < rows; ++row)
	{
		swap(data[row][i], data[row][j]);
	}
}

template<typename T>
void Matrix<T>::AddRow(std::size_t srcIndex, std::size_t destIndex, const T& factor)
{
	for (std::size_t col = 0; col < cols; ++col)
	{
		data[destIndex][col] += factor * data[srcIndex][col];
	}
}

template<typename T>
void Matrix<T>::SubtractRow(std::size_t srcIndex, std::size_t destIndex, const T& factor)
{
	AddRow(srcIndex, destIndex, -factor);
}

template<typename T>
void Matrix<T>::MultiplyRow(std::size_t row, const T& value)
{
	for (std::size_t col = 0; col < cols; ++col)
	{
		data[row][col] *= value;
	}
}

template<typename T>
void Matrix<T>::DivideRow(std::size_t row, const T& value)
{
	for (std::size_t col = 0; col < cols; ++col)
	{
		data[row][col] /= value;
	}
}

template<typename T>
void Matrix<T>::AddCol(std::size_t srcIndex, std::size_t destIndex, const T& factor)
{
	for (std::size_t row = 0; row < rows; ++row)
	{
		data[row][destIndex] += factor * data[row][srcIndex];
	}
}

template<typename T>
void Matrix<T>::SubtractCol(std::size_t srcIndex, std::size_t destIndex, const T& factor)
{
	AddCol(srcIndex, destIndex, -factor);
}

template<typename T>
void Matrix<T>::MultiplyCol(std::size_t col, const T& value)
{
	for (std::size_t row = 0; row < rows; ++row)
	{
		data[row][col] *= value;
	}
}

template<typename T>
void Matrix<T>::DivideCol(std::size_t col, const T& value)
{
	for (std::size_t row = 0; row < rows; ++row)
	{
		data[row][col] /= value;
	}
}

template<typename T>
Matrix<T> Matrix<T>::Submatrix(const std::vector<std::size_t>& rows, const std::vector<std::size_t>& cols) const
{
	Matrix<T> result(rows.size(), cols.size());

	for (std::size_t i = 0; i < rows.size(); ++i)
	{
		for (std::size_t j = 0; j < cols.size(); ++j)
		{
			result[i][j] = data[rows[i]][cols[j]];
		}
	}

	return result;
}

template<typename T>
Matrix<T> Matrix<T>::Identity(std::size_t n)
{
	Matrix<T> result(n, n);

	for (std::size_t i = 0; i < n; ++i)
	{
		result[i][i] = 1;
	}

	return result;
}

