///////////////////////////////////////////////////////////
// Usage : 
//  > root -l 'runFrequentist.C("ch1.dat")'
//  or
//  > root -l 'runFrequentist.C("ch1.dat","ch2.dat")'
//  or
//  > root -l 'runFrequentist.C("ch1.dat","ch2.dat","ch3.dat")'
///////////////////////////////////////////////////////////

#include "RooStats/HistFactory/Channel.h"

using namespace RooStats ;
using namespace HistFactory;

void runFrequentist(const std::string& file1, 
		    const std::string& file2="", 
		    const std::string& file3="",
		    const std::string& file4="",
		    const std::string& file5=""
		    )
{
  gSystem->Load("Models/ModelHistFactory_C");
  gSystem->Load("Frequentist/Frequentist_C");
 
  modelHistFactory::ModelHistFactory mod;
  //mod.setConstraintType("Gaussian");
  Channel* ch1 = mod.addChannel("ch1",file1);
  if(file2!="")
    Channel* ch2 = mod.addChannel("ch2",file2);
  if(file3!="")
    Channel* ch3 = mod.addChannel("ch3",file3);
  if(file4!="")
    Channel* ch4 = mod.addChannel("ch4",file4);
  if(file5!="")
    Channel* ch5 = mod.addChannel("ch5",file5);
  mod.printChannel("ch1");
  mod.makeModel();

  Frequentist fre(mod.getWorkspace());
  fre.setNworkers(5);
  //fre.computeLimit(20,1,20,50000); // 1000 GeV
  fre.computeLimit(20,0,3,50000); // 800 GeV
  fre.makePlots();
  fre.printInterval();
}
