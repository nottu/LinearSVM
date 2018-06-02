//
// Created by Javier Peralta on 5/30/18.
//

#ifndef SVM_OMP_HPP
#define SVM_OMP_HPP

#include "Data.hpp"

class OMP {
  Data dat;
  vect u;
  vect r;
  unsigned t;
  std::vector<unsigned> I;
  std::vector<unsigned> L;
  void updateResidual();
  void getLambda();
  void updateU();

public:
  OMP(Data &dat, unsigned s);
  bool iterate(double threshold);
};


#endif //SVM_OMP_HPP
