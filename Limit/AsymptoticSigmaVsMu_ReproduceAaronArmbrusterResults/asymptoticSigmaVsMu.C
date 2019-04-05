using namespace RooFit ;

bool doTilde               = 1;

double getCdf(double mu, const TH1 *pHisto) 
{
  double totalContent=0;
  double cdf=0;

  for(int b=0; b<=pHisto->GetNbinsX()+1; ++b) {
    totalContent+=pHisto->GetBinContent(b);
  }

  for(int b=0; b<=pHisto->GetNbinsX()+1 && pHisto->GetBinCenter(b)<=mu; ++b) {
    cdf+=pHisto->GetBinContent(b);
  }

  cdf=cdf/totalContent;

  return cdf;
}

double getQmu(RooNLLVar* nll, double mu)
{
  double nll_muhat = map_nll_muhat[nll];
  bool isConst = firstPOI->isConstant();
  firstPOI->setConstant(1);
  setMu(mu);
  double nll_val = getNLL(nll);
  firstPOI->setConstant(isConst);
  //cout << "qmu = 2 * (" << nll_val << " - " << nll_muhat << ")" << endl;
  return 2*(nll_val-nll_muhat);
}

double getSigma(RooNLLVar* nll, double mu, double muhat, double& qmu)
{
  qmu = getQmu(nll, mu);
  if (verbose) cout << "qmu = " << qmu << endl;
  if (mu*direction < muhat) return fabs(mu-muhat)/sqrt(qmu);
  else if (muhat < 0 && doTilde) return sqrt(mu*mu-2*mu*muhat*direction)/sqrt(qmu);
  else return (mu-muhat)*direction/sqrt(qmu);
}


void asymptoticSigmaVsMu(int Npseudoexp=10000, bool conditionalensemble=false, bool print=false)
{
  ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(-1);
  RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);

  ///////////////////////////////////////////
  // Construct the model
  ///////////////////////////////////////////
  RooWorkspace *w = new RooWorkspace("w",kTRUE) ;  

  
    // Model 4
  w->factory("Poisson::main(N[200,0,1000],expr::Nexp('mu*S+B',mu[1,-5,5],S[50],B[200,0,1000]))") ;
  w->factory("Gaussian::aux(Bnom[200,0,1000],B,20)") ;
  w->factory("PROD::model(main,aux)") ;
  

  // Model 5
  //w->factory("Poisson::main(N[200,0,1000],expr::Nexp('mu*S+B',mu[1,-5,5],S[50,0,1000],B[200]))") ;
  //w->factory("Gaussian::aux(Snom[50,0,1000],S,5)") ;
  //w->factory("PROD::model(main,aux)") ;

  // Model 1 (no uncertainties)
  //w->factory("Poisson::model(N[200,0,1000],expr::Nexp('mu*S+B',mu[1,-5,5],S[50],B[200]))") ;

  w->var("N")->setBins(w->var("N")->getMax());
  w->var("Bnom")->setBins(w->var("Bnom")->getMax());

  ///////////////////////////////////////////////////////
  // Initial fit to determine conditionnal estimator 
  // that are then used to generate pseudo-data
  ///////////////////////////////////////////////////////

  RooDataSet data("data","data",RooArgSet(*w->var("N"),*w->var("Bnom"))) ;
  data.add(RooArgSet(*w->var("N"),*w->var("Bnom"))) ;
  //RooDataSet data("data","data",RooArgSet(*w->var("N"))) ;
  //data.add(RooArgSet(*w->var("N"))) ;
  w->var("mu")->setVal(0);
  w->var("mu")->setConstant(1);
  w->pdf("model")->fitTo(data);
  cout << "mu fit=" << w->var("mu")->getVal() << endl;
  cout << "B fit=" << w->var("B")->getVal() << endl;
  cout << "pdf value=" << w->pdf("model")->getVal() << endl;
  
  ///////////////////////////////////////////
  // generate pseudo-data and plot them
  ///////////////////////////////////////////

  RooDataSet* pseudodata = w->pdf("model")->generate(RooArgSet(*(w->var("N")),*(w->var("Bnom"))),Npseudoexp);
  //RooDataSet* pseudodata = w->pdf("model")->generate(RooArgSet(*(w->var("N"))),Npseudoexp);

  gROOT->SetStyle("Plain");
  gStyle->SetPadGridX(1);
  TCanvas* c = new TCanvas("c","c",800,400);
  c->Divide(2,1);
  c->cd(1);
  RooPlot* Nframe = w->var("N")->frame();
  pseudodata->plotOn(Nframe);
  Nframe->Draw();
  c->cd(2);
  RooPlot* Bnomframe = w->var("Bnom")->frame();
  pseudodata->plotOn(Bnomframe);
  Bnomframe->Draw();
  
  
  ///////////////////////////////////////////
  // loop over pseudo data set 
  ///////////////////////////////////////////

  if(print) {
    cout << endl;
    cout << "Investigating pseudodata set" << endl;
  }

  RooArgSet* obs=pseudodata->get();
  RooRealVar* pseudoN = obs->find("N");
  RooRealVar* pseudoBnom = (RooRealVar*) obs->find("Bnom");

  TH1F* h_qmu = new TH1F("h_qmu","h_qmu",100,0,30);
  TH1F* h_muhat = new TH1F("muhat","muhat",100,-5,5);
  TH1F* h_bhat = new TH1F("bhat","bhat",100,0,1000);
  TH1F* h_bhathat = new TH1F("bhathat","bhathat",100,0,1000);

  for(int i=0; i<pseudodata->numEntries(); ++i) {
    pseudodata->get(i);
    if(print) {
      cout << endl << "pseudoN, pseudoBnom= " << pseudoN->getVal() << "  " << pseudoBnom->getVal() << endl;
      //cout << endl << "pseudoN= " << pseudoN->getVal() << endl;
    }
    
    RooDataSet* dataforfit = new RooDataSet("dataforfit","dataforfit",RooArgSet(*w->var("N"),*w->var("Bnom"))) ;
    //RooDataSet* dataforfit = new RooDataSet("dataforfit","dataforfit",RooArgSet(*w->var("N"))) ;

    w->var("N")->setVal(pseudoN->getVal()) ;
    
    if(conditionalensemble) {
      w->var("Bnom")->setVal(200) ;
    }
    else 
      w->var("Bnom")->setVal(pseudoBnom->getVal()) ;
    dataforfit->add(RooArgSet(*w->var("N"),*w->var("Bnom"))) ;
    //dataforfit->add(RooArgSet(*w->var("N"))) ;

    // unconditionnal fit
    w->var("mu")->setConstant(0);
    w->pdf("model")->fitTo(*dataforfit,PrintLevel(-1));
    if(print) {
      cout << " o Unconditionnal result" << endl;
      cout << "  -> params mu, B = " << w->var("mu")->getVal() << "  " << w->var("B")->getVal() << endl;
      cout << "  -> pdf value=" << w->pdf("model")->getVal() << endl;
    }
    h_muhat->Fill(w->var("mu")->getVal());
    h_bhat->Fill(w->var("B")->getVal());
    double denominator=w->pdf("model")->getVal();

    // conditionnal fit
    w->var("mu")->setVal(0);
    w->var("mu")->setConstant(1);
    w->pdf("model")->fitTo(*dataforfit,PrintLevel(-1));
    if(print) {
      cout << " o Conditionnal result" << endl;
      cout << "  -> params mu, B = " << w->var("mu")->getVal() << "  " << w->var("B")->getVal() << endl;
      cout << "  -> pdf value=" << w->pdf("model")->getVal() << endl;
    }
    h_bhathat->Fill(w->var("B")->getVal());
    double numerator=w->pdf("model")->getVal();

    w->var("mu")->setConstant(0);

    double qmu = -2 * TMath::Log(numerator/denominator);
    h_qmu->Fill(qmu);
  }

  cout << "h_muhat->Integral()=" << h_muhat->Integral() << endl;

  TGraph* g = new TGraph();
  int counter=0;
  double muprime=0.;

  for(float mu=0.5; mu<2; mu+=0.1) {
    double cdf = getCdf(mu,h_muhat);
    cout << "cdf(mu=" << mu << ")=" << cdf << endl;
    if(ROOT::Math::normal_quantile(cdf,1)!=0) {
      double sigma_mu_muprime=(mu-muprime)/ROOT::Math::normal_quantile(cdf,1);
      g->SetPoint(counter,mu,sigma_mu_muprime);
      ++counter;
    }
  }
  
  g->SetMarkerSize(2);
  g->SetMarkerStyle(8);

  TCanvas* cSigma = new TCanvas("cSigma","cSigma",600,600);
  g->Draw("ap");


  TCanvas* cc = new TCanvas("cc","cc",1200,400);
  cc->Divide(3,1);
  cc->cd(1);
  h_muhat->Draw();
  cc->cd(2);
  h_bhat->Draw();
  cc->cd(3);
  h_bhathat->Draw();

  h_qmu->Scale(1/h_qmu->Integral("width"));
  new TCanvas();
  gPad->SetLogy();
  h_qmu->Draw();
  TF1* f = new TF1("f","1*ROOT::Math::chisquared_pdf(x,1,0)", 0,20);
  f->SetLineColor(kBlack);
  f->SetLineStyle(7);
  f->Draw("same");
 
}
