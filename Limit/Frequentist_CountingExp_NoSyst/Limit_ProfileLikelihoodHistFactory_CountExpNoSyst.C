
#include "TFile.h"
#include "RooWorkspace.h"
#include "RooAbsPdf.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooStats/ModelConfig.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TApplication.h"

#include "RooStats/HybridCalculator.h"
#include "RooStats/FrequentistCalculator.h"
#include "RooStats/ToyMCSampler.h"
#include "RooStats/HypoTestPlot.h"

#include "RooStats/NumEventsTestStat.h"
#include "RooStats/ProfileLikelihoodTestStat.h"
#include "RooStats/SimpleLikelihoodRatioTestStat.h"
#include "RooStats/RatioOfProfiledLikelihoodsTestStat.h"
#include "RooStats/MaxLikelihoodEstimateTestStat.h"

#include "RooStats/HypoTestInverter.h"
#include "RooStats/HypoTestInverterResult.h"
#include "RooStats/HypoTestInverterPlot.h"

#include "RooStats/HistFactory/Measurement.h"
#include "RooStats/HistFactory/HistoToWorkspaceFactoryFast.h"

using namespace RooFit;
using namespace RooStats;
using namespace HistFactory;

bool plotHypoTestResult = true; 
bool useProof = true;
bool optimize = false;
int nworkers = 4;


HypoTestInverterResult * RunInverter(RooWorkspace * w, const char * modelSBName, const char * dataName,
                                     int npoints, double poimin, double poimax, int ntoys );

// This method has been adapted from StandardFrequentistCLsDemo.C
void StandardFrequentistCLs(RooWorkspace* w = NULL,
			    const char * modelSBName = "ModelConfig",
			    const char * dataName = "asimovData",                 
			    int npoints = 10,   
			    double poimin = 0,  
			    double poimax = 50, 
			    int ntoys=3000 )    
{
  HypoTestInverterResult *r = NULL;

  if (w != NULL) {
    r = RunInverter(w, modelSBName, dataName, npoints, poimin, poimax,  ntoys);    
    if (!r) { 
      std::cerr<<"Error running the HypoTestInverter - Exit "<<std::endl;
      return;          
    }
  }
  else 
    { 
      std::cerr<<"Error: workspace not found - Exit"<<std::endl;
      return;
    }		
  
  
   double upperLimit = r->UpperLimit();
   double ulError = r->UpperLimitEstimatedError();

   std::cout << "The computed upper limit is: " << upperLimit << " +/- " << ulError << std::endl;
 
   const int nEntries = r->ArraySize();

   const char *  typeName = "Frequentist";
   const char * resultName = (w) ? w->GetName() : r->GetName();
   TString plotTitle = TString::Format("%s CL Scan for workspace %s",typeName,resultName);
   plotTitle="";
   HypoTestInverterPlot *plot = new HypoTestInverterPlot("HTI_Result_Plot",plotTitle,r);
   plot->Draw("CLb 2CL");  // plot all and Clb

   if (plotHypoTestResult) { 
      TCanvas * c2 = new TCanvas();
      c2->Divide( 2, TMath::Ceil(nEntries/2));
      for (int i=0; i<nEntries; i++) {
         c2->cd(i+1);
         SamplingDistPlot * pl = plot->MakeTestStatPlot(i);
         pl->SetLogYaxis(true);
         pl->Draw();
      }
   }


   std::cout << " expected limit (median) " <<  r->GetExpectedUpperLimit(0) << std::endl;
   std::cout << " expected limit (-1 sig) " << r->GetExpectedUpperLimit(-1) << std::endl;
   std::cout << " expected limit (+1 sig) " << r->GetExpectedUpperLimit(1) << std::endl;
}


// internal routine to run the inverter
HypoTestInverterResult *  RunInverter(RooWorkspace * w, const char * modelSBName, 
                                      const char * dataName, 
                                      int npoints, double poimin, double poimax, 
                                      int ntoys) 
{

   std::cout << "Running HypoTestInverter on the workspace " << w->GetName() << std::endl;

   w->Print();

   const char* modelBName;

   RooAbsData * data = w->data(dataName); 
   if (!data) { 
      Error("StandardHypoTestDemo","Not existing data %s",dataName);
      return 0;
   }
   else 
      std::cout << "Using data set " << dataName << std::endl;

   
   // get models from WS
   // get the modelConfig out of the file
   ModelConfig* bModel = NULL;
   ModelConfig* sbModel = (ModelConfig*) w->obj(modelSBName);

   if (!sbModel) {
      Error("StandardHypoTestDemo","Not existing ModelConfig %s",modelSBName);
      return 0;
   }
   // check the model 
   if (!sbModel->GetPdf()) { 
      Error("StandardHypoTestDemo","Model %s has no pdf ",modelSBName);
      return 0;
   }
   if (!sbModel->GetParametersOfInterest()) {
      Error("StandardHypoTestDemo","Model %s has no poi ",modelSBName);
      return 0;
   }
   if (!sbModel->GetParametersOfInterest()) {
      Error("StandardHypoTestInvDemo","Model %s has no poi ",modelSBName);
      return 0;
   }
   if (!sbModel->GetSnapshot() ) { 
      Info("StandardHypoTestInvDemo","Model %s has no snapshot  - make one using model poi",modelSBName);
      sbModel->SetSnapshot( *sbModel->GetParametersOfInterest() );
   }


   if (!bModel || bModel == sbModel) {
      Info("StandardHypoTestInvDemo","The background model does not exist");
      Info("StandardHypoTestInvDemo","Copy it from ModelConfig %s and set POI to zero",modelSBName);
      bModel = (ModelConfig*) sbModel->Clone();
      bModel->SetName(TString(modelSBName)+TString("_with_poi_0"));      
      RooRealVar * var = dynamic_cast<RooRealVar*>(bModel->GetParametersOfInterest()->first());
      if (!var) return 0;
      double oldval = var->getVal();
      var->setVal(0);
      bModel->SetSnapshot( RooArgSet(*var)  );
      var->setVal(oldval);
   }
   else { 
      if (!bModel->GetSnapshot() ) { 
         Info("StandardHypoTestInvDemo","Model %s has no snapshot  - make one using model poi and 0 values ",modelBName);
         RooRealVar * var = dynamic_cast<RooRealVar*>(bModel->GetParametersOfInterest()->first());
         if (var) { 
            double oldval = var->getVal();
            var->setVal(0);
            bModel->SetSnapshot( RooArgSet(*var)  );
            var->setVal(oldval);
         }
         else { 
            Error("StandardHypoTestInvDemo","Model %s has no valid poi",modelBName);
            return 0;
         }         
      }
   }
   
   ProfileLikelihoodTestStat profll(*sbModel->GetPdf());
   profll.SetOneSided(1);
   if (optimize) profll.SetReuseNLL(true);

   TestStatistic * testStat = &profll;
  
   FrequentistCalculator* hc = new FrequentistCalculator(*data, *bModel, *sbModel);

   ToyMCSampler *toymcs = (ToyMCSampler*)hc->GetTestStatSampler();
   toymcs->SetTestStatistic(testStat);

   hc->SetToys(ntoys,ntoys); 

   // Get the result
   RooMsgService::instance().getStream(1).removeTopic(RooFit::NumIntegration);


   TStopwatch tw; tw.Start(); 
   const RooArgSet * poiSet = sbModel->GetParametersOfInterest();
   RooRealVar *poi = (RooRealVar*)poiSet->first();

   // fit the data first
   sbModel->GetPdf()->fitTo(*data);
   double poihat  = poi->getVal();

   HypoTestInverter calc(*hc);
   calc.SetConfidenceLevel(0.95);

   calc.UseCLs(true);
   calc.SetVerbose(true);

   // can speed up using proof-lite
   if (useProof && nworkers > 1) { 
      ProofConfig pc(*w, nworkers, "", kFALSE);
      toymcs->SetProofConfig(&pc);    // enable proof
   }

   
   if (npoints > 0) {
      if (poimin >= poimax) { 
         // if no min/max given scan between MLE and +4 sigma 
         poimin = int(poihat);
         poimax = int(poihat +  4 * poi->getError());
      }
      std::cout << "Doing a fixed scan  in interval : " << poimin << " , " << poimax << std::endl;
      calc.SetFixedScan(npoints,poimin,poimax);
   }
   else { 
      //poi->setMax(10*int( (poihat+ 10 *poi->getError() )/10 ) );
      std::cout << "Doing an  automatic scan  in interval : " << poi->getMin() << " , " << poi->getMax() << std::endl;
   }

   HypoTestInverterResult * r = calc.GetInterval();
   tw.Stop(); 
   tw.Print();

   return r; 
}

// My method building the workspace with the histfactory model and calling StandardFrequentistCLs
void Limit(double Nbckg, double Nsig)
{
  int i=2; char* s[2] = {"",""};
  TApplication TheApp("TheApplication",&i,s);
  TheApp.SetReturnFromRun(true);

  //TFile* file = new TFile("workspaces/myfile.root","recreate");

  ////////////////////////////////
  // Create measurement
  ////////////////////////////////

  Measurement meas("meas","meas");

  meas.SetOutputFilePrefix("myWorkspace");
  meas.SetPOI("SigXsecOverSM");
  meas.SetLumi(1.0);
  //meas.SetLumiRelErr(0.034);

  ///////////////////////////////
  // Create single channel 
  ///////////////////////////////

  Channel ch("ch");
  ch.SetData(Nbckg);
  //ch.SetStatErrorConfig(0.05, "Poisson");

  Sample sig("sig");
  sig.SetValue(Nsig);
  sig.AddNormFactor("SigXsecOverSM", 1, 0, 70);

  Sample background("background");
  background.SetValue(Nbckg);

  ch.AddSample(sig);
  ch.AddSample(background);

  meas.AddChannel(ch);

  HistoToWorkspaceFactoryFast HTWF(meas);

  RooWorkspace* workspace = HTWF.MakeSingleChannelModel(meas,ch);

  //workspace->Write();
  //file->Write();
  //file->Close();
  
  //Result* res = StandardTestStatDistributionDemo(4,"workspaces/myfile.root","ch");

  StandardFrequentistCLs(workspace,"ModelConfig","asimovData",10,20,50);

  TheApp.Run();
}

int main()
{

  Limit(4.97,0.149);

  //Limit(15,0.5);

  return 0;
}
