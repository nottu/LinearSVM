//
// Created by Javier Peralta on 5/30/18.
//

#include <iostream>
#include <cmath>
#include "Matrix.hpp"

using namespace std;

void Vector::scale(vect &v, double s){
  for(auto &vl : v) vl *= s;
}
vect Vector::add(vect &v1, vect &v2){
  vect out(v1);
  for (int i = 0; i < v1.size(); ++i) {
    out[i] += v2[i];
  }
  return out;
}
vect Vector::substract(vect &v1, vect &v2){
  vect out(v1);
  for (int i = 0; i < v1.size(); ++i) {
    out[i] -= v2[i];
  }
  return out;
}
double Vector::norm1(vect &v){
  double val = 0;
  for (auto &d : v){
    if(isnan(d))
      continue;
    val += abs(d);
  }
  return val;
}

double Vector::norm2(vect &v){
  double val = 0;
  for (auto &d : v){
    if(isnan(d))
      continue;
    val += d * d;
  }
  return (val);
}

double Vector::dotProduct(vect &v1, vect &v2){
  double val = 0;
  for (int i = 0; i < v1.size(); i++)
    val += v1[i] * v2[i];
  if (abs(val) < 1E-8 && abs(val) > 1E-20){
    val = 0;
  }
  return val;
}
void Vector::printVector(vect &v){
  for (auto &val : v) cout << val << "\t";
}
// MATRIX FUNCTIONS

matrix Matrix::addMatrix(matrix &m1, matrix &m2){
  matrix out(m1);
  for (int i = 0; i < out.size(); ++i) {
    for (int j = 0; j < out[i].size(); ++j) {
      out[i][j] += m2[i][j];
    }
  }
  return out;
}
matrix Matrix::transposedMultiply(matrix &m1, matrix &m2){
  auto mt = transposeMatrix(m1);
  auto m2t = transposeMatrix(m2);
  return multiplyTransposed(mt, m2t);
}
matrix Matrix::multiplyTransposed(matrix &m1, matrix &m2){
  matrix out;
  for (auto &v1 : m1) {
    vect tmp; tmp.reserve(v1.size());
    for (auto &v2 : m2) {
      double dp = Vector::dotProduct(v1, v2);
      tmp.emplace_back(dp);
    }
    out.emplace_back(tmp);
  }
  return out;
}
vect Matrix::multiply_vector(matrix &m1, vect &v){
  vect out; out.reserve(m1.size());
  for (auto &mv : m1) out.emplace_back( Vector::dotProduct(mv, v) );
  return out;
}
vect Matrix::multiplyTransposed_vector(matrix &m1, vect &v){
  auto mt = transposeMatrix(m1);
  return multiply_vector(mt, v);
}

matrix Matrix::getIdentity(unsigned n){
  matrix identity; identity.reserve(n);
  for (int i = 0; i < n; ++i) {
    vect cannon; cannon.reserve(n);
    for (int j = 0; j < n; ++j) {
      cannon.emplace_back(i == j);
    }
    identity.emplace_back(cannon);
  }
  return identity;
}

matrix Matrix::transposeMatrix(matrix &m1){
  matrix trans; trans.reserve(m1[0].size());
  for (int i = 0; i < m1[0].size(); ++i) {
    vect v; v.reserve(m1.size());
    for (auto &mv : m1) {
      v.emplace_back(mv[i]);
    }
    trans.emplace_back(v);
  }
  return trans;
}