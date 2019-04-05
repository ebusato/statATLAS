/////////////////////////////////////////////////
// This is an adapted version of RooStatsTools/StandardFrequentistCLsDemo.C
// (see https://svnweb.cern.ch/trac/atlasphys/browser/Physics/StatForum/RooStatsTools/StandardFrequentistCLsDemo.C)
/////////////////////////////////////////////////

#include <stdexcept>

#include "Frequentist.h"
#include "TFile.h"
#include "RooWorkspace.h"
#include "RooAbsPdf.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooStats/ModelConfig.h"
#include "TCanvas.h"
#include "TLine.h"

//#include "RooStats/HybridCalculator.h"

#include "RooStats/FrequentistCalculator.h"
#include "RooStats/ToyMCSampler.h"
#include "RooStats/HypoTestPlot.h"

#include "RooStats/ProfileLikelihoodTestStat.h"
#include "RooStats/HypoTestInverter.h"
#include "RooStats/HypoTestInverterPlot.h"

using namespace std;
using namespace RooFit;
using namespace RooStats;

Frequentist::Frequentist() :
  m_ws(0),
  m_modelType(Frequentist::EB),
  m_nWorkers(0),
  m_pHTIR(0)
{}

Frequentist::Frequentist(RooWorkspace* ws) :
  m_ws(ws),
  m_modelType(Frequentist::EB),
  m_nWorkers(0),
  m_pHTIR(0)
{}

double Frequentist::computeLimit(int npoints, double mumin, double mumax, int ntoys)    
{
  if(!m_ws){
    throw runtime_error("ERROR ! workspace pointer is 0");
    return -1;
  }
  ModelConfig* mc = (ModelConfig*) m_ws->obj("ModelConfig");
  if(!mc) {
    throw runtime_error("ERROR ! ModelConfig not found, printing workspace");
    m_ws->Print();
    return -1;
  }
  if (!mc->GetPdf()) { 
    throw runtime_error("ERROR ! model has not pdf");
    return -1;
  }
  RooDataSet* data = (RooDataSet*) m_ws->data("obsData");
  if(!data){
    throw runtime_error("ERROR ! dataset not found, printing workspace");
    m_ws->Print();
    return -1;
  }
  const RooArgSet* POIs = mc->GetParametersOfInterest();
  if(!POIs) {
    throw runtime_error("ERROR ! POIs set not found");
    return -1;
  }
  RooRealVar* mu = (RooRealVar*) POIs->first();
  if(!mu) {
    throw runtime_error("ERROR !");
    cout << "ERROR ! parameter of interest not found" <<endl;
    return -1;
  }

  if (!mc->GetSnapshot() ) { 
    cout << "-> Creating snapshot for ModelConfig" << endl;
    mc->SetSnapshot(*mc->GetParametersOfInterest());
  }
  
  cout << "Make s+b model by copying bOnly model and setting POI to zero" << endl;
  ModelConfig* mcbOnly = (ModelConfig*) mc->Clone();
  TString mcbOnly_Name("ModelConfig_bOnly");
  mcbOnly->SetName(mcbOnly_Name);      
  RooRealVar *var = dynamic_cast<RooRealVar*>(mcbOnly->GetParametersOfInterest()->first());
  if(var) {
    double oldval = var->getVal();
    var->setVal(0);
    mcbOnly->SetSnapshot(RooArgSet(*var));
    var->setVal(oldval);
  }
  else { 
    throw runtime_error("ERROR !");
    cout << "ERROR ! parameter of interest for ModelConfig_bOnly not found" <<endl;
    return -1;
  }  

  if (!mcbOnly->GetSnapshot() ) { 
    cout << "-> Creating snapshot for ModelConfig_bOnly" << endl;
    double oldval = var->getVal();
    if(oldval!=0) {
      throw runtime_error("ERROR !");
      cout << "ERROR ! mu should be 0 but it's not" <<endl;
      return -1;
    }
    var->setVal(0);
    mcbOnly->SetSnapshot(RooArgSet(*var));
    var->setVal(oldval);
  }

  ProfileLikelihoodTestStat profll(*mc->GetPdf());
  profll.SetOneSided(1);
  profll.SetReuseNLL(false);

  TestStatistic* testStat = &profll;
  FrequentistCalculator* hc = new FrequentistCalculator(*data, *mcbOnly, *mc);
  ToyMCSampler *toymcs = (ToyMCSampler*)hc->GetTestStatSampler();
  toymcs->SetTestStatistic(testStat);
  hc->SetToys(ntoys,ntoys); 

  RooMsgService::instance().getStream(1).removeTopic(RooFit::NumIntegration);

  mc->GetPdf()->fitTo(*data);
  double muhat = mu->getVal();

  HypoTestInverter calc(*hc);
  calc.SetVerbose(2);
  calc.SetConfidenceLevel(0.95);
  calc.UseCLs(true);
  calc.SetVerbose(false);

  if(m_nWorkers>0) {
    ProofConfig pc(*m_ws, m_nWorkers, "", false);
    toymcs->SetProofConfig(&pc);    // enable proof
  }  

  if (npoints > 0) {
    if (mumin >= mumax) { 
      mumin = int(muhat);
      mumax = int(muhat+4*mu->getError());
    }
    std::cout << "Doing a fixed scan  in interval : " << mumin << " , " << mumax << std::endl;
    calc.SetFixedScan(npoints,mumin,mumax);
  }
  else { 
    //mu->setMax(10*int( (muhat+ 10*mu->getError() )/10 ) );
    std::cout << "Doing an  automatic scan  in interval : " << mu->getMin() << " , " << mu->getMax() << std::endl;
  }

  m_pHTIR = calc.GetInterval();
  if(!m_pHTIR) { 
    throw runtime_error("ERROR ! HypoTestInverterResult doesn't exit");
    std::cout << "ERROR ! HypoTestInverterResult doesn't exit -> QUIT " << std::endl;
    return -1;          
  }
  return m_pHTIR->UpperLimit();
}

void Frequentist::printInterval()
{
  cout << " -> Observed=" << m_pHTIR->UpperLimit() << endl;
  cout << " -> Expected -2 sig=" << getExpM2() << endl;
  cout << " -> Expected -1 sig=" << getExpM1() << endl;
  cout << " -> Expected median=" << getExpMed() << endl;
  cout << " -> Expected +1 sig=" << getExpP1() << endl;
  cout << " -> Expected +2 sig=" << getExpP2() << endl;
}

void Frequentist::makePlots()
{
  TCanvas* c1 = new TCanvas("c1","CL vs mu",400,400);
  HypoTestInverterPlot *plot = new HypoTestInverterPlot("HTI_Result_Plot","CL scan",m_pHTIR);
  plot->Draw("CLb 2CL");  // plot all and Clb
  
  TCanvas* c2 = new TCanvas("c2","test stat distrib");
  const int nEntries = m_pHTIR->ArraySize();
  c2->Divide( 2, TMath::Ceil(nEntries/2));
  for (int i=0; i<nEntries; i++) {
    c2->cd(i+1);
    SamplingDistPlot * pl = plot->MakeTestStatPlot(i);
    pl->SetLogYaxis(true);
    pl->Draw();
  }
  
  TFile* fileOut = new TFile("outputFrequentist.root","RECREATE");
  m_pHTIR->Write();
  c1->Write();
  c2->Write();
  fileOut->Close();
}
