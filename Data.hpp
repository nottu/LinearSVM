//
// Created by Javier Peralta on 5/30/18.
//

#ifndef SVM_DATA_HPP
#define SVM_DATA_HPP

#include <string>
#include <vector>

#include "Matrix.hpp"


class Data {
  Data();
public:
  matrix x; //actual data matrix
  std::vector<int> y; // category
  char delim = ',';
  explicit  Data(std::string filename, bool cat_last=true, std::string cat1="-1", std::string cat2="1", long n_instances=-1);
  void shuffle();
  void normalize();
  Data getSubData(unsigned start, unsigned n_data);
};



#endif //SVM_DATA_HPP
