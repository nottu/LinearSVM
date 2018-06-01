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
  static void substract(vect &v1, vect &v2, vect &out);
  static void add(vect &v1, vect &v2, vect &out);

  static double norm1(vect &v);
  static double norm2(vect &v);
  static double dotProduct(vect &v1, vect &v2);
};

class Matrix {
public:
  static void multiply(matrix &m1, matrix &m2, matrix &out);
  static void multiply_vector(matrix &m1, vect &m2, vect &out);
};


#endif //SVM_MATRIX_HPP
