#include<iostream>
using namespace std;

class Matrix;
void FillRand(Matrix& obj,int minrand=0,int maxrand=10);
Matrix operator+(const Matrix& Left, const Matrix& Right);
Matrix operator-(const Matrix& Left, const Matrix& Right);
Matrix operator*(const Matrix& Left, const Matrix& Right);

void Print(double**& matrix, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) cout << matrix[i][j] << "\t";
		cout << endl;
	}
}

class Matrix
{
	int rows;
	int cols;
	int** matrix;

public:
	int Get_rows() const
	{
		return rows;
	}
	int Get_cols()const
	{
		return cols;
	}

	//					Constructors

	Matrix(int rows=2, int cols=2): rows(rows), cols(cols), matrix(new int* [rows])
	{
		for (int i = 0; i < rows; i++) matrix[i] = new int[cols] {};
		cout << "Constructor" << "\t" << this << endl;
	}
	Matrix(int cols) :Matrix(1, cols)
	{
		cout << "1ArgConstructor" << "\t" << endl;
	}
	Matrix(const Matrix& other): Matrix(other.rows,other.cols)
	{
		*this = other;
		cout << "CopyConstructor" << "\t" << this << endl;
	}
	Matrix(Matrix&& other): matrix(other.matrix), rows(other.rows), cols(other.cols)
	{
		other.matrix = nullptr;
		other.rows = 0;
		other.cols = 0;
		cout << "MoveConstructor" << "\t" << this << endl;
	}



	~Matrix()
	{
		for (int i = 0; i < rows; i++) delete[] matrix[i];
		delete[] matrix;
		matrix = nullptr;
		rows = 0;
		cols = 0;
		cout << "Destructor" <<"\t"<<this << endl;
	}

	//					Operators

	Matrix& operator=(const Matrix& other)
	{
		if (this == &other)return *this;
		this->~Matrix();
		this->rows = other.rows;
		this->cols = other.cols;
		this->matrix = new int* [rows] {};
		for (int i = 0; i < rows; i++)
		{
			this->matrix[i] = new int[cols] {};
			for (int j = 0; j < cols; j++) this->matrix[i][j] = other.matrix[i][j];
		}
		cout << "CopuAssignment" << "\t" << this << endl;
		return *this;
	}

	Matrix& operator=(Matrix&& other)
	{
		if (this == &other)return *this;
		this->~Matrix();
		this->matrix = other.matrix;
		this->rows = other.rows;
		this->cols = other.cols;
		other.matrix = nullptr;
		other.rows = 0;
		other.cols = 0;
		cout << "MoveAssignment" << "\t" << this << endl;
		return *this;

	}
	const int* operator[](int i)const
	{
		return matrix[i];
	}
	int* operator[](int i)
	{
		return matrix[i];
	}
	Matrix& operator+=(const Matrix& other)
	{
		return *this = *this + other;
	}
	Matrix& operator-=(const Matrix& other)
	{
		return *this = *this - other;
	}
	Matrix& operator*=(const Matrix& other)
	{
		return *this = *this * other;
	}


	std::ostream& print(std::ostream& os = std::cout)const
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++) os << matrix[i][j] << "\t";
			os << endl;
		}
		return os;
	}

	//					Methods

	bool dimension(const Matrix& other)const
	{
		return rows * other.Get_cols() == other.Get_rows() * cols;
	}

	double determinant()
	{
		double det = 1;
		if (rows != cols) 
		{
			cerr << "Ошибка, определитель можно вычислить только для квадратной матрицы " << endl;
			return det = 0;
		}
		double** matrix = new double* [rows]; 
		for (int i = 0; i < rows; i++) matrix[i] = new double[cols] {};
		for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) matrix[i][j] = this->matrix[i][j];
		for (int k = 0; k < cols - 1; k++)
		{

			for (int i = k + 1; i < rows; i++)
			{
				double mul = 0;
				for (int j = k; j < cols; j++)
				{
					if (j == k) mul = -matrix[i][j] / matrix[k][j];
					matrix[i][j] += matrix[k][j] * mul;
				}
				if (matrix[i][i] == 0)
				{

				return det = 0;
				}

			}
		}
		Print(matrix, rows);

		for (int i = 0; i < rows; i++) det *= matrix[i][i];
		for (int i = 0; i < rows; i++) delete[] matrix[i];
		delete[] matrix;
		return det;
	}

};


std::ostream& operator<<(std::ostream& os, const Matrix& obj)
{
	return obj.print(os);
}

Matrix operator+(const Matrix& Left, const Matrix& Right)
{
	if (!Left.dimension(Right))
	{
		cerr << "Ошибка, матрицы разных размеров " << endl;
		return Matrix();
	}
	Matrix Sum(Left.Get_rows(), Left.Get_cols());
	for (int i = 0; i < Sum.Get_rows(); i++) for (int j = 0; j < Sum.Get_cols(); j++) Sum[i][j] = Left[i][j] + Right[i][j];
	return Sum;
}Matrix operator-(const Matrix& Left, const Matrix& Right)
{
	if (!Left.dimension(Right))
	{
		cerr << "Ошибка, матрицы разных размеров " << endl;
		return Matrix();
	}
	Matrix Difference(Left.Get_rows(), Left.Get_cols());
	for (int i = 0; i < Difference.Get_rows(); i++) for (int j = 0; j < Difference.Get_cols(); j++) Difference[i][j] = Left[i][j] - Right[i][j];
	return Difference;
}
Matrix operator*(const Matrix& Left, const Matrix& Right)
{
	if (Left.Get_cols() != Right.Get_rows())
	{
		cerr<<"Ошибка,число столбцов первой матрицы не равно числу строк второй матрицы"<<endl;
		return Matrix();
	}
	Matrix Multiplication(Left.Get_rows(), Right.Get_cols());
	for (int i = 0; i < Multiplication.Get_rows(); i++) for (int j = 0; j < Right.Get_cols(); j++) for (int k = 0; k < Left.Get_cols(); k++)
		Multiplication[i][j] += Left[i][k] * Right[k][j];
	return Multiplication;
}
bool operator==(const Matrix& Left, const Matrix& Right)
{
	if (!Left.dimension(Right))
	{
		cerr << "Ошибка, матрицы разных размеров " << endl;
		return false;
	}
	for (int i = 0; i < Left.Get_rows(); i++) for (int j = 0; j < Left.Get_cols(); j++) if (Left[i][j] != Right[i][j]) return false;
	return true;
}bool operator!=(const Matrix& Left, const Matrix& Right)
{
	if (!Left.dimension(Right))
	{
		cerr << "Ошибка, матрицы разных размеров " << endl;
		return false;
	}
	return !(Left == Right);
}




void main()
{
	setlocale(LC_ALL, "");

	Matrix A(3, 3);
	FillRand(A,1,5);
	cout << A << endl;
	//Matrix S;
	//S = A;
	//cout << S << endl;
	Matrix B(3, 3);
	FillRand(B, 2, 3);
	cout << B << endl;
	Matrix C =A * B;
	cout << C << endl;
    //cout << A.determinant() << endl;
	//cout << (A != B) << endl;



}

void FillRand(Matrix& obj, int minrand, int maxrand)
{
	if (minrand > maxrand)
	{
		int bufer = maxrand; maxrand = minrand; minrand = bufer;
	}
	for (int i = 0; i < obj.Get_rows(); i++)
	{
		for (int j = 0; j < obj.Get_cols(); j++) obj[i][j] = rand() % (maxrand-minrand)+minrand;
	}
}
