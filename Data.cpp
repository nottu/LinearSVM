//
// Created by Javier Peralta on 5/30/18.
//
#include <fstream>
#include <iostream>
#include <sstream>

#include "Data.hpp"
using namespace std;

Data::Data(string filename) {
  ifstream file(filename);
  if(file.is_open()) {
    string line;
    while (getline(file, line)){
      vector<double> line_data;
      istringstream ss(line);
      while(getline(ss, line, delim)){
        double v = strtod(line.c_str(), nullptr);
        line_data.emplace_back(v);
      }
      y.emplace_back(line_data.back());
      line_data.pop_back();
      x.emplace_back(line_data);
    }
    file.close();
  } else{
    cout << "Error loading file :" << filename << endl;
    exit(1);
  }
}