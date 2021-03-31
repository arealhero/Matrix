#include "Matrix.h"

template<typename T>
Matrix<T> ReadMatrix()
{
	std::size_t rows, cols;

	std::cout << "Rows: ";
	std::cin >> rows;

	std::cout << "Cols: ";
	std::cin >> cols;

	Matrix<T> result(rows, cols);

	std::cout << "Enter elements.\n";

	for (std::size_t i = 0; i < rows; ++i)
	{
		for (std::size_t j = 0; j < cols; ++j)
		{
			std::cin >> result[i][j];
		}
	}

	return result;
}

int main()
{
	std::cout << "First matrix.\n";
	auto a = ReadMatrix<int>();

	std::cout << "Second Matrix.\n";
	auto b = ReadMatrix<int>();

	std::cout << "a + b:\n" << (a + b);
	std::cout << "a - b:\n" << (a - b);

	if (a.Cols() == b.Rows())
	{
		std::cout << "a * b:\n" << (a * b);
	}

	if (b.Cols() == a.Rows())
	{
		std::cout << "b * a:\n" << (b * a);
	}

	std::cout << "a transpose:\n" << a.Transpose();
	std::cout << "b transpose:\n" << b.Transpose();

	std::cout << "det a: " << a.Determinant() << '\n';
	std::cout << "det b: " << b.Determinant() << '\n';

	return 0;
}

