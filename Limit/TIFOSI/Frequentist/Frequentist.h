#ifndef FREQUENTIST_H
#define FREQUENTIST_H

#include "RooStats/HypoTestInverterResult.h"

class RooWorkspace;
class RooRealVar;
class TCanvas;

class Frequentist {
 public:
  Frequentist(RooWorkspace* ws);
  Frequentist();
  enum {EB,HistFactory};
  inline void setModelType(const int i) {m_modelType=i;}
  inline void setNworkers(const int n) {m_nWorkers=n;}
  inline double getObserved() const {return m_pHTIR->UpperLimit();}
  inline double getExpMed() const {return m_pHTIR->GetExpectedLimit(0,"P");}
  inline double getExpM1() const {return m_pHTIR->GetExpectedLimit(-1,"P");}
  inline double getExpP1() const {return m_pHTIR->GetExpectedLimit(+1,"P");}
  inline double getExpM2() const {return m_pHTIR->GetExpectedLimit(-2,"P");}
  inline double getExpP2() const {return m_pHTIR->GetExpectedLimit(+2,"P");}
  void makePlots();
  double computeLimit(int npoints = 10, double mumin = 0, double mumax = 50, int ntoys=3000);
  void printInterval();

 private:
  RooWorkspace* m_ws;
  int m_modelType;
  int m_nWorkers;
  RooStats::HypoTestInverterResult* m_pHTIR;
};

#endif // BAYESIANMCMC_H
