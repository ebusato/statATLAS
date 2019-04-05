#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <TH1F.h>
#include <TString.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>
#include <TLatex.h>

double XsecFromMass(int mass)
{
  if(350==mass)
    return 8152*1.82;
  else if(400==mass)
    return 3467*1.89;
  else if(500==mass)
    return 792*2.03;
  else if(600==mass)
    return 201*2.17;
  else if(800==mass)
    return 19.5*2.46;
  else if(1000==mass)
    return 2.457*2.80;
  else if(1250==mass)
    return 0.224*3.31;
  else
    throw runtime_error("ERROR! mass not known");
}

class Limit {

public:
  enum {expM2,expM1,expMed,expP1,expP2,obs};
  Limit();
  Limit(const int type, const double value);
  virtual ~Limit();

  inline int getType() const {return m_type;}
  std::string getTypeString() const;
  inline double getValue() const {return m_value;}

  void print() const;

private:
  int m_type;
  double m_value;
};

Limit::Limit()
{}

Limit::Limit(const int type, const double value) :
  m_type(type),
  m_value(value)
{}

Limit::~Limit()
{}

std::string Limit::getTypeString() const
{
  std::string type("");
  if(m_type==expM2) 
    type="expM2";
  else if(m_type==expM1) 
    type="expM1";
  else if(m_type==expMed) 
    type="expMed";
  else if(m_type==expP1) 
    type="expP1";
  else if(m_type==expP2) 
    type="expP2";
  else if(m_type==obs) 
    type="obs";
  else
    throw runtime_error(Form("ERROR! type not recognized (type=%i)",m_type));
  return type;
}

void Limit::print() const
{
  cout << " -> Limit type=" << getTypeString() << ", value=" << m_value << endl;
}

class LimitExpsObs {
  
public:
  LimitExpsObs();
  LimitExpsObs(const std::string name, const int mass, const double xsec=1);
  virtual ~LimitExpsObs();

  inline std::string getName() const {return m_name;}
  inline int getMass() const {return m_mass;}
  inline double getXsec() const {return m_xsec;}
  inline void setXsec(const double xsec) {m_xsec=xsec;}
  void add(const Limit& limit);
  inline void getLimitsInXsec() {m_limitInXsec=true;}
  double getLimit(const int type);

  void print() const;

private:
  std::string m_name;
  int m_mass;
  double m_xsec;
  bool m_limitInXsec;
  std::vector<Limit> m_limitVec;
};

LimitExpsObs::LimitExpsObs()
{}

LimitExpsObs::LimitExpsObs(const std::string name, const int mass, const double xsec) :
  m_name(name),
  m_mass(mass),
  m_xsec(xsec),
  m_limitInXsec(false),
  m_limitVec()
{}

LimitExpsObs::~LimitExpsObs()
{}

void LimitExpsObs::print() const 
{
  cout << " -> Printing LimitExpsObs object with name=" << m_name << " and mass=" << m_mass << endl;
  for(unsigned int i=0; i<m_limitVec.size(); ++i) {
    m_limitVec[i].print();
  }
}

void LimitExpsObs::add(const Limit& limit)
{
  for(int unsigned i=0; i<m_limitVec.size(); ++i) {
    if(m_limitVec[i].getType()==limit.getType()) {
      throw runtime_error(Form("ERROR! limit with type %i already added to vector->not adding",limit.getType()));
    }
  }
  m_limitVec.push_back(limit);
}

double LimitExpsObs::getLimit(const int type)
{
  for(unsigned int i=0; i<m_limitVec.size(); ++i) {
    if(type==m_limitVec[i].getType()) {
      if(m_limitInXsec)
	return m_limitVec[i].getValue()*m_xsec;
      else
	return m_limitVec[i].getValue();
    }
  }
  throw runtime_error("ERROR! limit not found in vectorUnknown systematic uncertainty style !");
}

class LimitBrasilPlot {
public:
  LimitBrasilPlot(const std::string name);
  virtual ~LimitBrasilPlot();

  void readFile(const std::string fileName);
  inline std::string getName() const {return m_name;}
  void add(const LimitExpsObs& limits);

  void print() const;

  void makePlot();

private:
  std::string m_name;
  std::vector<LimitExpsObs> m_limitsBrasil;
};

LimitBrasilPlot::LimitBrasilPlot(const std::string name) :
  m_name(name),
  m_limitsBrasil()
{}

LimitBrasilPlot::~LimitBrasilPlot()
{}

void LimitBrasilPlot::print() const
{
  cout << " -> Printing LimitBrasilPlot object with name=" << m_name << " and " << m_limitsBrasil.size() << " mass points" << endl;
  for(unsigned int i=0; i<m_limitsBrasil.size(); ++i) {
    m_limitsBrasil[i].print();
  }
}

void LimitBrasilPlot::readFile(const std::string fileName)
{
  ifstream f(fileName.c_str());
  if(!f) {
    throw runtime_error(Form("ERROR! unable to open file %s",fileName.c_str()));
  }
  else 
    cout << "-> Parsing file " << fileName << endl;

  string line("");
  int NoMassPoints=0;
  std::vector<LimitExpsObs*> vec;
  bool expM2done=false;
  bool expM1done=false;
  bool expMeddone=false;
  bool expP1done=false;
  bool expP2done=false;
  bool obsdone=false;
  for ( ; !f.eof() ; ) {
    if(!getline(f,line)) break;
    if(line.find("#") != string::npos) continue;
    TString ts(line.c_str());
    ts.ReplaceAll("\\\\","");
    ts.ReplaceAll("\\hline","");
    TObjArray* arr=ts.Tokenize("&");
    if(NoMassPoints==0) { // reading first line and determining number of mass points
      for (int i=1; i<arr->GetEntries(); ++i) {
	++NoMassPoints;
	TString entry = ((TObjString*)arr->At(i))->GetString();
	if(""!=entry) {
	  TObjArray* arr2=entry.Tokenize(" ");
	  if(arr2->GetEntries()==2) {
	    // Goes here when first line is like : Sgluon 350 & Sgluon 400 & Sgluon 500 & ...
	    TString entryMassString = ((TObjString*)arr2->At(1))->GetString();
	    int entryMass=0;
	    istringstream is(entryMassString.Data());
	    is >> entryMass;
	    entry.ReplaceAll(" ","");
	    cout << "-> creating LimitExpsObs(" << entry.Data() << "," << entryMass << ")" << endl;
	    LimitExpsObs* lim=new LimitExpsObs(entry.Data(),entryMass);
	    lim->setXsec(XsecFromMass(entryMass));
	    vec.push_back(lim);
	  }
	  else if(arr2->GetEntries()==1) {
	    // Goes here when first line is like : 350 & 400 & 500 & ...
	    int entryMass=0;
	    istringstream is(entry.Data());
	    is >> entryMass;
	    LimitExpsObs* lim=new LimitExpsObs("Unknown",entryMass);
	    lim->setXsec(XsecFromMass(entryMass));
	    vec.push_back(lim);
	  }
	  else {
	    cout << "Number of fields not supported (No fields=" << arr2->GetEntries() << ")" << endl;
	    throw runtime_error("->Quitting");
	  }
	}
	else
	  throw runtime_error("ERROR! entry is empty");
      }
      cout << "-> Found " << NoMassPoints << " mass points" << endl;
      if((int) vec.size()!=NoMassPoints) {
	cout << "ERROR! vector size and NoMassPoints are different (vec size=" << vec.size() << ", NoMassPoints=" << NoMassPoints << ")" << endl;
	throw runtime_error("->Quitting");
      }
    }
    else {
      cout << ts << endl;
      for (int i=1; i<arr->GetEntries(); ++i) {
	TString entry = ((TObjString*)arr->At(i))->GetString().ReplaceAll(" ","");
	//cout << "entry=" << entry << endl;
	double val=0;
	istringstream is(entry.Data());
	is >> val;
	if(expM2done==false) {
	  vec[i-1]->add(Limit(Limit::expM2,val));
	}
	else if(expM1done==false) {
	  vec[i-1]->add(Limit(Limit::expM1,val));
	}
	else if(expMeddone==false) {
	  vec[i-1]->add(Limit(Limit::expMed,val));
	}
	else if(expP1done==false) {
	  vec[i-1]->add(Limit(Limit::expP1,val));
	}
	else if(expP2done==false) {
	  vec[i-1]->add(Limit(Limit::expP2,val));
	}
	else if(obsdone==false) {
	  vec[i-1]->add(Limit(Limit::obs,val));
	}
      }
      if(expM2done==false)
	expM2done=true;
      else if(expM2done==true && expM1done==false)
	expM1done=true;
      else if(expM1done==true && expMeddone==false)
	expMeddone=true;
      else if(expMeddone==true && expP1done==false)
	expP1done=true;
      else if(expP1done==true && expP2done==false)
	expP2done=true;
      else if(expP2done==true && obsdone==false)
	obsdone=true;    
    }
  }

  for(unsigned int i=0; i<vec.size(); ++i) {
    this->add(*vec[i]);
  }
}

void LimitBrasilPlot::add(const LimitExpsObs& limits)
{
  for(int unsigned i=0; i<m_limitsBrasil.size(); ++i) {
    if(m_limitsBrasil[i].getName()==limits.getName()) {
      cout << "WARNING! limits with name " << limits.getName() << " already added to vector->make sure it's ok" << endl;
    }
  }
  m_limitsBrasil.push_back(limits);
}

void LimitBrasilPlot::makePlot()
{
  const unsigned int npoints = m_limitsBrasil.size();
  TGraph* g_obs = new TGraph(npoints);
  TGraphAsymmErrors* g_expmed_1sigma = new TGraphAsymmErrors(npoints);
  TGraphAsymmErrors* g_expmed_2sigma = new TGraphAsymmErrors(npoints);
  g_obs->SetMarkerStyle(20);
  g_obs->SetMarkerColor(kBlack);
  g_obs->SetLineColor(kBlack);
  g_obs->SetLineWidth(2);
  g_expmed_1sigma->SetMarkerStyle(20);
  g_expmed_1sigma->SetFillColor(kGreen);
  g_expmed_1sigma->SetLineColor(kBlack);
  g_expmed_2sigma->SetTitle("Excusion graph;mass [TeV];#sigma #times BR [pb]");
  g_expmed_2sigma->GetXaxis()->SetTitleOffset(1.2);
  g_expmed_2sigma->SetFillColor(kYellow);
  
  double Ymax=1e3;
  double Ymin=0.1;
  for(unsigned int i=0; i<npoints; ++i) {
    LimitExpsObs& limits=m_limitsBrasil[i];
    limits.getLimitsInXsec();
    g_obs->SetPoint(i,limits.getMass(),limits.getLimit(Limit::obs));
    g_expmed_1sigma->SetPoint(i,limits.getMass(),limits.getLimit(Limit::expMed));
    g_expmed_2sigma->SetPoint(i,limits.getMass(),limits.getLimit(Limit::expMed));
    g_expmed_1sigma->SetPointError(i,0.,0.,limits.getLimit(Limit::expMed)-limits.getLimit(Limit::expM1),limits.getLimit(Limit::expP1)-limits.getLimit(Limit::expMed));
    g_expmed_2sigma->SetPointError(i,0.,0.,limits.getLimit(Limit::expMed)-limits.getLimit(Limit::expM2),limits.getLimit(Limit::expP2)-limits.getLimit(Limit::expMed));
    if(0==i) {
      Ymax=limits.getLimit(Limit::expP2);
    }
    else if(i==npoints-1) {
      Ymin=limits.getLimit(Limit::expM2);
    }
  }

  cout <<  "Ymax=" << Ymax << endl;
  cout <<  "Ymin=" << Ymin << endl;
  g_expmed_2sigma->GetHistogram()->SetMaximum(Ymax*5);
  g_expmed_2sigma->GetHistogram()->SetMinimum(Ymin*0.5);

  TCanvas* c = new TCanvas("c","c",800,600);
  c->cd();
  g_expmed_2sigma->Draw("AF3");
  g_expmed_1sigma->Draw("LF3");
  TGraphAsymmErrors* g_expmed_1sigmaClone = (TGraphAsymmErrors*) g_expmed_1sigma->Clone("g_expmed_2sigmaClone");
  g_expmed_1sigmaClone->SetLineWidth(2);
  g_expmed_1sigmaClone->SetLineStyle(2);  
  g_expmed_1sigmaClone->Draw("LX");
  g_obs->Draw("LP");
  gPad->SetLogy();
  //TGraphAsymmErrors* g_theoLine = (TGraphAsymmErrors*) g_theo->Clone("g_theoLine");
  // g_theo->Draw("LF3");
  //  g_theoLine->Draw("LX");

  /*  std::pair<double,double> cross1=getCrossing(g_theo,g_expmed_1sigma);
  TLine* line1 = new TLine(cross1.first,0,cross1.first,cross1.second);
  line1->SetLineColor(kRed);
  line1->SetLineWidth(2);
  line1->SetLineStyle(3);
  line1->Draw();                                                                                                                      
  std::pair<double,double> cross2=getCrossing(g_theo,g_obs);
  TLine* line2 = new TLine(cross2.first,0,cross2.first,cross2.second);
  line2->SetLineColor(kBlack);
  line2->SetLineWidth(2);
  line2->SetLineStyle(3);
  line2->Draw();                                                                                                                      
  */
  float atlasX=0.47,atlasY=0.82;
  float intLumi=20.3;
  TLatex* pLat1=new TLatex();
  pLat1->SetNDC();
  pLat1->SetTextColor(1);
  pLat1->SetTextSize(0.05);
  pLat1->SetTextFont(72);
  pLat1->DrawLatex(atlasX,atlasY,"ATLAS");
  pLat1->SetTextFont(42);
  pLat1->SetTextSize(0.05);
  TString label="Work in progress";
  pLat1->DrawLatex(atlasX+0.13,atlasY,label);
  pLat1->DrawLatex(atlasX,atlasY-0.09,TString::Format("#intLdt = %.1f fb^{-1}, #sqrt{s} = 8 TeV",intLumi));

  TLegend* leg = new TLegend(0.129397,0.8461538,0.4145729,0.9965035);
  leg->SetBorderSize(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->AddEntry(g_expmed_1sigmaClone,"Expected limit at 95% CL","L");
  leg->AddEntry(g_expmed_1sigma,"Expected limit #pm 1 #sigma","F");
  leg->AddEntry(g_expmed_2sigma,"Expected limit #pm 2 #sigma","F");
  //leg->AddEntry(g_theo,"Theory approx. LO","LF");
  leg->AddEntry(g_obs,"Observed limit at 95% CL","LEP");                                                                           
  leg->Draw();
}
