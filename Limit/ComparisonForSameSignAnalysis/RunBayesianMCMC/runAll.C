
#include "runTest.C"
#include "runTestHistFactory.C"

void runAll_AllCats()
{
  double limit_Sgluon350 = runTest("DAT/CH_Sgluon350_alladded_STD_END_SELECTION_Cat0_alladded_Yield_WITHDATASIMOV.dat",
					      "DAT/CH_Sgluon350_alladded_STD_END_SELECTION_Cat1_alladded_Yield_WITHDATASIMOV.dat",
					      "DAT/CH_Sgluon350_alladded_STD_END_SELECTION_Cat2_alladded_Yield_WITHDATASIMOV.dat",
					      "DAT/CH_Sgluon350_alladded_STD_END_SELECTION_Cat3_alladded_Yield_WITHDATASIMOV.dat",
					      "DAT/CH_Sgluon350_alladded_STD_END_SELECTION_Cat4_alladded_Yield_WITHDATASIMOV.dat",0.01);
 
   double limit_Sgluon400 = runTest("DAT/CH_Sgluon400_alladded_STD_END_SELECTION_Cat0_alladded_Yield_WITHDATASIMOV.dat",
					      "DAT/CH_Sgluon400_alladded_STD_END_SELECTION_Cat1_alladded_Yield_WITHDATASIMOV.dat",
					      "DAT/CH_Sgluon400_alladded_STD_END_SELECTION_Cat2_alladded_Yield_WITHDATASIMOV.dat",
					      "DAT/CH_Sgluon400_alladded_STD_END_SELECTION_Cat3_alladded_Yield_WITHDATASIMOV.dat",
					      "DAT/CH_Sgluon400_alladded_STD_END_SELECTION_Cat4_alladded_Yield_WITHDATASIMOV.dat",0.03);

  double limit_Sgluon500 = runTest("DAT/CH_Sgluon500_alladded_STD_END_SELECTION_Cat0_alladded_Yield_WITHDATASIMOV.dat",
					      "DAT/CH_Sgluon500_alladded_STD_END_SELECTION_Cat1_alladded_Yield_WITHDATASIMOV.dat",
					      "DAT/CH_Sgluon500_alladded_STD_END_SELECTION_Cat2_alladded_Yield_WITHDATASIMOV.dat",
					      "DAT/CH_Sgluon500_alladded_STD_END_SELECTION_Cat3_alladded_Yield_WITHDATASIMOV.dat",
					      "DAT/CH_Sgluon500_alladded_STD_END_SELECTION_Cat4_alladded_Yield_WITHDATASIMOV.dat",0.08);

  double limit_Sgluon600 = runTest("DAT/CH_Sgluon600_alladded_STD_END_SELECTION_Cat0_alladded_Yield_WITHDATASIMOV.dat",
					      "DAT/CH_Sgluon600_alladded_STD_END_SELECTION_Cat1_alladded_Yield_WITHDATASIMOV.dat",
					      "DAT/CH_Sgluon600_alladded_STD_END_SELECTION_Cat2_alladded_Yield_WITHDATASIMOV.dat",
					      "DAT/CH_Sgluon600_alladded_STD_END_SELECTION_Cat3_alladded_Yield_WITHDATASIMOV.dat",
					      "DAT/CH_Sgluon600_alladded_STD_END_SELECTION_Cat4_alladded_Yield_WITHDATASIMOV.dat",0.1);
  
  double limit_Sgluon800 = runTest("DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat0_alladded_Yield_WITHDATASIMOV.dat",
					      "DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat1_alladded_Yield_WITHDATASIMOV.dat",
					      "DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat2_alladded_Yield_WITHDATASIMOV.dat",
					      "DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat3_alladded_Yield_WITHDATASIMOV.dat",
					      "DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat4_alladded_Yield_WITHDATASIMOV.dat",1);
  
  double limit_Sgluon1000 = runTest("DAT/CH_Sgluon1000_alladded_STD_END_SELECTION_Cat0_alladded_Yield_WITHDATASIMOV.dat",
					       "DAT/CH_Sgluon1000_alladded_STD_END_SELECTION_Cat1_alladded_Yield_WITHDATASIMOV.dat",
					       "DAT/CH_Sgluon1000_alladded_STD_END_SELECTION_Cat2_alladded_Yield_WITHDATASIMOV.dat",
					       "DAT/CH_Sgluon1000_alladded_STD_END_SELECTION_Cat3_alladded_Yield_WITHDATASIMOV.dat",
					       "DAT/CH_Sgluon1000_alladded_STD_END_SELECTION_Cat4_alladded_Yield_WITHDATASIMOV.dat",7);
  
  double limit_Sgluon1250 = runTest("DAT/CH_Sgluon1250_alladded_STD_END_SELECTION_Cat0_alladded_Yield_WITHDATASIMOV.dat",
					       "DAT/CH_Sgluon1250_alladded_STD_END_SELECTION_Cat1_alladded_Yield_WITHDATASIMOV.dat",
					       "DAT/CH_Sgluon1250_alladded_STD_END_SELECTION_Cat2_alladded_Yield_WITHDATASIMOV.dat",
					       "DAT/CH_Sgluon1250_alladded_STD_END_SELECTION_Cat3_alladded_Yield_WITHDATASIMOV.dat",
					       "DAT/CH_Sgluon1250_alladded_STD_END_SELECTION_Cat4_alladded_Yield_WITHDATASIMOV.dat",20);

  cout << "  & 350 & 400 & 500 & 600 & 800 & 1000 & 1250 \\\\ \\hline" << endl;
  cout << "Bayesian & " 
       << limit_Sgluon350 <<  " & "
       << limit_Sgluon400 <<  " & "
       << limit_Sgluon500 <<  " & "
       << limit_Sgluon600 <<  " & "
       << limit_Sgluon800 <<  " & "
       << limit_Sgluon1000 <<  " & "
       << limit_Sgluon1250 <<  " \\\\ \\hline " << endl;
}

void run800_CatPerCat()
{
  double limit_Sgluon800_Cat0_nouncert = runTest("DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat0_alladded_Yield_WITHDATASIMOV_NOUNCERT.dat","","","","",80);
  double limit_Sgluon800_Cat1_nouncert = runTest("DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat1_alladded_Yield_WITHDATASIMOV_NOUNCERT.dat","","","","",30);
  double limit_Sgluon800_Cat2_nouncert = runTest("DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat2_alladded_Yield_WITHDATASIMOV_NOUNCERT.dat","","","","",7);
  double limit_Sgluon800_Cat3_nouncert = runTest("DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat3_alladded_Yield_WITHDATASIMOV_NOUNCERT.dat","","","","",3);
  double limit_Sgluon800_Cat4_nouncert = runTest("DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat4_alladded_Yield_WITHDATASIMOV_NOUNCERT.dat","","","","",2);
  double limit_Sgluon800_AllCats_nouncert = runTest("DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat0_alladded_Yield_WITHDATASIMOV_NOUNCERT.dat","DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat1_alladded_Yield_WITHDATASIMOV_NOUNCERT.dat","DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat2_alladded_Yield_WITHDATASIMOV_NOUNCERT.dat","DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat3_alladded_Yield_WITHDATASIMOV_NOUNCERT.dat","DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat4_alladded_Yield_WITHDATASIMOV_NOUNCERT.dat");

  double limit_Sgluon800_Cat0 = runTest("DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat0_alladded_Yield_WITHDATASIMOV.dat","","","","",80);
  double limit_Sgluon800_Cat1 = runTest("DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat1_alladded_Yield_WITHDATASIMOV.dat","","","","",30);
  double limit_Sgluon800_Cat2 = runTest("DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat2_alladded_Yield_WITHDATASIMOV.dat","","","","",7);
  double limit_Sgluon800_Cat3 = runTest("DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat3_alladded_Yield_WITHDATASIMOV.dat","","","","",3);
  double limit_Sgluon800_Cat4 = runTest("DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat4_alladded_Yield_WITHDATASIMOV.dat","","","","",2);
  double limit_Sgluon800_AllCats = runTest("DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat0_alladded_Yield_WITHDATASIMOV.dat","DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat1_alladded_Yield_WITHDATASIMOV.dat","DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat2_alladded_Yield_WITHDATASIMOV.dat","DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat3_alladded_Yield_WITHDATASIMOV.dat","DAT/CH_Sgluon800_alladded_STD_END_SELECTION_Cat4_alladded_Yield_WITHDATASIMOV.dat");

  cout << "Limits for Sgluon800: " << endl;
  cout << "  -> cat0 (no uncerts): " << limit_Sgluon800_Cat0_nouncert << endl;
  cout << "  -> cat1 (no uncerts): " << limit_Sgluon800_Cat1_nouncert << endl;
  cout << "  -> cat2 (no uncerts): " << limit_Sgluon800_Cat2_nouncert << endl;
  cout << "  -> cat3 (no uncerts): " << limit_Sgluon800_Cat3_nouncert << endl;
  cout << "  -> cat4 (no uncerts): " << limit_Sgluon800_Cat4_nouncert << endl;
  cout << "  -> all cats (no uncerts): " << limit_Sgluon800_AllCats_nouncert << endl;
  cout << "  -> cat0: " << limit_Sgluon800_Cat0 << endl;
  cout << "  -> cat1: " << limit_Sgluon800_Cat1 << endl;
  cout << "  -> cat2: " << limit_Sgluon800_Cat2 << endl;
  cout << "  -> cat3: " << limit_Sgluon800_Cat3 << endl;
  cout << "  -> cat4: " << limit_Sgluon800_Cat4 << endl;
  cout << "  -> all cats: " << limit_Sgluon800_AllCats << endl;
}

void runAll()
{
  runAll_AllCats();
  //run800_CatPerCat();
}
