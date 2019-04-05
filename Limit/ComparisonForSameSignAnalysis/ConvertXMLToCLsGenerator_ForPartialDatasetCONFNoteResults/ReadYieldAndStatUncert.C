#include <iostream>
#include "TString.h"
#include "TFile.h"
#include "TH1F.h"

using namespace std;

void usage()
{
  cout << "see code !" << endl;
}

int main(int nargs, char** args)
{
  TString file("");
  TString histo("");
  bool onlyYield(false);

  for (int i=1; i<nargs; ++i) {
    std::string argyo(args[i]);
    if(argyo=="-help") {usage(); exit(0);}
    else if(argyo=="-i") file=(TString) args[i+1];
    else if(argyo=="-h") histo=(TString) args[i+1];
    else if(argyo=="-onlyYield") onlyYield=true;
  }
  
  TFile* f = new TFile(file,"read");
  if(!f) {
    cout << "ERROR, file not found" << endl;
    return 0;
  }
  TH1F* h=(TH1F*) f->Get(histo);
  if(!h) {
    cout << "ERROR, histo not found" << endl;
    return 0;
  }

  double yield=h->GetBinContent(1);  
  cout << yield ;
  if(!onlyYield) {
    double statUncert=h->GetBinError(1);
    cout << "  " << statUncert << endl;
  }

  return 0;
}
