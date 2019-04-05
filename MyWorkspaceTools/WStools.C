#include <iostream>
#include "RooWorkspace.h"

using namespace std;
using namespace RooFit;
using namespace RooStats;

void printConstraint(const char* infile          = "Workspace.root",
		     const char* workspaceName   = "combined",
		     const char* constraintName = "alpha_XS4Constraint") 
{
  TFile *file = TFile::Open(infile);
  if (!file) {
    cerr << "ERROR: file " << infile << " not found -> QUIT" << endl;
    return;
  }
  
  RooWorkspace* w = (RooWorkspace*) file->Get(workspaceName);

  if(!w){
    cerr <<"ERROR: workspace not found -> QUIT" << endl;
    return;
  }
    
  cout << endl << "-----------------------" << endl;
  cout << "Printing Workspace" << endl;
  cout << "-----------------------" << endl;
  w->Print();

  ModelConfig* mc = (ModelConfig*) w->obj("ModelConfig");
  cout << endl << "-----------------------" << endl;
  cout << "Printing ModelConfig" << endl;
  cout << "-----------------------" << endl;
  mc->Print();

  cout << endl << "-----------------------" << endl;
  cout << "Printing PDF" << endl;
  cout << "-----------------------" << endl;
  RooAbsPdf* pdf = w->pdf(constraintName);
  pdf->Print();

  cout << endl << "-----------------------" << endl;
  cout << "Printing PDF variables" << endl;
  cout << "-----------------------" << endl;
  RooArgSet* set = pdf->getVariables();
  set->Print("v");

  cout << endl << "-----------------------" << endl;
  cout << "Drawing PDF" << endl;
  cout << "-----------------------" << endl;
  TString name(constraintName);
  name.ReplaceAll("Constraint","");
  RooRealVar* obs  = set->find(name);
  RooPlot* frame = obs->frame();
  pdf->plotOn(frame);
  frame->Draw();
  
}
    
