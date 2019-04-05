
TH1F* getHisto(const std::string fileName, const std::string histoName, const int color)
{
  TFile* f = new TFile(fileName.c_str(),"read");
  TH1F* h = f->Get(histoName.c_str());
  h->SetLineColor(color);
  return h;
}

void plotMuPosteriorAsimovVsObserved()
{
  TH1F* h2UEDRPP1200 = getHisto("results_2UEDRPP_4nov2014/posteriorMu1000.root","mu",kRed);
  TH1F* h2UEDRPP1200ASIMOV = getHisto("results_2UEDRPP_4nov2014/posteriorMu1000_ASIMOV.root","mu",kBlack);

  h2UEDRPP1200ASIMOV->Rebin(6);
  h2UEDRPP1200->Rebin(6);

  h2UEDRPP1200ASIMOV->Draw("c");
  h2UEDRPP1200->Draw("csame");
  
}
