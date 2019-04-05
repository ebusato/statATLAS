///////////////////////////////////////////////////////////
// Usage : 
//  > root -l 'runBayesianMCMCExtended.C("ch1.dat")'
//  or
//  > root -l 'runBayesianMCMCExtended.C("ch1.dat","ch2.dat")'
//  or
//  > root -l 'runBayesianMCMCExtended.C("ch1.dat","ch2.dat","ch3.dat")'
///////////////////////////////////////////////////////////


void runBayesianMCMCExtended(const std::string& file1, const std::string& file2="", const std::string& file3="")
{
  gSystem->Load("Models/ModelExtended_C");
  gSystem->Load("BayesianMCMC/BayesianMCMC_C");
  
  modelextended::ModelExtended mod(modelextended::ModelExtended::normal);
  mod.addChannel("ch1",file1);
  if(file2!="")
    mod.addChannel("ch2",file2);
  if(file3!="")
    mod.addChannel("ch3",file3);
  
  mod.printChannel("ch1",1);
  mod.makeModel();

  BayesianMCMC bay(mod.getWorkspace());
  bay.computeLimit();
  bay.printInterval();
  bay.makePlots();
}
