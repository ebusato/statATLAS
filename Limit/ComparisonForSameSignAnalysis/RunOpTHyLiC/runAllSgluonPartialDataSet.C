#include "runLimit.C"
#include "TStopwatch.h"

void runAllSgluonPartialDataSet()
{
  gSystem->Load("OpTHyLiC_C");

  TStopwatch w;
  w.Start();

  //const int interpExtrap=OpTHyLiC::mclimit;
  //const int interpExtrap=OpTHyLiC::polyexpo;
  const int interpExtrap=OpTHyLiC::linear;
  //const int statConstraint=OpTHyLiC::logN;
  //const int statConstraint=OpTHyLiC::normal;
  const int statConstraint=OpTHyLiC::gamma;
  const int nbExp=5e4;
  
  // Expected minus 2 sigma
  Result* expM2_350 = runLimit(expM2,interpExtrap,statConstraint,nbExp,
			       "DAT/CH_Sgluon350_ee.dat",
			       "DAT/CH_Sgluon350_em.dat",
			       "DAT/CH_Sgluon350_mm.dat");

  Result* expM2_400 = runLimit(expM2,interpExtrap,statConstraint,nbExp,
			       "DAT/CH_Sgluon400_ee.dat",
			       "DAT/CH_Sgluon400_em.dat",
			       "DAT/CH_Sgluon400_mm.dat");

  Result* expM2_500 = runLimit(expM2,interpExtrap,statConstraint,nbExp,
			       "DAT/CH_Sgluon500_ee.dat",
			       "DAT/CH_Sgluon500_em.dat",
			       "DAT/CH_Sgluon500_mm.dat");

  Result* expM2_600 = runLimit(expM2,interpExtrap,statConstraint,nbExp,
			       "DAT/CH_Sgluon600_ee.dat",
			       "DAT/CH_Sgluon600_em.dat",
			       "DAT/CH_Sgluon600_mm.dat");

  Result* expM2_800 = runLimit(expM2,interpExtrap,statConstraint,nbExp,
			       "DAT/CH_Sgluon800_ee.dat",
			       "DAT/CH_Sgluon800_em.dat",
			       "DAT/CH_Sgluon800_mm.dat");

  Result* expM2_1000 = runLimit(expM2,interpExtrap,statConstraint,nbExp,
				"DAT/CH_Sgluon1000_ee.dat",
				"DAT/CH_Sgluon1000_em.dat",
				"DAT/CH_Sgluon1000_mm.dat");
  
  // Expected minus 1 sigma
  Result* expM1_350 = runLimit(expM1,interpExtrap,statConstraint,nbExp,
			       "DAT/CH_Sgluon350_ee.dat",
			       "DAT/CH_Sgluon350_em.dat",
			       "DAT/CH_Sgluon350_mm.dat");

  Result* expM1_400 = runLimit(expM1,interpExtrap,statConstraint,nbExp,
			       "DAT/CH_Sgluon400_ee.dat",
			       "DAT/CH_Sgluon400_em.dat",
			       "DAT/CH_Sgluon400_mm.dat");

  Result* expM1_500 = runLimit(expM1,interpExtrap,statConstraint,nbExp,
			       "DAT/CH_Sgluon500_ee.dat",
			       "DAT/CH_Sgluon500_em.dat",
			       "DAT/CH_Sgluon500_mm.dat");

  Result* expM1_600 = runLimit(expM1,interpExtrap,statConstraint,nbExp,
			       "DAT/CH_Sgluon600_ee.dat",
			       "DAT/CH_Sgluon600_em.dat",
			       "DAT/CH_Sgluon600_mm.dat");

  Result* expM1_800 = runLimit(expM1,interpExtrap,statConstraint,nbExp,
			       "DAT/CH_Sgluon800_ee.dat",
			       "DAT/CH_Sgluon800_em.dat",
			       "DAT/CH_Sgluon800_mm.dat");

  Result* expM1_1000 = runLimit(expM1,interpExtrap,statConstraint,nbExp,
				"DAT/CH_Sgluon1000_ee.dat",
				"DAT/CH_Sgluon1000_em.dat",
				"DAT/CH_Sgluon1000_mm.dat");
  
  // Expected median
  Result* expMed_350 = runLimit(expMed,interpExtrap,statConstraint,nbExp,
				"DAT/CH_Sgluon350_ee.dat",
				"DAT/CH_Sgluon350_em.dat",
				"DAT/CH_Sgluon350_mm.dat");

  Result* expMed_400 = runLimit(expMed,interpExtrap,statConstraint,nbExp,
				"DAT/CH_Sgluon400_ee.dat",
				"DAT/CH_Sgluon400_em.dat",
				"DAT/CH_Sgluon400_mm.dat");

  Result* expMed_500 = runLimit(expMed,interpExtrap,statConstraint,nbExp,
				"DAT/CH_Sgluon500_ee.dat",
				"DAT/CH_Sgluon500_em.dat",
				"DAT/CH_Sgluon500_mm.dat");

  Result* expMed_600 = runLimit(expMed,interpExtrap,statConstraint,nbExp,
				"DAT/CH_Sgluon600_ee.dat",
				"DAT/CH_Sgluon600_em.dat",
				"DAT/CH_Sgluon600_mm.dat");

  Result* expMed_800 = runLimit(expMed,interpExtrap,statConstraint,nbExp,
				"DAT/CH_Sgluon800_ee.dat",
				"DAT/CH_Sgluon800_em.dat",
				"DAT/CH_Sgluon800_mm.dat");

  Result* expMed_1000 = runLimit(expMed,interpExtrap,statConstraint,nbExp,
				 "DAT/CH_Sgluon1000_ee.dat",
				 "DAT/CH_Sgluon1000_em.dat",
				 "DAT/CH_Sgluon1000_mm.dat");
  
  // Expected plus 1 sigma
  Result* expP1_350 = runLimit(expP1,interpExtrap,statConstraint,nbExp,
			       "DAT/CH_Sgluon350_ee.dat",
			       "DAT/CH_Sgluon350_em.dat",
			       "DAT/CH_Sgluon350_mm.dat");

  Result* expP1_400 = runLimit(expP1,interpExtrap,statConstraint,nbExp,
			       "DAT/CH_Sgluon400_ee.dat",
			       "DAT/CH_Sgluon400_em.dat",
			       "DAT/CH_Sgluon400_mm.dat");

  Result* expP1_500 = runLimit(expP1,interpExtrap,statConstraint,nbExp,
			       "DAT/CH_Sgluon500_ee.dat",
			       "DAT/CH_Sgluon500_em.dat",
			       "DAT/CH_Sgluon500_mm.dat");

  Result* expP1_600 = runLimit(expP1,interpExtrap,statConstraint,nbExp,
			       "DAT/CH_Sgluon600_ee.dat",
			       "DAT/CH_Sgluon600_em.dat",
			       "DAT/CH_Sgluon600_mm.dat");

  Result* expP1_800 = runLimit(expP1,interpExtrap,statConstraint,nbExp,
			       "DAT/CH_Sgluon800_ee.dat",
			       "DAT/CH_Sgluon800_em.dat",
			       "DAT/CH_Sgluon800_mm.dat");

  Result* expP1_1000 = runLimit(expP1,interpExtrap,statConstraint,nbExp,
				"DAT/CH_Sgluon1000_ee.dat",
				"DAT/CH_Sgluon1000_em.dat",
				"DAT/CH_Sgluon1000_mm.dat");
  
  // Expected plus 2 sigma
  Result* expP2_350 = runLimit(expP2,interpExtrap,statConstraint,nbExp,
			       "DAT/CH_Sgluon350_ee.dat",
			       "DAT/CH_Sgluon350_em.dat",
			       "DAT/CH_Sgluon350_mm.dat");

  Result* expP2_400 = runLimit(expP2,interpExtrap,statConstraint,nbExp,
			       "DAT/CH_Sgluon400_ee.dat",
			       "DAT/CH_Sgluon400_em.dat",
			       "DAT/CH_Sgluon400_mm.dat");

  Result* expP2_500 = runLimit(expP2,interpExtrap,statConstraint,nbExp,
			       "DAT/CH_Sgluon500_ee.dat",
			       "DAT/CH_Sgluon500_em.dat",
			       "DAT/CH_Sgluon500_mm.dat");

  Result* expP2_600 = runLimit(expP2,interpExtrap,statConstraint,nbExp,
			       "DAT/CH_Sgluon600_ee.dat",
			       "DAT/CH_Sgluon600_em.dat",
			       "DAT/CH_Sgluon600_mm.dat");

  Result* expP2_800 = runLimit(expP2,interpExtrap,statConstraint,nbExp,
			       "DAT/CH_Sgluon800_ee.dat",
			       "DAT/CH_Sgluon800_em.dat",
			       "DAT/CH_Sgluon800_mm.dat");

  Result* expP2_1000 = runLimit(expP2,interpExtrap,statConstraint,nbExp,
				"DAT/CH_Sgluon1000_ee.dat",
				"DAT/CH_Sgluon1000_em.dat",
				"DAT/CH_Sgluon1000_mm.dat");
  
  // Observed limits (mclimit,normal)
  Result* obs_350 = runLimit(obs,interpExtrap,statConstraint,nbExp,
			     "DAT/CH_Sgluon350_ee.dat",
			     "DAT/CH_Sgluon350_em.dat",
			     "DAT/CH_Sgluon350_mm.dat");

  Result* obs_400 = runLimit(obs,interpExtrap,statConstraint,nbExp,
			     "DAT/CH_Sgluon400_ee.dat",
			     "DAT/CH_Sgluon400_em.dat",
			     "DAT/CH_Sgluon400_mm.dat");

  Result* obs_500 = runLimit(obs,interpExtrap,statConstraint,nbExp,
			     "DAT/CH_Sgluon500_ee.dat",
			     "DAT/CH_Sgluon500_em.dat",
			     "DAT/CH_Sgluon500_mm.dat");

  Result* obs_600 = runLimit(obs,interpExtrap,statConstraint,nbExp,
			     "DAT/CH_Sgluon600_ee.dat",
			     "DAT/CH_Sgluon600_em.dat",
			     "DAT/CH_Sgluon600_mm.dat");

  Result* obs_800 = runLimit(obs,interpExtrap,statConstraint,nbExp,
			     "DAT/CH_Sgluon800_ee.dat",
			     "DAT/CH_Sgluon800_em.dat",
			     "DAT/CH_Sgluon800_mm.dat");

  Result* obs_1000 = runLimit(obs,interpExtrap,statConstraint,nbExp,
			      "DAT/CH_Sgluon1000_ee.dat",
			      "DAT/CH_Sgluon1000_em.dat",
			      "DAT/CH_Sgluon1000_mm.dat");

  w.Stop();
  cout << endl;
  cout << "--------------------------------------------------" << endl;
  cout << "                 JOB RESULT                      " << endl;
  cout << endl;
  cout << "\\documentclass[a4paper,notitlepage]{article}" << endl;
  cout << "\\begin{document}" << endl;
  cout << "\\begin{table}" << endl;
  cout << "\\begin{center}" << endl;
  cout << "\\caption{Limits for sgluon (total cpu time=" << w.CpuTime() << " sec, total real time=" << w.RealTime() << " sec). Following parameters have been used: No pseudo exp.=" << nbExp << ", interpolation/extrapolation=" ;
  if(OTH::mclimit==interpExtrap) cout << "mclimit";
  else if(OTH::linear==interpExtrap) cout << "linear";
  else if(OTH::expo==interpExtrap) cout << "expo";
  else if(OTH::polyexpo==interpExtrap) cout << "polyexpo";
  cout << ", stat constraint p.d.f=" ;
  if(OpTHyLiC::normal==statConstraint) cout << "normal";
  else if(OTH::logN==statConstraint) cout << "logN";
  else if(OTH::gamma==statConstraint) cout << "gamma";
  cout << ".}" << endl;
  cout << "\\begin{tabular}{ | c | c | c | c | c | c | c | }" << endl;
  cout << "\\hline" << endl;
  cout << "  & 350 & 400 & 500 & 600 & 800 & 1000  \\\\ \\hline" << endl;
  cout << "-2$\\sigma$ &"
       << expM2_350->limit << " & " 
       << expM2_400->limit << " & " 
       << expM2_500->limit << " & " 
       << expM2_600->limit << " & " 
       << expM2_800->limit << " & " 
       << expM2_1000->limit << " \\\\ \\hline " 
       << endl;
  cout << "-1$\\sigma$ &"
       << expM1_350->limit << " & " 
       << expM1_400->limit << " & " 
       << expM1_500->limit << " & " 
       << expM1_600->limit << " & " 
       << expM1_800->limit << " & " 
       << expM1_1000->limit << " \\\\ \\hline " 
       << endl;

  cout << "median &"
       << expMed_350->limit << " & " 
       << expMed_400->limit << " & " 
       << expMed_500->limit << " & " 
       << expMed_600->limit << " & " 
       << expMed_800->limit << " & " 
       << expMed_1000->limit << " \\\\ \\hline " 
       << endl;
  cout << "+1$\\sigma$ &"
       << expP1_350->limit << " & " 
       << expP1_400->limit << " & " 
       << expP1_500->limit << " & " 
       << expP1_600->limit << " & " 
       << expP1_800->limit << " & " 
       << expP1_1000->limit << " \\\\ \\hline " 
       << endl;
  cout << "+2$\\sigma$ &"
       << expP2_350->limit << " & " 
       << expP2_400->limit << " & " 
       << expP2_500->limit << " & " 
       << expP2_600->limit << " & " 
       << expP2_800->limit << " & " 
       << expP2_1000->limit << " \\\\ \\hline " 
       << endl;
  
  cout << "observed &"
       << obs_350->limit << " & " 
       << obs_400->limit << " & " 
       << obs_500->limit << " & " 
       << obs_600->limit << " & " 
       << obs_800->limit << " & " 
       << obs_1000->limit << " \\\\ \\hline " 
       << endl;
  cout << "\\end{tabular}" << endl;
  cout << "\\end{center}" << endl;
  cout << "\\end{table}" << endl;
  cout << "\\end{document}" << endl;
  cout << "--------------------------------------------------" << endl << endl;
}

