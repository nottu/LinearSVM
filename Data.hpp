//
// Created by Javier Peralta on 5/30/18.
//

#ifndef SVM_DATA_HPP
#define SVM_DATA_HPP

#include <string>
#include <vector>

#include "Matrix.hpp"


class Data {
public:
  matrix x; //actual data matrix
  std::vector<int> y; // category
  char delim = ',';
  explicit  Data(std::string filename);
};



#endif //SVM_DATA_HPP
