//
// Created by Javier Peralta on 5/31/18.
//

#include "DifferentialEvolution.hpp"

using namespace std;

vector<int> DifferentialEvolution::get_parent_idx(){
  vector<int> idxs;
  idxs.reserve(3);
  auto idx = int(rand() % population.size());
  idxs.emplace_back(idx);
  while(idxs.size() < 3) {
    bool has = false;
    idx = int(rand() % population.size());
    for (auto& ii : idxs) {
      if(idx == ii) {
        has = true;
        break;
      }
    }
    if(!has) idxs.push_back(idx);
  }
  return idxs;
}

DifferentialEvolution::DifferentialEvolution(vector<Individual> &pop, unsigned max_ev, double cr, double F,
                                             OptimizationProblem *problem, ProblemType type)
                                             : __cr(cr), __F(F), max_evals(max_ev) {
  __problem = problem;
  minimize = (type == ProblemType::MINIMIZE);
  num_vars = pop[0].get_data().size();
}

DifferentialEvolution::Individual DifferentialEvolution::getBest(){
  unsigned idx = 0;
  double min = population[0].get_value();
  for (unsigned i = 1; i < population.size(); i++) {
    if(population[i].get_value() < min) {
      min = population[i].get_value();
      idx = i;
    }
  }
  return population[idx];
}

bool DifferentialEvolution::iterate() {
//  double best = getBest().get_value();
  vector<Individual> children; children.reserve(population.size());
  for (auto& item : population) {
    vector<int> idxs = get_parent_idx();
    vector<double> dat(item.get_data());
    dat.reserve(num_vars);
    auto r1 =  population[idxs[0]].get_data();
    auto r2 =  population[idxs[1]].get_data();
    auto r3 =  population[idxs[2]].get_data();
    int jrand = rand() % num_vars;
    for (int j = 0; j < num_vars; ++j) {
      double p = (double)rand() / (double)RAND_MAX;
      if(p <= __cr || j == jrand){
        double v = r1[j];
        double dir = __F * (r2[j] - r3[j]);
        dat[j] = v+dir;
      } else {
        dat[j] = r1[j];
      }
    }
    Individual ind(dat);
    double fit = __problem->evaluateFunction(dat);
    max_evals-- ;
    ind.set_value(fit);
    if(fit < item.get_value()) children.emplace_back(ind);
    else children.emplace_back(item);
  }
  return max_evals > 0;
}

vect DifferentialEvolution::Individual::get_data(){
  return data;
}
double DifferentialEvolution::Individual::get_value(){
  return value;
}
void DifferentialEvolution::Individual::set_value(double val){
  value = val;
}
DifferentialEvolution::Individual::Individual(vect &dat){
  data.clear();
  for (auto& d : dat) {
    data.push_back(d);
  }
}