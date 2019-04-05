#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#include "TCanvas.h"
#include "TGraph.h"
#include "TLatex.h"
#include "TString.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TGraphErrors.h"
#include "TLine.h"
#include "TAxis.h"

double sigma600 = 1.2845;
double sigma800 = 0.11389;
double sigma1000 = 0.011719;
double sigma1200 = 0.0012215;

double getExpThCrossing(TGraph* gE, TGraph* gT, double& ordo){
  /*
  double a = 600., b = 1200.;
  double c=0;

  do{
    c = a + (b-a)/2;
    std::cout << "apr calc new c\t " << a << "  " << b << "  " << c << "  " << gE->Eval(c) << "  " << gT->Eval(c) << std::endl;
    if(gE->Eval(c) < gT->Eval(c))
      a = c;
    else
      b = c;
  } while( (b-a)>0.1 );

  return (b+a)/2;
  */

  double y800E,y800T,y1000E,y1000T;

  double x;

  gE->GetPoint(1,x,y800E);
  gE->GetPoint(2,x,y1000E);
  gT->GetPoint(1,x,y800T);
  gT->GetPoint(2,x,y1000T);

  double penteE = (std::log10(y1000E) - std::log10(y800E)) / .200;
  double ordoE = 0.5 *  (  (std::log10(y1000E) - penteE*1.000)  +  (std::log10(y800E) - penteE*.800)  );

  double penteT = (std::log10(y1000T) - std::log10(y800T)) / .200;
  double ordoT = 0.5 *  (  (std::log10(y1000T) - penteT*1.000)  +  (std::log10(y800T) - penteT*.800)  );

  if(   std::abs(   (std::log10(y1000T) - penteT*1.000)  -  (std::log10(y800T) - penteT*.800)   )   >    0.1*(std::log10(y1000T) - penteT*1.000)){
    std::cout << "Oh oh!" << std::endl;
    std::cout << std::log10(y1000T) - penteT*1.000 << "    " << std::log10(y800T) - penteT*.800 << std::endl;
  }

  double ab = (ordoT - ordoE)/(penteE-penteT);

  ordo = std::pow(10,ab * penteE + ordoE);

  return ab;

}

TStyle* AtlasStyle() 
{
  TStyle *atlasStyle = new TStyle("ATLAS","Atlas style");

  // use plain black on white colors
  Int_t icol=0; // WHITE
  atlasStyle->SetFrameBorderMe(icol);
  atlasStyle->SetFrameFillColor(icol);
  atlasStyle->SetCanvasBorderMode(icol);
  atlasStyle->SetCanvasColor(icol);
  atlasStyle->SetPadBorderMode(icol);
  atlasStyle->SetPadColor(icol);
  atlasStyle->SetStatColor(icol);
  //atlasStyle->SetFillColor(icol); // don't use: white fill color for *all* objects

  // set the paper & margin sizes
  atlasStyle->SetPaperSize(20,26);

  // set margin sizes
//   atlasStyle->SetPadTopMargin(0.05);
//   atlasStyle->SetPadRightMargin(0.05);
//   atlasStyle->SetPadBottomMargin(0.16);
//   atlasStyle->SetPadLeftMargin(0.16);

  // set title offsets (for axis label)
//   atlasStyle->SetTitleXOffset(1.4);
//   atlasStyle->SetTitleYOffset(1.4);

  // use large fonts
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

  // use bold lines and markers
//   atlasStyle->SetMarkerStyle(20);
  atlasStyle->SetMarkerSize(1.2);
  atlasStyle->SetHistLineWidth(2.);
  atlasStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

  // get rid of X error bars 
  //atlasStyle->SetErrorX(0.001);
  // get rid of error bar caps
  atlasStyle->SetEndErrorSize(0.);

  // do not display any of the standard histogram decorations
  atlasStyle->SetOptTitle(0);
  //atlasStyle->SetOptStat(1111);
  atlasStyle->SetOptStat(0);
  //atlasStyle->SetOptFit(1111);
  atlasStyle->SetOptFit(0);

  // put tick marks on top and RHS of plots
  atlasStyle->SetPadTickX(1);
  atlasStyle->SetPadTickY(1);

  atlasStyle->SetLegendBorderSize(0); // from NEW style
  return atlasStyle;

}



void SetStyle()
{
   TStyle* atlasStyle = AtlasStyle();
   gROOT->SetStyle("ATLAS");
   gROOT->ForceStyle();
}



std::vector<TGraph*> getGraphs(const char* fileName){

  std::vector<TGraph*> result,prov;

  TGraph* g = 0;
  double mu600, mu800, mu1000, mu1200;

  ifstream file(fileName);

  if(file.is_open() && file.good()){

    while(!file.eof()){
      std::string line;
      if (!getline(file,line)) break;
      if (!line.empty()) {
	std::istringstream values(line);
	values >> mu600 >> mu800 >> mu1000 >> mu1200;
	g = new TGraph();
	g->SetPoint(0,.600,mu600*sigma600);
	g->SetPoint(1,.800,mu800*sigma800);
	g->SetPoint(2,1.000,mu1000*sigma1000);
	g->SetPoint(3,1.200,mu1200*sigma1200);

	prov.push_back(g);

      }
    }
  }

  for(int i = (int)prov.size(); i < 6; ++i)
    prov.push_back(0);// in case there is no observed limit

  result.push_back(prov[2]);
  result.push_back(prov[1]);
  result.push_back(prov[3]);
  result.push_back(prov[0]);
  result.push_back(prov[4]);
  result.push_back(prov[5]);

  return result;

}



int exclusionFromFile(){

  SetStyle();

  const int nbPtsMasse = 4;

  TCanvas* c = new TCanvas("c","c"/*,700,600*/);
  c->SetBottomMargin(.13);
  TGraph* g = 0;
  TLegend* leg = new TLegend(0.14,0.17,.45,.43);

  double max = sigma600;
  double min = sigma1200;

  std::vector<TGraph*> gVect = getGraphs("/AtlasDisk/users/simon/limites/macro_Loic/v9/output_du_py/stat/mu_Nj2_Nb2_Ht650_MET40.txt"); 
  // devra : [0] = mean ; [1] = +1sigma ; [2] = -1 sigma ; [3] = +2 sigma ; [4] = -2 sigma ; [5] = observe

  for(int i = 0; i < (int)gVect.size(); ++i){
    g = gVect[i];
    if(g->GetN() != nbPtsMasse){
      std::cout << "Problem with graphs" << std::endl;
      return -1;
    } 

    double x=0,y=0;

    for(int j = 0; j < 6; ++j){
      g->GetPoint(j,x,y);
      if(y!=0){
	if(y<min)
	  min=y;
	if(y>max)
	  max=y;
      }
    }

  }

  max*=1.1;
  min*=0.9;

  TGraphAsymmErrors* g1 = new TGraphAsymmErrors();
  TGraphAsymmErrors* g2 = new TGraphAsymmErrors();

  double x=0,y=0,xl=0,yl=0,xh=0,yh=0;

  for(int i = 0; i < nbPtsMasse; ++i){

    gVect[0]->GetPoint(i,x,y);
    g1->SetPoint(i,x,y);
    g2->SetPoint(i,x,y);

    gVect[1]->GetPoint(i,xh,yh);
    gVect[2]->GetPoint(i,xl,yl);

    g1->SetPointError(i,0,0,y-yl,yh-y);

    gVect[3]->GetPoint(i,xh,yh);
    gVect[4]->GetPoint(i,xl,yl);

    g2->SetPointError(i,0,0,y-yl,yh-y);

  }

  g2->SetMaximum(4*max);
  g2->SetMinimum(.15*min);
  g2->SetTitle("Excusion graph - 2UED RPP;m_{KK} [TeV];#sigma #times BR [pb]");

  g2->SetFillStyle(1001);
  g2->SetFillColor(kYellow);

  g2->GetXaxis()->SetTitleOffset(1.2);

  g2->Draw("ALF3");

  g1->SetFillStyle(1001);
  g1->SetFillColor(kGreen);

  g1->Draw("LF3");

  gVect[0]->SetLineStyle(2);
  gVect[0]->SetLineWidth(2);

  gVect[0]->Draw("L");

  gVect[5]->SetLineStyle(1);
  gVect[5]->SetLineWidth(3);
  gVect[5]->SetMarkerStyle(20);
  //gVect[5]->Draw("LP");


  TGraphAsymmErrors* gTh = new TGraphAsymmErrors();
  gTh->SetPoint(0,.600,sigma600);
  gTh->SetPoint(1,.800,sigma800);
  gTh->SetPoint(2,1.000,sigma1000);
  gTh->SetPoint(3,1.200,sigma1200);

  gTh->SetPointError(0,0,0,.5*sigma600,.5*sigma600);
  gTh->SetPointError(1,0,0,.5*sigma800,.5*sigma800);
  gTh->SetPointError(2,0,0,.5*sigma1000,.5*sigma1000);
  gTh->SetPointError(3,0,0,.5*sigma1200,.5*sigma1200);

  gTh->SetLineeColor(kRed);
  gTh->SetLineWidth(2);
  gTh->SetFillColor(kRed);
  gTh->SetFillStyle(3004);
  gTh->Draw("LF3");
  /*
  for(int i = 0; i < 4; ++i){
    std::cout << "Pt " << i << ": mean = ";
    double xx,yy;
    gTh->GetPoint(i,xx,yy);
    std::cout << yy << "; up = " << gTh->GetErrorYhigh(i) << "; down = " << gTh->GetErrorYlow(i) << std::endl;
  }
  */
  TGraph* gTh2 = new TGraph();
  gTh2->SetPoint(0,.600,sigma600);
  gTh2->SetPoint(1,.800,sigma800);
  gTh2->SetPoint(2,1.000,sigma1000);
  gTh2->SetPoint(3,1.200,sigma1200);
  gTh2->SetLineColor(kRed);
  gTh2->SetLineWidth(2);
  gTh2->Draw("L");
  
  leg->AddEntry(gVect[0],"Expected limit at 95% CL","L");
  leg->AddEntry(g1,"Expected limit #pm 1 #sigma","F");
  leg->AddEntry(g2,"Expected limit #pm 2 #sigma","F");
  leg->AddEntry(gTh,"Theory approx. LO","LF");
  //leg->AddEntry(gVect[5],"Observed limit at 95% CL","LEP");

  leg->SetFillStyle(0);

  leg->Draw();

  //from TreeAnalyzer: nice title

  float atlasX=0.49,atlasY=0.79;
  float intLumi=14.324;
  TLatex* pLat1=new TLatex();
  pLat1->SetNDC();
  pLat1->SetTextColor(1);
  pLat1->SetTextSize(0.05);
  pLat1->SetTextFont(72);
  pLat1->DrawLatex(atlasX,atlasY,"ATLAS");
  pLat1->SetTextFont(42);
  pLat1->SetTextSize(0.04);
  TString label="Work in progress";
  pLat1->DrawLatex(atlasX+0.14,atlasY,label);
  pLat1->DrawLatex(atlasX,atlasY-0.09,TString::Format("#intLdt = %.1f fb^{-1}, #sqrt{s} = 8 TeV",intLumi));
  
  pLat1->SetTextFont(42);
  pLat1->SetTextSize(0.04);
  TString statOnly = "Stat only";
  pLat1->DrawLatex(atlasX,atlasY-0.18,statOnly);
  
  c->SetLogy();

  double ord;
  double ab = getExpThCrossing(gVect[5],gTh,ord);

  double ord2;
  double ab2 = getExpThCrossing(g2,gTh,ord2);

  std::cout << "Observed limit: " << ab << " TeV; expected limit: " << ab2 << std::endl;

  TLine* indic = new TLine(ab,0,ab,ord);
  //TLine* indic = new TLine(700,.01,700,1);

  indic->SetLineColor(kRed);
  indic->SetLineWidth(2);
  indic->SetLineStyle(3);
  //indic->Draw();

  TLine* indic2 = new TLine(ab2,0,ab2,ord2);

  indic2->SetLineColor(kBlue);
  indic2->SetLineWidth(2);
  indic2->SetLineStyle(5);
  indic2->Draw();

  return 0;

}

