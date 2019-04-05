#ifndef HYBRIDLIMIT_H
#define HYBRIDLIMIT_H

#include "RooStats/HypoTestInverterResult.h"

class RooWorkspace;

class HybridLimit {
 public:
  HybridLimit(RooWorkspace* ws);
  enum {simpleLhoodRatio,profLhood};
  inline void setTestStat(const int testStat) {m_testStat=testStat;}
  double computeLimit(int npoints=0, double poimin=0, double poimax=100, int ntoys=1e4);
  void printInterval();
  void makePlots();

 private:
  HybridLimit();
  RooWorkspace* m_ws;
  int m_testStat;
  RooStats::HypoTestInverterResult* m_result;
};

#endif // HYBRIDLIMIT_H
