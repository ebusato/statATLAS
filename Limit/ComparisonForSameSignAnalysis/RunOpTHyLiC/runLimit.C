///////////////////////////////////////////////////////////
// Usage : 
//  > root -l 'runLimit.C(type,"ch1.dat")'
//  or
//  > root -l 'runLimit.C(type,"ch1.dat","ch2.dat")'
//  or
//  > root -l 'runLimit.C(type,"ch1.dat","ch2.dat","ch3.dat")'
///////////////////////////////////////////////////////////

#include "OpTHyLiC.h"
#include "TStopwatch.h"

using namespace OTH;

class Result {
public:
  int NpseudoExp;
  double limit;
  double cpuTime;
  std::string interpExtrap;
  std::string statConstraint;

  inline double diffWrtMcLimit(double mclimitVal) {return (limit-mclimitVal)/mclimitVal;}
};

//enum {expM2,expM1,expMed,expP1,expP2,obs};
Result* runLimit(const OTH::LimitType type,
		 const OTH::SystType interpExtrap,
		 const OTH::StatType statConstraint,
		 const int randomEngine,
		 const int nbExp,
		 const std::string& file1="", 
		 const std::string& file2="", 
		 const std::string& file3="", 
		 const std::string& file4="", 
		 const std::string& file5="") {
  TStopwatch w;
  w.Start();

  //gSystem->Load("OpTHyLiC_C");
  OpTHyLiC oth(interpExtrap,statConstraint,randomEngine);

  if(file1!="")
    oth.addChannel("ch1",file1);
  if(file2!="")
    oth.addChannel("ch2",file2);
  if(file3!="")
    oth.addChannel("ch3",file3);
  if(file4!="")
    oth.addChannel("ch4",file4);
  if(file5!="")
    oth.addChannel("ch5",file5);

  //oth.printSamples();

  double cls;
  double limit=0;
  limit=oth.sigStrengthExclusion(type,nbExp,cls);
  /*
  if(type==expM2)
    limit=oth.sigStrengthExclusion(OTH::LimExpectedM2sig,nbExp,cls);
  else if(type==expM1)
    limit=oth.sigStrengthExclusion(OTH::LimExpectedM1sig,nbExp,cls);
  else if(type==expMed)
    limit=oth.sigStrengthExclusion(OTH::LimExpectedMed,nbExp,cls);
  else if(type==expP1)
    limit=oth.sigStrengthExclusion(OTH::LimExpectedP1sig,nbExp,cls);
  else if(type==expP2)
    limit=oth.sigStrengthExclusion(OTH::LimExpectedP2sig,nbExp,cls);
  else if(type==obs)
    limit=oth.sigStrengthExclusion(OTH::LimObserved,nbExp,cls);
  */
  w.Stop(); 
  
  cout << "Result:" << endl;
  cout << "  -> limit="   << limit << endl;  
  cout << "  -> CPU time=" << w.CpuTime() << endl;

  Result* res = new Result();
  res->NpseudoExp=nbExp;
  res->limit=limit;
  res->cpuTime=w.CpuTime();
  if(OTH::SystMclimit==interpExtrap) res->interpExtrap="mclimit";
  else if(OTH::SystLinear==interpExtrap) res->interpExtrap="linear";
  else if(OTH::SystPolyexpo==interpExtrap) res->interpExtrap="polyexpo";
  else if(OTH::SystExpo==interpExtrap) res->interpExtrap="expo";
  if(OTH::StatNormal==statConstraint) res->statConstraint="normal";
  else if(OTH::StatLogN==statConstraint) res->statConstraint="logN";
  else if(OTH::StatGammaHyper==statConstraint) res->statConstraint="gammahyper";
  else if(OTH::StatGammaUni==statConstraint) res->statConstraint="gammauni";
  else if(OTH::StatGammaJeffreys==statConstraint) res->statConstraint="gammajeffreys";
  return res;
}
