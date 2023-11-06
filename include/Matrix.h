#pragma once
#include <iostream>
#include <random>
#include <complex>
#include <exception>
#include <math.h>
#include <iomanip>
#include <cstdlib>

using namespace std;

namespace matrix {

	template <typename T>
	class Matrix {
	private:
		T** array;
		int rows;
		int cols;

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
			for (int i = 0; i < rows; i++) {
				array[i] = (T*) new T[cols];
			}
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					array[i][j] = 0;
				}
			}
		}

		Matrix(const Matrix& _array) {
			rows = _array.rows;
			cols = _array.cols;
			array = (T**) new T * [rows];
			for (int i = 0; i < rows; i++) {
				array[i] = (T*) new T[cols];
			}
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					array[i][j] = _array.array[i][j]; ;
				}
			}
		}

		Matrix& operator=(const Matrix& _array) {
			for (int i = 0; i < rows; i++)
				delete[] array[i];
			delete[] array;
			rows = _array.rows;
			cols = _array.cols;
			array = (T**) new T * [rows];
			for (int i = 0; i < rows; i++) {
				array[i] = (T*) new T[cols];
			}
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					array[i][j] = _array.array[i][j]; ;
				}
			}
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
			for (int i = 0; i < rows; i++) {
				array[i] = (T*)new T[cols];
			}
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					random_device rd;
					mt19937 gen(rd());
					uniform_real_distribution<> segment(bottom_limit, upper_limit);
					array[i][j] = segment(gen);
				}
			}
		}

		void init() {
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					cout << "[" << i << "][" << j << "]";
					cin >> array[i][j] << endl;
				}
			}
		}

		Matrix(int _rows, int _cols, T _array[], int size) {
			rows = _rows;
			cols = _cols;
			array = (T**) new T * [rows];
			for (int i = 0; i < rows; i++) {
				array[i] = (T*)new T[cols];
			}
			int _size = 0;
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++)
					if (_size < size) {
						array[i][j] = _array[_size];
						_size++;
					}
					else {
						array[i][j] = 0;
					}
			}
		}

		T& operator()(const int _index_row, const int _index_col) const {
			return array[_index_row][_index_col];
		}

		Matrix& operator+=(const Matrix& _array) {
			if (rows != _array.rows || cols != _array.cols)
				throw "The sizes of the matrices do not match";
			else {
				for (int i = 0; i < rows; i++)
					for (int j = 0; j < cols; j++)
						array[i][j] += _array.array[i][j];
			}
			return *this;
		}

		Matrix& operator-=(const Matrix& _array) {
			if (rows != _array.rows || cols != _array.cols)
				throw "The sizes of the matrices do not match";
			else {
				for (int i = 0; i < rows; i++)
					for (int j = 0; j < cols; j++)
						array[i][j] -= _array.array[i][j];
			}
			return *this;
		}

		friend Matrix operator+(Matrix& array, const Matrix& _array) {
			if (array.rows != _array.rows || array.cols != _array.cols)
				throw "The sizes of the matrices do not match";
			else {
				Matrix c(array);
				c += _array;
				return c;
			}
		}

		friend Matrix operator-(Matrix& array, const Matrix& _array) {
			if (array.rows != _array.rows || array.cols != _array.cols)
				throw "The sizes of the matrices do not match";
			else {
				Matrix c(array);
				c -= _array;
				return c;
			}
		}

		friend Matrix operator*(Matrix& _array, const Matrix& array) {
			if (array.rows != _array.cols || array.cols != _array.rows)
				throw "The size of the matrices does not satisfy the multiplication condition";
			else {
				Matrix a(array.rows, _array.cols);
				for (int i = 0; i < array.rows; ++i)
				{
					for (int j = 0; j < _array.cols; ++j)
					{
						a(i, j) = 0;
						for (int k = 0; k < array.cols; ++k) {
							a(i, j) += array(i, k) * _array(k, j);
						}
					}
				}
				return a;
			}
		}

		friend Matrix operator*(Matrix& array, T scalar) {
			Matrix _array(array);
			for (int i = 0; i < _array.rows; i++) {
				for (int j = 0; j < _array.cols; j++) {
					_array.array[i][j] = _array.array[i][j] * scalar;
				}
			}
			return _array;
		}

		friend Matrix operator*(T scalar, Matrix& array) {
			Matrix _array(array);
			for (int i = 0; i < _array.rows; i++) {
				for (int j = 0; j < _array.cols; j++) {
					_array.array[i][j] = _array.array[i][j] * scalar;
				}
			}
			return _array;
		}

		friend Matrix operator/(Matrix& array, T scalar) {
			if (scalar == T(0))
				throw "You can't divide by zero!";
			else {
				Matrix _array(array);
				for (int i = 0; i < _array.rows; i++)
					for (int j = 0; j < _array.cols; j++)
						_array.array[i][j] = _array.array[i][j] / scalar;
				return _array;
			}
		}

		T trace_matrix() {
			if (rows != cols)
				throw "The matrix must be square";
			else {
				T trace = 0;
				for (int i = 0; i < rows; i++)
					for (int j = 0; j < cols; j++)
						trace += array[i][j];
				return trace;
			}
		}

		T determinate_matrix() {
			if (rows != cols)
				throw "The matrix must be square.";
			else if (rows == 1)
				return array[0][0];
			else if (rows == 2)
				return array[0][0] * array[1][1] - array[0][1] * array[1][0];
			else if (rows == 3)
				return array[0][0] * array[1][1] * array[2][2] + array[0][1] * array[1][2] * array[2][0] + array[0][2] * array[1][0] * array[2][1] -
				(array[2][0] * array[1][1] * array[0][2] + array[1][2] * array[2][1] * array[0][0] + array[2][2] * array[0][1] * array[1][0]);
			else
				throw "The size of the matrix should not exceed 3.";
		}

		void triangular_matrix() {
			if (rows != cols)
				throw "The matrix must be square.";
			else if (determinate_matrix() == T(0))
				throw "The matrix cannot be reduced to a triangular form, because it is degenerate.";
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
				for (int k = rows - 1; k > 0; k--) {
					for (int i = k - 1; i > -1; i--) {
						T m = -array[i][k] / array[k][k];
						for (int j = 0; j < rows; j++) {
							array[i][j] += array[k][j] * m;
						}
					}
				}
			}
		}

		bool operator ==(Matrix& _array) const {
			if (cols != _array.cols || rows != _array.rows)
				return false;
			else {
				for (int i = 0; i < rows; i++) {
					for (int j = 0; j < rows; j++) {
						if (array[i][j] == _array[i][j])
							return true;
					}
				}
				return false;
			}
		}

		bool operator!=(Matrix& _array) const {
			return !(array == _array);
		}
	};


	template<typename T>
	ostream& operator<<(ostream& os, Matrix<T>& a) {
		for (int i = 0; i < a.get_row(); ++i)
		{
			cout << endl;
			for (int j = 0; j < a.get_col(); ++j)
			{
				std::cout << setw(10) << a(i, j);
			}
			cout << endl;
		}
		return os;
	}

}