#include <fstream>
#include <sstream>
#include <map>

#include "TString.h"
#include "TTree.h"
#include "Model.h"
#include "RooRealVar.h"
#include "RooArgSet.h"
#include "RooDataSet.h"
#include "RooWorkspace.h"
#include "RooPoisson.h"
#include "RooSimultaneous.h"
#include "RooCategory.h"
#include "RooStats/HistFactory/FlexibleInterpVar.h"
#include "RooStats/ModelConfig.h"

using namespace std;
using namespace RooFit;
using namespace RooStats ;
using namespace HistFactory;
using namespace model;

Syst::Syst(const string& name, const double up, const double down) :
  m_name(name),
  m_up(up),
  m_down(down)
{}

Syst::~Syst()
{}

Sample::Sample(const int type, const string& name, const double yield, const double stat) :
  m_type(type),
  m_name(name),
  m_yield(yield),
  m_stat(stat),
  m_syst(0)
{}

Sample::~Sample()
{}

Channel::Channel(const string& name) :
  m_name(name),
  m_bkgSample(0),
  m_pSigSample(0)
{}

Channel::~Channel()
{}

void Sample::addSyst(const string& name, const double up, const double down) 
{
  m_syst.push_back(new Syst(name,up,down));
}

void Sample::print(const bool printSysts) const
{
  string type("");
  if(m_type==bkg) type="background";
  else if(m_type==sig) type="signal";
  else cout << "ERROR ! type of sample unknown" << endl;
  cout << "Informations for sample " << m_name << endl;
  cout << " -> sample type: " << type << endl; 
  cout << " -> yield: " << m_yield << endl;
  cout << " -> stat. uncert.: " << m_stat << endl;
  if(printSysts) {
    cout << " -> syst. uncert.:" << endl;
    for(unsigned int i=0; i<m_syst.size(); ++i) {
      cout << "  o " << m_syst[i]->getName() << ": " << m_syst[i]->getUp() << "  " << m_syst[i]->getDown() << endl;
    }
  }
}

Model::Model(const int statSampling, const int interpExtrapStyle) :
  m_channel(0),
  m_ws(0),
  m_statSampling(statSampling),
  m_interpExtrapStyle(interpExtrapStyle)
{}

Model::~Model()
{}

Channel* Model::addChannel(const string& channelName, const string& fileName)
{
  Channel* ch = new Channel(channelName);

  ifstream in(fileName.c_str());
  if (!in) {
    cerr << "ERROR ! Unable to open file '" << fileName << "' !" << endl;
    return 0;
  }
  enum {None,Background,Signal};
  int type=None;
  bool signalSet=false;
  Sample* samp = 0;
  for(; !in.eof() ;) {
    string line;
    if (!getline(in,line)) break;
    if (!line.empty() && line[0]!='#') {

      istringstream istr(line);
      string keyword,name;
      double val1,val2=0;
      istr >> keyword >> name >> val1 >> val2;

      TString name2(name.c_str());
      name2.ReplaceAll("/","");
      name=name2.Data();
      if ("+bg"==keyword) {
	type=Background;
	samp = new Sample(Sample::bkg,name,val1,val2);
	ch->addBkgSample(samp);
      } else if ("+sig"==keyword) {
	type=Signal;
	samp = new Sample(Sample::sig,"sig",val1,val2);
	ch->setSigSample(samp);
	if (signalSet) {
	  cerr << "WARNING ! Signal already set while setting new signal '" << name << "' !" << endl;
	}
	signalSet=true;
      } else if (".syst"==keyword) {
	if (None==type) {
	  cerr << "SYNTAX ERROR ! Trying to define a systematic uncertainty '" << name 
	       << "' before defining any sample !" << endl;
	} else {
	  if(val1!=0 && val2!=0)
	    samp->addSyst(name,1+val1,1+val2);
	}
      } else if ("+data"==keyword) {
	istringstream istr2(name);
	istr2 >> val1;
	ch->setYieldData(val1);
      }
    }
  }
  m_channel.push_back(ch);
  return ch;
}


void Model::printChannel(const string& channelName, const bool printSysts) const
{
  Channel* ch = 0;
  for(unsigned int i=0; i<m_channel.size(); ++i) {
    ch = m_channel[i];
    if(ch->getName()==channelName)
      break;
  }
  if(!ch) {
    cout << "ERROR ! channel not found" << endl;
    return;
  }

  vector<Sample*> bkgSamples = ch->getBkgSamples();
  Sample* sigSample = ch->getSigSample();

  if(!sigSample) {
    cout << "ERROR ! sig sample not defined" <<endl;
    return;
  }
  else {
    sigSample->print(printSysts);
  }
  
  for(unsigned int i=0; i<bkgSamples.size(); ++i) {
    bkgSamples[i]->print(printSysts);
  }

  cout << "Informations for sample data" << endl;
  cout << " -> yield: " << ch->getYieldData() << endl; 
}

void Model::addSampleToWS(RooWorkspace* w, Channel* chan, Sample* samp)
{
  w->factory(Form("%sYield_%s[%f,0,%f]",samp->getName().c_str(),chan->getName().c_str(),samp->getYield(),samp->getYield()+samp->getStat()*10));
  w->factory(Form("%sYieldNom_%s[%f]",samp->getName().c_str(),chan->getName().c_str(),samp->getYield()));
  // Stat. uncert.
  w->factory(Form("%sYieldUncert_%s[%f]",samp->getName().c_str(),chan->getName().c_str(),samp->getStat()));
  // Retrieve systematics
  RooArgSet systset("alpha_");
  vector<double> lowVec, highVec;
  for(unsigned int i=0; i<samp->getSyst().size(); ++i) {
    Syst* syst = samp->getSyst()[i];
    string systname(Form("alpha_%s",syst->getName().c_str()));
    RooRealVar* systvar = (RooRealVar*) w->var(systname.c_str());
    if(!systvar) {
      w->factory((systname+"[-5,5]").c_str());
      systvar = (RooRealVar*) w->var(systname.c_str());
    }
    systset.add(*systvar);
    lowVec.push_back(syst->getDown());
    highVec.push_back(syst->getUp());
  }
  // Make FlexibleInterpVar
  string interpVarName =  samp->getName() + "InterpVar_" + chan->getName(); 
  FlexibleInterpVar interp((interpVarName).c_str(),"",systset,1.,lowVec,highVec);      
  //cout << "Using interp/extrap style = " << m_interpExtrapStyle << endl;
  interp.setAllInterpCodes(m_interpExtrapStyle);
  w->import(interp,Silence());
  // Make product (yield nom * fij)
  w->factory(Form("prod::%s_%s(%sYield_%s,%s)",samp->getName().c_str(),chan->getName().c_str(),samp->getName().c_str(),chan->getName().c_str(),interpVarName.c_str()));
}

pair<string,string> Model::addAlphaYieldConstraintTerms(RooWorkspace* w, Channel* ch)
{
  RooPoisson* pois = (RooPoisson*) w->pdf(Form("pois_%s",ch->getName().c_str()));
  RooArgSet* allVars = pois->getVariables();
  TIterator* itr = allVars->createIterator();
  RooRealVar* var;
  string constAlphaString;
  string constYieldString;
  bool firstPassAlpha=true;
  bool firstPassYield=true;
  while ((var=(RooRealVar*)itr->Next())) {
    if (!var) {
      cout << "ERROR ! var " << var->GetName() << " doesn't exist" << endl;
      continue;
    }
    TString name=var->GetName();
    if(name.Contains("alpha") || (name.Contains("Yield") && !name.Contains("Uncert") && !name.Contains("Nom"))) {
      if(name.Contains("alpha")) {
	w->factory(Form("Gaussian::%s_Constraint(%s,%sNom[0],1)",name.Data(),name.Data(),name.Data()));
	if(!firstPassAlpha) constAlphaString+=",";
	constAlphaString+=Form("%s_Constraint",name.Data());
	firstPassAlpha=false;
      }
      else if(name.Contains("Yield") && !name.Contains("Uncert") && !name.Contains("Nom")) {
	TString temp1(name);
	temp1.ReplaceAll("Yield","YieldUncert");
	RooRealVar* uncert = (RooRealVar*) w->var(temp1.Data());
	if(!uncert) {
	  cout << "ERROR ! uncert variable unknown" << endl;
	  continue;
	}
	if(uncert->getVal()==0) {
	  var->setConstant();
	}
	else {
	  TString temp2(name);
	  temp2.ReplaceAll("Yield","YieldNom");
	  if(var->getVal()==0 || m_statSampling==Model::normal) {
	    w->factory(Form("Gaussian::%s_Constraint(%s,%s,%s)",name.Data(),name.Data(),temp2.Data(),temp1.Data()));
	  }
	  else {
	    if(m_statSampling==Model::logN) {
	      TString temp3(name);
	      temp3.ReplaceAll("Yield","LogNm0");
	      w->factory(Form("expr::%s('%s*%s/TMath::Sqrt(%s*%s+%s*%s)',%s,%s)",temp3.Data(),temp2.Data(),temp2.Data(),temp2.Data(),temp2.Data(),temp1.Data(),temp1.Data(),temp2.Data(),temp1.Data()));
	      TString temp4(name);
	      temp4.ReplaceAll("Yield","LogNk");
	      w->factory(Form("expr::%s('TMath::Exp(TMath::Sqrt(TMath::Log(1+%s*%s/%s/%s)))',%s,%s)",temp4.Data(),temp1.Data(),temp1.Data(),temp2.Data(),temp2.Data(),temp1.Data(),temp2.Data()));
	      w->factory(Form("Lognormal::%s_Constraint(%s,%s,%s)",name.Data(),name.Data(),temp3.Data(),temp4.Data()));
	    }
	    else if(m_statSampling==Model::gamma) {
	      TString temp3(name);
	      temp3.ReplaceAll("Yield","Gammagamma");
	      w->factory(Form("expr::%s('%s*%s/%s/%s',%s,%s)",temp3.Data(),temp2.Data(),temp2.Data(),temp1.Data(),temp1.Data(),temp2.Data(),temp1.Data()));
	      TString temp4(name);
	      temp4.ReplaceAll("Yield","Gammabeta");
	      w->factory(Form("expr::%s('%s*%s/%s',%s,%s)",temp4.Data(),temp1.Data(),temp1.Data(),temp2.Data(),temp1.Data(),temp2.Data()));
	      w->factory(Form("Gamma::%s_Constraint(%s,%s,%s,0)",name.Data(),name.Data(),temp3.Data(),temp4.Data()));
	    }
	    else {
	      cout << "ERROR ! m_statSampling set to an undefined value" << endl;
	      return make_pair("","");
	    }
	  }
	  if(!firstPassYield) constYieldString+=",";
	  constYieldString+=Form("%s_Constraint",name.Data());
	  firstPassYield=false;
	}
      }
    }
  }
  return make_pair(constAlphaString,constYieldString);
}

void SetGlobalObservables(RooWorkspace* w, Channel* ch)
{
  RooAbsPdf* pdf = (RooAbsPdf*) w->pdf(Form("lhood_%s",ch->getName().c_str()));
  RooArgSet* allVars = pdf->getVariables();
  TIterator* itr = allVars->createIterator();
  RooRealVar* var;
  string globalObsString;
  bool firstPassGlobalObs=true;
  while ((var=(RooRealVar*)itr->Next())) {
    if (!var) {
      cout << "ERROR ! var " << var->GetName() << " doesn't exist" << endl;
      continue;
    }
    TString name=var->GetName();
    if(name.Contains("Nom")) {
      if(!firstPassGlobalObs) globalObsString+=",";
      globalObsString+=name.Data();
      firstPassGlobalObs=false;
    }
  }
  w->defineSet("globalObservables",globalObsString.c_str());
}

void MakeModelConfig(RooWorkspace* w, Channel* ch)
{
  ModelConfig* wConfig = new ModelConfig("ModelConfig",w);
  wConfig->SetWorkspace(*w);
  RooAbsPdf* pdf = (RooAbsPdf*) w->pdf(Form("lhood_%s",ch->getName().c_str()));
  RooRealVar* Nobs = (RooRealVar*) w->var(Form("Nobs_%s",ch->getName().c_str()));
  RooRealVar* mu = (RooRealVar*) w->var("mu");
  RooArgSet* nuisance = (RooArgSet*) w->set("nuisanceSet");
  RooArgSet* globalObs = (RooArgSet*) w->set("globalObservables");
  if(!pdf || !Nobs || !mu || !nuisance || !globalObs) {
    cout << "ERROR ! ModelConfig can't be set (some pointers are 0)" << endl;
    return;
  }
  wConfig->SetPdf(*pdf);
  wConfig->SetObservables(RooArgSet(*Nobs));
  wConfig->SetParametersOfInterest(RooArgSet(*mu));
  wConfig->SetNuisanceParameters(*nuisance);
  wConfig->SetGlobalObservables(*globalObs);
  w->import(*wConfig,wConfig->GetName());
}

RooWorkspace* Model::makeSingleChannelModel(Channel* ch)
{
  if(!ch) {
    cout << "ERROR ! channel not found" << endl;
    return 0;
  }

  RooWorkspace* w = new RooWorkspace(("ws_"+ch->getName()).c_str(),("ws_"+ch->getName()).c_str());

  // Make mu*s+b
  w->factory("mu[1,0,100]");
  Sample* sig = ch->getSigSample();
  addSampleToWS(w,ch,sig);
  w->factory(Form("prod::mus_%s(mu,%s_%s)",ch->getName().c_str(),sig->getName().c_str(),ch->getName().c_str()));
  string sum(Form("sum::totYield_%s(mus_%s",ch->getName().c_str(),ch->getName().c_str()));
  for(unsigned int i=0; i<ch->getBkgSamples().size(); ++i) {
    Sample* bkg=ch->getBkgSamples()[i];
    addSampleToWS(w,ch,bkg);
    sum=sum+","+bkg->getName()+"_"+ch->getName();
  }
  sum+=")";
  w->factory(sum.c_str());

  // Make poisson pdf
  //w->factory(Form("Nobs_%s[%i,0,100]",ch->getName().c_str(),ch->getYieldData()));
  w->factory(Form("Nobs_%s[%f]",ch->getName().c_str(),ch->getYieldData()));
  w->factory(Form("Poisson::pois_%s(Nobs_%s,totYield_%s)",ch->getName().c_str(),ch->getName().c_str(),ch->getName().c_str()));
  
  // Define dataset
  RooRealVar* Nobs = (RooRealVar*) w->var(Form("Nobs_%s",ch->getName().c_str()));
  w->defineSet("obsData",RooArgSet(*Nobs));
  RooDataSet* dataSet = new RooDataSet("obsData","",*w->set("obsData"));
  dataSet->add(RooArgSet(*Nobs));
  w->import(*dataSet);
  
  // Add constraint terms to workspace
  pair<string,string> pairString = addAlphaYieldConstraintTerms(w,ch);

  // Make full likelihood (pois * all constraints)
  w->factory(Form("PROD::lhood_%s(pois_%s,%s,%s)",ch->getName().c_str(),ch->getName().c_str(),pairString.first.c_str(),pairString.second.c_str()));

  // Set global observables
  SetGlobalObservables(w,ch);

  // Define nuisance parameters set
  TString nuisanceString((pairString.first+","+pairString.second).c_str());
  nuisanceString.ReplaceAll("_Constraint","");
  w->defineSet("nuisanceSet",nuisanceString.Data());
  
  // Make ModelConfig
  MakeModelConfig(w,ch);

  return w;
}

void Model::makeModel(const string& outputName)
{
  map<string,RooAbsPdf*> pdfMap;
  stringstream ss;
  RooArgSet globalObs;
  RooArgSet nuisanceSet;
  vector<RooWorkspace*> wVec;
  RooArgList obsList;

  for(unsigned int i=0; i<m_channel.size(); ++i) {
    Channel* ch = m_channel[i];
    RooWorkspace* wCh = makeSingleChannelModel(ch);
    //wCh->Print();
    if(outputName!="") {
      TString fileName(outputName.c_str()); fileName.ReplaceAll(".root",("_"+ch->getName()+".root").c_str());
      wCh->writeToFile(fileName.Data());
    }
    wVec.push_back(wCh);
    RooAbsPdf* pdfCh = wCh->pdf(Form("lhood_%s",ch->getName().c_str()));
    if(!pdfCh) {
      cout << "ERROR ! lhood for channel " << ch->getName() << " not found " << endl;
      return;
    }
    pdfMap[ch->getName()]=pdfCh;
    if(ss.str().empty()) ss << ch->getName();
    else ss << "," << ch->getName();
    globalObs.add(*wCh->set("globalObservables"),true);
    nuisanceSet.add(*wCh->set("nuisanceSet"),true);
    ModelConfig* chConfig = (ModelConfig*) wCh->obj("ModelConfig");
    if(!chConfig) {
      cout << "ERROR ! ModelConfig for channel " << ch->getName() << " not found " << endl;
      return;
    }
    obsList.add(*chConfig->GetObservables());
  }

  m_ws = new RooWorkspace("ws_combined","ws_combined");  
  RooCategory* chCat = (RooCategory*) m_ws->factory(("channelCat["+ss.str()+"]").c_str());
  RooSimultaneous* simPdf = new RooSimultaneous("simPdf","",pdfMap,*chCat);
  ModelConfig* wConfig = new ModelConfig("ModelConfig",m_ws);
  wConfig->SetWorkspace(*m_ws);
  m_ws->import(globalObs,Silence());
  m_ws->defineSet("globalObservables",globalObs);
  wConfig->SetGlobalObservables(*m_ws->set("globalObservables"));
  m_ws->import(nuisanceSet,Silence());
  m_ws->defineSet("nuisanceSet",nuisanceSet);
  wConfig->SetNuisanceParameters(*m_ws->set("nuisanceSet"));

  RooDataSet* simData=0;
  for(unsigned int i=0; i<m_channel.size(); ++i) {
    Channel* ch = m_channel[i];
    RooDataSet* obsDataCh = (RooDataSet*) wVec[i]->data("obsData");
    if(!obsDataCh) {
      cout << "ERROR ! observed dataset for channel " << ch->getName() << " not found " << endl;
      return;
    }
    RooDataSet* tempData =  new RooDataSet(ch->getName().c_str(),
					   "",
					   obsList,
					   Index(*chCat),
					   Import(ch->getName().c_str(),*obsDataCh));
    if(simData) {
      simData->append(*tempData);
      delete tempData;
    }
    else 
      simData=tempData;
  }
  if(!simData) {
    cout << "ERROR ! simData pointer is 0" << endl;
    return;
  }
  m_ws->import(*simData,Rename("obsData"));
  obsList.add(*chCat);
  m_ws->defineSet("observables",obsList);
  wConfig->SetObservables(*m_ws->set("observables"));
  m_ws->import(*simPdf,RecycleConflictNodes(),Silence());
  wConfig->SetPdf(*simPdf);
  RooRealVar* mu = (RooRealVar*) m_ws->var("mu");
  wConfig->SetParametersOfInterest(RooArgSet(*mu));
  m_ws->import(*wConfig,wConfig->GetName());
  m_ws->Print();
  wConfig->Print();

  if(outputName!="") 
    m_ws->writeToFile(outputName.c_str());
}
