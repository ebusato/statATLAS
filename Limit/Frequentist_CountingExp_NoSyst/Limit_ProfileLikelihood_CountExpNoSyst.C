#include <iostream>
#include <vector>

#include "TFile.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TCanvas.h"

#include "AtlasUtils.h"
#include "AtlasUtils.C"
#include "AtlasStyle.C"

void SetHistoStyle(TH1F* h, int color, int marker, int markersize, int fillstyle, TString xtitle, TString ytitle)
{
  //h->Sumw2();
  h->SetLineWidth(2);
  h->SetLineColor(color);
  h->SetMarkerColor(color);
  h->GetXaxis()->SetTitle(xtitle);
  h->GetXaxis()->SetTitleOffset(1);
  h->GetYaxis()->SetTitle(ytitle);
  h->GetYaxis()->SetTitleOffset(1);
  h->GetXaxis()->SetLabelSize(0.045);
  h->GetYaxis()->SetLabelSize(0.045);
  h->SetFillColor(color);
  h->SetFillStyle(fillstyle);  
}

void SetArrowStyle(TArrow* arr, int color)
{
  arr->SetArrowSize(0.02);
  arr->SetLineColor(color);
  arr->SetFillColor(color);
  arr->SetLineWidth(2);
  arr->SetAngle(30);
}

float qmu(float n, float b, float s, float mu)
{
  float L_mu = TMath::Power(b+mu*s,n)*TMath::Exp(-b-mu*s);

  // maximazing the previous likelihood gives muhat = (n-b)/s. The maximum likelihood is therefore :
  float L_muhat = TMath::Power(n,n)*TMath::Exp(-n);

  float q = 0.;

  //if((n-b)/s >0 && (n-b)/s <mu)
    q = -2*TMath::Log(L_mu/L_muhat);
 
  return q;
}

void PrintText(float mu, float b, float s, int nobs)
{
  TString text_b("b = "); text_b+=b;
  myText(0.2,0.87,1,text_b, 0.045);
  TString text_s("s = "); text_s+=s;
  myText(0.2,0.82,1,text_s, 0.045);
  TString text_nobs("nobs = "); text_nobs+=nobs;
  myText(0.2,0.77,1,text_nobs, 0.045);
  TString text_mu("mu = "); text_mu+=mu;
  myText(0.2,0.72,1,text_mu, 0.045);
}

std::vector<TH1F*> sample_qmu(float mu, float b, float s)
{
  //////////////////////////////////////////////////////////////
  // Make sampling distribution
  //////////////////////////////////////////////////////////////

  TH1F* h_qmu_mu = new TH1F("h_qmu_mu","h_qmu_mu",1e3,-12,30);
  TH1F* h_qmu_0 = new TH1F("h_qmu_0","h_qmu_0",1e3,-12,30);

  SetHistoStyle(h_qmu_mu,1,1,1,3002,"q_{#mu}","f(q_{#mu}|#mu)");
  SetHistoStyle(h_qmu_0,4,1,1,0,"q_{#mu}","");

  for(int i =0; i<1e5; ++i) {
    float n_mu0 = gRandom->Poisson(b);
    float n_mu = gRandom->Poisson(b + mu*s);

    float qmu_mu = qmu(n_mu,b,s,mu);
    float qmu_0 = qmu(n_mu0,b,s,mu);

    //std::cout<<qmu_mu<<"  "<<qmu_0<<std::endl;

    h_qmu_mu->Fill(qmu_mu);
    h_qmu_0->Fill(qmu_0);
  }

  h_qmu_mu->Scale(1/h_qmu_mu->Integral());
  h_qmu_0->Scale(1/h_qmu_0->Integral());

  std::vector<TH1F*> vec;
  vec.push_back(h_qmu_mu);
  vec.push_back(h_qmu_0);

  return vec;
}



void Limit(double Nbckg, double Nsig)
{
  SetAtlasStyle();

  double nobs=Nbckg;

  for(float mu=0; mu<100; mu+=1) {

    //mu=15;

    std::vector<TH1F*> vec = sample_qmu(mu,Nbckg,Nsig);

    TH1F* h_qmu_mu = vec[0];
    TH1F* h_qmu_0 = vec[1];
    
    float qmuobs = qmu(nobs,Nbckg,Nsig,mu);
    
    float CLsb = h_qmu_mu->Integral(h_qmu_mu->FindBin(qmuobs),1e3);
    float CLb = h_qmu_0->Integral(h_qmu_0->FindBin(qmuobs),1e3);
    
    std::cout<<mu<<"  "<<CLsb<<"   "<<CLb<<"   "<<CLsb/CLb<<std::endl;

    delete h_qmu_mu;
    delete h_qmu_0;
  }

  // Drawing
  /*h_qmu_mu->GetYaxis()->SetRangeUser(4e-4,0.9);
  h_qmu_mu->Draw();
  h_qmu_0->Draw("same");
  
  TArrow* arr_qmuobs = new TArrow(qmuobs,0.65,qmuobs,0.75,0.02,"<|");
  arr_qmuobs->Draw();

  PrintText(mu,b,s,nobs);
  */

}

int main()
{

  Limit(4.97,0.149);

  return 0;
}
