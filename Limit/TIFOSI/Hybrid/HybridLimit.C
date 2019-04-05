#include <stdexcept>

#include "TCanvas.h"

#include "RooWorkspace.h"
#include "RooAbsPdf.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooStats/ModelConfig.h"
#include "RooStats/HybridCalculator.h"
#include "RooStats/ToyMCSampler.h"
#include "RooStats/SimpleLikelihoodRatioTestStat.h"
#include "RooStats/ProfileLikelihoodTestStat.h"
#include "RooStats/HypoTestInverter.h"
#include "RooStats/HypoTestInverterResult.h"
#include "RooStats/HypoTestPlot.h"
#include "RooStats/HypoTestInverterPlot.h"

#include "RooExtendPdf.h"
#include "RooSimultaneous.h"

#include "HybridLimit.h"

using namespace RooFit;
using namespace RooStats;

bool useProof2 = false;
int nworkers2 = 1;

namespace temp{
  void FactorizePdf(const RooArgSet &observables, RooAbsPdf &pdf, RooArgList &obsTerms, RooArgList &constraints) {
    // utility function to factorize constraint terms from a pdf 
    // (from G. Petrucciani)
    const std::type_info & id = typeid(pdf);
    if (id == typeid(RooProdPdf)) {
      RooProdPdf *prod = dynamic_cast<RooProdPdf *>(&pdf);
      RooArgList list(prod->pdfList());
      for (int i = 0, n = list.getSize(); i < n; ++i) {
	RooAbsPdf *pdfi = (RooAbsPdf *) list.at(i);
	temp::FactorizePdf(observables, *pdfi, obsTerms, constraints);
      }
    } else if (id == typeid(RooExtendPdf)) {
      TIterator *iter = pdf.serverIterator(); 
      // extract underlying pdf which is extended; first server is the pdf; second server is the number of events variable
      RooAbsPdf *updf = dynamic_cast<RooAbsPdf *>(iter->Next());
      assert(updf != 0);
      delete iter;
      temp::FactorizePdf(observables, *updf, obsTerms, constraints);
    } else if (id == typeid(RooSimultaneous)) {    //|| id == typeid(RooSimultaneousOpt)) {
      RooSimultaneous *sim  = dynamic_cast<RooSimultaneous *>(&pdf);
      assert(sim != 0);
      RooAbsCategoryLValue *cat = (RooAbsCategoryLValue *) sim->indexCat().Clone();
      for (int ic = 0, nc = cat->numBins((const char *)0); ic < nc; ++ic) {
	cat->setBin(ic);
	temp::FactorizePdf(observables, *sim->getPdf(cat->getLabel()), obsTerms, constraints);
      }
      delete cat;
    } else if (pdf.dependsOn(observables)) {
      if (!obsTerms.contains(pdf)) obsTerms.add(pdf);
    } else {
      if (!constraints.contains(pdf)) constraints.add(pdf);
    }
  }

  RooAbsPdf * MakeNuisancePdf(RooAbsPdf &pdf, const RooArgSet &observables, const char *name) { 
    // make a nuisance pdf by factorizing out all constraint terms in a common pdf 
    RooArgList obsTerms, constraints;
    temp::FactorizePdf(observables, pdf, obsTerms, constraints);
    if(constraints.getSize() == 0) {
      oocoutW((TObject *)0, Eval) << "RooStatsUtils::MakeNuisancePdf - no constraints found on nuisance parameters in the input model" << endl;
      return 0;
    }
    return new RooProdPdf(name,"", constraints);
  }

  RooAbsPdf * MakeNuisancePdf(const RooStats::ModelConfig &model, const char *name) { 
    // make a nuisance pdf by factorizing out all constraint terms in a common pdf
    if (!model.GetPdf() || !model.GetObservables() ) { 
      oocoutE((TObject*)0, InputArguments) << "RooStatsUtils::MakeNuisancePdf - invalid input model: missing pdf and/or observables" << endl;
      return 0;
    }
    return temp::MakeNuisancePdf(*model.GetPdf(), *model.GetObservables(), name);
  }
}

HybridLimit::HybridLimit(RooWorkspace* ws) :
  m_ws(ws),
  m_testStat(HybridLimit::simpleLhoodRatio),
  m_result(0)
{}

double HybridLimit::computeLimit(int npoints, double poimin, double poimax, int ntoys) 
{
  if(!m_ws)
    throw runtime_error("ERROR ! workspace pointer is 0");
  ModelConfig* mc_sb = (ModelConfig*) m_ws->obj("ModelConfig");
  if(!mc_sb) {
    m_ws->Print();
    throw runtime_error("ERROR ! ModelConfig not found, printing workspace");
  }
  RooDataSet* data = (RooDataSet*) m_ws->data("obsData");
  if(!data){
    m_ws->Print();
    throw runtime_error("ERROR ! dataset not found, printing workspace");
  }
  RooAbsData::setDefaultStorageType(RooAbsData::Vector);
  data->convertToVectorStore() ;
  if (!mc_sb->GetSnapshot() ) { 
    cout << "ModelConfig has no snapshot: make one using model poi" << endl;
    mc_sb->SetSnapshot(*mc_sb->GetParametersOfInterest());
  }
  const RooArgSet* POIs = mc_sb->GetParametersOfInterest();
  if(!POIs) 
    throw runtime_error("ERROR ! POIs set not found");
  RooRealVar* mu = (RooRealVar*) POIs->first();
  if(!mu)
    throw runtime_error("ERROR ! parameter of interest not found");
  
  ModelConfig* mc_b = (ModelConfig*) mc_sb->Clone();
  mc_b->SetName(TString(mc_sb->GetName())+TString("_withPoi0"));      
  double oldmu = mu->getVal();
  mu->setVal(0);
  mc_b->SetSnapshot(RooArgSet(*mu));
  mu->setVal(oldmu);

  SimpleLikelihoodRatioTestStat* sLhRatio = new SimpleLikelihoodRatioTestStat(*mc_sb->GetPdf(),*mc_b->GetPdf());
  RooArgSet nullParams(*mc_sb->GetSnapshot());
  if (mc_sb->GetNuisanceParameters()) nullParams.add(*mc_sb->GetNuisanceParameters());
  if (mc_sb->GetSnapshot()) sLhRatio->SetNullParameters(nullParams);
  RooArgSet altParams(*mc_b->GetSnapshot());
  if (mc_b->GetNuisanceParameters()) altParams.add(*mc_b->GetNuisanceParameters());
  if (mc_b->GetSnapshot()) sLhRatio->SetAltParameters(altParams);
  sLhRatio->SetReuseNLL(true);

  ProfileLikelihoodTestStat* pLh = new ProfileLikelihoodTestStat(*mc_sb->GetPdf());
  pLh->SetOneSided(1);
  pLh->SetReuseNLL(true);

  HybridCalculator* hc = new HybridCalculator(*data, *mc_b, *mc_sb);
  hc->SetToys(ntoys,ntoys/2.); 
  RooAbsPdf* nuisPdf = temp::MakeNuisancePdf(*mc_sb,"nuisancePdf_sb");
  hc->ForcePriorNuisanceAlt(*nuisPdf);
  hc->ForcePriorNuisanceNull(*nuisPdf);
  
  TestStatistic* testStat=0; 
  if(m_testStat==HybridLimit::simpleLhoodRatio) testStat=sLhRatio;
  else if(m_testStat==HybridLimit::profLhood) testStat=pLh;
  else
    throw runtime_error("ERROR ! test statistics not defined");

  ToyMCSampler* toymcs = (ToyMCSampler*) hc->GetTestStatSampler();
  toymcs->SetTestStatistic(testStat);
  toymcs->SetGenerateBinned(false);
  toymcs->SetUseMultiGen(false);
  ToyMCSampler::SetAlwaysUseMultiGen(false);

  mc_b->SetGlobalObservables(RooArgSet());
  mc_sb->SetGlobalObservables(RooArgSet());

  RooMsgService::instance().getStream(1).removeTopic(RooFit::NumIntegration);

  HypoTestInverter calc(*hc);
  calc.SetConfidenceLevel(0.95);
  calc.UseCLs(true);
  calc.SetVerbose(true);

  if (useProof2 && nworkers2 > 1) { 
    ProofConfig pc(*m_ws, nworkers2, "", kFALSE);
    toymcs->SetProofConfig(&pc);  
  }
   
  if (npoints > 0) {
    calc.SetFixedScan(npoints,poimin,poimax);
  }
  m_result = calc.GetInterval();
  return m_result->UpperLimit();
}

void HybridLimit::printInterval()
{
  if(!m_result)
    throw runtime_error("ERROR ! HypoTestInverterResult pointer is 0");
  cout << "  Observed limit : " << m_result->UpperLimit() << " +/- " << m_result->UpperLimitEstimatedError() << endl;
  cout << "  Expected limit (median): " << m_result->GetExpectedUpperLimit(0)  << endl;
  cout << "  Expected limit (-1 sig): " << m_result->GetExpectedUpperLimit(-1) << endl;
  cout << "  Expected limit (+1 sig): " << m_result->GetExpectedUpperLimit(1)  << endl;
}

void HybridLimit::makePlots()
{
  TCanvas* c1 = new TCanvas("c1","CL vs mu",400,400); c1->cd();
  HypoTestInverterPlot *plot = new HypoTestInverterPlot("HTI_Result_Plot","mu scan",m_result);
  plot->Draw("CLb 2CL");  // plot all and Clb
  
  TCanvas * c2 = new TCanvas("c2","test stat distrib");
  const int nEntries = m_result->ArraySize();
  c2->Divide(2,TMath::Ceil(nEntries/2));
  for (int i=0; i<nEntries; i++) {
    c2->cd(i+1);
    gPad->SetBottomMargin(0.12);
    SamplingDistPlot * pl = plot->MakeTestStatPlot(i);
    pl->SetLogYaxis(true);
    pl->Draw();
  }
}

