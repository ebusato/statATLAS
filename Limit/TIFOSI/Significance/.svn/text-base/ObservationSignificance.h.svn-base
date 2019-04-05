#ifndef OBSERVATIONSIGNIFICANCE_H
#define OBSERVATIONSIGNIFICANCE_H

#include <iostream>

class RooWorkspace;
class TH1F;

class ObservationSignificance {
 public:
  ObservationSignificance(RooWorkspace* ws);
  inline void setNworkers(const int n) {m_nWorkers=n;}
  void evaluateSignificance();
  inline void setNToys(const int i) {m_nToys=i;}

 private:
  ObservationSignificance();
  RooWorkspace* m_ws;
  int m_nWorkers;
  int m_nToys;
  TH1F* m_pDistrqMu_bHyp;
  TH1F* m_pDistrqMu_sbHyp;
  double m_qMuObs;
};

#endif
