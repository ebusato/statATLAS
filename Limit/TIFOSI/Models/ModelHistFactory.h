#ifndef MODELHISTFACTORY_H
#define MODELHISTFACTORY_H

#include <iostream>
#include <vector>
#include "RooStats/HistFactory/Channel.h"
#include "RooStats/HistFactory/Measurement.h"

class RooWorkspace;

namespace modelHistFactory {

  class ModelHistFactory {
    
  public:
    ModelHistFactory();
    void printChannel(const std::string& channelName) const;
    RooStats::HistFactory::Channel* addChannel(const std::string& channelName, const std::string& fileName);
    void setConstraintType(const std::string type) {m_constraintType=type;}
    void makeModel();
    inline RooWorkspace* getWorkspace() {return m_ws;}
    void printStatUncert();

  private:
    std::vector<RooStats::HistFactory::Channel*> m_channel;
    bool m_lumiCached;
    double m_lumiSyst;
    std::string m_constraintType;
    RooStats::HistFactory::Measurement* m_meas;
    RooWorkspace* m_ws;
  };
}
#endif // MODELHISTFACTORY_H
