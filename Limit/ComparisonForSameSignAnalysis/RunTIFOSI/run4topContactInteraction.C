#include "runBayesianMCMC.C"

double run4topContactInteraction(TString postfix, double upperlimit, bool SR4t0=true, bool SR4t1=true, bool SR4t2=true, bool SR4t3=true, bool SR4t4=true)
{
  std::string file_SR4t0=SR4t0 ? Form("../Files4topContactInt_11dec2014/Ht+Lt_700_NbbJets_2/CH.All%s.dat",postfix.Data()) : "";
  std::string file_SR4t1=SR4t1 ? Form("../Files4topContactInt_11dec2014/Ht+Lt_700_NbbJets_3/CH.All%s.dat",postfix.Data()) : "";
  std::string file_SR4t2=SR4t2 ? Form("../Files4topContactInt_11dec2014/Ht+Lt_700_NbbJets_2_METdown_100/CH.All%s.dat",postfix.Data()) : "";
  std::string file_SR4t3=SR4t3 ? Form("../Files4topContactInt_11dec2014/Ht+Lt_700_NbbJets_2_METup_100/CH.All%s.dat",postfix.Data()) : "";
  std::string file_SR4t4=SR4t4 ? Form("../Files4topContactInt_11dec2014/Ht+Lt_700_NbbJets_3_METup_40/CH.All%s.dat",postfix.Data()) : "";

  double limit=runBayesianMCMC(upperlimit,Form("posteriors4topContactInteraction_polyexpo_normal%s_%d_%d_%d_%d_%d.pdf",postfix.Data(),SR4t0,SR4t1,SR4t2,SR4t3,SR4t4),
			       file_SR4t0,
			       file_SR4t1,
			       file_SR4t2,
			       file_SR4t3,
			       file_SR4t4);
  
  ofstream of(Form("results_4topContactInteraction_11dec2014/bayesian_polyexpo_normal%s_%d_%d_%d_%d_%d.txt",postfix.Data(),SR4t0,SR4t1,SR4t2,SR4t3,SR4t4));
  of << "limit=" << limit << endl;
  return limit;
}

void run4topContactInteraction()
{/*
  double limit_obs_all = run4topContactInteraction("_NOSIGUNCERT",3);
  double limit_obs_SR4t0 = run4topContactInteraction("_NOSIGUNCERT",50,true,false,false,false,false);
  double limit_obs_SR4t1 = run4topContactInteraction("_NOSIGUNCERT",18,false,true,false,false,false);
  double limit_obs_SR4t2 = run4topContactInteraction("_NOSIGUNCERT",11,false,false,true,false,false);
  double limit_obs_SR4t3 = run4topContactInteraction("_NOSIGUNCERT",8,false,false,false,true,false);
  double limit_obs_SR4t4 = run4topContactInteraction("_NOSIGUNCERT",3,false,false,false,false,true);

  double limit_asimov_all = run4topContactInteraction("_ASIMOV_NOSIGUNCERT",1.2);
  double limit_asimov_SR4t0 = run4topContactInteraction("_ASIMOV_NOSIGUNCERT",25,true,false,false,false,false);
  double limit_asimov_SR4t1 = run4topContactInteraction("_ASIMOV_NOSIGUNCERT",10,false,true,false,false,false);
  double limit_asimov_SR4t2 = run4topContactInteraction("_ASIMOV_NOSIGUNCERT",6,false,false,true,false,false);
  double limit_asimov_SR4t3 = run4topContactInteraction("_ASIMOV_NOSIGUNCERT",8,false,false,false,true,false);
  double limit_asimov_SR4t4 = run4topContactInteraction("_ASIMOV_NOSIGUNCERT",1.5,false,false,false,false,true);
 */
  double limit_obs_all = run4topContactInteraction("",3);
  double limit_obs_SR4t0 = run4topContactInteraction("",50,true,false,false,false,false);
  double limit_obs_SR4t1 = run4topContactInteraction("",18,false,true,false,false,false);
  double limit_obs_SR4t2 = run4topContactInteraction("",11,false,false,true,false,false);
  double limit_obs_SR4t3 = run4topContactInteraction("",8,false,false,false,true,false);
  double limit_obs_SR4t4 = run4topContactInteraction("",3,false,false,false,false,true);

  double limit_asimov_all = run4topContactInteraction("_ASIMOV",1.2);
  double limit_asimov_SR4t0 = run4topContactInteraction("_ASIMOV",25,true,false,false,false,false);
  double limit_asimov_SR4t1 = run4topContactInteraction("_ASIMOV",10,false,true,false,false,false);
  double limit_asimov_SR4t2 = run4topContactInteraction("_ASIMOV",6,false,false,true,false,false);
  double limit_asimov_SR4t3 = run4topContactInteraction("_ASIMOV",8,false,false,false,true,false);
  double limit_asimov_SR4t4 = run4topContactInteraction("_ASIMOV",1.5,false,false,false,false,true);
  
  cout << "Results: obs and expMed" << endl;
  cout << "SR4t0: " << limit_obs_SR4t0 << ",  " << limit_asimov_SR4t0 << endl;
  cout << "SR4t1: " << limit_obs_SR4t1 << ",  " << limit_asimov_SR4t1 << endl;
  cout << "SR4t2: " << limit_obs_SR4t2 << ",  " << limit_asimov_SR4t2 << endl;
  cout << "SR4t3: " << limit_obs_SR4t3 << ",  " << limit_asimov_SR4t3 << endl;
  cout << "SR4t4: " << limit_obs_SR4t4 << ",  " << limit_asimov_SR4t4 << endl;
  cout << "All:   " << limit_obs_all << ",  " << limit_asimov_all << endl;
}
