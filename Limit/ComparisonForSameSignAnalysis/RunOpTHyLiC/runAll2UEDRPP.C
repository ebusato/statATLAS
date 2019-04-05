///////////////////////////////////////////
//usage : 
//  root -l load.C runAll2UEDRPP.C
///////////////////////////////////////////

#if defined EXECUTABLE || defined __CLING__
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#include <TROOT.h>
#include <TSystem.h>
#include <TStopwatch.h>
#include <TApplication.h>
#include <TString.h>
#include "OpTHyLiC.h"

using namespace std;
using namespace OTH;

#endif

#include "runLimit.C"
#include "TStopwatch.h"

void runAll2UEDRPP(TString postfix="")
{
  //gSystem->Load("OpTHyLiC_C");

  TStopwatch w;
  w.Start();

  //const OTH::SystType interpExtrap=OTH::SystMclimit;
  const OTH::SystType interpExtrap=OTH::SystPolyexpo;
  //const OTH::SystType interpExtrap=OTH::SystLinear;
  //const OTH::StatType statConstraint=OTH::StatLogN;
  //const OTH::StatType statConstraint=OTH::StatNormal;
  //const OTH::StatType statConstraint=OTH::StatGammaHyper;
  const OTH::StatType statConstraint=OTH::StatGammaUni;
  //const int randomEngine=OTH::TR3;
  const int randomEngine=OTH::STD_mt19937;
  const int nbExp=5e4;
  
  // Expected minus 2 sigma
  Result* expM2_600 = runLimit(OTH::LimExpectedM2sig,interpExtrap,statConstraint,randomEngine,nbExp,
			       Form("../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/600GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/600GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));

  Result* expM2_800 = runLimit(OTH::LimExpectedM2sig,interpExtrap,statConstraint,randomEngine,nbExp,
			       Form("../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/800GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/800GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));

  Result* expM2_1000 = runLimit(OTH::LimExpectedM2sig,interpExtrap,statConstraint,randomEngine,nbExp,
				Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));

  Result* expM2_1200 = runLimit(OTH::LimExpectedM2sig,interpExtrap,statConstraint,randomEngine,nbExp,
				Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));
  
  // Expected minus 1 sigma
  Result* expM1_600 = runLimit(OTH::LimExpectedM1sig,interpExtrap,statConstraint,randomEngine,nbExp,
			       Form("../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/600GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/600GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));  

  Result* expM1_800 = runLimit(OTH::LimExpectedM1sig,interpExtrap,statConstraint,randomEngine,nbExp,
			       Form("../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/800GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/800GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));

  Result* expM1_1000 = runLimit(OTH::LimExpectedM1sig,interpExtrap,statConstraint,randomEngine,nbExp,
				Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));
  
  Result* expM1_1200 = runLimit(OTH::LimExpectedM1sig,interpExtrap,statConstraint,randomEngine,nbExp,
				Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));

  // Expected median
  Result* expMed_600 = runLimit(OTH::LimExpectedMed,interpExtrap,statConstraint,randomEngine,nbExp,
				Form("../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/600GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/600GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));	

  Result* expMed_800 = runLimit(OTH::LimExpectedMed,interpExtrap,statConstraint,randomEngine,nbExp,
				Form("../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/800GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/800GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));

  Result* expMed_1000 = runLimit(OTH::LimExpectedMed,interpExtrap,statConstraint,randomEngine,nbExp,
				 Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
				 Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
				 Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
				 Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
				 Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));

  Result* expMed_1200 = runLimit(OTH::LimExpectedMed,interpExtrap,statConstraint,randomEngine,nbExp,
				 Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
				 Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
				 Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
				 Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
				 Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));

  // Expected plus 1 sigma
  Result* expP1_600 = runLimit(OTH::LimExpectedP1sig,interpExtrap,statConstraint,randomEngine,nbExp,
			       Form("../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/600GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/600GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));

  Result* expP1_800 = runLimit(OTH::LimExpectedP1sig,interpExtrap,statConstraint,randomEngine,nbExp,
			       Form("../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/800GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/800GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));

  Result* expP1_1000 = runLimit(OTH::LimExpectedP1sig,interpExtrap,statConstraint,randomEngine,nbExp,
				Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));

  Result* expP1_1200 = runLimit(OTH::LimExpectedP1sig,interpExtrap,statConstraint,randomEngine,nbExp,
				Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));

  // Expected plus 2 sigma
  Result* expP2_600 = runLimit(OTH::LimExpectedP2sig,interpExtrap,statConstraint,randomEngine,nbExp,
			       Form("../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/600GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/600GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));

  Result* expP2_800 = runLimit(OTH::LimExpectedP2sig,interpExtrap,statConstraint,randomEngine,nbExp,
			       Form("../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/800GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
			       Form("../Files2UEDRPP_4nov2014/800GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));

  Result* expP2_1000 = runLimit(OTH::LimExpectedP2sig,interpExtrap,statConstraint,randomEngine,nbExp,
				Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));

  Result* expP2_1200 = runLimit(OTH::LimExpectedP2sig,interpExtrap,statConstraint,randomEngine,nbExp,
				Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
				Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));

  // Observed limits (mclimit,normal)
  Result* obs_600 = runLimit(OTH::LimObserved,interpExtrap,statConstraint,randomEngine,nbExp,
			     Form("../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
			     Form("../Files2UEDRPP_4nov2014/600GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
			     Form("../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
			     Form("../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
			     Form("../Files2UEDRPP_4nov2014/600GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));

  Result* obs_800 = runLimit(OTH::LimObserved,interpExtrap,statConstraint,randomEngine,nbExp,
			     Form("../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
			     Form("../Files2UEDRPP_4nov2014/800GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
			     Form("../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
			     Form("../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
			     Form("../Files2UEDRPP_4nov2014/800GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));

  Result* obs_1000 = runLimit(OTH::LimObserved,interpExtrap,statConstraint,randomEngine,nbExp,
			      Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
			      Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
			      Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
			      Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
			      Form("../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));
				
  Result* obs_1200 = runLimit(OTH::LimObserved,interpExtrap,statConstraint,randomEngine,nbExp,
			      Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
			      Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
			      Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
			      Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
			      Form("../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));

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
  if(OTH::SystMclimit==interpExtrap) cout << "mclimit";
  else if(OTH::SystLinear==interpExtrap) cout << "linear";
  else if(OTH::SystExpo==interpExtrap) cout << "expo";
  else if(OTH::SystPolyexpo==interpExtrap) cout << "polyexpo";
  cout << ", stat constraint p.d.f=" ;
  if(OTH::StatNormal==statConstraint) cout << "normal";
  else if(OTH::StatLogN==statConstraint) cout << "logN";
  else if(OTH::StatGammaHyper==statConstraint) cout << "gammahyper";
  else if(OTH::StatGammaUni==statConstraint) cout << "gammauni";
  else if(OTH::StatGammaJeffreys==statConstraint) cout << "gammajeffreys";
  cout << ".}" << endl;
  cout << "\\begin{tabular}{ | c | c | c | c | c | }" << endl;
  cout << "\\hline" << endl;
  cout << "  & 600 & 800 & 1000 & 1200  \\\\ \\hline" << endl;
  cout << "-2$\\sigma$ &"
       << expM2_600->limit << " & " 
       << expM2_800->limit << " & " 
       << expM2_1000->limit << " & " 
       << expM2_1200->limit << " \\\\ \\hline " 
       << endl;
  cout << "-1$\\sigma$ &"
       << expM1_600->limit << " & " 
       << expM1_800->limit << " & " 
       << expM1_1000->limit << " & " 
       << expM1_1200->limit << " \\\\ \\hline " 
       << endl;

  cout << "median &"
       << expMed_600->limit << " & " 
       << expMed_800->limit << " & " 
       << expMed_1000->limit << " & " 
       << expMed_1200->limit << " \\\\ \\hline " 
       << endl;
  cout << "+1$\\sigma$ &"
       << expP1_600->limit << " & " 
       << expP1_800->limit << " & " 
       << expP1_1000->limit << " & " 
       << expP1_1200->limit << " \\\\ \\hline " 
       << endl;
  cout << "+2$\\sigma$ &"
       << expP2_600->limit << " & " 
       << expP2_800->limit << " & " 
       << expP2_1000->limit << " & " 
       << expP2_1200->limit << " \\\\ \\hline " 
       << endl;
  cout << "observed &"
       << obs_600->limit << " & " 
       << obs_800->limit << " & " 
       << obs_1000->limit << " & " 
       << obs_1200->limit << " \\\\ \\hline " 
       << endl;
  cout << "\\end{tabular}" << endl;
  cout << "\\end{center}" << endl;
  cout << "\\end{table}" << endl;
  cout << "\\end{document}" << endl;
  cout << "--------------------------------------------------" << endl << endl;
}

