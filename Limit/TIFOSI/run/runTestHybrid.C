///////////////////////////////////////////////////////////
// Usage : 
//  > root -l 'runTestHybrid.C("ch1.dat")'
//  or
//  > root -l 'runTestHybrid.C("ch1.dat","ch2.dat")'
//  or
//  > root -l 'runTestHybrid.C("ch1.dat","ch2.dat","ch3.dat")'
///////////////////////////////////////////////////////////

void runTestHybrid(const std::string& file1, const std::string& file2="", const std::string& file3="")
{
  //gSystem->Load("Models/ModelExtended_C");
  gSystem->Load("Models/ModelHistFactory_C");
  gSystem->Load("Hybrid/HybridLimit_C");
  
  modelHistFactory::ModelHistFactory mod;
  //modelextended::ModelExtended mod(modelextended::ModelExtended::normal);
  mod.addChannel("ch1",file1);
  if(file2!="")
    mod.addChannel("ch2",file2);
  if(file3!="")
    mod.addChannel("ch3",file3);
  
  //mod.printChannel("ch1",1);
  //mod.makeModel("workspaces/model_ws.root");
  mod.printChannel("ch1");
  mod.makeModel();

  HybridLimit hyb(mod.getWorkspace());
  hyb.computeLimit();//4,0,10,1e3);
  hyb.printInterval();
  hyb.makePlots();
}
