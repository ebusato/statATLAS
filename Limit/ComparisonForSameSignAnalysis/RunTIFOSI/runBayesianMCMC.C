///////////////////////////////////////////////////////////
// Usage : 
//  > root -l 'runBayesianMCMC.C("ch1.dat")'
//  or
//  > root -l 'runBayesianMCMC.C("ch1.dat","ch2.dat")'
//  or
//  > root -l 'runBayesianMCMC.C("ch1.dat","ch2.dat","ch3.dat")'
///////////////////////////////////////////////////////////

double runBayesianMCMC(double upperBound, const std::string& posteriorPdfFile, const std::string& posteriorMuRootFile,
		       const std::string& file1="", 
		       const std::string& file2="", 
		       const std::string& file3="",
		       const std::string& file4="",
		       const std::string& file5=""
		       )
{
  gSystem->Load("Models/Model_C");
  gSystem->Load("BayesianMCMC/BayesianMCMC_C");
  
  model::Model mod(model::Model::normal,4); // polyexpo
  //model::Model mod(model::Model::logN,4); // polyexpo
  //model::Model mod(model::Model::logN,1); // expo
  if(file1!="")
    mod.addChannel("ch1",file1);
  if(file2!="")
    mod.addChannel("ch2",file2);
  if(file3!="")
    mod.addChannel("ch3",file3);
  if(file4!="")
    mod.addChannel("ch4",file4);
  if(file5!="")
    mod.addChannel("ch5",file5);
  
  mod.makeModel();
  mod.printChannel("ch5",1);

  BayesianMCMC bay(mod.getWorkspace());
  //bay.setNumIters(25e5);
  bay.setNumIters(1e5);
  //bay.setPriorPdf(BayesianMCMC::Exponential);
  double limit=bay.computeLimit(upperBound);
  bay.printInterval();
  bay.makePlots(true,posteriorPdfFile.c_str(),false);
  //bay.drawDistrib1D(*(bay.getWS()->var("mu")),true,500);

  if(posteriorMuRootFile!="") {
    TFile* fout = new TFile(posteriorMuRootFile.c_str(),"recreate");
    bay.getMuPosterior()->Write();
    fout->Write();
    fout->Close();
  }
  return limit;
}

