#pragma once
#include <iostream>
#include <random>
#include <complex>
#include <math.h>
#include <iomanip>
#include <stdexcept>

using namespace std;

namespace matrix {
	template <typename T>
	class Matrix {
	private:
		T** array;
		int rows;
		int cols;
		const double epsilon = 0.000001;

	public:
		Matrix() {
			array = nullptr;
			rows = 0;
			cols = 0;
		}

		Matrix(int _rows, int _cols) {
			rows = _rows;
			cols = _cols;
			array = (T**) new T * [rows];
			for (int i = 0; i < rows; i++) 
				array[i] = (T*) new T[cols];
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++) 
					array[i][j] = 0;
		}

		Matrix(const Matrix& _array) {
			rows = _array.rows;
			cols = _array.cols;
			array = (T**) new T * [rows];
			for (int i = 0; i < rows; i++)
				array[i] = (T*) new T[cols];
			for (int i = 0; i < rows; i++) 
				for (int j = 0; j < cols; j++) 
					array[i][j] = _array.array[i][j]; ;
		}

		Matrix& operator=(const Matrix& _array) {
			for (int i = 0; i < rows; i++)
				delete[] array[i];
			delete[] array;
			rows = _array.rows;
			cols = _array.cols;
			array = (T**) new T * [rows];
			for (int i = 0; i < rows; i++)
				array[i] = (T*) new T[cols];
			for (int i = 0; i < rows; i++) 
				for (int j = 0; j < cols; j++) 
					array[i][j] = _array.array[i][j];
			return *this;
		}

		~Matrix() {
			for (int i = 0; i < rows; i++)
				delete[] array[i];
			delete[] array;
		}

		int get_row() {
			return rows;
		}

		int get_col() {
			return cols;
		}

		Matrix(int _rows, int _cols, T bottom_limit, T upper_limit) {
			rows = _rows;
			cols = _cols;
			array = (T**) new T * [rows];
			for (int i = 0; i < rows; i++) 
				array[i] = (T*)new T[cols];
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					random_device rd;
					mt19937 gen(rd());
					uniform_real_distribution<> segment(bottom_limit, upper_limit);
					array[i][j] = segment(gen);
				}
			}
		}

		Matrix(int _rows, int _cols, T _array[]) {
			rows = _rows;
			cols = _cols;
			array = (T**) new T * [rows];
			for (int i = 0; i < rows; i++) 
				array[i] = (T*)new T[cols];
			int _size = 0;
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					array[i][j] = _array[_size];
					_size++;
				}
			}
		}

		T& operator()(const int _index_row, const int _index_col) const {
			return array[_index_row][_index_col];
		}

		Matrix& operator+=(const Matrix& _array) {
			if (rows != _array.rows || cols != _array.cols)
				throw std::invalid_argument("Matrix::The sizes of the matrices do not match");
			else {
				for (int i = 0; i < rows; i++)
					for (int j = 0; j < cols; j++)
						array[i][j] += _array.array[i][j];
			}
			return *this;
		}

		Matrix& operator-=(const Matrix& _array) {
			if (rows != _array.rows || cols != _array.cols)
				throw std::invalid_argument("Matrix::The sizes of the matrices do not match");
			else {
				for (int i = 0; i < rows; i++)
					for (int j = 0; j < cols; j++)
						array[i][j] -= _array.array[i][j];
			}
			return *this;
		}

		friend Matrix operator+(Matrix& array, const Matrix& _array) {
			if (array.rows != _array.rows || array.cols != _array.cols)
				throw std::invalid_argument("Matrix::The sizes of the matrices do not match");
			else {
				Matrix c(array);
				c += _array;
				return c;
			}
		}

		friend Matrix operator-(Matrix& array, const Matrix& _array) {
			if (array.rows != _array.rows || array.cols != _array.cols)
				throw std::invalid_argument("Matrix::The sizes of the matrices do not match");
			else {
				Matrix c(array);
				c -= _array;
				return c;
			}
		}

		friend Matrix operator*(Matrix& _array, const Matrix& array) {
			if (array.rows != _array.cols || array.cols != _array.rows)
				throw std::invalid_argument("Matrix::The size of the matrices does not satisfy the multiplication condition");
			else {
				Matrix a(array.rows, _array.cols);
				for (int i = 0; i < array.rows; ++i) 
					for (int j = 0; j < _array.cols; ++j) 
						for (int k = 0; k < array.cols; ++k) 
							a(i, j) += array(i, k) * _array(k, j);
				return a;
			}
		}

		friend Matrix operator*(Matrix & array, T scalar) {
			Matrix _array(array);
			for (int i = 0; i < _array.rows; i++) 
				for (int j = 0; j < _array.cols; j++) 
					_array.array[i][j] = _array.array[i][j] * scalar;
			return _array;
		}

		friend Matrix operator*(T scalar, Matrix & array) {
			Matrix _array(array);
			for (int i = 0; i < _array.rows; i++) 
				for (int j = 0; j < _array.cols; j++)
					_array.array[i][j] = _array.array[i][j] * scalar;
			return _array;
		}

		friend Matrix operator/(Matrix & array, T scalar) {
			if (scalar == T(0))
				throw std::exception("Matrix::Division by zero");
			else {
				Matrix _array(array);
				for (int i = 0; i < _array.rows; i++)
					for (int j = 0; j < _array.cols; j++)
						_array.array[i][j] /= scalar;
				return _array;
			}
		}

		T trace_matrix() {
			if (rows != cols)
				throw std::invalid_argument("Matrix::The matrix must be square");
			else {
				T trace = 0;
				for (int i = 0; i < rows; i++)
					trace += array[i][i];
				return trace;
			}
		}

		bool operator ==(Matrix & _array) const {
			if (cols != _array.cols || rows != _array.rows)
				return false;
			else {
				for (int i = 0; i < rows; i++)
					for (int j = 0; j < rows; j++)
						if (abs(array[i][j] - _array[i][j]) > epsilon)
							return false;
			}
			return true;
		}

		bool operator!=(Matrix & _array) const {
			return !(array == _array);
		}

		template<typename U>
		Matrix(int _rows, int _cols, U bottom_limit_real, U upper_limit_real, U bottom_limit_imag, U upper_limit_imag) {
			rows = _rows;
			cols = _cols;
			array = (T**) new T*[rows];
			for (int i = 0; i < rows; i++) 
				array[i] = (T*) new T[cols];
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++) 
					array[i][j] = complex((bottom_limit_real + rand() % (upper_limit_real - bottom_limit_real)), 
						(bottom_limit_imag + rand() % (upper_limit_imag - bottom_limit_imag)));
		}
	};

	template<typename T>
	T determinate_matrix(Matrix<T>& _array) {
		if (_array.get_row() != _array.get_col())
			throw std::invalid_argument("Matrix::The matrix must be square.");
		else if (_array.get_row() == 1)
			return _array(0, 0);
		else if (_array.get_row() == 2)
			return _array(0, 0) * _array(1, 1) - _array(0, 1) * _array(1, 0);
		else if (_array.get_row() == 3)
			return _array(0, 0) * _array(1, 1) * _array(2, 2) + _array(0, 1) * _array(1, 2) * _array(2, 0) + _array(0, 2) * _array(1, 0) * _array(2, 1) -
			(_array(2, 0) * _array(1, 1) * _array(0, 2) + _array(1, 2) * _array(2, 1) * _array(0, 0) + _array(2, 2) * _array(0, 1) * _array(1, 0));
		else
			throw std::invalid_argument("Matrix::The size of the matrix should not exceed 3.");
	}

	template<typename T>
	void triangular_matrix(Matrix<T>& _array) {
		if (_array.get_row() != _array.get_col())
			throw std::invalid_argument("Matrix::The matrix must be square.");
		else if (determinate_matrix(_array) == T(0))
			throw std::invalid_argument("Matrix::The matrix cannot be reduced to a triangular form, because it is degenerate.");
		else {
			/*T max = array[0][rows - 1];
			int imax = 0;
			for (int i = 0; i < rows; i++) {
				if (abs(array[i][rows-1]) > max) {
					max = abs(array[i][rows-1]);
					imax = i;
				}
			}*/
			//swap(array[rows-1], array[imax]);	
			for (int k = _array.get_row() - 1; k > 0; k--) {
				for (int i = k - 1; i > -1; i--) {
					T m = -_array(i, k) / _array(k, k);
					for (int j = 0; j < _array.get_row(); j++)
						_array(i, j) += _array(k, j) * m;
				}
			}
		}
	}

	template<typename T>
	ostream& operator<<(ostream& os, Matrix<T>& a) {
		cout << endl;
		for (int i = 0; i < a.get_row(); ++i){
			for (int j = 0; j < a.get_col(); ++j) {
				os << setw(10) << a(i, j);
			}
			os << endl;
		}
		return os;
	}

	template<typename T>
	bool operator==(Matrix<complex<T>>& array1, Matrix<complex<T>>& array2) {
		if (array1.get_row() != array2.get_row() || array1.get_col() != array2.get_col())
			return false;
		else {
			for (int i = 0; i < array1.get_row(); i++) 
				for (int j = 0; j < array1.get_col(); j++) 
					if (array1(i, j).real() != array2(i, j).real() || array1(i, j).imag() != array2(i, j).imag())
						return false;
			return true;
		}
	}

	template<typename T>
	bool operator!=(Matrix<complex<T>>& array1, Matrix<complex<T>>& array2) {
		return !(array1 == array2);
	}
}