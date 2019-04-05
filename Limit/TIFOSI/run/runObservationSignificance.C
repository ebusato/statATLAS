///////////////////////////////////////////////////////////
// Usage : 
//  > root -l 'runObservationSignificance.C("ch1.dat")'
//  or
//  > root -l 'runObservationSignificance.C("ch1.dat","ch2.dat")'
//  or
//  > root -l 'runObservationSignificance.C("ch1.dat","ch2.dat","ch3.dat")'
//  ...
///////////////////////////////////////////////////////////

void runObservationSignificance(const std::string& file1, 
				const std::string& file2="", 
				const std::string& file3="",
				const std::string& file4="",
				const std::string& file5=""
				)
{
  //gSystem->Load("Models/ModelExtended_C");
  gSystem->Load("Models/ModelHistFactory_C");
  gSystem->Load("Significance/ObservationSignificance_C");
  
  //modelextended::ModelExtended mod(modelextended::ModelExtended::normal);
  modelHistFactory::ModelHistFactory mod;
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
  //mod.printChannel("ch1");
  mod.makeModel();

  ObservationSignificance signif(mod.getWorkspace());
  //signif.setNworkers(10);
  signif.setNworkers(5);
  signif.setNToys(5e4);
  //signif.setNToys(1e3);
  signif.evaluateSignificance();
}
