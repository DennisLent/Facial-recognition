#pragma once

#include <memory>
#include <iostream>
#include <cmath>
#include <tuple>
#include <omp.h>

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
  @brief return the element at the specified position (starting from 0,0 to M-1,N-1)
  @param row row number
  @param col column number
  @returns element at position of type T
  */
  inline T &operator()(int row, int col) const {
    if(((row > M-1) || (row < 0)) || ((col > N-1) || (col < 0))){
      throw domain_error("invalid row or col index");
    }
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
  static Matrix<T> multMat(const Matrix<T> &a, const Matrix<T> &b){
	if(a.N != b.M){
		throw domain_error("Matrix dimensions do not match");
	}
	
	int result_rows = a.M;
	int result_cols = b.N;

	auto result = Matrix<T>(result_rows, result_cols);

  #pragma omp parallel for
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
  @brief multiply matrix with a scalar
  @param A: Matrix<T> a matrix of type T
  @param scalar: Scalar of type T
  @returns Matrix of type T multiplied with the scalar
  */
  static Matrix<T> multScalar(const Matrix<T> &a, const T &scalar){
    auto result = Matrix<T>(a.M, a.N);
  
    #pragma omp parallel for
    for(int i = 0; i<a.M; i++){
      for(int j = 0; j<a.N; j++){
        result(i,j) = a(i,j) * scalar;
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
	  return multMat(*this, other);
  }

  /*
  @brief multiply one matrix of type T with a scalar
  @param scalar scalar of type T
  @returns multiplied matrix of type T
  */
  Matrix<T> operator*(const T &scalar){
    return multScalar(*this, scalar);
  }

  /*
  @brief transpose the matrix of type T from M by N to N by M
  @returns transposed matrix of type T 
  */
  Matrix<T> transpose() const {
    Matrix<T> result(N, M);
  
    #pragma omp parallel for
    for(int i=0; i<M; i++){
      for(int j=0; j<N; j++){
        result(j,i) = this->operator()(i,j);
      }
    }
    return result;
  }

  /*
  @brief method to change matrix of any type to a matrix of float
  @return Matrix as type float
  */
  Matrix<float> toFloat() {
    Matrix<float> result(N,M);

    #pragma omp parallel for
    for(int i=0; i<M; i++){
      for(int j=0; j<N; j++){
        result(i,j) = float(this->operator()(i,j));
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

  #pragma omp parallel for
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

  #pragma omp parallel for
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
  @brief return the selected column of a matrix of type T (starting at index 0 to M-1)
  @returns a Matrix (N, 1) with the values of the column vector
  */
  Matrix<T> getColumn(int col) {
    if (col > this->M){
      throw domain_error("column index out of range");
    }

    auto result = Matrix<T>(this->N, 1);
    for(int i = 0; i<this->N; i++){
      result(i,0) = this->operator()(i, col);
    }

    return result;
  }

  /*
  @brief set the selected column of the matrix with a 1D Matrix (starting at index 0 to M-1)
  */
  void setColumn(int col, const Matrix<T> &a) {
    if (col > this->M){
      throw domain_error("column index out of range");
    }
    if(a.N > this->N){
      throw domain_error("length of vector a does not fit the matrix");
    }

    for(int i = 0; i<this->N; i++){
      this->operator()(i, col) = a(i,0);
    }

  }

  /*
  @brief calcualtes the norm of the matrix (measure of size or magnitude)
  @returns float norm value
  */
  float norm(){
    float sum = 0.0;

    for(int i = 0; i < this->M; i++){
      for(int j = 0; j<this->N; j++){
        sum += float(this->operator()(i,j)*this->operator()(i,j));
      }
    }
    return sqrt(sum);
  }

  /*
  @brief L2 comparison of the matrices (|A-B|^2)
  @returns float of the L2 norm
  */
  static float L2(const Matrix<T> &a, const Matrix<T> &b){
    if((a.M != b.M) || (a.N != b.N)){
      throw domain_error("Matrix dimensions do not match");
    }

    float result = 0;

    for(int i=0; i<a.M; i++){
      for(int j=0; j<a.N; j++){
        result += ((a(i,j)-b(i,j))*(a(i,j)-b(i,j)));
      }
    }

    result /= (a.M*a.N);
    return result;
  }

  /*
  @brief extract the diagonal elements of the Matrix into a new 1D Matrix
  @returns 1D Matrix of type T with only the diagonal elements
  */
  Matrix<T> diagonal(){
    int smallestSide = (this->M >= this->N) ? this->N : this->M;
    auto result = Matrix<T>(smallestSide, 1);

    for(int i=0; i<smallestSide; i++){
      result(i,0) = this->operator()(i,i);
    }

    return result;
  }

  /*
  @brief create an identity matrix in form of the the reference matrix (has to be square)
  @returns indentity matrix
  */
  Matrix<T> identity(){
    if(this->M != this->N){
      throw domain_error("not a square matrix");
    }

    auto result = Matrix<T>(this->M, this->M);

    #pragma omp parallel for
    for(int i = 0; i<this->M; i++){
      for(int j = 0; j<this->M; j++){
        if(i == j){
          result(i,j) = static_cast<T>(1);
        }
        else{
          result(i,j) = static_cast<T>(0);
        }
      }
    }

    return result;
  }

  /*
  @brief method to divide matrix by a given scalar a/s
  @returns matrix of type T divided by a scalar
  */
  static Matrix<T> div(const Matrix<T> &a, const T &scalar){
    
    auto result = Matrix<T>(a.M, a.N);

    #pragma omp parallel for
    for(int i=0; i<a.M; i++){
      for(int j=0; j<a.N; j++){
        result(i,j) = a(i,j) / scalar;
      }
    }

	  return result;
  }

  /*
  @brief operator for dividing matrix by a scalar
  @returns matrix divided by a scalar
  */
  Matrix<T> operator/(const T &scalar){
	  return div(*this, scalar);
  }

  /*
  @brief divide and assign method for matrices
  */
  void operator/=(const T &scalar){

    #pragma omp parallel for
    for(int i=0; i<this->M; i++){
      for(int j=0; j<this->N; j++){
        this->operator()(i,j) = this->operator()(i,j) / scalar;
      }
    }
  }

  /*
  @brief subtract and assign method for matrices
  */
  void operator-=(const Matrix<T> &other){
    if(this->N != other.N || this->M != other.M){
      throw domain_error("Matrix dimensions do not match");
    }

    #pragma omp parallel for
    for(int i = 0; i<this->M; i++){
      for(int j =0; j<this->N; j++){
        this->operator()(i,j) = this->operator()(i,j) - other(i,j);
      }
    }
  }

  /*
  @brief add and assign method for matrices
  */
  void operator+=(const Matrix<T> &other){
    if(this->N != other.N || this->M != other.M){
      throw domain_error("Matrix dimensions do not match");
    }

    #pragma omp parallel for
    for(int i = 0; i<this->M; i++){
      for(int j =0; j<this->N; j++){
        this->operator()(i,j) = this->operator()(i,j) + other(i,j);
      }
    }
  }

  /*
  @brief Gram-Schmidt process to form an orthonormal basis for matrix. link: https://en.wikipedia.org/wiki/Gram%E2%80%93Schmidt_process
  @returns Matrix of floats that contain the orthonormal basis
  */
  Matrix<float> GramSchmidt(){

    //copy matrix to be of type float
    auto temp = this->toFloat();

    //calculate the projection of v on u
    auto proj = [](Matrix<float> u, Matrix<float> v){

      //dot product for projections
      auto dotProduct = [](Matrix<float> a, Matrix<float> b){

        float result = 0.0;

        for(int i = 0; i<a.M; i++){
          result += a(i,0) * b(i,0);
        }

        return result;
      };

      float vu = dotProduct(u,v);
      float uu = dotProduct(u,u);

      float scalar = vu/uu;

      Matrix<float> result = u*scalar;

      return result;
    };

    //Gram Schmidt process
    auto result = Matrix<float>(this->M, this->N);

    //first column vector is u1
    Matrix<float> u1 = temp.getColumn(0);
    u1 /= u1.norm();
    result.setColumn(0, u1);

    //iterate over every column
    for(int i = 1; i<this->N; i++){

      Matrix<float> v2 = temp.getColumn(i);

      //subtract projection of colum on each previous column
      for(int j = 0; j<i; j++){
        auto projection = proj(result.getColumn(j), v2);
        v2 -= projection;
      }

      //normalize the vector
      v2 /= v2.norm();

      //add vector to result
      result.setColumn(i, v2);

    }

    return result;
  }

  /*
  @brief Do QR decomposition using Gram-Schmidt process. link: https://en.wikipedia.org/wiki/QR_decomposition
  @returns tuple of Matrix Q and Matrix R
  */
  tuple<Matrix<float>, Matrix<float>> QRDecomposition(){

    auto temp = this->toFloat();

    Matrix<float> Q = this->GramSchmidt();
    Matrix<float> QTranspose = Q.transpose();

    // R = Q^T * A
    Matrix<float> R = QTranspose*temp;

    //make R upper triangle
    #pragma omp parallel for
    for(int i = 0; i<this->M; i++){
      for(int j = 0; j<this->N; j++){
        if(i > j){
          R(i,j) = 0.0;
        }
      }
    }

    return make_tuple(Q, R);
  }

  /*
  @brief calculate approximations the eigenvalues and eigenvectors using QR decomposition and the Gram-Schmidt process. link: https://people.inf.ethz.ch/arbenz/ewp/Lnotes/chapter4.pdf
  @param iterations amount of iterations to be done (50000 by default)
  @param progress prints more information about the process for the main loop (false by default)
  @returns returns Matrix E (M by M) containing all the eigenvectors and Matrix e (M by 1) with all the eigenvalues
  */
  tuple<Matrix<float>, Matrix<float>> eigen(int iterations = 50000, bool progress=false){
    int width = 50;

    //make copy for float
    auto temp = this->toFloat();

    auto E = temp.identity();

    if(progress){
      cout << "Progress: [";
    }

    for(int i = 0; i<iterations; i++){
      auto decomp = temp.QRDecomposition();
      auto Q = get<0>(decomp);
      auto R = get<1>(decomp);
      temp = R*Q;
      E = E*Q;

      if(progress){
        int pos = width * int(i/iterations);
        for(int j = 0; j<width; j++){
          if(j< pos){
            cout << "=";
          }
          else if(j == pos){
            cout << ">";
          }
          else{
            cout << " ";
          }
        }
        

        cout << "] " << int(i/iterations * 100.0) << "%\r";
        cout.flush();
      }
    }

    if(progress){
      cout << endl;
    }

    auto e = temp.diagonal();

    return make_tuple(E, e);   

  }

  /*
  @brief method to change the shape of the matrix from M by N to M*N by 1
  @returns flattened matrix
  */
  Matrix<T> flatten(){
    auto result = Matrix<T>(this->M*this->N, 1);

    for(int i=0; i<this->M*this->N; i++){
      result[i] = this->operator[](i);
    }

    return result;
  }

  /*
  @brief method to return slices of the matrix 
  @param start starting index of the column to extract
  @param end ending index of the columns to extract (not included)
  @returns matrix with selected columns
  */
  Matrix<T> slice(int start, int end){
    if((start < 0) || (end >= this->N) || (start > end)){
      throw domain_error("invalid columns");
    }

    int newCols = end - start;
    Matrix<T> result(this->M, newCols);

    #pragma omp parallel for
    for(int i = 0; i<this->M; i++){
      for(int j = start; j < end; j++){
        result(i, j - start) = this->operator()(i,j);
      }
    }

    return result;

  }

};