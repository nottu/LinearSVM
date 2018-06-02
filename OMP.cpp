//
// Created by Javier Peralta on 5/30/18.
//
#include "OMP.hpp"

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
void OMP::getLambda(){
  double l = 0;
  unsigned idx = 0;
  auto sz = dat.x[0].size();
  for (unsigned ii = 0; ii < I.size(); ++ii) {
    unsigned i = I[ii];
    vect ai; ai.reserve(dat.y.size());
    if(i < 2*sz) {
      int mult = i < sz ? 1 : -1;
      for (unsigned j = 0; j < dat.y.size(); j++) {
        ai.emplace_back( mult * dat.y[j] * dat.x[j][i]);
      }
    } else {
      int mult = i == 2*sz ? 1 : -1;
      for (auto &val : dat.y) {
        ai.emplace_back( mult * val);
      }
    }
    double ar = Vector::dotProduct(ai, r);
    if(abs(ar) > l) {
      l = abs(ar);
      idx = ii;
    }
  }
  L.emplace_back(I[idx]);
  I.erase(I.begin() + idx);
}
void OMP::updateU(){

//  vect function(vect p, vect &f){
//    // do function stuff
//    return f;
//  }
//  matrix jacobian_approx(vect p, int n, int m, matrix& J){
//    vect p_t(p);
//    matrix J1;
//    vect r;
//
//    return J;
//  }
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
  t -= 1;
  return t > 0 && Vector::norm2(r) < threshold;
}