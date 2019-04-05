///////////////////////////////////////////////////////////
// Usage : 
//  > root -l 'runTest.C("ch1.dat")'
//  or
//  > root -l 'runLimit.C("ch1.dat","ch2.dat")'
//  or
//  > root -l 'runLimit.C("ch1.dat","ch2.dat","ch3.dat")'
///////////////////////////////////////////////////////////

double runLimit(const int interpExtrap,
		const int statConstraint,
		const int nIters,
		const std::string& file1, 
		const std::string& file2="", 
		const std::string& file3="",
		const std::string& file4="",
		const std::string& file5="",
		const double muMax=1,
		const std::string outFile="")
{
  gSystem->Load("Models/Model_C");
  gSystem->Load("BayesianMCMC/BayesianMCMC_C");
  
  model::Model mod(statConstraint,interpExtrap);
  mod.addChannel("ch1",file1);
  if(file2!="")
    mod.addChannel("ch2",file2);
  if(file3!="")
    mod.addChannel("ch3",file3);
  if(file4!="")
    mod.addChannel("ch4",file4);
  if(file5!="")
    mod.addChannel("ch5",file5);
  
  //mod.printChannel("ch1",1);
  mod.makeModel();

  BayesianMCMC bay(mod.getWorkspace());
  //bay.setAutoMuMax();
  bay.setNumIters(nIters);
  
  double limit=bay.computeLimit(muMax);
  bay.printInterval();
  bay.makePlots(true,outFile);
  return limit;
}
