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
  @brief calculate the eigenvalues and eigenvectors of the matrix using the jacobi method
  @returns returns Matrix E (M by M) containing all the eigenvectors and Matrix e (M by 1) with all the eigenvalues
  */
  tuple<Matrix<float>, Matrix<float>> eigen(){

    //convert actual matrix to one of float to be able to work with calculations
    auto temp = Matrix<float>(this->M, this->M);

    for(int i = 0; i < this->M; i++){
      for(int j = 0; j < this->M; j++){
        temp(i,j) = float(this->operator()(i,j));
      }
    }


    //---------- FUNCTIONS ----------

    //index of the largest off-diagonal element in row k
    auto maxind = [](int k, int n, const Matrix<float> temp){
      int m = k + 1;
      for(int i=(k+2); i<n; i++){
        if(abs(temp(k-1,i-1)) > abs(temp(k-1,m-1))){
          m = i;
        }
      }
      return m;
    };

    //update e_k and its status
    auto update = [](int k, float t, const Matrix<float>* e, const Matrix<bool>* changed, int* state){
      float y = e->operator()(k-1,0);
      e->operator()(k-1,0) = y + t;
      //if changed and y = e_k
      if(changed->operator()(k-1,0) && (abs(y - e->operator()(k-1,0)) < epsilon)){
        changed->operator()(k-1,0) = false;
        state--;
      }
      //if not changed and y != e_k
      else if(!(changed->operator()(k-1,0)) && (abs(y - e->operator()(k-1,0)) > epsilon)){
        changed->operator()(k-1,0) = true;
        state++;
      }
    };

    //perform rotation on S_ij & S_kl
    auto rotate = [](int k, int l, int i, int j, float c, float s, const Matrix<float>* temp){
      float rotationData[4] = {c, -s, s, c};
      auto rotationMatrix = Matrix<float>(2,2, rotationData);
      float sValues[2] = {temp->operator()(k-1, l-1), temp->operator()(i-1,j-1)};
      auto sValuesMatrix = Matrix<float>(2,1, sValues);
      auto newValues = rotationMatrix*sValuesMatrix;
      temp->operator()(k-1,l-1) = newValues[0];
      temp->operator()(i-1,j-1) = newValues[1];
    };

    // ---------- INIT ----------

    //output matrix E with eigenvectors (E=I)
    auto E = Matrix<float>(this->M, this->M);
    for(int i = 0; i<this->M; i++){
      for(int j= 0; j<this->M; j++){
        if(i == j){
          E(i,j) = 1;
        }
        else{
          E(i,j) = 0;
        }
      }
    }

    //output matrix e (a vector) with all the eigenvalues
    auto e = Matrix<float>(this->M, 1);

    //logical array changed holds the status of each eigenvalue
    //if the numerical value of e_k or e_l changes during iteration the corresponding component of changed is set to true
    bool changedData[this->M];
    for(int i = 0; i<this->M; i++){
      changedData[i] = true;
    }
    auto changed = Matrix<bool>(this->M, 1, changedData);

    //the integer state counts the number of components of changed which have the value true
    //iteration stops as soon as state = 0
    int state = this->M;

    //array ind
    auto indArray = Matrix<int>(this->M, 1);

    //define n
    int n = this->M + 1;

    //initialize indArray and e
    for(int k = 1; k<n; k++){
      indArray(k-1,0) = maxind(k, n, temp);
      e(k-1,0) = temp(k-1,k-1);
    }

    int iteration = 0;

    // ---------- MAIN ----------
    while(state != 0 && iteration < 20){
      cout << "iteration: " << iteration << endl;
      cout << "state: " << state << endl;
      indArray.print();

      int m = 1;
      //find index (k,l) to pivot p
      for(int k = 2; k<(n - 1); k++){
        if(abs(temp(k-1, indArray(k-1,0))) > abs(temp(m-1, indArray(m-1,0)))){
          m = k;
        }
      }

      int k = m;
      int l = indArray(m-1, 0);
      float p = temp(k-1, l-1);

      //calculate c and s
      float y = (e(l-1,0) - e(k-1,0))/2;
      float d = abs(y) + sqrt(pow(p,2) + pow(y,2));
      float r = sqrt(pow(p,2) + pow(d,2));
      float c = d/r;
      float s = p/r;
      float t = pow(p,2)/d;
      if(y < 0){
        s = -s;
        t = -t;
      }

      temp(k-1,l-1) = 0.0;
      update(k, -t, &e, &changed, &state);
      update(l,t, &e, &changed, &state);

      //rotate rows and columns k and l
      for(int i = 1; i<k; i++){
        rotate(i, k, i, l, c, s, &temp);
      }
      for(int i = (k+1); i<l; i++){
        rotate(k, i, i, l, c, s, &temp);
      }
      for(int i = (l+1); i<n; i++){
        rotate(k, i, l, i, c, s, &temp);
      }

      //rotate eigenvectors
      for(int i = 1; i<n; i++){
        float rotationData[4] = {c, -s, s, c};
        auto rotationMatrix = Matrix<float>(2,2, rotationData);
        float EValues[2] = {temp(k-1, l-1), temp(i-1,l-1)};
        auto EValuesMatrix = Matrix<float>(2,1, EValues);
        auto EValuesResult = rotationMatrix*EValuesMatrix;
        E(i-1,k-1) = EValuesResult[0];
        E(i-1,l-1) = EValuesResult[1];
      }

      //update all all potential changed ind_i
      for(int i = 1; i<n; i++){
        indArray(i-1,0) = maxind(i, n, temp);
      }

      iteration++;
    }

    return make_tuple(E, e);

  }

};

template<typename T>
float det(const Matrix<T> &mat){
	if(mat.M != mat.N){
		throw domain_error("Not a square matrix");
	}
	return mat.determinant();

}