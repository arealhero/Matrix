#include <gtest/gtest.h>

#include <Matrix.h>

#include "utils.h"

#include <utility>

#include "Matrix.Friends.spec.h"


TEST(Matrix, ShouldHaveTransposeMethod)
{
	Matrix<int> matrix = GenerateRandomMatrix<int>();
	Matrix<int> transposed = matrix.Transpose();

	ASSERT_EQ(matrix.Rows(), transposed.Cols());
	ASSERT_EQ(matrix.Cols(), transposed.Rows());

	for (std::size_t i = 0; i < matrix.Rows(); ++i)
	{
		for (std::size_t j = 0; j < matrix.Cols(); ++j)
		{
			ASSERT_EQ(matrix[i][j], transposed[j][i]);
		}
	}
}

int main(int argc, char* argv[])
{
	srand(time(nullptr));

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

