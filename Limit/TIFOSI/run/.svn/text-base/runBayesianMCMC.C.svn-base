///////////////////////////////////////////////////////////
// Usage : 
//  > root -l 'runBayesianMCMC.C("ch1.dat")'
//  or
//  > root -l 'runBayesianMCMC.C("ch1.dat","ch2.dat")'
//  or
//  > root -l 'runBayesianMCMC.C("ch1.dat","ch2.dat","ch3.dat")'
///////////////////////////////////////////////////////////

#include "quantiles.C"

void runBayesianMCMC(const std::string& file1, 
		     const std::string& file2="", 
		     const std::string& file3="",
		     const std::string& file4="",
		     const std::string& file5=""
		     )
{
  gSystem->Load("Models/Model_C");
  gSystem->Load("BayesianMCMC/BayesianMCMC_C");
  
  model::Model mod(model::Model::normal,4); // polyexpo
  //model::Model mod(model::Model::normal,1); // expo
  mod.addChannel("ch1",file1);
  if(file2!="")
    mod.addChannel("ch2",file2);
  if(file3!="")
    mod.addChannel("ch3",file3);
  if(file4!="")
    mod.addChannel("ch4",file4);
  if(file5!="")
    mod.addChannel("ch5",file5);
  
  mod.printChannel("ch1",1);
  mod.makeModel();

  BayesianMCMC bay(mod.getWorkspace());
  bay.setNumIters(1e7);
  //bay.setPriorPdf(BayesianMCMC::Exponential);
  //bay.setSeed(1);
  bay.computeLimit(3);
  bay.printInterval();
  //bay.saveMeanStdDevVsIterationToFile("fileMeanStdDevVsIteration");
  //bay.makePlots(true,"posteriorDistribs.pdf");
  bay.drawDistrib1D(*(bay.getWS()->var("mu")),true,500);

  TH1F* hMuPosterior = bay.getMuPosterior();
  hMuPosterior->Scale(1/hMuPosterior->Integral());

  TCanvas* cMu = new TCanvas("cMu","cMu",400,400);
			     
  hMuPosterior->Draw();

  computeQuantiles(hMuPosterior,true);
}
