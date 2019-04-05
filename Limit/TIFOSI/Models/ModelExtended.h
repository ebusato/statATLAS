#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>

class RooWorkspace;

namespace modelextended {
  class Syst {

  public:
    Syst(const std::string& name, const double up, const double down);
    inline std::string getName() const {return m_name;}
    inline double getUp() const {return m_up;}
    inline double getDown() const {return m_down;}

  private:
    Syst();

    std::string m_name;
    double m_up, m_down;
  };

  class Sample {

  public:
    enum {bkg,sig};
    Sample(const int type, const std::string& name, const double yield, const double stat);
    void addSyst(const std::string& name, const double up, const double down);
    void print(const bool printSysts=true) const;
    inline std::string getName() const {return m_name;}
    inline double getYield() const {return m_yield;}
    inline double getStat() const {return m_stat;}
    inline std::vector<Syst*> getSyst() const {return m_syst;}
  
  private:
    int m_type;
    std::string m_name;
    double m_yield,m_stat;
    std::vector<Syst*> m_syst;
  };

  class Channel {
  
  public:
    Channel(const std::string& name);
    inline std::string getName() {return m_name;}
    inline void addBkgSample(Sample* samp) {m_bkgSample.push_back(samp);}
    inline void setSigSample(Sample* samp) {m_pSigSample = samp;}
    inline std::vector<Sample*> getBkgSamples() const {return m_bkgSample;}
    inline Sample* getSigSample() const {return m_pSigSample;}
    inline void setYieldData(const int yield) {m_yieldData=yield;}
    inline int getYieldData() const {return m_yieldData;}

  private:
    std::string m_name;
    int m_yieldData;
    std::vector<Sample*> m_bkgSample;
    Sample* m_pSigSample;
  };

  class ModelExtended {
    
  public:
    enum {normal,logN,gamma};
    ModelExtended(const int statSampling);
    Channel* addChannel(const std::string& channelName, const std::string& fileName);
    void printChannel(const std::string& channelName, const bool printSysts) const;
    RooWorkspace* makeSingleChannelModel(Channel* ch);
    void makeModel(const std::string& outputName="");
    inline RooWorkspace* getWorkspace() {return m_ws;}
    std::pair<std::string,std::string> addAlphaYieldConstraintTerms(RooWorkspace* w, Channel* ch);

  private:
    std::vector<Channel*> m_channel;
    RooWorkspace* m_ws;
    int m_statSampling;
  };
}
#endif // MODEL_H
