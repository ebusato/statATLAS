#include <stdexcept>

#include "TCanvas.h"
#include "TStyle.h"
#include "TMath.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "RooWorkspace.h"
#include "RooAbsData.h"
#include "RooUniform.h"
#include "RooExponential.h"
#include "RooStats/ModelConfig.h"
#include "RooStats/MCMCCalculator.h"
#include "RooStats/MCMCIntervalPlot.h"
#include "RooStats/SequentialProposal.h"
#include "RooStats/ProposalHelper.h"
#include "RooStats/ProposalHelper.h"
#include "RooFitResult.h"
#include "RooRandom.h"

#include "BayesianMCMC.h"

using namespace std;
using namespace RooFit;
using namespace RooStats;

BayesianMCMC::BayesianMCMC() :
  m_ws(0),
  m_interval(0),
  m_confLevel(0.95),
  m_numIters(1e6),
  m_useAsimovData(false),
  m_setAutoMuMax(false),
  m_modelType(BayesianMCMC::EB),
  m_priorPdf(BayesianMCMC::Uniform),
  m_outFileMeanStdDevVsIteration(""),
  m_seed(0),
  m_pMuPosterior(0)
{}

BayesianMCMC::BayesianMCMC(RooWorkspace* ws) :
  m_ws(ws),
  m_interval(0),
  m_numIters(1e6),
  m_useAsimovData(false),
  m_setAutoMuMax(false),
  m_modelType(BayesianMCMC::EB),
  m_priorPdf(BayesianMCMC::Uniform),
  m_outFileMeanStdDevVsIteration(""),
  m_seed(0),
  m_pMuPosterior(0)
{}

TCanvas* BayesianMCMC::drawMeanStdDevVsIteration(const RooRealVar& var)
{
  if(!m_interval) {
    cout << "ERROR ! m_interval pointer is 0" << endl;
    return NULL;
  }
  const MarkovChain* markovChain = m_interval->GetChain();
  
  Int_t size = markovChain->Size();
  
  int counterGraphPoints=0;
  TGraph* gMean = new TGraph(size);
  gMean->SetName("gMean");
  TGraph* gStdDev = new TGraph(size);
  gStdDev->SetName("gStdDev");
  TH1F* hVar = new TH1F(Form("%s_temp",var.GetName()),Form("%s_temp",var.GetName()),150,var.getMin(),var.getMax());

  hVar->GetXaxis()->SetTitle(var.GetName());

  for (Int_t i = 0; i < size; i++) {
    hVar->Fill(markovChain->Get(i)->getRealValue(var.GetName()),markovChain->Weight());
    double mean=hVar->GetMean();
    double stddev=hVar->GetRMS();
    gMean->SetPoint(counterGraphPoints,i,mean);
    gStdDev->SetPoint(counterGraphPoints,i,stddev);
    ++counterGraphPoints;
  }

  TCanvas* cTemp = new TCanvas("cTemp","cTemp",800,600);
  cTemp->cd();
  hVar->Draw();

  TString cName(var.GetName()); cName+="CanvasMeanStdDev";
  TCanvas* cVar = new TCanvas(cName,cName,800,600);
  cVar->Divide(1,2);
  cVar->cd(1);
  gMean->Draw("ap");
  cVar->cd(2);
  gStdDev->Draw("ap");

  if(m_outFileMeanStdDevVsIteration!="") {
    TFile* fout = new TFile(Form("%s_%s.root",m_outFileMeanStdDevVsIteration.c_str(),var.GetName()),"recreate");
    gMean->Write();
    gStdDev->Write();
    fout->Write();
    fout->Close();
  }
  return cVar;
}

TCanvas* BayesianMCMC::drawDistrib1D(const RooRealVar& var, const bool drawPrior, const int nbins)
{
  if(!m_interval) {
    cout << "ERROR ! m_interval pointer is 0" << endl;
    return NULL;
  }
  const MarkovChain* markovChain = m_interval->GetChain();
  
  Int_t size = markovChain->Size();
  Int_t burnInSteps = m_interval->GetNumBurnInSteps();
  
  TH1F* hVar = new TH1F(var.GetName(),var.GetName(),nbins,var.getMin(),var.getMax());
  TString varBurnInName(var.GetName()); varBurnInName+="BurnIn";
  TH1F* hVarBurnIn = new TH1F(varBurnInName,varBurnInName,nbins,var.getMin(),var.getMax());
  TString varInitValName(var.GetName()); varInitValName+="InitVal";
  TH1F* hVarInitVal = new TH1F(varInitValName,varInitValName,nbins,var.getMin(),var.getMax());
  
  if(var.GetName()==TString("mu")) {
    m_pMuPosterior=hVar;
  }

  if(TString(var.GetName()).Contains("mu")) {
    hVar->SetStats(0);
    hVarBurnIn->SetStats(0);
    hVarInitVal->SetStats(0);
  }
  hVar->GetXaxis()->SetTitle(var.GetName());

  for (Int_t i = burnInSteps; i < size; i++) {
    hVar->Fill(markovChain->Get(i)->getRealValue(var.GetName()),markovChain->Weight());
  }

  for (Int_t i = 0; i < burnInSteps; i++) {
    hVarBurnIn->Fill(markovChain->Get(i)->getRealValue(var.GetName()),markovChain->Weight());
  }

  hVarInitVal->Fill(markovChain->Get(0)->getRealValue(var.GetName()),markovChain->Weight());

  hVar->SetLineColor(kBlack);
  hVarBurnIn->SetLineColor(kRed);
  hVarInitVal->SetLineColor(kBlue);

  double hVarInt=hVar->Integral("width");
  hVar->Scale(1/hVarInt);
  hVarBurnIn->Scale(1/hVarInt);
  hVarInitVal->Scale(1/hVarInt);

  TString cName(var.GetName()); cName+="Canvas";
  TCanvas* cVar = new TCanvas(cName,cName,800,600);
  cVar->cd();
  hVar->Draw();
  hVarBurnIn->Draw("same");
  hVarInitVal->Draw("same");

  if(drawPrior) {
    cout << "Treating nuisance parameter " << var.GetName() << endl;
    TString pdfName(var.GetName()); 
    if(m_modelType==BayesianMCMC::HistFactory) {
      if(pdfName.BeginsWith("alpha")) {
	pdfName+="Constraint";
      }
      else if(pdfName.BeginsWith("gamma")) {
	pdfName+="_constraint";
      }
    }
    else if(m_modelType==BayesianMCMC::EB) {
      pdfName+="_Constraint";
    }
    cout << "  -> pdfName=" << pdfName << endl;
    RooAbsPdf* nuisPdf=m_ws->pdf(pdfName.Data());
    if(nuisPdf) {
      TH1* nuisPdfTH=nuisPdf->createHistogram(var.GetName());
      nuisPdfTH->SetLineColor(kMagenta);
      nuisPdfTH->Scale(1/nuisPdfTH->Integral("width"));
      nuisPdfTH->Draw("same");      
    }
    else {
      cout << "ERROR! nuisPdf pointer is NULL" << endl;
    }
  }    

  return cVar;
}

TCanvas* BayesianMCMC::drawDistrib2D(const RooRealVar& var1, const RooRealVar& var2)
{
  if(!m_interval) {
    cout << "ERROR ! m_interval pointer is 0" << endl;
    return NULL;
  }
  const MarkovChain* markovChain = m_interval->GetChain();

  TString histoName("h_");
  histoName+=var1.GetName(); histoName+="_vs_"; histoName+=var2.GetName();
  TH2F* hVar = new TH2F(histoName,histoName,100,var1.getMin(),var1.getMax(),100,var2.getMin(),var2.getMax());
  hVar->GetXaxis()->SetTitle(var1.GetName());
  hVar->GetYaxis()->SetTitle(var2.GetName());
  hVar->GetYaxis()->SetTitleOffset(1.3);
  hVar->SetContour(4);

  Int_t size = markovChain->Size();
  Int_t burnInSteps = m_interval->GetNumBurnInSteps();
  for (Int_t i = burnInSteps; i < size; i++) {
    hVar->Fill(markovChain->Get(i)->getRealValue(var1.GetName()),markovChain->Get(i)->getRealValue(var2.GetName()),markovChain->Weight());
  }

  double hVarInt=hVar->Integral("width");
  hVar->Scale(1/hVarInt);

  TString cName(var1.GetName()); cName+="_vs_"; cName+=var2.GetName(); cName+="Canvas";
  TCanvas* cVar = new TCanvas(cName,cName,600,600);
  cVar->cd();
  hVar->SetTitle("");
  hVar->SetStats(0);
  hVar->Draw("col");

  return cVar;
}

void BayesianMCMC::makePlots(bool all, std::string outFile, bool meanStddevVsIt)
{
  TCanvas* c1 = new TCanvas("c1","c1"); c1->cd();
  MCMCIntervalPlot plot(*m_interval);
  plot.Draw();
  
  RooRealVar* mu = (RooRealVar*) m_ws->var("mu");
  TCanvas* c=drawDistrib1D(*mu,true);
  if(outFile!="") {
    c->SaveAs(Form("%s[",outFile.c_str()));
    c->SaveAs(outFile.c_str());
  }
  if(meanStddevVsIt) {
    c=drawMeanStdDevVsIteration(*mu);
    if(outFile!="") {
      c->SaveAs(outFile.c_str());
    }
  }

  if(all) {

    ModelConfig* mc = (ModelConfig*) m_ws->obj("ModelConfig");
    const RooArgSet* list = mc->GetNuisanceParameters();
    if(!list) return;
    if(list->getSize()==0) return;
        
    TIterator* it = list->createIterator();
    RooRealVar* nuis = NULL;
    while( (nuis = (RooRealVar*) it->Next() )){
      c=drawDistrib1D(*nuis,true);
      if(outFile!="") {
	c->SaveAs(outFile.c_str());
      }
      if(meanStddevVsIt) {
	c=drawMeanStdDevVsIteration(*nuis);
	if(outFile!="") {
	  c->SaveAs(outFile.c_str());
	}
      }
      /*
      // uncomment to draw 2D markov chain (can be
      // very time consumming if number of iterations is large)
      plot.DrawChainScatter(*mu,*nuis);
      if(outFile!="") {
	c->SaveAs(outFile.c_str());
      }
      */
      c=drawDistrib2D(*mu,*nuis);
      if(outFile!="") {
	c->SaveAs(outFile.c_str());
      }
    }
  }
  if(outFile!="") {
    c->SaveAs(Form("%s]",outFile.c_str()));
  }
}

void BayesianMCMC::printInterval()
{
  RooRealVar* mu = (RooRealVar*) m_ws->var("mu");
  double lowlimit = m_interval->LowerLimit(*mu);
  double uplimit = m_interval->UpperLimit(*mu);
  cout << "\n95% interval is : ["<< lowlimit << ", "<< uplimit <<"] "<<endl;
}

double BayesianMCMC::computeLimit(const float& muMax)
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
  RooDataSet* data = NULL;
  if(!m_useAsimovData) 
    data = (RooDataSet*) m_ws->data("obsData");
  else
    data = (RooDataSet*) m_ws->data("asimovData");
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
  if(!m_setAutoMuMax) {
    mu->setMax(muMax);
  }
  else {
    cout << "Setting muMax automatically" << endl;
    mc->GetPdf()->fitTo(*data);
    double muhat=mu->getVal();
    cout << "  -> muhat=" << muhat << endl;
    cout << "  -> setting muMax=" << 100*muhat << endl;
    mu->setMax(100*muhat);
  }  
  if(BayesianMCMC::Exponential==m_priorPdf) {
    RooRealVar lambda("lambda", "slope", -0.5);
    RooExponential prior("mu_Constraint", "exponential PDF", *mu, lambda);
    m_ws->import(prior);
    mc->SetPriorPdf(*m_ws->pdf("mu_Constraint"));
    /*mc->Print("v");
      TCanvas* cPrior = new TCanvas("cPrior","cPrior",400,400); cPrior->cd();
      RooPlot* framePrior = mu->frame();
      prior.plotOn(framePrior);
      framePrior->Draw();
    */
  }
  else if(BayesianMCMC::Uniform==m_priorPdf) {
    RooUniform prior("mu_Constraint","",*mc->GetParametersOfInterest());
    m_ws->import(prior);
    mc->SetPriorPdf(*m_ws->pdf("mu_Constraint"));
  }
  else {
    cout << "ERROR! prior not known -> quit" << endl;
    throw runtime_error("ERROR !");
  }

  RooRandom::randomGenerator()->SetSeed(m_seed); 

  SequentialProposal sp(0.1);
  MCMCCalculator mcmc(*data,*mc);
  mcmc.SetConfidenceLevel(m_confLevel);
  mcmc.SetProposalFunction(sp);   
  mcmc.SetNumIters(m_numIters);      
  mcmc.SetNumBurnInSteps(50);     
  mcmc.SetLeftSideTailFraction(0); // One-sided Bayesian interval
  mcmc.SetNumBins(1e3);
  m_interval = mcmc.GetInterval();
  return m_interval->UpperLimit(*mu);
}
