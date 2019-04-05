#include "runBayesianMCMC.C"

void runAll2UEDRPP(TString postfix, double upperlimit600, double upperlimit800, double upperlimit1000, double upperlimit1200)
{
  double limit600=runBayesianMCMC(upperlimit600,
				  Form("results_2UEDRPP_4nov2014/posteriors600%s.pdf",postfix.Data()),
				  Form("results_2UEDRPP_4nov2014/posteriorMu600%s.root",postfix.Data()),
				  Form("DAT/600GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
				  Form("DAT/600GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
				  Form("DAT/600GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
				  Form("DAT/600GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
				  Form("DAT/600GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));

  double limit800=runBayesianMCMC(upperlimit800,
				  Form("results_2UEDRPP_4nov2014/posteriors800%s.pdf",postfix.Data()),
				  Form("results_2UEDRPP_4nov2014/posteriorMu800%s.root",postfix.Data()),
				  Form("DAT/800GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
				  Form("DAT/800GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
				  Form("DAT/800GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
				  Form("DAT/800GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
				  Form("DAT/800GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));

  double limit1000=runBayesianMCMC(upperlimit1000,
				   Form("results_2UEDRPP_4nov2014/posteriors1000%s.pdf",postfix.Data()),
				   Form("results_2UEDRPP_4nov2014/posteriorMu1000%s.root",postfix.Data()),
				   Form("DAT/1000GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
				   Form("DAT/1000GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
				   Form("DAT/1000GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
				   Form("DAT/1000GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
				   Form("DAT/1000GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));

  double limit1200=runBayesianMCMC(upperlimit1200,
				   Form("results_2UEDRPP_4nov2014/posteriors1200%s.pdf",postfix.Data()),
				   Form("results_2UEDRPP_4nov2014/posteriorMu1200%s.root",postfix.Data()),
				   Form("DAT/1200GeV/Opti_lowB_lowHt%s.txt",postfix.Data()),
				   Form("DAT/1200GeV/Opti_highB_lowHt%s.txt",postfix.Data()),
				   Form("DAT/1200GeV/Opti_lowB_highHt_lowMET%s.txt",postfix.Data()),
				   Form("DAT/1200GeV/Opti_lowB_highHt_highMET%s.txt",postfix.Data()),
				   Form("DAT/1200GeV/Opti_highB_highHt_highMET%s.txt",postfix.Data()));

  ofstream of(Form("results_2UEDRPP_4nov2014/bayesian_polyexpo_normal%s.txt",postfix.Data()));
  of << "  & 600 & 800 & 1000 & 1200  \\\\ \\hline" << endl;
  of << "observed &"
     << limit600 << " & " 
     << limit800 << " & " 
     << limit1000 << " & " 
     << limit1200 << " \\\\ \\hline " 
     << endl;
}

void runAll2UEDRPP()
{
  runAll2UEDRPP("",0.08,0.5,10,30);
  runAll2UEDRPP("_ASIMOV",0.03,0.25,3,25);
  //runAll2UEDRPP("_ASIMOVMedian",0.03,0.25,3,25);
}
