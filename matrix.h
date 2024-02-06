#pragma once

#include <memory>
#include <iostream>
#include <cmath>

#define epsilon 1e-5

using namespace std;

/*
@brief Struct for a M by N matrix of type T
@tparam T type of values stored in the matrix can be int, float or double
@param M number of rows
@param N number of columns
@param values pointer to array of elements of type T to initialize matrix with values (optional)
*/
template<typename T>
struct Matrix {
  int M = 0; //rows
  int N = 0; //columns
  std::shared_ptr<T> data = nullptr;

  /*
  @brief constructor method for Matrix
  @param M number of rows
  @param N number of columns
  @param values pointer to array of elements of type T to initialize matrix with values (optional)
  */
  Matrix<T>(int M, int N, const T* values = nullptr) : M(M), N(N){
	if ((M <= 0) && (N<=0)){
		throw domain_error("Dimensions of matrix have to be positive integers");
	}

	data = shared_ptr<T>(new T[M*N](), std::default_delete<T[]>());

	if (values){

		for(int i=0; i<M*N; i++){
			data.get()[i] = values[i];
				
		}
	}    
  }

  /*
  @brief return the element at the specified position / index in the matrix
  @param position the index of the element
  @returns element at index of type T
  */
  inline T &operator[](int position){
        return data.get()[position];
  }

  /*
  @brief return the element at the specified position (starting from 1,1 to M,N)
  @param row row number
  @param col column number
  @returns element at position of type T
  */
  inline T &operator()(int row, int col) const {
        return data.get()[row * N + col];
  }

  /*
  @brief print the matrix in it's entirety (not advised for large matrices)
  */
  void print() {
        for(int row=0; row<M; row++){
			for(int col=0; col<N; col++){
				cout << this->operator()(row, col) << " ";
			}
			cout << "\n";
        }  
  }

  /*
  @brief multiply two matrices
  @param A: Matrix<T> a matrix of type T (A by B)
  @param B: Matrix<T> a matrix of type T (B by C)
  @returns result multiplied matrix of type T (A by C)
  */
  static Matrix<T> mult(const Matrix<T> &a, const Matrix<T> &b){
	if(a.N != b.M){
		throw domain_error("Matrix dimensions do not match");
	}
	
	int result_rows = a.M;
	int result_cols = b.N;

	auto result = Matrix<T>(result_rows, result_cols);

	for(int i=0; i<result_rows; i++){
		for(int j=0; j<result_cols; j++){
			
			T prod = T();

			for(int k=0; k<b.M; k++){
				prod += a(i, k) * b(k, j);
			}

			result(i, j) = prod;
		}
	}

	return result;

  }
  
  /*
  @brief multiply one matrix of type T with another matrix of type T 
  @param other other matrix of type T to multiply with
  @returns multiplied matrix of type T
  */
  Matrix<T> operator*(const Matrix<T> &other){
	return mult(*this, other);
  }

  /*
  @brief transpose the matrix of type T from M by N to N by M
  @returns transposed matrix of type T 
  */
  Matrix<T> transpose() const {
	Matrix<T> result(N, M);

	for(int i=0; i<M; i++){
		for(int j=0; j<N; j++){
			result(j,i) = this->operator()(i,j);
		}
	}
	return result;
  }

  /*
  @brief subract a matrix of type T from another matrix of the same type and dimension
  @param A: Matrix<T> a matrix of type T (A by B)
  @param B: Matrix<T> a matrix of type T (A by B)
  @returns C: Matrix<T> subtracted result of matrix A and B
  */
  static Matrix<T> sub(const Matrix<T> &a, const Matrix<T> &b){
	if((a.M != b.M) || (a.N != b.N)){
		throw domain_error("Matrix dimensions do not match");
	}

	auto result = Matrix<T>(a.M, a.N);

	for(int i=0; i<a.M; i++){
		for(int j=0; j<a.N; j++){
			result(i,j) = a(i,j) - b(i,j);
		}
	}

	return result;
  }

  /*
  @brief subract one matrix of type T from another matrix of type T 
  @returns subtracted matrix of type T
  */
  Matrix<T> operator-(const Matrix<T> &other){
	  return sub(*this, other);
  }

  /*
  @brief add a matrix of type T from another matrix of the same type and dimension. This function uses math based matrix indexing
  so it has to be adjusted for when using the matrix
  @param A: Matrix<T> a matrix of type T (A by B)
  @param B: Matrix<T> a matrix of type T (A by B)
  @returns C: Matrix<T> added result of matrix A and B
  */
  static Matrix<T> add(const Matrix<T> &a, const Matrix<T> &b){
	if((a.M != b.M) || (a.N != b.N)){
		throw domain_error("Matrix dimensions do not match");
	}

	auto result = Matrix<T>(a.M, a.N);

	for(int i=0; i<a.M; i++){
		for(int j=0; j<a.N; j++){
			result(i,j) = a(i,j) + b(i,j);
		}
	}

	return result;

  }

  /*
  @brief add one matrix of type T from another matrix of type T 
  @returns added matrix of type T
  */
  Matrix<T> operator+(const Matrix<T> &other){
	  return add(*this, other);
  }

  /*
  @brief calculate the eigenvalues and eigenvectors of the matrix using QR decomposition
  @returns returns Matrix E (M by M) containing all the eigenvectors and Matrix e (M by 1) with all the eigenvalues
  */
  tuple<Matrix<float>, Matrix<float>> eigen(){}

};

template<typename T>
float eig(const Matrix<T> &mat){
	if(mat.M != mat.N){
		throw domain_error("Not a square matrix");
	}
	return mat.eigen();

}