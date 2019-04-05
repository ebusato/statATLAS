
#include "runLimit.C"
#include "TStopwatch.h"

void runAllSgluon()
{
  gSystem->Load("Models/Model_C");

  TStopwatch w;
  w.Start();

  const int interpExtrap=4; // 0->linear, 1->expo , 4->polyexpo
  const int statConstraint=model::Model::logN;
  const int nIters=1e6;

  double limit_Sgluon350 = runLimit(interpExtrap,statConstraint,nIters,
				    "DAT/CH_Sgluon350_alladded_STD_END_SELECTION_Cat0_alladded_Yield.dat",
				    "DAT/CH_Sgluon350_alladded_STD_END_SELECTION_Cat1_alladded_Yield.dat",
				    "DAT/CH_Sgluon350_alladded_STD_END_SELECTION_Cat2_alladded_Yield.dat",
				    "DAT/CH_Sgluon350_alladded_STD_END_SELECTION_Cat3_alladded_Yield.dat",
				    "DAT/CH_Sgluon350_alladded_STD_END_SELECTION_Cat4_alladded_Yield.dat",0.04,"outSgluon350.pdf");
  
  double limit_Sgluon400 = runLimit(interpExtrap,statConstraint,nIters,
				   "DAT/CH_Sgluon400_alladded_STD_END_SELECTION_Cat0_alladded_Yield.dat",
				   "DAT/CH_Sgluon400_alladded_STD_END_SELECTION_Cat1_alladded_Yield.dat",
				   "DAT/CH_Sgluon400_alladded_STD_END_SELECTION_Cat2_alladded_Yield.dat",
				   "DAT/CH_Sgluon400_alladded_STD_END_SELECTION_Cat3_alladded_Yield.dat",
				   "DAT/CH_Sgluon400_alladded_STD_END_SELECTION_Cat4_alladded_Yield.dat",0.05,"outSgluon400.pdf");
  
  double limit_Sgluon500 = runLimit(interpExtrap,statConstraint,nIters,
				   "DAT/CH_Sgluon500_alladded_STD_END_SELECTION_Cat0_alladded_Yield.dat",
				   "DAT/CH_Sgluon500_alladded_STD_END_SELECTION_Cat1_alladded_Yield.dat",
				   "DAT/CH_Sgluon500_alladded_STD_END_SELECTION_Cat2_alladded_Yield.dat",
				   "DAT/CH_Sgluon500_alladded_STD_END_SELECTION_Cat3_alladded_Yield.dat",
				   "DAT/CH_Sgluon500_alladded_STD_END_SELECTION_Cat4_alladded_Yield.dat",0.1,"outSgluon500.pdf");

  double limit_Sgluon600 = runLimit(interpExtrap,statConstraint,nIters,
				   "DAT/CH_Sgluon600_alladded_STD_END_SELECTION_Cat0_alladded_Yield.dat",
				   "DAT/CH_Sgluon600_alladded_STD_END_SELECTION_Cat1_alladded_Yield.dat",
				   "DAT/CH_Sgluon600_alladded_STD_END_SELECTION_Cat2_alladded_Yield.dat",
				   "DAT/CH_Sgluon600_alladded_STD_END_SELECTION_Cat3_alladded_Yield.dat",
				   "DAT/CH_Sgluon600_alladded_STD_END_SELECTION_Cat4_alladded_Yield.dat",0.3,"outSgluon600.pdf");
  
  double limit_Sgluon800 = runLimit(interpExtrap,statConstraint,nIters,
				   "DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat0_alladded_Yield.dat",
				   "DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat1_alladded_Yield.dat",
				   "DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat2_alladded_Yield.dat",
				   "DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat3_alladded_Yield.dat",
				   "DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat4_alladded_Yield.dat",2.5,"outSgluon800.pdf");
  
  double limit_Sgluon1000 = runLimit(interpExtrap,statConstraint,nIters,
				    "DAT/CH_Sgluon1000_alladded_STD_END_SELECTION_Cat0_alladded_Yield.dat",
				    "DAT/CH_Sgluon1000_alladded_STD_END_SELECTION_Cat1_alladded_Yield.dat",
				    "DAT/CH_Sgluon1000_alladded_STD_END_SELECTION_Cat2_alladded_Yield.dat",
				    "DAT/CH_Sgluon1000_alladded_STD_END_SELECTION_Cat3_alladded_Yield.dat",
				    "DAT/CH_Sgluon1000_alladded_STD_END_SELECTION_Cat4_alladded_Yield.dat",20,"outSgluon1000.pdf");
  
  double limit_Sgluon1250 = runLimit(interpExtrap,statConstraint,nIters,
				    "DAT/CH_Sgluon1250_alladded_STD_END_SELECTION_Cat0_alladded_Yield.dat",
				    "DAT/CH_Sgluon1250_alladded_STD_END_SELECTION_Cat1_alladded_Yield.dat",
				    "DAT/CH_Sgluon1250_alladded_STD_END_SELECTION_Cat2_alladded_Yield.dat",
				    "DAT/CH_Sgluon1250_alladded_STD_END_SELECTION_Cat3_alladded_Yield.dat",
				    "DAT/CH_Sgluon1250_alladded_STD_END_SELECTION_Cat4_alladded_Yield.dat",400,"outSgluon1250.pdf");
  
  w.Stop();
  cout << endl;
  cout << "--------------------------------------------------" << endl;
  cout << "                 JOB RESULT                      " << endl;
  cout << endl;
  cout << "\\documentclass[a4paper,notitlepage]{article}" << endl;
  cout << "\\begin{document}" << endl;
  cout << "\\begin{table}" << endl;
  cout << "\\begin{center}" << endl;
  cout << "\\caption{Limits for sgluon (total cpu time=" << w.CpuTime() << " sec). Following parameters have been used: No iterations=" << nIters << ", interpolation/extrapolation=" ;
  if(0==interpExtrap) cout << "linear";
  else if(1==interpExtrap) cout << "expo";
  else if(4==interpExtrap) cout << "polyexpo";
  cout << ", stat constraint p.d.f=" ;
  if(model::Model::normal==statConstraint) cout << "normal";
  else if(model::Model::logN==statConstraint) cout << "logN";
  else if(model::Model::gamma==statConstraint) cout << "gamma";
  cout << ".}" << endl;
  cout << "\\begin{tabular}{ | c | c | c | c | c | c | c | c |}" << endl;
  cout << "\\hline" << endl;

  cout << "  & 350 & 400 & 500 & 600 & 800 & 1000 & 1250 \\\\ \\hline" << endl;
  cout << "Bayesian & " 
       << limit_Sgluon350 <<  " & "
       << limit_Sgluon400 <<  " & "
       << limit_Sgluon500 <<  " & "
       << limit_Sgluon600 <<  " & "
       << limit_Sgluon800 <<  " & "
       << limit_Sgluon1000 <<  " & "
       << limit_Sgluon1250 <<  " \\\\ \\hline " << endl;
  cout << "\\end{tabular}" << endl;
  cout << "\\end{center}" << endl;
  cout << "\\end{table}" << endl;
  cout << "\\end{document}" << endl;
  cout << "--------------------------------------------------" << endl << endl;
}

