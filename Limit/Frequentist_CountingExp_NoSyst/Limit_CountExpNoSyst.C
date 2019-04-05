//////////////////////////////////////////////////////////////////////////////////////
//
// This macro implements the basic counting experiment upper limit calculation 
// without syst based on the poisson distribution of the expected number of events.
// 
// More details can be found in Cowan's book "Statistical data analysis".
//
// Remark: an even faster implementation would be to compute the observed limit
//         using directly equation 9.18 for b in Cowan's book :
//           mu_observed = (0.5*ROOT::Math::chisquared_quantile(CL,2*(Ndata+1)) - Nbckg)/Nsig
//
//////////////////////////////////////////////////////////////////////////////////////

#include "TH1F"

double pvalue(double Nexp, int N)
{
  return ROOT::Math::poisson_cdf_c(N,Nexp);
}

double Observed(int Ndata, double Nbckg, double Nsig, double CLs=true, double CL=0.95)
{
  double a = 0.;
  double b = 200.;
  double proba = 0.;
  double mu=0.;
  double precision = 0.000001;
  
  while (fabs(proba - (1-CL)) > precision && (a+b)/2. > 0.000000001) {
    
    mu = (a + b) / 2.;
    
    double Nexp = Nbckg + mu*Nsig;
    
    //std::cout<<a<<"   "<<b<<"   "<<mu<<"  "<<proba<<std::endl;
    
    proba = 1 - pvalue(Nexp,Ndata);
    if(CLs) 
      proba = proba/(1 - pvalue(Nbckg,Ndata));

    if(proba > 1-CL) a = mu;
    else b = mu;
  }
  
  //std::cout<<"Observed limit on mu : "<<mu<<" (proba="<<proba<<")"<<std::endl;
  
  return mu;
}

double Expected(double Nbckg, double Nsig, double CL=0.95)
{
  double mu_average = 0;

  int npoints = 10000;

  TRandom rand;

  TH1F* h_mu = new TH1F("h_mu","h_mu",1e3,0,1e2);

  for(int i = 0; i < npoints ; ++i)
    {
      int Ndata = rand.Poisson(Nbckg);

      double mu = Observed(Ndata,Nbckg,Nsig,CL);

      h_mu->Fill(mu);

      mu_average += mu;
    }

  mu_average = mu_average / (float) npoints;

  double* mu_median = new double[1];
  double* probSum = new double[1];
  *probSum = 0.5;
  h_mu->GetQuantiles(1,mu_median,probSum);

  //h_mu->Draw();

  std::cout<<"Expected average limit on mu : "<<mu_average<<std::endl;
  std::cout<<"Expected median limit on mu : "<<*mu_median<<std::endl;

  //return mu_average;
  return *mu_median;

}

