//
// Created by Javier Peralta on 5/30/18.
//
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include <random>

#include "Data.hpp"
using namespace std;

Data::Data(){};

Data::Data(string filename, bool last, string c1, string c2, long n_instances) {
  ifstream file(filename);
  if(file.is_open()) {
    unsigned long instances = 0;
    string line;
    while (getline(file, line) && instances != n_instances){
      vector<double> line_data;
      istringstream ss(line);
      while(getline(ss, line, delim)){
        if(line.compare(c1) == 0) line = "-1";
        if(line.compare(c2) == 0) line = "1";
        char *pend;
        double v = strtod(line.c_str(), nullptr);
        line_data.emplace_back(v);
      }
      if(last){
        y.emplace_back(line_data.back());
        line_data.pop_back();
      } else {
        y.emplace_back(line_data.front());
        line_data.erase(line_data.begin());
      }
      x.emplace_back(line_data);
      instances++;
    }
    file.close();
  } else{
    cout << "Error loading file :" << filename << endl;
    exit(1);
  }
}

void Data::normalize(){
  for (int i = 0; i < x.at(0).size(); ++i) {
    double mean = 0;
    for (auto &v : x) {
      mean += v[i];
    }
    mean /= x.size();
    double var = 0;
    for (auto &v : x) {
      v[i] -= mean;
      var += (v[i] - mean) * (v[i] - mean);
    }
    var = sqrt(var);
    for (auto &v : x) {
      if(var == 0) continue;
      v[i] /= var;
    }
  }
}
void Data::shuffle(){
  std::random_device rd;
  std::mt19937 g(rd());
  vector<int> indexes;
  indexes.reserve(y.size());
  for (int i = 0; i < y.size(); ++i)
    indexes.emplace_back(i);
  std::shuffle(indexes.begin(), indexes.end(), g);
  matrix x_2;
  vector<int> y_2;
  for (int i = 0; i < y.size(); ++i){
    x_2.emplace_back(x[indexes[i]]);
    y_2.emplace_back(y[indexes[i]]);
  }
  x = x_2;
  y = y_2;
}
Data Data::getSubData(unsigned start, unsigned n_data){
  Data sub;
  unsigned max_idx = start + n_data;
  if (max_idx > y.size()) max_idx = (unsigned) y.size();
  for (int i = start; i < max_idx; ++i) {
    sub.x.push_back(x[i]);
    sub.y.push_back(y[i]);
  }
  return sub;
}