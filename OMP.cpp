//
// Created by Javier Peralta on 5/30/18.
//
#include "OMP.hpp"
#include "Optimization/LevenbergMarquardt.hpp"

#include <cmath>

using namespace std;

void OMP::updateResidual(){
  for (unsigned i = 0; i < r.size(); ++i) {
    double aiu = 0;
    auto sz = dat.x[i].size();
    auto xi = dat.x[i];
    auto yi = dat.y[i];
    for (unsigned j = 0; j < sz; ++j) {
      aiu += yi * xi[j] * u[j];
      aiu += yi * xi[j] * u[sz + j];
    }
    aiu += yi * u[2*sz];
    aiu -= yi * u[2*sz];
    r[i] = 1 - aiu;
  }
}
//void OMP::getLambda(){
//  double l = 0;
//  unsigned idx = 0;
//  auto sz = dat.x[0].size();
//
//}
void OMP::getLambda(){
  double l = 0;
  unsigned idx = 0;
  auto sz = dat.x[0].size();
  for (unsigned ii = 0; ii < I.size(); ++ii) {
    unsigned i = I[ii];
    vect ai; ai.reserve(dat.y.size());
    if(i < 2*sz) {
      int mult = 1;
      if( i >= sz){
        mult = -1; i -= sz;
      }
      for (unsigned j = 0; j < dat.y.size(); j++) {
        auto xj = dat.x[j];
        auto xij = xj[i];
        ai.emplace_back( mult * dat.y[j] * xij);
      }
    } else {
      int mult = i == 2*sz ? 1 : -1;
      for (auto &val : dat.y) {
        ai.emplace_back( mult * val);
      }
    }
    double ar = Vector::dotProduct(ai, r);
    if(abs(ar) >= l) {
      l = abs(ar);
      idx = ii;
    }
  }
  L.emplace_back(I[idx]);
  I.erase(I.begin() + idx);
}
void OMP::updateU(){
  OMP_LS ls(this);
  vect n_u;
  for (auto &i : L) n_u.emplace_back(u[i]);
  n_u = levenbergMarquardt(n_u, ls, 500, 1E-6, 1.25);
  for (int ij = 0; ij < L.size(); ++ij) {
    u[L[ij]] = n_u[ij];
  }
}
OMP::OMP(Data &dat, unsigned s): dat(dat), t(s){
  u.reserve(dat.y.size() * 2 + 2);
  for (int i = 0; i < dat.x[0].size() * 2 + 2; ++i) {
    u.emplace_back(0);
    I.emplace_back(i);
  }
  r.reserve(dat.x[0].size());
  for (int i = 0; i < dat.y.size(); ++i){
    r.emplace_back(1);
  }
}
bool OMP::iterate(double threshold){
  getLambda();
  updateU();
  t -= 1;
  updateResidual();
  return t > 0 && Vector::norm2(r) > threshold;
}
void OMP::printHyper(){
  auto sz = u.size() / 2 - 1;
  vect betas(u.begin(), u.begin() + sz);
  for (int i = 0; i < betas.size(); ++i) {
    betas[i] -= u[i + sz];
  }
  betas.emplace_back(u[2 * sz] - u[2 * sz + 1]);
  Vector::printVector(betas);
}
int OMP::predict(vect& x){
  auto sz = x.size();
  vect betas(u.begin(), u.begin() + sz);
  for (int i = 0; i < betas.size(); ++i) {
    betas[i] -= u[i + sz];
  }
  double cl = Vector::dotProduct(betas, x) + u[2 * sz] - u[2 * sz + 1];
  return cl > 0 ? 1 : -1;
}
OMP::OMP_LS::OMP_LS(OMP *parent) : parent(parent) {}
vect OMP::OMP_LS::evaluateFunction (vect& vals){
  auto n  = parent->dat.y.size();
  auto sz = parent->dat.x[0].size();
  vect f; f.reserve(n);
  for (unsigned i = 0; i < n; i++) {
    double res = 1;
//    for (auto j : parent->L) {
    for (int ij = 0; ij < parent->L.size(); ++ij){
      auto j = parent->L[ij];
      double aj = 0;
      if(j < 2*sz) {
        int mult = 1;
        int ji = j;
        if (j > sz) {
          mult = -1;
          ji -= sz;
        }
        auto xij = parent->dat.x[i][ji];
        aj = mult * parent->dat.y[i] * xij;
      } else {
        int mult = j == 2*sz ? 1 : -1;
        aj = mult * parent->dat.y[i];
      }
      double valsj = vals[ij];
      res -= aj * valsj;
    }
    f.emplace_back(res);
  }
  return f;
}
matrix OMP::OMP_LS::evaluateJacobian(vect& vals){
// only use variables in L, makes Joaco smaller....
  matrix joaco;
  vect v_t(vals);
  matrix j1;
  vect r;
  auto n = v_t.size();
  auto m = parent->dat.y.size();
  for (int i = 0; i < n; ++i){
    v_t[i] +=  h;
    r = evaluateFunction(v_t);
    j1.emplace_back(r);
    v_t[i] -= h;
  }
  r = evaluateFunction(vals);
  for (int i = 0; i < m; ++i){
    vect joacov;
    for (int j = 0; j < n; ++j){
      joacov.emplace_back( (j1[j][i] - r[i]) / h);
    }
    joaco.emplace_back(joacov);
  }
  return joaco;
}