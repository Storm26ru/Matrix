#include<iostream>
using namespace std;

class Matrix
{
	int rows;
	int cols;
	int** matrix;

public:

	Matrix(int rows = 2, int cols = 2): rows(rows), cols(cols), matrix(new int* [rows])
	{
		for (int i = 0; i < rows; i++) matrix[i] = new int[cols] {};
		cout << "Constructor" << "\t" << this << endl;
	}

	Matrix(const Matrix& other): Matrix(other.rows,other.cols)
	{
		/*for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++) this->matrix[i][j] = other.matrix[i][j];
		}*/
		*this = other;
		cout << "CopyConstructor" << "\t" << this << endl;
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

	/*Matrix& operator=(Matrix&& other)
	{
		if (this == &other)return *this;
		this->~Matrix();

	}*/


	void print()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++) cout << matrix[i][j] << "\t";
			cout << endl;
		}

	}

};








void main()
{
	setlocale(LC_ALL, "");

	Matrix A(3, 3);
	Matrix B(3, 3); B = A;
	B.print();




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