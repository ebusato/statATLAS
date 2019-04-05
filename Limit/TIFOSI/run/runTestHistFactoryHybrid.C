///////////////////////////////////////////////////////////
// Usage : 
//  > root -l 'runTestHistFactory.C("ch1.dat")'
//  or
//  > root -l 'runTestHistFactory.C("ch1.dat","ch2.dat")'
//  or
//  > root -l 'runTestHistFactory.C("ch1.dat","ch2.dat","ch3.dat")'
///////////////////////////////////////////////////////////

#include "RooStats/HistFactory/Channel.h"

using namespace RooStats ;
using namespace HistFactory;

void runTestHistFactoryHybrid(const std::string& file1, const std::string& file2="", const std::string& file3="")
{
  gSystem->Load("ModelHistFactory_C");
  gSystem->Load("HybridLimit_C");
  
  modelHistFactory::ModelHistFactory mod;
  //mod.setConstraintType("Gaussian");
  Channel* ch1 = mod.addChannel("ch1",file1);
  if(file2!="")
    Channel* ch2 = mod.addChannel("ch2",file2);
  if(file3!="")
    Channel* ch3 = mod.addChannel("ch3",file3);
  
  mod.printChannel("ch1");
  mod.makeModel();
  mod.printStatUncert();

  HybridLimit hyb(mod.getWorkspace());
  //hyb.setTestStat(HybridLimit::profLhood);
  hyb.computeLimit(4,0,4,1e3);
  hyb.printInterval();
  hyb.makePlots();
}
