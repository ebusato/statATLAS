

#include "RooWorkspace.h"

using namespace RooFit;
using namespace RooStats;

void PrintModel(const char* infile = "workspaces/4tops_combined_meas_model.root",
		const char* workspaceName = "CHee",
		const char* modelConfigName = "ModelConfig") {
  
  const char* filename = infile;
  
  TFile *file = TFile::Open(filename);
  
  if(!file){
    cout <<"file not found" << endl;
    return;
  } 
  
  // get stuff out of the workspace
  RooWorkspace* w = (RooWorkspace*) file->Get(workspaceName);
  if(!w){
    cout <<"workspace not found" << endl;
    return;
  }
  
  ModelConfig* mc = (ModelConfig*) w->obj(modelConfigName);
  
  if(!mc){
    w->Print();
    cout << "ModelConfig was not found" <<endl;
    return;
  }
  
  mc->Print();
  
  RooAbsPdf* pdf = (RooAbsPdf*) *mc->GetPdf();
  
  //pdf->Print("t");

  //pdf->graphVizTree("model.dot");

}
