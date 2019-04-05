

double* computeQuantiles(const TH1 *pHisto,const bool print)
{
  // compute quantiles
  const int nbQuant=5;
  const double cdf[nbQuant]={0.0228,0.1587,0.5,0.8413,0.9772};
  double* varQ = new double[nbQuant];
  double sum=0,sumPrev=0,varPrev=0;
  for(int b=0,q=0 ; b<=pHisto->GetNbinsX()+1 && q<nbQuant ; ++b) {
    const double val=pHisto->GetBinContent(b);
    if (val>0) {
      sum+=val;
      const double var=pHisto->GetBinLowEdge(b);
      for(; sum>cdf[q] && q<nbQuant ; ++q) {
	if (0==sumPrev) varQ[q]=var;
	else {
	  const double distance=(cdf[q]-sumPrev)/(sum-sumPrev);
	  varQ[q]=varPrev+distance*(var-varPrev);
	}
      }
      varPrev=var;
      sumPrev=sum;
    }
  }

  if(print) {
    cout << "======= Expected signal strengths ==============" << endl;
    const char *names[nbQuant]={"-2 sig","-1 sig","median","+1 sig","+2 sig"};
    for(int q=0 ; q<nbQuant ; ++q) {
      cout << "---> var(" << names[q] << ")=" << varQ[q] << endl;    
    }
  }

  return varQ;
}
