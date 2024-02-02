#pragma once

#include <memory>
#include <iostream>

template<typename T>
struct Matrix {
  int M = 0; //rows
  int N = 0; //columns
  std::shared_ptr<T> data = nullptr;

  //constructor method to empty initialize
  Matrix<T>(int M, int N, const T* values = nullptr) : M(M), N(N){
	if ((M <= 0) && (N<=0)){
		std::domain_error("Dimensions of Matrix have to be positive integers");
	}

	data = std::shared_ptr<T>(new T[M*N](), std::default_delete<T[]>());

	if (values){
		for(int i=0; i<M*N; i++){
			data.get()[i] = values[i];
				
		}
	}    
  }

  //return element at a given position
  inline T &operator[](int position){
        return data.get()[position];
  }

  //return element of matrix at point (x,y)
  inline T &operator()(int row, int col) const {
        return data.get()[row * N + col];
  }

  void print() {
        for(int row=0; row<M; row++){
			for(int col=0; col<N; col++){
				std::cout << this->operator()(row, col) << " ";
			}
			std::cout << "\n";
        }  
  }

  static Matrix<T> mult(const Matrix<T> &a, const Matrix<T> &b){
	if(a.N != b.M){
		std::domain_error("Matrix Dimensions do not match");
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

  Matrix<T> operator*(const Matrix<T> &other){
	return mult(*this, other);
  }

  Matrix<T> transpose() const {
	Matrix<T> result(N, M);

	for(int i=0; i<M; i++){
		for(int j=0; j<N; j++){
			result(j,i) = this->operator()(i,j);
		}
	}
	return result;
  }

};

template<typename T>
T det(const Matrix<T> &mat){
	if(mat.M != mat.N){
		std::domain_error("Not a square matrix");
	}
	mat.determinant;
}