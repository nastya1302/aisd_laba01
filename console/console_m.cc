#include <iostream>
#include <Matrix.h>

using namespace std;
using namespace matrix;

int main() {
	//Matrix<complex<double>> array(2, 2, 0, 10, 0, 10);
	//cout << array;

	cout << "data type: INT" << endl;
	int array1[] = { 1,2,1,1,1,2,4,5,3 };
	Matrix<int> a(3, 3, array1, 9);
	int array2[] = { 1,2,1,3,1,2,3,4,1 };
	Matrix<int> b(3, 3, array2,9);
	cout << "First matrix a: " << a;
	cout << "Second matrix b: " << b;
	Matrix<int> c = a + b;
	a += b;
	cout << "a+b" << a;
	c = a - b;
	cout << "a-b" << c;
	c = a * b;
	cout << "a*b" << c;
	c = a * 2;
	cout << "a*2" << c;
	c = 2 * b;
	cout << "2*b" << c;
	c = a / 1;
	cout << "a / 1" << c;
	Matrix<int> d(3, 3, 1, 100);
	cout << "Random matrix 3x3: " << d;
	int trace = a.trace_matrix();
	cout << "Trace matrix 'a' is " << trace << endl;
	int array3[] = { 1,1,2,1 };
	Matrix<int> arr(2, 2, array3, 9);
	cout << "Third matrix 'arr': " << arr;
	triangular_matrix(arr);
	cout << "Triangular matrix arr is " << arr;

	/*cout << "data type: DOUBLE" << endl;
	double array1[] = { 1.5,2,1,1, 1, 2, 4, 5, 3 };
	Matrix<double> a(3, 3, array1, 9);
	double array2[] = { 1.5,2,1,3,1,4,2,1,3 };
	Matrix<double> b(3, 3, array2, 9);
	cout << "First matrix a: " << a;
	cout << "Second matrix b: " << b;
	Matrix<double> c = a + b;
	cout << "a+b" << c;
	c = a - b;
	cout << "a-b" << c;
	c = a * b;
	cout << "a*b" << c;
	c = a * 2;
	cout << "a*2" << c;
	c = 2 * b;
	cout << "2*b" << c;
	c = a / 1;
	cout << "a / 1" << c;
	Matrix<double> d(3, 3, 1, 100);
	cout << "Random matrix 3x3: " << d;
	double trace = a.trace_matrix();
	cout << "Trace matrix 'a' is " << trace << endl;
	triangular_matrix(a);
	cout << "Triangular matrix arr is " << a;*/

	/*cout << "data type: COMPLEX<FLOAT>" << endl;
	std::complex<float> a(1, 1), b(2,2), c(3,3), d(4,4);
	std::complex<float> mas1[] = { a,b,c,d };
	Matrix<std::complex<float>> array1(2, 2, mas1, 4);
	std::complex<float> mas2[] = { d, c, b, a };
	Matrix<std::complex<float>> array2(2, 2, mas2, 4);
	cout << "First matrix a: " << array1;
	cout << "Second matrix b: " << array2;
	Matrix<std::complex<float>> array3 = array1 + array2;
	cout << "a+b" << array3;
	array3 = array1 - array2;
	cout << "a-b" << array3;
	array3 = array1 * array2;
	cout << "a*b" << array3;
	array3 = array1 * 2;
	cout << "a*2" << array3;
	array3 = 2 * array2;
	cout << "2*b" << array3;
	array3 = array1 / 2;
	cout << "a / 2" << array3;
	Matrix<std::complex<float>> arr(3, 3, 1, 100, 1, 100);
	cout << "Random matrix 3x3: " << arr;
	complex<float> trace = array1.trace_matrix();
	cout << "Trace matrix 'a' is " << trace << endl;
	triangular_matrix(array1);
	cout << "Triangular matrix 'a' is " << array1;*/
	return 0;
}