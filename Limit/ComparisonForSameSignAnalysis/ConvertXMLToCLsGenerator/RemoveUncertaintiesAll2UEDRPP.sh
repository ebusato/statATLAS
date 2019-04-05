
rm -f ../Files2UEDRPP_4nov2014/{6,8,10,12}00GeV/*_NOUNCERT*.txt

### Remove all uncertainties

# RPP 600

./RemoveUncertainties.awk ../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_lowHt.txt > ../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_lowHt_NOUNCERT.txt
./RemoveUncertainties.awk ../Files2UEDRPP_4nov2014/600GeV/Opti_highB_lowHt.txt > ../Files2UEDRPP_4nov2014/600GeV/Opti_highB_lowHt_NOUNCERT.txt
./RemoveUncertainties.awk ../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_lowMET.txt > ../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_lowMET_NOUNCERT.txt
./RemoveUncertainties.awk ../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_highMET.txt > ../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_highMET_NOUNCERT.txt
./RemoveUncertainties.awk ../Files2UEDRPP_4nov2014/600GeV/Opti_highB_highHt_highMET.txt > ../Files2UEDRPP_4nov2014/600GeV/Opti_highB_highHt_highMET_NOUNCERT.txt

# RPP 800

./RemoveUncertainties.awk ../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_lowHt.txt > ../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_lowHt_NOUNCERT.txt
./RemoveUncertainties.awk ../Files2UEDRPP_4nov2014/800GeV/Opti_highB_lowHt.txt > ../Files2UEDRPP_4nov2014/800GeV/Opti_highB_lowHt_NOUNCERT.txt
./RemoveUncertainties.awk ../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_lowMET.txt > ../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_lowMET_NOUNCERT.txt
./RemoveUncertainties.awk ../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_highMET.txt > ../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_highMET_NOUNCERT.txt
./RemoveUncertainties.awk ../Files2UEDRPP_4nov2014/800GeV/Opti_highB_highHt_highMET.txt > ../Files2UEDRPP_4nov2014/800GeV/Opti_highB_highHt_highMET_NOUNCERT.txt

# RPP 1000

./RemoveUncertainties.awk ../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_lowHt.txt > ../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_lowHt_NOUNCERT.txt
./RemoveUncertainties.awk ../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_lowHt.txt > ../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_lowHt_NOUNCERT.txt
./RemoveUncertainties.awk ../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_lowMET.txt > ../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_lowMET_NOUNCERT.txt
./RemoveUncertainties.awk ../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_highMET.txt > ../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_highMET_NOUNCERT.txt
./RemoveUncertainties.awk ../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_highHt_highMET.txt > ../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_highHt_highMET_NOUNCERT.txt

# RPP 1200

./RemoveUncertainties.awk ../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_lowHt.txt > ../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_lowHt_NOUNCERT.txt
./RemoveUncertainties.awk ../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_lowHt.txt > ../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_lowHt_NOUNCERT.txt
./RemoveUncertainties.awk ../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_lowMET.txt > ../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_lowMET_NOUNCERT.txt
./RemoveUncertainties.awk ../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_highMET.txt > ../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_highMET_NOUNCERT.txt
./RemoveUncertainties.awk ../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_highHt_highMET.txt > ../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_highHt_highMET_NOUNCERT.txt

### Remove all uncertainties but fakes'

# RPP 600

./RemoveUncertaintiesButFakes.awk ../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_lowHt.txt > ../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_lowHt_NOUNCERTBUTFAKES.txt
./RemoveUncertaintiesButFakes.awk ../Files2UEDRPP_4nov2014/600GeV/Opti_highB_lowHt.txt > ../Files2UEDRPP_4nov2014/600GeV/Opti_highB_lowHt_NOUNCERTBUTFAKES.txt
./RemoveUncertaintiesButFakes.awk ../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_lowMET.txt > ../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_lowMET_NOUNCERTBUTFAKES.txt
./RemoveUncertaintiesButFakes.awk ../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_highMET.txt > ../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_highMET_NOUNCERTBUTFAKES.txt
./RemoveUncertaintiesButFakes.awk ../Files2UEDRPP_4nov2014/600GeV/Opti_highB_highHt_highMET.txt > ../Files2UEDRPP_4nov2014/600GeV/Opti_highB_highHt_highMET_NOUNCERTBUTFAKES.txt

# RPP 800

./RemoveUncertaintiesButFakes.awk ../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_lowHt.txt > ../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_lowHt_NOUNCERTBUTFAKES.txt
./RemoveUncertaintiesButFakes.awk ../Files2UEDRPP_4nov2014/800GeV/Opti_highB_lowHt.txt > ../Files2UEDRPP_4nov2014/800GeV/Opti_highB_lowHt_NOUNCERTBUTFAKES.txt
./RemoveUncertaintiesButFakes.awk ../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_lowMET.txt > ../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_lowMET_NOUNCERTBUTFAKES.txt
./RemoveUncertaintiesButFakes.awk ../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_highMET.txt > ../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_highMET_NOUNCERTBUTFAKES.txt
./RemoveUncertaintiesButFakes.awk ../Files2UEDRPP_4nov2014/800GeV/Opti_highB_highHt_highMET.txt > ../Files2UEDRPP_4nov2014/800GeV/Opti_highB_highHt_highMET_NOUNCERTBUTFAKES.txt

# RPP 1000

./RemoveUncertaintiesButFakes.awk ../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_lowHt.txt > ../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_lowHt_NOUNCERTBUTFAKES.txt
./RemoveUncertaintiesButFakes.awk ../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_lowHt.txt > ../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_lowHt_NOUNCERTBUTFAKES.txt
./RemoveUncertaintiesButFakes.awk ../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_lowMET.txt > ../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_lowMET_NOUNCERTBUTFAKES.txt
./RemoveUncertaintiesButFakes.awk ../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_highMET.txt > ../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_highMET_NOUNCERTBUTFAKES.txt
./RemoveUncertaintiesButFakes.awk ../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_highHt_highMET.txt > ../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_highHt_highMET_NOUNCERTBUTFAKES.txt

# RPP 1200

./RemoveUncertaintiesButFakes.awk ../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_lowHt.txt > ../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_lowHt_NOUNCERTBUTFAKES.txt
./RemoveUncertaintiesButFakes.awk ../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_lowHt.txt > ../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_lowHt_NOUNCERTBUTFAKES.txt
./RemoveUncertaintiesButFakes.awk ../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_lowMET.txt > ../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_lowMET_NOUNCERTBUTFAKES.txt
./RemoveUncertaintiesButFakes.awk ../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_highMET.txt > ../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_highMET_NOUNCERTBUTFAKES.txt
./RemoveUncertaintiesButFakes.awk ../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_highHt_highMET.txt > ../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_highHt_highMET_NOUNCERTBUTFAKES.txt

