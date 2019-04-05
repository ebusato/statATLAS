Compile() {
  gROOT->LoadMacro("Models/Model.C+");
  gROOT->LoadMacro("Models/ModelExtended.C+");
  gROOT->LoadMacro("Models/ModelHistFactory.C+");
  gROOT->LoadMacro("BayesianMCMC/BayesianMCMC.C+");
  gROOT->LoadMacro("Frequentist/Frequentist.C+");
  gROOT->LoadMacro("Significance/ObservationSignificance.C+");
  gROOT->LoadMacro("Asymptotic/runAsymptoticsCLs.C+");
}
