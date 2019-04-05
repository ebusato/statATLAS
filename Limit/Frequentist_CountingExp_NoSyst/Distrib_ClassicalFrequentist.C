
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

  float L = TMath::Power(b,n)*TMath::Exp(-b);

  float q = -2*TMath::Log(L_mu/L);
 
  return q;
}

void PrintText(float b, float s, int nobs)
{
  TString text_b("b = "); text_b+=b;
  myText(0.2,0.87,1,text_b, 0.045);
  TString text_s("s = "); text_s+=s;
  myText(0.2,0.82,1,text_s, 0.045);
  TString text_nobs("nobs = "); text_nobs+=nobs;
  myText(0.2,0.77,1,text_nobs, 0.045);

}

void sample_qmu(float b, float s=0, int nobs=0)
{
  //////////////////////////////////////////////////////////////
  // Make sampling distribution
  //////////////////////////////////////////////////////////////

  TH1F* h_q1_1 = new TH1F("h_q1_1","h_q1_1",130,-40,18);
  TH1F* h_q4_4 = new TH1F("h_q4_4","h_q4_4",50,-40,18);
  TH1F* h_q10_10 = new TH1F("h_q10_10","h_q10_10",20,-40,18);
  TH1F* h_q15_15 = new TH1F("h_q15_15","h_q15_15",15,-40,18);

  SetHistoStyle(h_q1_1,1,1,1,3002,"q_{#mu}","f(q_{#mu}|#mu)");
  SetHistoStyle(h_q4_4,4,1,1,3002,"q_{#mu}","f(q_{#mu}|#mu)");
  SetHistoStyle(h_q10_10,6,1,1,3002,"q_{#mu}","f(q_{#mu}|#mu)");
  SetHistoStyle(h_q15_15,8,1,1,3002,"q_{#mu}","f(q_{#mu}|#mu)");

  TH1F* h_q1_0 = new TH1F("h_q1_0","h_q1_0",130,-40,18);
  TH1F* h_q4_0 = new TH1F("h_q4_0","h_q4_0",50,-40,18);
  TH1F* h_q10_0 = new TH1F("h_q10_0","h_q10_0",20,-40,18);
  TH1F* h_q15_0 = new TH1F("h_q15_0","h_q15_0",15,-40,18);

  SetHistoStyle(h_q1_0,1,1,1,1,"q_{#mu}","");
  SetHistoStyle(h_q4_0,4,1,1,1,"q_{#mu}","");
  SetHistoStyle(h_q10_0,6,1,1,1,"q_{#mu}","");
  SetHistoStyle(h_q15_0,8,1,1,1,"q_{#mu}","");

  for(int i =0; i<1e5; ++i) {
    float n_mu0 = gRandom->Poisson(b);
    float n_mu1 = gRandom->Poisson(b + 1*s);
    float n_mu4 = gRandom->Poisson(b + 4*s);
    float n_mu10 = gRandom->Poisson(b + 10*s);
    float n_mu15 = gRandom->Poisson(b + 15*s);

    float q1_1 = qmu(n_mu1,b,s,1);
    float q4_4 = qmu(n_mu4,b,s,4);
    float q10_10 = qmu(n_mu10,b,s,10);
    float q15_15 = qmu(n_mu15,b,s,15);

    //std::cout<<q1_1<<"  "<<q4_4<<"  "<<q10_10<<"  "<<q15_15<<std::endl;

    float q1_0 = qmu(n_mu0,b,s,1);
    float q4_0 = qmu(n_mu0,b,s,4);
    float q10_0 = qmu(n_mu0,b,s,10);
    float q15_0 = qmu(n_mu0,b,s,15);

    h_q1_1->Fill(q1_1);
    h_q4_4->Fill(q4_4);
    h_q10_10->Fill(q10_10);
    h_q15_15->Fill(q15_15);

    h_q1_0->Fill(q1_0);
    h_q4_0->Fill(q4_0);
    h_q10_0->Fill(q10_0);
    h_q15_0->Fill(q15_0);
  }

  h_q1_1->Scale(1/h_q1_1->Integral());
  h_q4_4->Scale(1/h_q4_4->Integral());
  h_q10_10->Scale(1/h_q10_10->Integral());
  h_q15_15->Scale(1/h_q15_15->Integral());

  h_q1_0->Scale(1/h_q1_0->Integral());
  h_q4_0->Scale(1/h_q4_0->Integral());
  h_q10_0->Scale(1/h_q10_0->Integral());
  h_q15_0->Scale(1/h_q15_0->Integral());

  //////////////////////////////////////////////////////////////
  // Compute observed test
  //////////////////////////////////////////////////////////////

  float q1obs = qmu(nobs,b,s,1);
  float q4obs = qmu(nobs,b,s,4);
  float q10obs = qmu(nobs,b,s,10);
  float q15obs = qmu(nobs,b,s,15);

  std::cout<<"qmuobs : "<<q1obs<<"  "<<q4obs<<"  "<<q10obs<<"  "<<q15obs<<std::endl;

  TArrow* arr_q1obs = new TArrow(q1obs,0.8,q1obs,2,0.05,"<|");
  TArrow* arr_q4obs = new TArrow(q4obs,0.8,q4obs,2,0.05,"<|");
  TArrow* arr_q10obs = new TArrow(q10obs,0.8,q10obs,2,0.05,"<|");
  TArrow* arr_q15obs = new TArrow(q15obs,0.8,q15obs,2,0.05,"<|");

  SetArrowStyle(arr_q1obs,1);
  SetArrowStyle(arr_q4obs,4);
  SetArrowStyle(arr_q10obs,6);
  SetArrowStyle(arr_q15obs,8);

  //////////////////////////////////////////////////////////////
  // Drawing
  //////////////////////////////////////////////////////////////

  TCanvas* c1 = new TCanvas("c1","c1",500,400);
  c1->SetLogy();
  h_q1_1->GetYaxis()->SetRangeUser(4e-4,5);
  h_q1_1->Draw();
  h_q4_4->Draw("same");
  h_q10_10->Draw("same");
  h_q15_15->Draw("same");

  arr_q1obs->Draw();
  arr_q4obs->Draw();
  arr_q10obs->Draw();
  arr_q15obs->Draw();
  myText(0.65,0.89,1,"observed test stat.", 0.035);

  TLegend* l = new TLegend(0.4,0.75,0.7,0.92);
  l->AddEntry(h_q1_1,"#mu = 1","l");
  l->AddEntry(h_q4_4,"#mu = 4","l");
  l->AddEntry(h_q10_10,"#mu = 10","l");
  l->AddEntry(h_q15_15,"#mu = 15","l");
  l->SetTextSize(0.045);
  l->SetFillStyle(0);
  l->SetBorderSize(0);
  l->Draw("same");

  PrintText(b,s,nobs);

  c1->SaveAs("ClassicalFrequentist_1.pdf");


  TCanvas* c2 = new TCanvas("c2","c2",800,600);
  c2->Divide(2,2);
  c2->cd(1);
  gPad->SetLogy();
  h_q1_0->GetYaxis()->SetRangeUser(4e-4,5);
  h_q1_0->GetXaxis()->SetRangeUser(-6,6);
  h_q1_0->Draw();
  h_q1_1->Draw("same");
  arr_q1obs->Draw();
  PrintText(b,s,nobs);
  myText(0.2,0.72,1,"#mu=1", 0.045);
  myText(0.35,0.5,1,"f(q_{1}|1)", 0.045);
  myText(0.65,0.5,1,"f(q_{1}|0)", 0.045);
  c2->cd(2);
  gPad->SetLogy();
  h_q4_0->GetYaxis()->SetRangeUser(4e-4,5);
  h_q4_0->GetXaxis()->SetRangeUser(-15,15);
  h_q4_0->Draw();
  h_q4_4->Draw("same");
  arr_q4obs->Draw();
  PrintText(b,s,nobs);
  myText(0.2,0.72,1,"#mu=4", 0.045);
  myText(0.3,0.5,1,"f(q_{4}|4)", 0.045);
  myText(0.7,0.5,1,"f(q_{4}|0)", 0.045);
  c2->cd(3);
  gPad->SetLogy();
  h_q10_0->GetYaxis()->SetRangeUser(4e-4,5);
  h_q10_0->Draw();
  h_q10_10->Draw("same");
  arr_q10obs->Draw();
  PrintText(b,s,nobs);
  myText(0.2,0.72,1,"#mu=10", 0.045);
  myText(0.35,0.5,1,"f(q_{10}|10)", 0.045);
  myText(0.82,0.7,1,"f(q_{10}|0)", 0.045);
  c2->cd(4);
  gPad->SetLogy();
  h_q15_0->GetYaxis()->SetRangeUser(4e-4,5);
  h_q15_0->Draw();
  h_q15_15->Draw("same");
  arr_q15obs->Draw();
  PrintText(b,s,nobs);
  myText(0.2,0.72,1,"#mu=15", 0.045);
  myText(0.22,0.5,1,"f(q_{15}|15)", 0.045);
  myText(0.82,.74,1,"f(q_{15}|0)", 0.045);

  c2->SaveAs("ClassicalFrequentist_2.pdf");

  return;
}


void go()
{
  SetAtlasStyle();

  sample_qmu(5,0.5,5); // (b,s,nobs)
}
