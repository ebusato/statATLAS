#include <stdexcept>
#include <fstream>
#include <sstream>
#include "TMath.h"
#include "ModelHistFactory.h"
#include "RooStats/HistFactory/Systematics.h"
#include "RooStats/HistFactory/Measurement.h"
#include "RooStats/HistFactory/MakeModelAndMeasurementsFast.h"
#include "RooStats/HistFactory/HistoToWorkspaceFactoryFast.h"

using namespace std;
using namespace RooStats ;
using namespace HistFactory;
using namespace modelHistFactory;
using namespace Constraint;

ModelHistFactory::ModelHistFactory() :
  m_channel(0),
  m_lumiCached(false),
  m_lumiSyst(0),
  m_constraintType("Poisson"),
  m_meas(0),
  m_ws(0)
{}

void ModelHistFactory::printChannel(const string& channelName) const
{
  Channel* ch = 0;
  for(unsigned int i=0; i<m_channel.size(); ++i) {
    ch = m_channel[i];
    if(ch->GetName()==channelName)
      break;
  }
  if(!ch) 
    throw runtime_error("ERROR ! channel not found");
  ch->Print();
}

void setHistoForSample(Sample* samp, const double val, const double err)
{
  samp->SetValue(val);
  TH1* hist = samp->GetHisto();
  if(!hist) 
    throw runtime_error("ERROR ! histo for sample not set");
  hist->SetBinError(1,err);
  //cout << "Content of histo for sample " << samp->GetName() << ": " << hist->GetBinContent(1) << " +- " << hist->GetBinError(1) << endl;
}

Channel* ModelHistFactory::addChannel(const string& channelName, const string& fileName)
{
  Channel* ch = new Channel(channelName);
  ch->SetStatErrorConfig(0.05, m_constraintType);

  ifstream in(fileName.c_str());
  if (!in) {
    cerr << "ERROR ! Unable to open file '" << fileName << "' !" << endl;
    throw runtime_error("ERROR ! Unable to open file");
  }
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
	samp = new Sample(name);
	setHistoForSample(samp,val1,val2);
	if(name2.Contains("Fake")|| name2.Contains("MisID") || name2.Contains("QmisId"))
	  samp->SetNormalizeByTheory(false);
	else
	  samp->SetNormalizeByTheory(true);
	samp->ActivateStatError();
	ch->AddSample(*samp);
      } else if ("+sig"==keyword) {
	samp = new Sample("sig");
	setHistoForSample(samp,val1,val2);
	samp->AddNormFactor("mu",1,0,40);
	samp->SetNormalizeByTheory(true);
	samp->ActivateStatError();
	ch->AddSample(*samp);
	if (signalSet) {
	  cerr << "WARNING ! Signal already set while setting new signal '" << name << "' !" << endl;
	}
	signalSet=true;
      } else if (".syst"==keyword) {
	if(name!="Lumi" && name!="Luminosity") {
	  // obliged to do this to retrieve sample (can't use directly samp) because Channel::AddSample 
	  // (which is called above) makes a copy of sample
	  Sample& samptemp = ch->GetSamples()[ch->GetSamples().size()-1];
	  if(samptemp.GetName()!=samp->GetName()) {
	    throw runtime_error("ERROR ! names of samples don't match");
	  }
	  else {
	    cout << "Adding syst for sample " << samptemp.GetName() << ": " << name << "  " << val1 << "  " << val2 << endl;
	    samptemp.AddOverallSys(name,1+val2,1+val1);
	  }
	}
	else {
	  if(val1!=-val2) 
	    throw runtime_error("ERROR ! lumi syst is not symetric");
	  else {
	    if(m_lumiCached) {
	      if(m_lumiSyst!=val1) {
		cout << "ERROR ! lumi not in agreement with cached value" << endl;
		cout << "   cached=" << m_lumiSyst << endl;
		cout << "   new=" << val1 << endl;
		throw runtime_error("ERROR ! Check input file");
		return 0;
	      }
	    }
	    else {
	      m_lumiSyst=val1;
	      m_lumiCached=true;
	    }
	  }
	}
      } else if ("+data"==keyword) {
	istringstream istr2(name);
	istr2 >> val1;
	ch->SetData(val1);
      }
    }
  }
  m_channel.push_back(ch);
  return ch;
}

void ModelHistFactory::makeModel()
{
  m_meas = new Measurement("meas","meas");
  if(m_lumiSyst==0) {
    cout << "\nWARNING ! m_lumiSyst==0\n" << endl;
    m_meas->AddConstantParam("Lumi");
  }
  else {
    cout << " -> setting lumi rel err to " << m_lumiSyst << endl;
    m_meas->SetLumiRelErr(m_lumiSyst);
  }
  
  m_meas->SetOutputFilePrefix("workspaces/HistFact");
  m_meas->SetExportOnly(true);
  //m_meas->SetExportOnly(false);
  m_meas->SetPOI("mu");
  m_meas->SetLumi(1.0);

  for(unsigned int i=0; i<m_channel.size(); ++i) {
    Channel* ch = m_channel[i];
    m_meas->AddChannel(*ch);
  }

  m_meas->PrintXML("temp/","test");

  m_ws = MakeModelAndMeasurementFast(*m_meas);
}

void ModelHistFactory::printStatUncert()
{
  cout << "\n-----------------------------------------" << endl;
  for(unsigned int i=0; i<m_meas->GetChannels().size(); ++i) {
    Channel channel = m_meas->GetChannels()[i];
    cout << "-> Printing stat uncertainty for channel " << channel.GetName() << endl;
    vector<Sample> sample = channel.GetSamples();
    TH1F* histoSum = new TH1F(("histoSum_"+channel.GetName()).c_str(),("histoSum_"+channel.GetName()).c_str(),1,0,1);
    histoSum->Sumw2();
    for(unsigned int j=0; j<sample.size(); ++j) {
      TH1F* histo = (TH1F*) sample[j].GetHisto();
      cout << " * Sample: " << sample[j].GetName() << "   " << histo->GetBinContent(1) << " +/- " << histo->GetBinError(1) << " events" << endl;
      histoSum->Add(histo);
    }
    cout << " * Sum: " << histoSum->GetName() << "   " << histoSum->GetBinContent(1) << " +/- " << histoSum->GetBinError(1) << " events" << endl;
    cout << "      => Relative stat uncert = " << histoSum->GetBinError(1)/histoSum->GetBinContent(1) << endl;
    cout << "      => Equivalent number of events = " << TMath::Power(histoSum->GetBinContent(1)/histoSum->GetBinError(1),2) << endl;
    cout << "-----------------------------------------\n" << endl;
  }
}
