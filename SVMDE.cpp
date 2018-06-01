//
// Created by Javier Peralta on 5/31/18.
//

#include "SVMDE.hpp"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define HINGE(x) MAX(x, 0)

SVMDE::SVMDE(Data &d) : dat(d) {}

SVMDE::SVMDE_Problem::SVMDE_Problem(Data &d, double m, double cte) : dat(d), mu(m) ,c(cte) {
  dim = (unsigned) d.x[0].size();
  sz  = (unsigned) d.x.size();
}

double SVMDE::SVMDE_Problem::get_mu() {return mu;}
void SVMDE::SVMDE_Problem::set_mu(double m) {mu = m;};

double SVMDE::SVMDE_Problem::evaluateFunction(vect& vals){
  vect betas(vals.begin(), vals.begin() + dim);
  double alpha = vals[dim];
  double val = c * Vector::norm2(betas);
  for (int i = 0; i < sz; ++i) {
    double classif = Vector::dotProduct(betas, dat.x[i]) + alpha;
    double errClas = HINGE(1 - classif);
    val += errClas;
  }
  return val;
}

//double SVMDE::SVMDE_Problem::evaluateFunction(vect& vals){
//  vect betas(vals.begin(), vals.begin() + dim);
//  double beta0 = vals[dim];
//  vect errors(vals.begin() + dim + 1, vals.end());
//  double val = 0;
//  val += fitnessValue(betas, errors);
//  vect rest = restrictions(vals, beta0, errors);
//  for (auto& r : rest){
//    val += (mu/2.0) * (r * r);
//  }
//  return val;
//}
double SVMDE::SVMDE_Problem::fitnessValue(vect& betas, vect& errors){
  double cerr = 0;
  for(auto &err : errors)
    cerr += err;
  return Vector::norm2(betas);
}
vect SVMDE::SVMDE_Problem::restrictions(vect& betas, double beta0, vect& errors){
  vect r;
  r.reserve(sz * 2);

  for (int i = 0; i < sz; ++i) {
    double proy = Vector::dotProduct(betas, dat.x[i]) + beta0;
    double classfit = dat.y[i] * proy;
    r.push_back( HINGE(1 - errors[i] - classfit) );
    r.push_back( HINGE(-errors[i]) );
  }

  return r;
}