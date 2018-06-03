//
// Created by Javier Peralta on 5/30/18.
//

#ifndef SVM_MATRIX_HPP
#define SVM_MATRIX_HPP

#include <vector>

typedef std::vector<std::vector<double> > matrix;
typedef std::vector<double> vect;

class Vector {
public:

  static void scale(vect &v, double s);

  static vect substract(vect &v1, vect &v2);
  static vect add(vect &v1, vect &v2);

  static double norm1(vect &v);
  static double norm2(vect &v);
  static double dotProduct(vect &v1, vect &v2);

  static void printVector(vect &v);
};

class Matrix {
public:

  static matrix addMatrix(matrix &m1, matrix &m2);

  static matrix multiply(matrix &m1, matrix &m2);
  static matrix multiplyTransposed(matrix &m1, matrix &m2);
  static matrix transposedMultiply(matrix &m1, matrix &m2);

  static vect multiply_vector(matrix &m1, vect &v);
  static vect multiplyTransposed_vector(matrix &m1, vect &v);

  static matrix getIdentity(unsigned n);
  static matrix transposeMatrix(matrix &m1);
};


#endif //SVM_MATRIX_HPP
