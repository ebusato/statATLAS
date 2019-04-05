#include "AtlasStyle.C"

void SetStyle()
{
   TStyle* atlasStyle = AtlasStyle();
   gROOT->SetStyle("ATLAS");
   gROOT->ForceStyle();
}

void runExclusionPlot()
{
  SetStyle();

  gSystem->Load("ExclusionPlot_C");

  LimitExpsObs limits350("350GeV",350);
  Limit limits350ExpM2(Limit::expM2,1);
  Limit limits350ExpM1(Limit::expM1,2);
  Limit limits350ExpMed(Limit::expMed,3);
  Limit limits350ExpP1(Limit::expP1,4);
  Limit limits350ExpP2(Limit::expP2,5);
  Limit limits350Obs(Limit::obs,4.5);
  limits350.add(limits350ExpM2);
  limits350.add(limits350ExpM1);
  limits350.add(limits350ExpMed);
  limits350.add(limits350ExpP1);
  limits350.add(limits350ExpP2);
  limits350.add(limits350Obs);

  LimitExpsObs limits400("400GeV",400);
  Limit limits400ExpM2(Limit::expM2,2);
  Limit limits400ExpM1(Limit::expM1,3);
  Limit limits400ExpMed(Limit::expMed,4);
  Limit limits400ExpP1(Limit::expP1,5);
  Limit limits400ExpP2(Limit::expP2,6);
  Limit limits400Obs(Limit::obs,5);
  limits400.add(limits400ExpM2);
  limits400.add(limits400ExpM1);
  limits400.add(limits400ExpMed);
  limits400.add(limits400ExpP1);
  limits400.add(limits400ExpP2);
  limits400.add(limits400Obs);

  LimitBrasilPlot limitBrasil("CLsGen_mclimit_normal");
  limitBrasil.readFile("input.txt");
  //limitBrasil.add(limits350);
  //limitBrasil.add(limits400);
  limitBrasil.print();
  limitBrasil.makePlot();
  
}
