///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Usage : 
// [] root -l 'MakeExclusionPlot("values.txt")'
// where values.txt has the following format :
//
//   mass_1 xsec_theo_1 xsec_excl_obs_1 xsec_excl_expmed_1 xsec_excl_expmed_p1_1 xsec_excl_expmed_p2_1 xsec_excl_expmed_m1_1 xsec_excl_expmed_m2_1        
//   mass_2 xsec_theo_2 xsec_excl_obs_2 xsec_excl_expmed_2 xsec_excl_expmed_p1_2 xsec_excl_expmed_p2_2 xsec_excl_expmed_m1_2 xsec_excl_expmed_m2_2        
//   ....
//   mass_i xsec_theo_i xsec_excl_obs_i xsec_excl_expmed_i xsec_excl_expmed_p1_i xsec_excl_expmed_p2_i xsec_excl_expmed_m1_i xsec_excl_expmed_m2_i
//   ....
//   mass_N xsec_theo_N xsec_excl_obs_N xsec_excl_expmed_N xsec_excl_expmed_p1_N xsec_excl_expmed_p2_N xsec_excl_expmed_m1_N xsec_excl_expmed_m2_N
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <pair>

TStyle* AtlasStyle() 
{
  TStyle *atlasStyle = new TStyle("ATLAS","Atlas style");

  Int_t icol=0; // WHITE
  atlasStyle->SetFrameBorderMode(icol);
  atlasStyle->SetFrameFillColor(icol);
  atlasStyle->SetCanvasBorderMode(icol);
  atlasStyle->SetCanvasColor(icol);
  atlasStyle->SetPadBorderMode(icol);
  atlasStyle->SetPadColor(icol);
  atlasStyle->SetStatColor(icol);
  //atlasStyle->SetFillColor(icol); // don't use: white fill color for *all* objects
  atlasStyle->SetPaperSize(20,26);
  //atlasStyle->SetPadTopMargin(0.05);
  //atlasStyle->SetPadRightMargin(0.05);
  atlasStyle->SetPadBottomMargin(0.16);
  //atlasStyle->SetPadLeftMargin(0.16);
  //atlasStyle->SetTitleXOffset(1.4);
  //atlasStyle->SetTitleYOffset(1.4);
  //Int_t font=72; // Helvetica italics
  Int_t font=42; // Helvetica
  Double_t tsize=0.05;
  atlasStyle->SetTextFont(font);
  atlasStyle->SetTextSize(tsize);
  atlasStyle->SetLabelFont(font,"x");
  atlasStyle->SetTitleFont(font,"x");
  atlasStyle->SetLabelFont(font,"y");
  atlasStyle->SetTitleFont(font,"y");
  atlasStyle->SetLabelFont(font,"z");
  atlasStyle->SetTitleFont(font,"z");
  atlasStyle->SetLabelSize(tsize,"x");
  atlasStyle->SetTitleSize(tsize,"x");
  atlasStyle->SetLabelSize(tsize,"y");
  atlasStyle->SetTitleSize(tsize,"y");
  atlasStyle->SetLabelSize(tsize,"z");
  atlasStyle->SetTitleSize(tsize,"z");
  //atlasStyle->SetMarkerStyle(20);
  atlasStyle->SetMarkerSize(1.2);
  atlasStyle->SetHistLineWidth(2.);
  atlasStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes
  //atlasStyle->SetErrorX(0.001);
  atlasStyle->SetEndErrorSize(0.);
  atlasStyle->SetOptTitle(0);
  //atlasStyle->SetOptStat(1111);
  atlasStyle->SetOptStat(0);
  //atlasStyle->SetOptFit(1111);
  atlasStyle->SetOptFit(0);
  atlasStyle->SetPadTickX(1);
  atlasStyle->SetPadTickY(1);
  atlasStyle->SetLegendBorderSize(0); 

  return atlasStyle;
}

void SetStyle()
{
   TStyle* atlasStyle = AtlasStyle();
   gROOT->SetStyle("ATLAS");
   gROOT->ForceStyle();
}

void getValues(const string file, std::vector<double>& mass, std::vector<double>& xsec_theo, std::vector<double>& xsec_excl_obs, std::vector<double>& xsec_excl_expmed, std::vector<double>& xsec_excl_expmed_p1, std::vector<double>& xsec_excl_expmed_p2, std::vector<double>& xsec_excl_expmed_m1, std::vector<double>& xsec_excl_expmed_m2) 
{
  ifstream f(file.c_str());
  if(!f) {
    cout << "ERROR: unable to open file " << file << " -> QUIT " << endl;
    return;
  }
  else 
    cout << "-> Parsing file " << file << endl;

  string line("");
  double m(0.);
  double theo(0.);
  double excl_obs(0.);
  double excl_expmed(0.);
  double excl_expmed_p1(0.);
  double excl_expmed_p2(0.);
  double excl_expmed_m1(0.);
  double excl_expmed_m2(0.);
  
  for ( ; !f.eof() ; ) {
    if(!getline(f,line)) break;
    if(line.find("#") != string::npos) continue;
    istringstream is(line);
    is >> m >> theo >> excl_obs >> excl_expmed >> excl_expmed_p1 >> excl_expmed_p2 >> excl_expmed_m1 >> excl_expmed_m2;
    mass.push_back(m);
    xsec_theo.push_back(theo);
    xsec_excl_obs.push_back(excl_obs);
    xsec_excl_expmed.push_back(excl_expmed);
    xsec_excl_expmed_p1.push_back(excl_expmed_p1);
    xsec_excl_expmed_p2.push_back(excl_expmed_p2);
    xsec_excl_expmed_m1.push_back(excl_expmed_m1);
    xsec_excl_expmed_m2.push_back(excl_expmed_m2);
  }
}

std::pair<double,double> getCrossing(TGraph* g1, TGraph* g2)
{
  double mass;
  double y1, y2;
  g1->GetPoint(0,mass,y1);
  g2->GetPoint(0,mass,y2);
  bool g2Aboveg1Init = y2 > y1 ? true : false;
  int iInversion;
  for(int i=1; i<g1->GetN(); ++i) {
    g1->GetPoint(i,mass,y1);
    g2->GetPoint(i,mass,y2);
    bool g2Aboveg1 = y2 > y1 ? true : false;
    if(g2Aboveg1Init!=g2Aboveg1) {
      iInversion=i-1;
      break;
    }
  }

  double mass1, mass2;
  double y1_mass1, y2_mass1, y1_mass2, y2_mass2;
  g1->GetPoint(iInversion,mass1,y1_mass1);
  g2->GetPoint(iInversion,mass1,y2_mass1);
  g1->GetPoint(iInversion+1,mass2,y1_mass2);
  g2->GetPoint(iInversion+1,mass2,y2_mass2);

  double pente1 = (std::log10(y1_mass2) - std::log10(y1_mass1))/(mass2 - mass1);
  double ordo1 = std::log10(y1_mass1) - pente1*mass1;
  double pente2 = (std::log10(y2_mass2) - std::log10(y2_mass1))/(mass2 - mass1);
  double ordo2 = std::log10(y2_mass1) - pente2*mass1;
  double x = (ordo2-ordo1)/(pente1-pente2);
  double y = std::pow(10,x * pente1 + ordo1);

  return std::make_pair(x,y);
}


void MakeExclusionPlot(const string file)
{
  SetStyle();

  std::vector<double> mass;
  std::vector<double> xsec_theo;
  std::vector<double> xsec_excl_obs;
  std::vector<double> xsec_excl_expmed;
  std::vector<double> xsec_excl_expmed_p1;
  std::vector<double> xsec_excl_expmed_p2;
  std::vector<double> xsec_excl_expmed_m1;
  std::vector<double> xsec_excl_expmed_m2;

  getValues(file,
	    mass,
	    xsec_theo,
	    xsec_excl_obs,
	    xsec_excl_expmed,
	    xsec_excl_expmed_p1,
	    xsec_excl_expmed_p2,
	    xsec_excl_expmed_m1,
	    xsec_excl_expmed_m2);

  const unsigned int npoints = xsec_theo.size();
  TGraphAsymmErrors* g_theo = new TGraphAsymmErrors(npoints);
  TGraph* g_obs = new TGraph(npoints);
  TGraphAsymmErrors* g_expmed_1sigma = new TGraphAsymmErrors(npoints);
  TGraphAsymmErrors* g_expmed_2sigma = new TGraphAsymmErrors(npoints);

  for(int i=0; i<npoints; ++i) {
    g_theo->SetPoint(i,mass[i],xsec_theo[i]);
    g_theo->SetPointError(i,0.,0.,0.5*xsec_theo[i],0.5*xsec_theo[i]);
    g_obs->SetPoint(i,mass[i],xsec_excl_obs[i]);
    g_expmed_1sigma->SetPoint(i,mass[i],xsec_excl_expmed[i]);
    g_expmed_2sigma->SetPoint(i,mass[i],xsec_excl_expmed[i]);
    g_expmed_1sigma->SetPointError(i,0.,0.,xsec_excl_expmed[i]-xsec_excl_expmed_m1[i],xsec_excl_expmed_p1[i]-xsec_excl_expmed[i]);
    g_expmed_2sigma->SetPointError(i,0.,0.,xsec_excl_expmed[i]-xsec_excl_expmed_m2[i],xsec_excl_expmed_p2[i]-xsec_excl_expmed[i]);
  }

  g_theo->SetMarkerStyle(30);
  g_theo->SetMarkerSize(2);
  g_theo->SetMarkerColor(kRed);
  g_theo->SetLineColor(kRed);
  g_theo->SetLineWidth(2);
  g_theo->SetFillColor(kRed);
  g_theo->SetFillStyle(3004);

  g_obs->SetMarkerStyle(20);
  g_obs->SetMarkerColor(kBlack);
  g_obs->SetLineColor(kBlack);
  g_obs->SetLineWidth(2);

  g_expmed_1sigma->SetMarkerStyle(20);
  g_expmed_1sigma->SetFillColor(kGreen);
  g_expmed_1sigma->SetLineColor(kBlack);
  g_expmed_2sigma->SetTitle("Excusion graph - 2UED RPP;m_{KK} [TeV];#sigma #times BR [pb]");
  g_expmed_2sigma->GetXaxis()->SetTitleOffset(1.2);
  g_expmed_2sigma->GetYaxis()->SetRangeUser(0.00008,3);  
  g_expmed_2sigma->SetFillColor(kYellow);

  TCanvas* c = new TCanvas("c","c",800,600);
  c->cd();
  gPad->SetLogy();
  g_expmed_2sigma->Draw("AF3");
  g_expmed_1sigma->Draw("LF3");
  TGraphAsymmErrors* g_expmed_1sigmaClone = (TGraphAsymmErrors*) g_expmed_1sigma->Clone("g_expmed_2sigmaClone");
  g_expmed_1sigmaClone->SetLineWidth(2);
  g_expmed_1sigmaClone->SetLineStyle(2);  
  g_expmed_1sigmaClone->Draw("LX");
  g_obs->Draw("LP");
  TGraphAsymmErrors* g_theoLine = (TGraphAsymmErrors*) g_theo->Clone("g_theoLine");
  g_theo->Draw("LF3");
  g_theoLine->Draw("LX");

  std::pair<double,double> cross1=getCrossing(g_theo,g_expmed_1sigma);
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

  float atlasX=0.47,atlasY=0.82;
  float intLumi=14.324;
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

  TLegend* leg = new TLegend(0.14,0.17,.45,.43);
  leg->AddEntry(g_expmed_1sigmaClone,"Expected limit at 95% CL","L");
  leg->AddEntry(g_expmed_1sigma,"Expected limit #pm 1 #sigma","F");
  leg->AddEntry(g_expmed_2sigma,"Expected limit #pm 2 #sigma","F");
  leg->AddEntry(g_theo,"Theory approx. LO","LF");
  leg->AddEntry(g_obs,"Observed limit at 95% CL","LEP");                                                                           
  leg->SetFillStyle(0);
  leg->Draw();
}
