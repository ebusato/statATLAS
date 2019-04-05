#ifndef BAYESIANMCMC_H
#define BAYESIANMCMC_H

#include "RooStats/MCMCInterval.h"

class RooWorkspace;
class RooRealVar;
class TCanvas;
class TH1F;

class BayesianMCMC {
 public:
  BayesianMCMC(RooWorkspace* ws);
  BayesianMCMC();
  enum {EB,HistFactory};
  inline void setConfLevel(const double c) {m_confLevel=c;}
  inline void setModelType(const int i) {m_modelType=i;}
  inline void setNumIters(const int n) {m_numIters=n;}
  inline void setUseAsimovData() {m_useAsimovData=true;}
  inline void setAutoMuMax() {m_setAutoMuMax=true;}
  enum {Uniform,Exponential};
  inline void setPriorPdf(const int pdf) {m_priorPdf=pdf;}
  TCanvas* drawMeanStdDevVsIteration(const RooRealVar& var);
  TCanvas* drawDistrib1D(const RooRealVar& var, const bool drawPrior=false, const int nbins=50);
  TCanvas* drawDistrib2D(const RooRealVar& var1, const RooRealVar& var2);
  void makePlots(bool all=true, std::string outFile="", bool meanStddevVsIt=true);
  double computeLimit(const float& muMax=20);
  void printInterval();
  void saveMeanStdDevVsIterationToFile(const std::string& file) {m_outFileMeanStdDevVsIteration=file;}
  void setSeed(const int seed) {m_seed=seed;}
  TH1F* getMuPosterior() const {return m_pMuPosterior;}
  RooWorkspace* getWS() const {return m_ws;}

 private:
  RooWorkspace* m_ws;
  RooStats::MCMCInterval* m_interval;
  double m_confLevel;
  int m_numIters;
  bool m_useAsimovData;
  bool m_setAutoMuMax;
  int m_modelType;
  int m_priorPdf;
  std::string m_outFileMeanStdDevVsIteration;
  int m_seed;
  TH1F* m_pMuPosterior;
};

#endif // BAYESIANMCMC_H
