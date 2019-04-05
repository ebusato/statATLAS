#include "runLimit.C"
#include "TStopwatch.h"
#include "pair.h"

std::pair<double, double> run(TString postfix="", bool SR4t0=true, bool SR4t1=true, bool SR4t2=true, bool SR4t3=true, bool SR4t4=true)
{
  gSystem->Load("OpTHyLiC_C");

  TStopwatch w;
  w.Start();

  const int interpExtrap=OTH::mclimit;
  //const int interpExtrap=OTH::polyexpo;
  //const int interpExtrap=OTH::expo;
  //const int interpExtrap=OTH::linear;
  //const int statConstraint=OTH::logN;
  const int statConstraint=OTH::normal;
  //const int statConstraint=OTH::gamma;
  const int nbExp=5e4;
  
  std::string file_SR4t0=SR4t0 ? Form("../Files4topSM_11dec2014/Ht+Lt_700_NbbJets_2/CH.All%s.dat",postfix.Data()) : "";
  std::string file_SR4t1=SR4t1 ? Form("../Files4topSM_11dec2014/Ht+Lt_700_NbbJets_3/CH.All%s.dat",postfix.Data()) : ""; 
  std::string file_SR4t2=SR4t2 ? Form("../Files4topSM_11dec2014/Ht+Lt_700_NbbJets_2_METdown_100/CH.All%s.dat",postfix.Data()) : "";
  std::string file_SR4t3=SR4t3 ? Form("../Files4topSM_11dec2014/Ht+Lt_700_NbbJets_2_METup_100/CH.All%s.dat",postfix.Data()) : "";
  std::string file_SR4t4=SR4t4 ? Form("../Files4topSM_11dec2014/Ht+Lt_700_NbbJets_3_METup_40/CH.All%s.dat",postfix.Data()) : ""; 


  // Expected minus 2 sigma
  Result* expM2 = runLimit(expM2,interpExtrap,statConstraint,nbExp,
			   file_SR4t0,
			   file_SR4t1,
			   file_SR4t2,
			   file_SR4t3,
			   file_SR4t4);

  // Expected minus 1 sigma
  Result* expM1 = runLimit(expM1,interpExtrap,statConstraint,nbExp,
			   file_SR4t0,
			   file_SR4t1,
			   file_SR4t2,
			   file_SR4t3,
			   file_SR4t4);
 
  // Expected median
  Result* expMed = runLimit(expMed,interpExtrap,statConstraint,nbExp,
			    file_SR4t0,
			    file_SR4t1,
			    file_SR4t2,
			    file_SR4t3,
			    file_SR4t4);
 

  // Expected plus 1 sigma
  Result* expP1 = runLimit(expP1,interpExtrap,statConstraint,nbExp,
			   file_SR4t0,
			   file_SR4t1,
			   file_SR4t2,
			   file_SR4t3,
			   file_SR4t4);
 

  // Expected plus 2 sigma
  Result* expP2 = runLimit(expP2,interpExtrap,statConstraint,nbExp,
			   file_SR4t0,
			   file_SR4t1,
			   file_SR4t2,
			   file_SR4t3,
			   file_SR4t4);
  

  // Observed limits (mclimit,normal)
  Result* obs = runLimit(obs,interpExtrap,statConstraint,nbExp,
			 file_SR4t0,
			 file_SR4t1,
			 file_SR4t2,
			 file_SR4t3,
			 file_SR4t4);
 
 

  w.Stop();
  cout << endl;
  cout << "--------------------------------------------------" << endl;
  cout << "                 JOB RESULT                      " << endl;
  cout << endl;
  cout << "expM2: " << expM2->limit << endl;
  cout << "expM1: " << expM1->limit << endl;
  cout << "expMed: " << expMed->limit << endl;
  cout << "expP1: " << expP1->limit << endl;
  cout << "expP2: " << expP2->limit << endl;
  cout << "obs: " << obs->limit << endl;

  cout << "--------------------------------------------------" << endl << endl;

  return std::make_pair(expMed->limit,obs->limit);
}


void run4topsSM(TString postfix="")
{
  // All categories
  std::pair<double, double> res_all = run(postfix);

  std::pair<double, double> res_SR4t0 = run(postfix, true, false, false, false, false);
  std::pair<double, double> res_SR4t1 = run(postfix, false, true, false, false, false);
  std::pair<double, double> res_SR4t2 = run(postfix, false, false, true, false, false);
  std::pair<double, double> res_SR4t3 = run(postfix, false, false, false, true, false);
  std::pair<double, double> res_SR4t4 = run(postfix, false, false, false, false, true);

  cout << "Results: obs and expMed" << endl;
  cout << "SR4t0: " << res_SR4t0.second << ",  " << res_SR4t0.first << endl;
  cout << "SR4t1: " << res_SR4t1.second << ",  " << res_SR4t1.first << endl;
  cout << "SR4t2: " << res_SR4t2.second << ",  " << res_SR4t2.first << endl;
  cout << "SR4t3: " << res_SR4t3.second << ",  " << res_SR4t3.first << endl;
  cout << "SR4t4: " << res_SR4t4.second << ",  " << res_SR4t4.first << endl;
  cout << "All:   " << res_all.second << ",  " << res_all.first << endl;
}
