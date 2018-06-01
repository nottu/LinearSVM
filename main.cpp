#include <iostream>
#include <time.h>

#include "Data.hpp"
#include "DifferentialEvolution/DifferentialEvolutionTest.hpp"
#include "SVMDE.hpp"

using namespace std;

int main() {
  srand((unsigned)time(nullptr));
//  DifferentialEvolutionTest::runTest(Test::shpere, 30);
  Data d = Data("iris.data");
  SVMDE svm(d);
  vect v = svm.getHyper();
  Vector::printVector(v);
  cout << endl;
  return 0;
}