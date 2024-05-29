#include<iostream>
using namespace std;

class Matrix;
void FillRand(Matrix& obj,int minrand=0,int maxrand=0);
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
	Matrix(int rows = 2, int cols = 2): rows(rows), cols(cols), matrix(new int* [rows])
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

	std::ostream& print(std::ostream& os = std::cout)const
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++) os << matrix[i][j] << "\t";
			os << endl;
		}
		return os;
	}

};

std::ostream& operator<<(std::ostream& os, const Matrix& obj)
{
	return obj.print(os);
}

Matrix operator+(const Matrix& Left, const Matrix& Right)
{
	Matrix Sum(Left.Get_rows(), Left.Get_cols());
	for (int i = 0; i < Sum.Get_rows(); i++) for (int j = 0; j < Sum.Get_cols(); j++) Sum[i][j] = Left[i][j] + Right[i][j];
	return Sum;
}
bool operator==(const Matrix& Left, const Matrix& Right)
{
	if (Left.Get_rows() * Right.Get_cols() != Right.Get_rows() * Left.Get_cols())return false;
	fo
}




void main()
{
	setlocale(LC_ALL, "");

	Matrix A(3, 3);
	FillRand(A, 1, 10);
	cout << A << endl;
	Matrix B(3, 3);
	FillRand(B, 3, 9);
	cout << B << endl;
	Matrix C = A + B;
	cout << C << endl;



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




/*class Matrix
{
	int rows;
	int cols;
	int** arr;
public:
	int get_rows()const
	{
		return rows;
	}
	int get_cols()const
	{
		return cols;
	}
	//				Constructors:
	Matrix(int rows = 2, int cols = 2)
	{
		this->rows = rows;
		this->cols = cols;
		this->arr = new int* [rows] {};
		for (int i = 0; i < rows; i++)
		{
			arr[i] = new int[cols] {};
		}
		cout << "Constructor:\t" << this << endl;
	}
	Matrix(int n) :Matrix(1, n)
	{

	}
	Matrix(const Matrix& other)//:Matrix(other.rows, other.cols)
	{
		/*for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				this->arr[i][j] = other.arr[i][j];
			}
		}*/
		/**this = other;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Matrix()
	{
		for (int i = 0; i < rows; i++)
		{
			delete[] arr[i];
		}
		delete[] arr;
		arr = nullptr;
		rows = 0;
		cols = 0;
		cout << "Destructor:\t" << this << endl;
	}

	//				Operators:
	Matrix& operator=(const Matrix& other)
	{
		if (this == &other)return *this;
		this->~Matrix();
		this->rows = other.rows;
		this->cols = other.cols;
		this->arr = new int* [rows] {};
		for (int i = 0; i < rows; i++)
		{
			this->arr[i] = new int[cols] {};
			memcpy(this->arr[i], other.arr[i], cols * sizeof(int));
		}
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	const int* operator[](int i)const
	{
		return arr[i];
	}
	int* operator[](int i)
	{
		return arr[i];
	}

	//				Methods:
	void print()const
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				cout << arr[i][j] << "\t";
			}
			cout << endl;
		}
	}
};

void main()
{
	setlocale(LC_ALL, "Russin");
	Matrix A(3, 4);
	for (int i = 0; i < A.get_rows(); i++)
	{
		for (int j = 0; j < A.get_cols(); j++)
		{
			A[i][j] = rand() % 100;
		}
	}
	A = A;
	A.print();
	Matrix B;
	B = A;	//Copy assignment
	B.print();
}*/