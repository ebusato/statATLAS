///////////////////////////////////////////////////////////
// Usage : 
//  > root -l 'runSignificance.C("ch1.dat")'
//  or
//  > root -l 'runSignificance.C("ch1.dat","ch2.dat")'
//  or
//  > root -l 'runSignificance.C("ch1.dat","ch2.dat","ch3.dat")'
///////////////////////////////////////////////////////////

using namespace RooFit;

void setPlotStyle(TPad* c, RooPlot* frame, const std::string Xtitle, const std::string Ytitle)
{
  frame->SetTitle("");
  //frame->GetXaxis()->SetRangeUser(-50,50);
  frame->GetXaxis()->SetTitle(Xtitle.c_str());
  frame->GetYaxis()->SetTitle(Ytitle.c_str());
  frame->GetXaxis()->SetTitleSize(0.05);
  frame->GetXaxis()->SetTitleOffset(1.42);
  frame->GetXaxis()->SetLabelSize(0.045);
  frame->GetXaxis()->SetLabelOffset(0.017);
  frame->GetYaxis()->SetTitleSize(0.05);
  frame->GetYaxis()->SetTitleOffset(0.74);
  frame->GetYaxis()->SetLabelSize(0);
  frame->GetYaxis()->SetTickLength(0);
}

void runSignificance(const double normalization,
		     const std::string& file1, 
		     const std::string& file2="", 
		     const std::string& file3="",
		     const std::string& file4="", 
		     const std::string& file5="") {
  TStopwatch w;
  w.Start();

  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);

  gSystem->Load("OpTHyLiC_C");
  OpTHyLiC oth(OTH::mclimit,OTH::normal);

  oth.addChannel("ch1",file1);
  if(file2!="")
    oth.addChannel("ch2",file2);
  if(file3!="")
    oth.addChannel("ch3",file3);
  if(file4!="")
    oth.addChannel("ch4",file4);
  if(file5!="")
    oth.addChannel("ch5",file5);

  oth.printSamples();
  
  const int Nexp=5e5;
  //const int Nexp=1e4;
  
  oth.setSigStrength(1);

  oth.generateDistrLLR(Nexp);
  TH1F* hLLRb=oth.getHisto(OpTHyLiC::hLLRb);
  //hLLRb->Scale(1/hLLRb->Integral(0,hLLRb->GetNbinsX()+1,"width"));
  hLLRb->Rebin(20);
  hLLRb->GetXaxis()->SetTitleSize(0.05);
  hLLRb->GetXaxis()->SetTitleOffset(0.88);
  hLLRb->GetXaxis()->SetTitle("q_{ #mu}");
  hLLRb->GetYaxis()->SetTitle("");
  hLLRb->SetLineColor(14);

  double qmuobs=oth.computeLLRdata();

  RooRealVar qmu("qmu","qmu",-70,50);
  RooDataHist* dataHistb = new RooDataHist("dataHistb","dataHistb",RooArgList(qmu),hLLRb);
  RooHistPdf* pdfHistb = new RooHistPdf("pdfHistb","pdfHistb",RooArgSet(qmu),*dataHistb);

  RooPlot* frame = qmu.frame();
  setPlotStyle(c1, frame, "q_{ #mu}", "p(q_{ #mu}| #mu'=0 )");
  pdfHistb->plotOn(frame,LineColor(14),Normalization(1,RooAbsReal::Raw));
  pdfHistb->plotOn(frame,LineColor(14),Normalization(normalization,RooAbsReal::Raw),Range(-100,qmuobs),FillColor(14),FillStyle(3004),DrawOption("F"),VLines());
  frame->GetYaxis()->SetRangeUser(1e-5,8e-2);
  frame->Draw();

  TLatex latex0;
  latex0.SetTextSize(0.045);
  latex0.SetTextColor(14);
  latex0.SetTextColor(9);
  latex0.SetTextColor(kBlack);
  latex0.DrawLatexNDC(0.18,0.85,"OpTHyLiC");

  TArrow* arr = new TArrow(qmuobs,hLLRb->GetMaximum()/5.,qmuobs,0,0.02,"|>");
  arr->SetLineWidth(3);
  arr->SetLineColor(kRed);
  arr->SetFillColor(kRed);
  arr->Draw();
  TLatex latex1;
  latex1.SetTextSize(0.045);
  latex1.SetTextColor(kRed);
  latex1.DrawLatexNDC(0.4,0.7,"q_{ #mu}^{ obs}");

  const int bin=hLLRb->FindBin(qmuobs);
  const double pval=hLLRb->Integral(0,bin);
  const double zval=sqrt(2.)*TMath::ErfInverse(1-2*pval);

  ostringstream os1;
  os1 << int(zval*100)/100.;
  ostringstream os2;
  os2 << int(pval*1e5)/1e5.;

  latex1.SetTextColor(kBlack);
  latex1.DrawLatex(-65,1e-3,Form("p=%s",os2.str().c_str()));
  latex1.DrawLatex(-65,5e-4,Form("Z=%s",os1.str().c_str()));
  w.Stop();

  cout << endl << "Results (cpu time=" << w.CpuTime()<< " sec, real time=" << w.RealTime() << " sec): " << endl;
  cout << " -> p-value=" << pval << endl;
  cout << " -> significance=" << zval << endl;
}

void runSignificance()
{
  TCanvas *c1 = new TCanvas("c1", "c1",600,600,600,600);
  c1->SetLogy();
  c1->SetBottomMargin(0.17);
  c1->SetLeftMargin(0.14);
  runSignificance(0.008,"../Files4topContactInt_11dec2014/Ht+Lt_700_NbbJets_2/CH.All.dat","../Files4topContactInt_11dec2014/Ht+Lt_700_NbbJets_3/CH.All.dat","../Files4topContactInt_11dec2014/Ht+Lt_700_NbbJets_2_METdown_100/CH.All.dat","../Files4topContactInt_11dec2014/Ht+Lt_700_NbbJets_2_METup_100/CH.All.dat","../Files4topContactInt_11dec2014/Ht+Lt_700_NbbJets_3_METup_40/CH.All.dat");

  TLatex latex;
  latex.SetTextSize(0.035);
  latex.SetTextColor(14);
  latex.SetTextColor(9);
  latex.SetTextColor(kBlack);
  latex.DrawLatexNDC(0.18,0.8,"Contact interaction");

  c1->SaveAs("significanceContactInteraction.pdf");

  TCanvas *c2 = new TCanvas("c2", "c2",600,600,600,600);
  c2->SetLogy();
  c2->SetBottomMargin(0.17);
  c2->SetLeftMargin(0.14);
  runSignificance(0.0065,"../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_lowHt.txt","../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_lowHt.txt","../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_lowMET.txt","../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_highMET.txt","../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_highHt_highMET.txt");
  latex.DrawLatexNDC(0.18,0.8,"2UED/RPP");
  latex.DrawLatexNDC(0.18,0.76,"m_{KK}=1000 GeV");

  c2->SaveAs("significanceRPP1000GeV.pdf");
}
