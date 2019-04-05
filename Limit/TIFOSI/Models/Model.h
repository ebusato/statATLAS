#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>

class RooWorkspace;

namespace model {
  class Syst {

  public:
    Syst(const std::string& name, const double up, const double down);
    ~Syst();
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
    ~Sample();
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
    ~Channel();
    inline std::string getName() {return m_name;}
    inline void addBkgSample(Sample* samp) {m_bkgSample.push_back(samp);}
    inline void setSigSample(Sample* samp) {m_pSigSample = samp;}
    inline std::vector<Sample*> getBkgSamples() const {return m_bkgSample;}
    inline Sample* getSigSample() const {return m_pSigSample;}
    inline void setYieldData(const float yield) {m_yieldData=yield;}
    inline float getYieldData() const {return m_yieldData;}

  private:
    std::string m_name;
    float m_yieldData;
    std::vector<Sample*> m_bkgSample;
    Sample* m_pSigSample;
  };

  class Model {
    
  public:
    // interExtrapStyle : 0-> piece-wise linear, 1->piece-wise expo, 4->poly interp+expo extrap
    enum {normal,logN,gamma};
    Model(const int statSampling, const int interExtrapStyle=1);
    ~Model();
    Channel* addChannel(const std::string& channelName, const std::string& fileName);
    void printChannel(const std::string& channelName, const bool printSysts) const;
    RooWorkspace* makeSingleChannelModel(Channel* ch);
    void makeModel(const std::string& outputName="");
    inline RooWorkspace* getWorkspace() {return m_ws;}
    void addSampleToWS(RooWorkspace* w, Channel* chan, Sample* samp);
    std::pair<std::string,std::string> addAlphaYieldConstraintTerms(RooWorkspace* w, Channel* ch);

  private:
    std::vector<Channel*> m_channel;
    RooWorkspace* m_ws;
    int m_statSampling;
    int m_interpExtrapStyle; // 0->piece-wise linear, 1->piece-wise log, 2->parabolic with linear, 4->Aaron Armbruster - exponential extrapolation, polynomial interpolation
  };
}
#endif // MODEL_H
