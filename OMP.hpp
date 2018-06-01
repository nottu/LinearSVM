//
// Created by Javier Peralta on 5/30/18.
//

#ifndef SVM_OMP_HPP
#define SVM_OMP_HPP

#include "Data.hpp"

class OMP {
  Data dat;
  std::vector<double> u;
  std::vector<double> r;


public:
  OMP(Data &dat);
  void iterate(unsigned max_iter, unsigned s, double threshold);
};


#endif //SVM_OMP_HPP
