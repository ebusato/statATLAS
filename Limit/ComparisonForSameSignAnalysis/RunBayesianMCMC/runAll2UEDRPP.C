
#include "runLimit.C"
#include "TStopwatch.h"

void runAll2UEDRPP()
{
  gSystem->Load("Models/Model_C");

  TStopwatch w;
  w.Start();

  const int interpExtrap=4; // 0->linear, 1->expo , 4->polyexpo
  //const int statConstraint=model::Model::logN;
  const int statConstraint=model::Model::normal;
  //const int nIters=5e5;
  const int nIters=1e6;

  double limit_600 = runLimit(interpExtrap,statConstraint,nIters,
			      "../Files2UEDRPP_4nov2014/600GeV/Opti_highB_highHt_highMET.txt",
			      "../Files2UEDRPP_4nov2014/600GeV/Opti_highB_lowHt.txt",
			      "../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_highMET.txt",
			      "../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_lowMET.txt",
			      "../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_lowHt.txt",
			      0.1,
			      "plots2UEDRPP600.pdf");
  
  double limit_800 = runLimit(interpExtrap,statConstraint,nIters,
			      "../Files2UEDRPP_4nov2014/800GeV/Opti_highB_highHt_highMET.txt",
			      "../Files2UEDRPP_4nov2014/800GeV/Opti_highB_lowHt.txt",
			      "../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_highMET.txt",
			      "../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_lowMET.txt",
			      "../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_lowHt.txt",
			      1,
			      "plots2UEDRPP800.pdf");
  
  double limit_1000 = runLimit(interpExtrap,statConstraint,nIters,
			       "../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_highHt_highMET.txt",
			       "../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_lowHt.txt",
			       "../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_highMET.txt",
			       "../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_lowMET.txt",
			       "../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_lowHt.txt"
			       ,7,
			      "plots2UEDRPP1000.pdf");
  
  double limit_1200 = runLimit(interpExtrap,statConstraint,nIters,
			       "../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_highHt_highMET.txt",
			       "../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_lowHt.txt",
			       "../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_highMET.txt",
			       "../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_lowMET.txt",
			       "../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_lowHt.txt",
			       20,
			      "plots2UEDRPP1200.pdf");
  
  w.Stop();
  cout << endl;
  cout << "--------------------------------------------------" << endl;
  cout << "                 JOB RESULT                      " << endl;
  cout << endl;
  cout << "\\documentclass[a4paper,notitlepage]{article}" << endl;
  cout << "\\begin{document}" << endl;
  cout << "\\begin{table}" << endl;
  cout << "\\begin{center}" << endl;
  cout << "\\caption{Limits for 2UED/RPP (total cpu time=" << w.CpuTime() << " sec). Following parameters have been used: No iterations=" << nIters << ", interpolation/extrapolation=" ;
  if(0==interpExtrap) cout << "linear";
  else if(1==interpExtrap) cout << "expo";
  else if(4==interpExtrap) cout << "polyexpo";
  cout << ", stat constraint p.d.f=" ;
  if(model::Model::normal==statConstraint) cout << "normal";
  else if(model::Model::logN==statConstraint) cout << "logN";
  else if(model::Model::gamma==statConstraint) cout << "gamma";
  cout << ".}" << endl;
  cout << "\\begin{tabular}{ | c | c | c | c | c | }" << endl;
  cout << "\\hline" << endl;
  
  cout << "  & 600 & 800 & 1000 & 1200 \\\\ \\hline" << endl;
  cout << "Bayesian & " 
       << limit_600 <<  " & "
       << limit_800 <<  " & "
       << limit_1000 <<  " & "
       << limit_1200 <<  " \\\\ \\hline " << endl;
  cout << "\\end{tabular}" << endl;
  cout << "\\end{center}" << endl;
  cout << "\\end{table}" << endl;
  cout << "\\end{document}" << endl;
  cout << "--------------------------------------------------" << endl << endl;
}

