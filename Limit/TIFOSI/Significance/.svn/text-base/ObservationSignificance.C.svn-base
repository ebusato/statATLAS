#include "TFile.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TArrow.h"
#include "TLatex.h"
#include "TMath.h"
#include "TStyle.h"

#include "RooWorkspace.h"
#include "RooAbsData.h"
#include "RooStats/ModelConfig.h"
#include "RooStats/ToyMCSampler.h"
#include "RooStats/ProfileLikelihoodTestStat.h"
#include "RooStats/HypoTestResult.h"
#include "RooStats/HypoTestPlot.h"
#include "RooStats/FrequentistCalculator.h"


#include "TH1F.h"

#include "ObservationSignificance.h"

using namespace std;
using namespace RooFit;
using namespace RooStats;

ObservationSignificance::ObservationSignificance(RooWorkspace* ws) :
  m_ws(ws),
  m_nWorkers(0),
  m_nToys(1e3),
  m_pDistrqMu_bHyp(0),
  m_pDistrqMu_sbHyp(0),
  m_qMuObs(0)
{}


void ObservationSignificance::evaluateSignificance()
{  
  ///////////////////////////////////////////////////////////////
  // Code below is adapted from StandardFrequentistDiscovery.C
  ///////////////////////////////////////////////////////////////

  gStyle->SetOptTitle(0);

  if(!m_ws){
    cout <<"workspace not found" << endl;
    return;
  }
  
  ModelConfig* mc = (ModelConfig*) m_ws->obj("ModelConfig");
  RooAbsData* data = m_ws->data("obsData");
  
  if(!data || !mc){
    m_ws->Print();
    cout << "data or ModelConfig was not found" <<endl;
    return;
  }
  
  mc->Print();
  
  RooRealVar* mu = (RooRealVar*) mc->GetParametersOfInterest()->first();
  mu->setVal(1);
  mc->SetSnapshot(*mc->GetParametersOfInterest());
  ModelConfig *mcNull = mc->Clone("ModelConfigNull");
  mu->setVal(0);
  mcNull->SetSnapshot(*(RooArgSet*)mcNull->GetParametersOfInterest()->snapshot());

  ProfileLikelihoodTestStat* plts =  new ProfileLikelihoodTestStat(*mc->GetPdf());
  plts->SetOneSidedDiscovery(true);
  //plts->SetPrintLevel(1);
  plts->SetVarName( "q_{0}/2" );

  ToyMCSampler toymcs(*plts, 50);

  if (!mc->GetPdf()->canBeExtended()) {
    if (data->numEntries() == 1) {
      toymcs.SetNEventsPerToy(1);
    } else cout << "Not sure what to do about this model" << endl;
  }

  if(m_nWorkers>0) {
    ProofConfig pc(*m_ws, m_nWorkers, "", false);
    toymcs.SetProofConfig(&pc);    // enable proof
  }

  FrequentistCalculator freqCalc(*data, *mc, *mcNull, &toymcs);
  freqCalc.SetToys(m_nToys,m_nToys); // null toys, alt toys

  HypoTestResult* freqCalcResult = freqCalc.GetHypoTest();
  freqCalcResult->GetNullDistribution()->SetTitle( "b only" );
  freqCalcResult->GetAltDistribution()->SetTitle( "s+b" );
  freqCalcResult->Print();
  cout << "Null pvalue=" << freqCalcResult->NullPValue() << endl;
  
  // plot
  TCanvas* c1 = new TCanvas();
  HypoTestPlot *plot = new HypoTestPlot(*freqCalcResult, 100, -0.01, 9.51);
  plot->SetLogYaxis(true);
   
  TF1* f = new TF1("f","1*ROOT::Math::chisquared_pdf(2*x,1,0)", 0,20);
  f->SetLineColor(kBlack);
  f->SetLineStyle(7);
  plot->AddTF1(f,"#chi^{2}(2x,1)");
  
  plot->Draw();
  c1->SaveAs("outputObservationSignificance.C");
  c1->SaveAs("outputObservationSignificance.root");
  c1->SaveAs("outputObservationSignificance.pdf");

}

//////////////////////////////////////////////////////////////////////////
// OLD STUFF - could eventually be removed if it happens to be not used
/*
  RooRealVar* mu = (RooRealVar*) mc->GetParametersOfInterest()->first();
  mu->setVal(muVal); // set POI value for generation
  //To avoid effects from boundary and simplify asymptotic comparison, set min=-max
  mu->setMin(-1*mu->getMax()); 

  
  RooRealVar* firstPOI = (RooRealVar*) mc->GetParametersOfInterest()->first();
  ProfileLikelihoodCalculator plc(*data,*mc);
  LikelihoodInterval* interval = plc.GetInterval();
  double plcUpperLimit = interval->UpperLimit(*firstPOI);
  delete interval;

  cout <<"\nGenerating sampling distribution at " << mu->GetName() << " = " << mu->getVal() <<endl;
  int nPOI = mc->GetParametersOfInterest()->getSize();
  if(nPOI>1){
    cout <<"ERROR: more than one POI -> printing and stopping"<<endl;
    mc->GetParametersOfInterest()->Print("v");
    return;
  }
  
  ProfileLikelihoodTestStat ts(*mc->GetPdf());
  //ts.SetOneSidedDiscovery();

  ToyMCSampler sampler(ts,m_nToys);
  sampler.SetPdf(*mc->GetPdf());
  sampler.SetObservables(*mc->GetObservables());
  sampler.SetGlobalObservables(*mc->GetGlobalObservables());
  mu->setVal(muVal); 
  cout << "Printing observables" << endl;
  mc->GetObservables()->Print("v");
  cout << "Printing global observables" << endl;
  mc->GetGlobalObservables()->Print("v");
  if(!mc->GetPdf()->canBeExtended() && (data->numEntries()==1)){
    cout << "tell it to use 1 event"<<endl;
    sampler.SetNEventsPerToy(1);
  }

  cout << "VAL=" << mu->getVal() << endl;
  sampler.SetParametersForTestStat(*mc->GetParametersOfInterest()); // set POI value for evaluation

  RooArgSet allParameters;
  allParameters.add(*mc->GetParametersOfInterest());
  allParameters.add(*mc->GetNuisanceParameters());
  cout << "Printing all parameters" << endl;
  allParameters.Print("v");

  SamplingDistribution* sampDist = sampler.GetSamplingDistribution(allParameters);
  SamplingDistPlot plot;//(100,-0.05,3);
  plot.AddSamplingDistribution(sampDist,"NORMALIZE");
  //plot.AddSamplingDistribution(sampDist);
  //plot.GetTH1F(sampDist)->GetYaxis()->SetTitle(Form("f(-log #lambda(#mu=%.2f) | #mu=%.2f)",muVal,muVal));
  //plot.SetAxisTitle(Form("-log #lambda(#mu=%.2f)",muVal));

  //plot.Draw();
  
  
  //double min = plot.GetTH1F(sampDist)->GetXaxis()->GetXmin();
  //double max = plot.GetTH1F(sampDist)->GetXaxis()->GetXmax();
  //TF1* f = new TF1("f",Form("2*ROOT::Math::chisquared_pdf(2*x,%d,0)",nPOI),min,max);
  //f->SetLineColor(kBlue);
  //f->Draw("same");
  

  
  m_pDistrqMuObs = plot.GetTH1F(sampDist);
  m_pDistrqMuObs->Scale(1/m_pDistrqMuObs->Integral(-1,m_pDistrqMuObs->GetNbinsX()+1));
  RooArgSet* POIs = (RooArgSet*) mc->GetParametersOfInterest();
  m_qMuObs = ts.Evaluate(*data,*POIs);
  cout << "Integral=" << m_pDistrqMuObs->Integral(-1,m_pDistrqMuObs->GetNbinsX()+1) << endl;
  const int bin=m_pDistrqMuObs->FindBin(m_qMuObs);
  const double pval=m_pDistrqMuObs->Integral(bin,m_pDistrqMuObs->GetNbinsX()+1);
  const double zval=sqrt(2.)*TMath::ErfInverse(1-2*pval);
  cout << "qmuobs=" << m_qMuObs << endl;
  cout << "pval=" << pval << endl;
  cout << "zval=" << zval << endl;
  cout << "zval (asymptotic)=" << sqrt(m_qMuObs) << endl;

  TCanvas* c1 = new TCanvas("c1"); 
  c1->SetBottomMargin(0.15);
  c1->SetLeftMargin(0.15);
  m_pDistrqMuObs->GetYaxis()->SetTitle(Form("f(q_{ #mu=%.2f} | #mu=%.2f)",muVal,muVal));
  m_pDistrqMuObs->GetYaxis()->SetTitleSize(0.05);
  m_pDistrqMuObs->GetYaxis()->SetLabelSize(0.05);
  m_pDistrqMuObs->GetYaxis()->SetTitleOffset(1.4);
  m_pDistrqMuObs->GetXaxis()->SetTitle(Form("q_{ #mu=%.2f}",muVal));
  m_pDistrqMuObs->GetXaxis()->SetTitleSize(0.05);
  m_pDistrqMuObs->GetXaxis()->SetLabelSize(0.05);
  m_pDistrqMuObs->GetXaxis()->SetTitleOffset(1.3);
  m_pDistrqMuObs->Draw("hist");

  TArrow* arr = new TArrow(m_qMuObs,0.05,m_qMuObs,0,0.02,"|>");
  arr->SetLineWidth(3);
  arr->SetLineColor(kRed);
  arr->SetFillColor(kRed);
  arr->Draw();
  TLatex latex1;
  latex1.SetTextSize(0.05);
  latex1.SetTextColor(kRed);
  latex1.DrawLatex(m_qMuObs,-0.01,(Form("q_{ #mu=%.2f}^{obs}",muVal)));
*/
//////////////////////////////////////////////////////////////////////////////

