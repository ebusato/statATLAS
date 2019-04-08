#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include <TH1F.h>
#include <TMath.h>
#include <TLine.h>
#include <TString.h>
#include <TObjArray.h>
#include <TObjString.h>
#include <TPad.h>
#include <TAxis.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>
#include <TLatex.h>

void printTGraphAsym(TGraphAsymmErrors* g) 
{
  for(int i=0; i<g->GetN(); ++i) {
    double x,y;
    g->GetPoint(i,x,y);
    double errYhigh=g->GetErrorYhigh(i);
    double errYlow=g->GetErrorYlow(i);
    cout << "x=" << x << ", y=" << y << endl;
    cout << " -> Yhigh=" << y+errYhigh << endl;
    cout << " -> Ylow=" << y-errYlow << endl;
  }
}

class Limit {

public:
  enum {expM2,expM1,expMed,expP1,expP2,obs};
  Limit();
  Limit(const int type, const double value);
  virtual ~Limit();

  inline void setMass(const int mass) {m_mass=mass;}
  inline void setValue(const double val) {m_value=val;}

  inline int getType() const {return m_type;}
  std::string getTypeString() const;
  inline double getValue() const {return m_value;}
  inline double getMass() const {return m_mass;}

  void print() const;

private:
  int m_type;
  int m_mass;
  double m_value;
};

Limit::Limit()
{}

Limit::Limit(const int type, const double value) :
  m_type(type),
  m_mass(0),
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
  cout << " -> Limit type=" << getTypeString() << ", value=" << m_value << " (mass=" << m_mass << ")" << endl;
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
      if(m_limitInXsec) {
	return m_limitVec[i].getValue()*m_xsec;
      }
      else
	return m_limitVec[i].getValue();
    }
  }
  throw runtime_error("ERROR! limit not found in vectorUnknown systematic uncertainty style !");
}

class TheoXsec {
public:
  enum {RPPFullStat,SgluonFullStat,SgluonPartialStat};
  TheoXsec(int type=SgluonFullStat);
  virtual ~TheoXsec();
  
  void set2UEDRPPFullDataSet();
  void setSgluonFullDataSet();
  void setSgluonPartialDataSet();
  inline double getTheoXsec(double mass) {return m_mapMassTheoXsec[mass];}
  inline double getGeneratedXsec(double mass) {return m_mapMassGeneratedXsec[mass];}
  void plotGraph(TGraph* g=0, int color=kRed);

private:
  std::map<double, double> m_mapMassTheoXsec;
  std::map<double, double> m_mapMassGeneratedXsec;
};

TheoXsec::TheoXsec(int type)
{
  if(type==TheoXsec::RPPFullStat) {
    set2UEDRPPFullDataSet();
  }
  else if(type==TheoXsec::SgluonFullStat) {
    setSgluonFullDataSet();
  }
  else if(type==TheoXsec::SgluonPartialStat) {
    setSgluonPartialDataSet();
  }
  else {
    cout << "ERROR ! type not found" << endl;
    throw runtime_error(" -> quitting");
  }
}

void TheoXsec::set2UEDRPPFullDataSet()
{
  m_mapMassTheoXsec[600*1e-3]=1285*1e-3;
  m_mapMassTheoXsec[800*1e-3]=114*1e-3;
  m_mapMassTheoXsec[1000*1e-3]=11.7*1e-3;
  m_mapMassTheoXsec[1200*1e-3]=1.22*1e-3;
  
  m_mapMassGeneratedXsec[600*1e-3]=m_mapMassTheoXsec[600*1e-3];
  m_mapMassGeneratedXsec[800*1e-3]=m_mapMassTheoXsec[800*1e-3];
  m_mapMassGeneratedXsec[1000*1e-3]=m_mapMassTheoXsec[1000*1e-3];
  m_mapMassGeneratedXsec[1200*1e-3]=m_mapMassTheoXsec[1200*1e-3];
}

void TheoXsec::setSgluonFullDataSet()
{
  m_mapMassTheoXsec[350*1e-3]=8152*1e-3*1.82;
  m_mapMassTheoXsec[400*1e-3]=3467*1e-3*1.89;
  m_mapMassTheoXsec[500*1e-3]=792*1e-3*2.03;
  m_mapMassTheoXsec[600*1e-3]=201*1e-3*2.17;
  m_mapMassTheoXsec[800*1e-3]=19.5*1e-3*2.46;
  m_mapMassTheoXsec[1000*1e-3]=2.457*1e-3*2.80;
  m_mapMassTheoXsec[1250*1e-3]=0.224*1e-3*3.31;
  
  m_mapMassGeneratedXsec[350*1e-3]=m_mapMassTheoXsec[350*1e-3];
  m_mapMassGeneratedXsec[400*1e-3]=m_mapMassTheoXsec[400*1e-3];
  m_mapMassGeneratedXsec[500*1e-3]=m_mapMassTheoXsec[500*1e-3];
  m_mapMassGeneratedXsec[600*1e-3]=m_mapMassTheoXsec[600*1e-3];
  m_mapMassGeneratedXsec[800*1e-3]=m_mapMassTheoXsec[800*1e-3];
  m_mapMassGeneratedXsec[1000*1e-3]=m_mapMassTheoXsec[1000*1e-3];
  m_mapMassGeneratedXsec[1250*1e-3]=m_mapMassTheoXsec[1250*1e-3];
}

void TheoXsec::setSgluonPartialDataSet()
{
  m_mapMassTheoXsec[350*1e-3]=8.152*1.823;
  m_mapMassTheoXsec[400*1e-3]=3.467*1.892;
  m_mapMassTheoXsec[500*1e-3]=0.762*2.029;
  m_mapMassTheoXsec[600*1e-3]=0.201*2.167;
  m_mapMassTheoXsec[800*1e-3]=0.018950*2.461;
  m_mapMassTheoXsec[1000*1e-3]=0.002457*2.799;

  m_mapMassGeneratedXsec[350*1e-3]=8.2806*1.66;
  m_mapMassGeneratedXsec[400*1e-3]=3.5137*1.68;
  m_mapMassGeneratedXsec[500*1e-3]=0.7826*1.75;
  m_mapMassGeneratedXsec[600*1e-3]=0.20709*1.81;
  m_mapMassGeneratedXsec[800*1e-3]=0.020211*1.97;
  m_mapMassGeneratedXsec[1000*1e-3]=0.0025464*2.15;
}

TheoXsec::~TheoXsec()
{}

double getExpThCrossing(TGraph* gE, TGraph* gT, double& ordo)
{
  if(gE->GetN()!=gT->GetN()) {
    cout << "ERROR! in getExpThCrossing: not the same number of points in both graphs: " << gE->GetN() << " and " << gT->GetN() << endl;
    throw runtime_error("->Quitting");
  }

  double y1E,y1T,y2E,y2T;
  double x1, x2;

  for(int i=0; i<gE->GetN()-1; ++i) {
    gE->GetPoint(i,x1,y1E);
    gE->GetPoint(i+1,x2,y2E);
    gT->GetPoint(i,x1,y1T);
    gT->GetPoint(i+1,x2,y2T);
    
    if(y1T>y1E && y2T<y2E)
      break;
  }

  /*
  cout << "x1=" << x1 << endl;
  cout << "x2=" << x2 << endl;
  cout << "y1E=" << y1E << endl;
  cout << "y2E=" << y2E << endl;
  cout << "y1T=" << y1T << endl;
  cout << "y2T=" << y2T << endl;
  */

  double penteE = (TMath::Log10(y2E) - TMath::Log10(y1E)) / (x2-x1);
  double ordoE = 0.5 *  (  (TMath::Log10(y2E) - penteE*x2)  +  (TMath::Log10(y1E) - penteE*x1)  );
  double penteT = (TMath::Log10(y2T) - TMath::Log10(y1T)) / (x2-x1);
  double ordoT = 0.5 *  (  (TMath::Log10(y2T) - penteT*x2)  +  (TMath::Log10(y1T) - penteT*x1)  );
  if(   TMath::Abs(   (TMath::Log10(y2T) - penteT*x2)  -  (TMath::Log10(y1T) - penteT*x1)   )   >    0.1*(TMath::Log10(y2T) - penteT*x2)){
    //std::cout << "Oh oh!" << std::endl;
    //std::cout << TMath::Log10(y2T) - penteT*x2 << "    " << TMath::Log10(y1T) - penteT*x1 << std::endl;
  }

  double ab = (ordoT - ordoE)/(penteE-penteT);
  ordo = TMath::Power(10,ab * penteE + ordoE);
  return ab;
}

void TheoXsec::plotGraph(TGraph* g, int color)
{  
  const int size=m_mapMassTheoXsec.size();
  TGraphAsymmErrors* pTheoGraph = new TGraphAsymmErrors(size);
  int counter=0;
  for(map<double,double>::const_iterator it=m_mapMassTheoXsec.begin() ; it!=m_mapMassTheoXsec.end() ; ++it) {
    //cout << "mass=" << it->first << ", xsec=" << it->second << endl;
    pTheoGraph->SetPoint(counter,it->first,it->second);
    pTheoGraph->SetPointError(counter,0.,0.,it->second*0.3,it->second*0.3);
    ++counter;
  }

  pTheoGraph->SetLineColor(kRed);
  pTheoGraph->SetFillColor(kRed);
  pTheoGraph->SetFillStyle(3005); // put 3005 instead of 3004 here because they are inverted when saving in pdf format (and I want 3004 in the output pdf) !
  pTheoGraph->SetMarkerColor(kRed);
  pTheoGraph->SetMarkerStyle(20);
  pTheoGraph->SetLineWidth(2);
  pTheoGraph->Draw("C3");

  if(g) // Draw intersection
    {
      double ord;
      double ab = getExpThCrossing(g,pTheoGraph,ord);
      TLine* indic = new TLine(ab,0,ab,ord);
      
      cout << "Limit on mass=" << ab << " TeV" << endl;

      indic->SetLineColor(color);
      indic->SetLineWidth(2);
      indic->SetLineStyle(3);
      indic->Draw();
    }
}

class LimitBrasilPlot {
public:
  LimitBrasilPlot(const std::string name, const int theoXsecType=TheoXsec::SgluonFullStat);
  virtual ~LimitBrasilPlot();

  void readFile(const std::string fileName);
  inline std::string getName() const {return m_name;}
  void add(const LimitExpsObs& limits);

  void print() const;

  void makePlot(bool overlay=false, double ymin=-1., double ymax=-1.);
  void plotTheoGraph(bool drawIntersection=false);

  TLegend* getLegend() const {return m_legend;}

  void setXtitle(const std::string title) {m_xTitle=title;}
  void setYtitle(const std::string title) {m_yTitle=title;}
  void setXtitleOffset(const double a) {m_xTitleOffset=a;}
  void setYtitleOffset(const double a) {m_yTitleOffset=a;}
  void setXtitleSize(const double a) {m_xTitleSize=a;}
  void setYtitleSize(const double a) {m_yTitleSize=a;}
  void setXlabelOffset(const double a) {m_xLabelOffset=a;}
  void setYlabelOffset(const double a) {m_yLabelOffset=a;}
  void setXlabelSize(const double a) {m_xLabelSize=a;}
  void setYlabelSize(const double a) {m_yLabelSize=a;}

private:
  std::string m_name;
  std::vector<LimitExpsObs> m_limitsBrasil;
  TGraph* m_pObsGraph;
  TGraphAsymmErrors* m_pExp1sigGraph;
  TGraphAsymmErrors* m_pExp2sigGraph;
  TGraph*  m_pExpPlus1sig;
  TGraph*  m_pExpPlus2sig;
  TGraph*  m_pExpMinus1sig;
  TGraph*  m_pExpMinus2sig;
  TheoXsec* m_theoXsec;
  TLegend* m_legend;
  std::string m_xTitle;
  std::string m_yTitle;
  double m_xTitleOffset;
  double m_yTitleOffset;
  double m_xTitleSize;
  double m_yTitleSize;
  double m_xLabelOffset;
  double m_yLabelOffset;
  double m_xLabelSize;
  double m_yLabelSize;
};

LimitBrasilPlot::LimitBrasilPlot(const std::string name, const int theoXsecType) :
  m_name(name),
  m_limitsBrasil(),
  m_pObsGraph(0),
  m_pExp1sigGraph(0),
  m_pExp2sigGraph(0),
  m_legend(0),
  m_xTitle(""),
  m_yTitle(""),
  m_xTitleOffset(-1),
  m_yTitleOffset(-1),
  m_xTitleSize(-1),
  m_yTitleSize(-1),
  m_xLabelOffset(-1),
  m_yLabelOffset(-1),
  m_xLabelSize(-1),
  m_yLabelSize(-1)
{
  m_theoXsec = new TheoXsec(theoXsecType);
}

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
	    lim->setXsec(m_theoXsec->getGeneratedXsec((double) entryMass*1e-3));
	    vec.push_back(lim);
	  }
	  else if(arr2->GetEntries()==1) {
	    // Goes here when first line is like : 350 & 400 & 500 & ...
	    int entryMass=0;
	    istringstream is(entry.Data());
	    is >> entryMass;
	    LimitExpsObs* lim=new LimitExpsObs("Unknown",entryMass);
	    lim->setXsec(m_theoXsec->getGeneratedXsec((double) entryMass*1e-3));
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
    else { // reading 2nd, 3rd, ... lines
      for (int i=1; i<arr->GetEntries(); ++i) {
	TString tempString = ((TObjString*)arr->At(i))->GetString();
	TString entry = tempString.ReplaceAll(" ","");
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
  /*
  for(int unsigned i=0; i<m_limitsBrasil.size(); ++i) {
    if(m_limitsBrasil[i].getName()==limits.getName()) {
      cout << "WARNING! limits with name " << limits.getName() << " already added to vector->make sure it's ok" << endl;
    }
  }
  */
  m_limitsBrasil.push_back(limits);
}

void LimitBrasilPlot::makePlot(bool overlay, double ymin, double ymax)
{
  const unsigned int npoints = m_limitsBrasil.size();
  m_pObsGraph = new TGraph(npoints);
  m_pExp1sigGraph = new TGraphAsymmErrors(npoints);
  m_pExp2sigGraph = new TGraphAsymmErrors(npoints);
  m_pExpPlus1sig = new TGraph(npoints);
  m_pExpPlus2sig = new TGraph(npoints);
  m_pExpMinus1sig = new TGraph(npoints);
  m_pExpMinus2sig = new TGraph(npoints);

  m_pObsGraph->SetMarkerStyle(20);
  m_pObsGraph->SetLineWidth(2);
  m_pExp1sigGraph->SetMarkerStyle(20);
  m_pExp1sigGraph->SetLineColor(kBlack);
  m_pExp2sigGraph->SetTitle("Excusion graph;mass [TeV];#sigma #times BR [pb]");
  if(overlay) {
    m_pObsGraph->SetMarkerColor(14);
    m_pObsGraph->SetLineColor(14);
    m_pExp1sigGraph->SetFillStyle(3004);
    m_pExp1sigGraph->SetFillColor(14);
    m_pExp1sigGraph->SetLineColor(14);
    m_pExp2sigGraph->SetFillStyle(3005);
    m_pExp2sigGraph->SetFillColor(14);
    m_pExp2sigGraph->SetLineColor(14);
    m_pExpPlus1sig->SetLineColor(12);
    m_pExpPlus2sig->SetLineColor(12);
    m_pExpMinus1sig->SetLineColor(12);
    m_pExpMinus2sig->SetLineColor(12);
  }
  else {
    m_pObsGraph->SetMarkerColor(kBlack);
    m_pObsGraph->SetLineColor(kBlack);
    m_pExp1sigGraph->SetFillColor(kGreen);
    m_pExp2sigGraph->SetFillColor(kYellow);
  }
  
  double Ymax=1e3;
  double Ymin=0.1;
  for(unsigned int i=0; i<npoints; ++i) {
    LimitExpsObs& limits=m_limitsBrasil[i];
    limits.getLimitsInXsec();
    cout << "In LimitBrasilPlot::makePlot(...): making graph with following values: " << endl;
    cout << "  -> mass=" << limits.getMass() << endl;
    cout << "  -> x-sec observed limit=" << limits.getLimit(Limit::obs) << endl;
    cout << "  -> x-sec exp med limit=" << limits.getLimit(Limit::expMed) << endl;
    m_pObsGraph->SetPoint(i,
			  limits.getMass()*1e-3,
			  limits.getLimit(Limit::obs));
    m_pExp1sigGraph->SetPoint(i,
			      limits.getMass()*1e-3,
			      limits.getLimit(Limit::expMed));
    m_pExp2sigGraph->SetPoint(i,
			      limits.getMass()*1e-3,
			      limits.getLimit(Limit::expMed));
    m_pExp1sigGraph->SetPointError(i,
				   0.,
				   0.,
				   limits.getLimit(Limit::expMed)-limits.getLimit(Limit::expM1),
				   limits.getLimit(Limit::expP1)-limits.getLimit(Limit::expMed));
    m_pExp2sigGraph->SetPointError(i,
				   0.,
				   0.,
				   limits.getLimit(Limit::expMed)-limits.getLimit(Limit::expM2),
				   limits.getLimit(Limit::expP2)-limits.getLimit(Limit::expMed));

    m_pExpPlus1sig->SetPoint(i,
			     limits.getMass()*1e-3,
			     limits.getLimit(Limit::expP1));
    m_pExpPlus2sig->SetPoint(i,
			     limits.getMass()*1e-3,
			     limits.getLimit(Limit::expP2));
    m_pExpMinus1sig->SetPoint(i,
			     limits.getMass()*1e-3,
			     limits.getLimit(Limit::expM1));
    m_pExpMinus2sig->SetPoint(i,
			     limits.getMass()*1e-3,
			     limits.getLimit(Limit::expM2));

    if(0==i) {
      Ymax=limits.getLimit(Limit::expP2);
    }
    else if(i==npoints-1) {
      Ymin=limits.getLimit(Limit::expM2);
    }
  }

  //printTGraphAsym(m_pExp1sigGraph);

  if(ymin==-1 && ymax==-1) {
    cout << "here-1: " << Ymax << "  " << Ymin << endl;
    m_pExp2sigGraph->GetHistogram()->SetMaximum(Ymax*15);
    m_pExp2sigGraph->GetHistogram()->SetMinimum(Ymin*0.1);
  }
  else {
    cout << "here; " << ymax << "  " << ymin << endl;
    m_pExp2sigGraph->GetHistogram()->SetMaximum(ymax);
    m_pExp2sigGraph->GetHistogram()->SetMinimum(ymin);
  }

  TGraphAsymmErrors* pExp1sigGraphClone = (TGraphAsymmErrors*) m_pExp1sigGraph->Clone("pExp1sigGraphClone");
  pExp1sigGraphClone->SetLineWidth(2);
  pExp1sigGraphClone->SetLineStyle(2);  

  //m_pExp2sigGraph->GetYaxis()->SetRangeUser(-0.01,0.042);

  if(!overlay) {
    m_pExp2sigGraph->Draw("A3");
    if(m_yTitle!="")
      m_pExp2sigGraph->GetYaxis()->SetTitle(m_yTitle.c_str());
    if(m_xTitle!="")
      m_pExp2sigGraph->GetXaxis()->SetTitle(m_xTitle.c_str());
  }
  else {
    m_pExp2sigGraph->Draw("3");
    m_pExpPlus1sig->Draw("L");
    m_pExpPlus2sig->Draw("L");
    m_pExpMinus1sig->Draw("L");
    m_pExpMinus2sig->Draw("L");
  }
  gPad->SetBottomMargin(0.12);
  gPad->SetLogy();
  if(m_yTitleSize!=-1)
    m_pExp2sigGraph->GetYaxis()->SetTitleSize(m_yTitleSize);
  else
    m_pExp2sigGraph->GetYaxis()->SetTitleSize(0.05);
  if(m_yTitleOffset!=-1)
    m_pExp2sigGraph->GetYaxis()->SetTitleOffset(m_yTitleOffset);
  else
    m_pExp2sigGraph->GetYaxis()->SetTitleOffset(1.02);
  if(m_yLabelSize!=-1)
    m_pExp2sigGraph->GetYaxis()->SetLabelSize(m_yLabelSize);
  else
    m_pExp2sigGraph->GetYaxis()->SetLabelSize(0.05);
  if(m_yLabelOffset!=-1)
    m_pExp2sigGraph->GetYaxis()->SetLabelOffset(m_yLabelOffset);
  else
    m_pExp2sigGraph->GetYaxis()->SetLabelOffset(0.005);

  if(m_xTitleSize!=-1)
    m_pExp2sigGraph->GetXaxis()->SetTitleSize(m_xTitleSize);
  else
    m_pExp2sigGraph->GetXaxis()->SetTitleSize(0.05);
  if(m_xTitleOffset!=-1)
    m_pExp2sigGraph->GetXaxis()->SetTitleOffset(m_xTitleOffset);
  else
    m_pExp2sigGraph->GetXaxis()->SetTitleOffset(1);
  if(m_xLabelSize!=-1)
    m_pExp2sigGraph->GetXaxis()->SetLabelSize(m_xLabelSize);
  else
    m_pExp2sigGraph->GetXaxis()->SetLabelSize(0.05);
  if(m_xLabelOffset!=-1)
    m_pExp2sigGraph->GetXaxis()->SetLabelOffset(m_xLabelOffset);
  else
    m_pExp2sigGraph->GetXaxis()->SetLabelOffset(0.005);
  m_pExp1sigGraph->Draw("3");
  pExp1sigGraphClone->Draw("LX");
  m_pObsGraph->Draw("LP");
  //TGraphAsymmErrors* g_theoLine = (TGraphAsymmErrors*) g_theo->Clone("g_theoLine");
  // g_theo->Draw("LF3");
  //  g_theoLine->Draw("LX");

  /*  std::pair<double,double> cross1=getCrossing(g_theo,m_pExp1sigGraph);
  TLine* line1 = new TLine(cross1.first,0,cross1.first,cross1.second);
  line1->SetLineColor(kRed);
  line1->SetLineWidth(2);
  line1->SetLineStyle(3);
  line1->Draw();                                                                                                                      
  std::pair<double,double> cross2=getCrossing(g_theo,m_pObsGraph);
  TLine* line2 = new TLine(cross2.first,0,cross2.first,cross2.second);
  line2->SetLineColor(kBlack);
  line2->SetLineWidth(2);
  line2->SetLineStyle(3);
  line2->Draw();                                                                                                                      
  */

  if(!overlay) {
    //float atlasX=0.22,atlasY=0.32;
    //float intLumi=20.3;
    TLatex* pLat1=new TLatex();
    pLat1->SetNDC();
    pLat1->SetTextColor(1);
    pLat1->SetTextSize(0.05);
    pLat1->SetTextFont(72);
    //pLat1->DrawLatex(atlasX,atlasY,"ATLAS");
    //pLat1->SetTextFont(42);
    //pLat1->SetTextSize(0.05);
    //TString label="Work in progress";
    //pLat1->DrawLatex(atlasX+0.13,atlasY,label);
    //pLat1->DrawLatex(atlasX,atlasY-0.09,TString::Format("#intLdt = %.1f fb^{-1}, #sqrt{s} = 8 TeV",intLumi));
  }

  if(!overlay) {
    //m_legend = new TLegend(0.2284483,0.6194503,0.545977,0.8710359);
    m_legend = new TLegend(0.22,0.6194503,0.56,0.8710359);
  }
  else {
    //m_legend = new TLegend(0.5632184,0.6194503,0.8807471,0.8710359);
    m_legend = new TLegend(0.57,0.6194503,0.91,0.8710359);
  }
  m_legend->SetHeader(m_name.c_str());
  m_legend->SetBorderSize(1);
  m_legend->SetFillColor(kWhite);
  //m_legend->SetFillStyle(1001);
  //m_legend->AddEntry(pExp1sigGraphClone,"Expected limit at 95% CL","L");
  //m_legend->AddEntry(m_pExp1sigGraph,"Expected limit #pm 1 #sigma","F");
  //m_legend->AddEntry(m_pExp2sigGraph,"Expected limit #pm 2 #sigma","F");
  //m_legend->AddEntry(g_theo,"Theory approx. LO","LF");
  m_legend->AddEntry(m_pObsGraph,"95% CL observed limit","LEP");                                                                           
  m_legend->AddEntry(pExp1sigGraphClone,"95% CL expected limit","L");
  m_legend->AddEntry(m_pExp1sigGraph,"#pm 1 #sigma 95% CL expected limit","F");
  m_legend->AddEntry(m_pExp2sigGraph,"#pm 2 #sigma 95% CL expected limit","F");
  m_legend->Draw();
}

void LimitBrasilPlot::plotTheoGraph(bool drawIntersection)
{
  if(drawIntersection) {
    cout << "Finding intersection with expected: " << endl;
    m_theoXsec->plotGraph(m_pExp1sigGraph,kBlack);
    cout << "Finding intersection with median: " << endl;
    m_theoXsec->plotGraph(m_pObsGraph,kBlack);
  }
  else {
    m_theoXsec->plotGraph();
  }
}

class LimitVsMass {
public:
  LimitVsMass(const std::string name, const int type, const int theoXsecType);
  virtual ~LimitVsMass();

  void readFile(const std::string fileName);
  inline std::string getName() const {return m_name;}
  TGraph* getGraph() const {return m_pGraph;}
  void print() const;
  void makePlot(bool drawLegend=true);
  void plotTheoGraph(bool drawIntersection=true);

private:
  std::string m_name;
  int m_type;
  std::vector<Limit*> m_limitVsMass;
  TGraph* m_pGraph;
  TheoXsec* m_theoXsec;
};

LimitVsMass::LimitVsMass(const std::string name, const int type, const int theoXsecType) :
  m_name(name),
  m_type(type),
  m_limitVsMass(),
  m_pGraph(0)
{
  m_theoXsec = new TheoXsec(theoXsecType);
}

LimitVsMass::~LimitVsMass()
{}

void LimitVsMass::plotTheoGraph(bool drawIntersection)
{
  if(drawIntersection) {
    cout << "Finding intersection with graph: " << endl;
    m_theoXsec->plotGraph(m_pGraph,kBlack);
  }
  else {
    m_theoXsec->plotGraph();
  }
}

void LimitVsMass::print() const
{
  cout << " -> Printing LimitVsMass object with name=" << m_name << " and " << m_limitVsMass.size() << " mass points" << endl;
  for(unsigned int i=0; i<m_limitVsMass.size(); ++i) {
    m_limitVsMass[i]->print();
  }
}

void LimitVsMass::readFile(const std::string fileName)
{
  ifstream f(fileName.c_str());
  if(!f) {
    throw runtime_error(Form("ERROR! unable to open file %s",fileName.c_str()));
  }
  else 
    cout << "-> Parsing file " << fileName << endl;

  string line("");
  int NoMassPoints=0;
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
	    cout << "-> creating Limit for mass " << entryMass << endl;
	    Limit* lim=new Limit(m_type,0);
	    lim->setMass(entryMass);
	    m_limitVsMass.push_back(lim);
	  }
	  else if(arr2->GetEntries()==1) {
	    // Goes here when first line is like : 350 & 400 & 500 & ...
	    int entryMass=0;
	    istringstream is(entry.Data());
	    is >> entryMass;
	    Limit* lim=new Limit(m_type,0);
	    lim->setMass(entryMass);
	    m_limitVsMass.push_back(lim);
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
      if((int) m_limitVsMass.size()!=NoMassPoints) {
	cout << "ERROR! m_limitVsMass size and NoMassPoints are different (vec size=" << m_limitVsMass.size() << ", NoMassPoints=" << NoMassPoints << ")" << endl;
	throw runtime_error("->Quitting");
      }
    }
    else { // reading 2nd line
      for (int i=1; i<arr->GetEntries(); ++i) {
	TString tempString = ((TObjString*)arr->At(i))->GetString();
	TString entry = tempString.ReplaceAll(" ","");
	//cout << "entry=" << entry << endl;
	double val=0;
	istringstream is(entry.Data());
	is >> val;
	m_limitVsMass[i-1]->setValue(val);
      }
    }
  }
}

void LimitVsMass::makePlot(bool drawLegend)
{
  // This method is only capable of overlaying a TGraph on already existing TGraphs

  const unsigned int npoints = m_limitVsMass.size();
  m_pGraph = new TGraph(npoints);
  if(m_type==Limit::obs) { 
    m_pGraph->SetMarkerColor(kBlue);
    m_pGraph->SetLineColor(kBlue);
    m_pGraph->SetMarkerStyle(20);
    m_pGraph->SetLineWidth(2);
  }
  else if(m_type==Limit::expMed) { 
    m_pGraph->SetMarkerColor(kBlue);
    m_pGraph->SetLineColor(kBlue);
    m_pGraph->SetMarkerStyle(0);
    m_pGraph->SetLineStyle(9);
    m_pGraph->SetLineWidth(2);
  }
  
  for(unsigned int i=0; i<npoints; ++i) {
    Limit* limit=m_limitVsMass[i];
    cout << "In LimitVsMass::makePlot(...): making graph with following values: " << endl;
    cout << "  -> mass=" << limit->getMass() << endl;
    cout << "  -> x-sec limit=" << limit->getValue()*m_theoXsec->getGeneratedXsec((double) limit->getMass()*1e-3) << endl;
    m_pGraph->SetPoint(i,
		       limit->getMass()*1e-3,
		       limit->getValue()*m_theoXsec->getGeneratedXsec((double) limit->getMass()*1e-3));
  }

  m_pGraph->Draw("CP");
  gPad->SetLogy();

  if(drawLegend) {
    TLegend* leg = new TLegend(0.62,0.52,0.9,0.76);
    leg->SetHeader(m_name.c_str());
    leg->SetBorderSize(1);
    leg->SetFillColor(kWhite);
    leg->SetFillStyle(1001);
    leg->AddEntry(m_pGraph,"Limit at 95% CL","LEP");                                                                           
    leg->Draw();
  }
}
