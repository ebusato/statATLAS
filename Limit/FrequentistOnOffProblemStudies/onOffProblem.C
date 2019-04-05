using namespace RooFit ;

void onOffProblem(int Npseudoexp=10000, bool conditionalensemble=false, bool print=false)
{
  ///////////////////////////////////////////
  // Construct the model
  ///////////////////////////////////////////
  RooWorkspace *w = new RooWorkspace("w",kTRUE) ;  
  w->factory("Poisson::model(N[100,0,200],expr::Nexp('mu*S+B',mu[50,0,100],S[1],B[50,0,200]))") ;
  w->factory("Poisson::aux(Bnom[50,0,200],B)") ;
  w->factory("PROD::model2(model,aux)") ;
 
  w->var("N")->setBins(w->var("N")->getMax());
  w->var("Bnom")->setBins(w->var("Bnom")->getMax());

  ///////////////////////////////////////////////////////
  // Initial fit to determine conditionnal estimator 
  // that are then used to generate pseudo-data
  ///////////////////////////////////////////////////////
  RooDataSet data("data","data",RooArgSet(*w->var("N"),*w->var("Bnom"))) ;
  data.add(RooArgSet(*w->var("N"),*w->var("Bnom"))) ;  
  w->var("mu")->setConstant(1);
  w->pdf("model2")->fitTo(data) ;
  cout << "mu fit=" << w->var("mu")->getVal() << endl;
  cout << "B fit=" << w->var("B")->getVal() << endl;
  cout << "pdf value=" << w->pdf("model2")->getVal() << endl;
  //cout << "pdf value=" << w->pdf("model2")->getVal(*(w->var("N"))) << endl;
  //cout << "pdf value=" << w->pdf("model2")->getVal(*(w->var("Bnom"))) << endl;
  //RooArgSet set(*(w->var("N")),*(w->var("Bnom")));
  //cout << "pdf value=" << w->pdf("model2")->getVal(set) << endl;

  ///////////////////////////////////////////
  // generate pseudo-data and plot them
  ///////////////////////////////////////////

  RooDataSet* pseudodata = w->pdf("model2")->generate(RooArgSet(*(w->var("N")),*(w->var("Bnom"))),Npseudoexp);

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
  TH1F* h_muhat = new TH1F("muhat","muhat",100,-20,200);
  TH1F* h_bhat = new TH1F("bhat","bhat",100,0,200);
  TH1F* h_bhathat = new TH1F("bhathat","bhathat",100,0,200);

  for(int i=0; i<pseudodata->numEntries(); ++i) {
    pseudodata->get(i);
    if(print) {
	cout << endl << "pseudoN, pseudoBnom= " << pseudoN->getVal() << "  " << pseudoBnom->getVal() << endl;
    }

    RooDataSet* dataforfit = new RooDataSet("dataforfit","dataforfit",RooArgSet(*w->var("N"),*w->var("Bnom"))) ;

    w->var("N")->setVal(pseudoN->getVal()) ;
    if(conditionalensemble) {
      w->var("Bnom")->setVal(50) ;
    }
    else 
      w->var("Bnom")->setVal(pseudoBnom->getVal()) ;
    dataforfit->add(RooArgSet(*w->var("N"),*w->var("Bnom"))) ;

    // unconditionnal fit
    w->var("mu")->setConstant(0);
    w->pdf("model2")->fitTo(*dataforfit,Verbose(0),PrintLevel(-1),Hesse(1));
    if(print) {
      cout << " o Unconditionnal result" << endl;
      cout << "  -> params mu, B = " << w->var("mu")->getVal() << "  " << w->var("B")->getVal() << endl;
      cout << "  -> pdf value=" << w->pdf("model2")->getVal() << endl;
    }
    h_muhat->Fill(w->var("mu")->getVal());
    h_bhat->Fill(w->var("B")->getVal());
    double denominator=w->pdf("model2")->getVal();

    // conditionnal fit
    w->var("mu")->setVal(50);
    w->var("mu")->setConstant(1);
    w->pdf("model2")->fitTo(*dataforfit,Verbose(0),PrintLevel(-1),Hesse(1));
    if(print) {
      cout << " o Conditionnal result" << endl;
      cout << "  -> params mu, B = " << w->var("mu")->getVal() << "  " << w->var("B")->getVal() << endl;
      cout << "  -> pdf value=" << w->pdf("model2")->getVal() << endl;
    }
    h_bhathat->Fill(w->var("B")->getVal());
    double numerator=w->pdf("model2")->getVal();

    w->var("mu")->setConstant(0);

    double qmu = -2 * TMath::Log(numerator/denominator);
    h_qmu->Fill(qmu);
  }

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
