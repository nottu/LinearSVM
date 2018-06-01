//
// Created by Javier Peralta on 5/30/18.
//

#include <iostream>
#include <cmath>
#include "Matrix.hpp"

using namespace std;

void Vector::substract(vect &v1, vect &v2, vect &out){
  if(v2.size() != v1.size()) {
    cout << "Error, vectors of different size";
    exit(1);
  }
  out.clear(); out.reserve(v1.size());
  for (int i = 0; i < v1.size(); i++){
    out.emplace_back(v1[i] - v2[i]);
  }
}
void Vector::add(vect &v1, vect &v2, vect &out){
  if(v2.size() != v1.size()) {
    cout << "Error, vectors of different size";
    exit(1);
  }
  out.clear(); out.reserve(v1.size());
  for (int i = 0; i < v1.size(); i++){
    out.emplace_back(v1[i] - v2[i]);
  }
}

double Vector::norm1(vect &v){
  double val = 0;
  for (auto &d : v)
    val += abs(d);
  return val;
}

double Vector::norm2(vect &v){
  double val = 0;
  for (auto &d : v)
    val += d * d;
  return sqrt(val);
}

double Vector::dotProduct(vect &v1, vect &v2){
  double val = 0;
  for (int i = 0; i < v1.size(); i++)
    val += v1[i] * v2[i];
  return val;
}
void Vector::printVector(vect &v){
  for (auto &val : v) cout << val << "\t";
}
// MATRIX FUNCTIONS

void Matrix::multiply(matrix &m1, matrix &m2, matrix &out){
  if (m1[0].size() != m2.size()) {
    cout << "Error, can't multiply matrices";
    exit(1);
  }
  out.clear(); out.reserve(m1.size());
  for (unsigned i = 0; i < m1.size(); ++i){
    vect tmp;
    for (unsigned j = 0; j < m1.at(i).size(); ++j){
      double c = 0;
      for (unsigned k = 0; k < m2.at(k).size(); ++k){
        c += m1[i][j] * m2[j][k];
      }
      tmp.emplace_back(c);
    }
    out.emplace_back(tmp);
  }
}
void Matrix::multiply_vector(matrix &mat, vect &v, vect &out){
  out.clear(); out.reserve(mat.size());
  for (auto &mv : mat) {
    double d = Vector::dotProduct(mv, v);
    out.emplace_back(d);
  }
}