#include "runBayesianMCMC.C"

double run4topSM(TString postfix, double upperlimit, bool SR4t0=true, bool SR4t1=true, bool SR4t2=true, bool SR4t3=true, bool SR4t4=true)
{
  std::string file_SR4t0=SR4t0 ? Form("../Files4topSM_11dec2014/Ht+Lt_700_NbbJets_2/CH.All%s.dat",postfix.Data()) : "";
  std::string file_SR4t1=SR4t1 ? Form("../Files4topSM_11dec2014/Ht+Lt_700_NbbJets_3/CH.All%s.dat",postfix.Data()) : "";
  std::string file_SR4t2=SR4t2 ? Form("../Files4topSM_11dec2014/Ht+Lt_700_NbbJets_2_METdown_100/CH.All%s.dat",postfix.Data()) : "";
  std::string file_SR4t3=SR4t3 ? Form("../Files4topSM_11dec2014/Ht+Lt_700_NbbJets_2_METup_100/CH.All%s.dat",postfix.Data()) : "";
  std::string file_SR4t4=SR4t4 ? Form("../Files4topSM_11dec2014/Ht+Lt_700_NbbJets_3_METup_40/CH.All%s.dat",postfix.Data()) : "";

  double limit=runBayesianMCMC(upperlimit,Form("posteriors4topSM_polyexpo_normal%s_%d_%d_%d_%d_%d.pdf",postfix.Data(),SR4t0,SR4t1,SR4t2,SR4t3,SR4t4),
			       file_SR4t0,
			       file_SR4t1,
			       file_SR4t2,
			       file_SR4t3,
			       file_SR4t4);
  
  ofstream of(Form("results_4topSM_11dec2014/bayesian_polyexpo_normal%s_%d_%d_%d_%d_%d.txt",postfix.Data(),SR4t0,SR4t1,SR4t2,SR4t3,SR4t4));
  of << "limit=" << limit << endl;
  return limit;
}

void run4topSM()
{
  double limit_obs_all = run4topSM("",400);
  double limit_asimov_all = run4topSM("_ASIMOV",200);

  cout << "Results: obs and expMed" << endl;
  cout << "All channels combined:   " << limit_obs_all << ",  " << limit_asimov_all << endl;
}
