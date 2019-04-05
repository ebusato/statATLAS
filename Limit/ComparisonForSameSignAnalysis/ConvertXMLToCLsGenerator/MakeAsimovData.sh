
rm -f ../Files2UEDRPP_4nov2014/{6,8,10,12}00GeV/*_ASIMOV*.txt
rm -f ../Files4topSM_11dec2014/Ht*/CH*ASIMOV.dat

### Remove all uncertainties

# RPP 600

./MakeAsimovData.awk ../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_lowHt.txt > ../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_lowHt_ASIMOV.txt
./MakeAsimovData.awk ../Files2UEDRPP_4nov2014/600GeV/Opti_highB_lowHt.txt > ../Files2UEDRPP_4nov2014/600GeV/Opti_highB_lowHt_ASIMOV.txt
./MakeAsimovData.awk ../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_lowMET.txt > ../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_lowMET_ASIMOV.txt
./MakeAsimovData.awk ../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_highMET.txt > ../Files2UEDRPP_4nov2014/600GeV/Opti_lowB_highHt_highMET_ASIMOV.txt
./MakeAsimovData.awk ../Files2UEDRPP_4nov2014/600GeV/Opti_highB_highHt_highMET.txt > ../Files2UEDRPP_4nov2014/600GeV/Opti_highB_highHt_highMET_ASIMOV.txt

# RPP 800

./MakeAsimovData.awk ../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_lowHt.txt > ../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_lowHt_ASIMOV.txt
./MakeAsimovData.awk ../Files2UEDRPP_4nov2014/800GeV/Opti_highB_lowHt.txt > ../Files2UEDRPP_4nov2014/800GeV/Opti_highB_lowHt_ASIMOV.txt
./MakeAsimovData.awk ../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_lowMET.txt > ../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_lowMET_ASIMOV.txt
./MakeAsimovData.awk ../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_highMET.txt > ../Files2UEDRPP_4nov2014/800GeV/Opti_lowB_highHt_highMET_ASIMOV.txt
./MakeAsimovData.awk ../Files2UEDRPP_4nov2014/800GeV/Opti_highB_highHt_highMET.txt > ../Files2UEDRPP_4nov2014/800GeV/Opti_highB_highHt_highMET_ASIMOV.txt

# RPP 1000

./MakeAsimovData.awk ../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_lowHt.txt > ../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_lowHt_ASIMOV.txt
./MakeAsimovData.awk ../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_lowHt.txt > ../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_lowHt_ASIMOV.txt
./MakeAsimovData.awk ../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_lowMET.txt > ../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_lowMET_ASIMOV.txt
./MakeAsimovData.awk ../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_highMET.txt > ../Files2UEDRPP_4nov2014/1000GeV/Opti_lowB_highHt_highMET_ASIMOV.txt
./MakeAsimovData.awk ../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_highHt_highMET.txt > ../Files2UEDRPP_4nov2014/1000GeV/Opti_highB_highHt_highMET_ASIMOV.txt

# RPP 1200

./MakeAsimovData.awk ../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_lowHt.txt > ../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_lowHt_ASIMOV.txt
./MakeAsimovData.awk ../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_lowHt.txt > ../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_lowHt_ASIMOV.txt
./MakeAsimovData.awk ../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_lowMET.txt > ../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_lowMET_ASIMOV.txt
./MakeAsimovData.awk ../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_highMET.txt > ../Files2UEDRPP_4nov2014/1200GeV/Opti_lowB_highHt_highMET_ASIMOV.txt
./MakeAsimovData.awk ../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_highHt_highMET.txt > ../Files2UEDRPP_4nov2014/1200GeV/Opti_highB_highHt_highMET_ASIMOV.txt

# 4top contact interaction
./MakeAsimovData_ForDanielasFiles.awk ../Files4topContactInt_11dec2014/Ht+Lt_700_NbbJets_2/CH.All.dat > ../Files4topContactInt_11dec2014/Ht+Lt_700_NbbJets_2/CH.All_ASIMOV.dat
./MakeAsimovData_ForDanielasFiles.awk ../Files4topContactInt_11dec2014/Ht+Lt_700_NbbJets_2_METdown_100/CH.All.dat > ../Files4topContactInt_11dec2014/Ht+Lt_700_NbbJets_2_METdown_100/CH.All_ASIMOV.dat
./MakeAsimovData_ForDanielasFiles.awk ../Files4topContactInt_11dec2014/Ht+Lt_700_NbbJets_2_METup_100/CH.All.dat > ../Files4topContactInt_11dec2014/Ht+Lt_700_NbbJets_2_METup_100/CH.All_ASIMOV.dat
./MakeAsimovData_ForDanielasFiles.awk ../Files4topContactInt_11dec2014/Ht+Lt_700_NbbJets_3/CH.All.dat > ../Files4topContactInt_11dec2014/Ht+Lt_700_NbbJets_3/CH.All_ASIMOV.dat
./MakeAsimovData_ForDanielasFiles.awk ../Files4topContactInt_11dec2014/Ht+Lt_700_NbbJets_3_METup_40/CH.All.dat > ../Files4topContactInt_11dec2014/Ht+Lt_700_NbbJets_3_METup_40/CH.All_ASIMOV.dat

# 4top SM
./MakeAsimovData_ForDanielasFiles.awk ../Files4topSM_11dec2014/Ht+Lt_700_NbbJets_2/CH.All.dat > ../Files4topSM_11dec2014/Ht+Lt_700_NbbJets_2/CH.All_ASIMOV.dat
./MakeAsimovData_ForDanielasFiles.awk ../Files4topSM_11dec2014/Ht+Lt_700_NbbJets_2_METdown_100/CH.All.dat > ../Files4topSM_11dec2014/Ht+Lt_700_NbbJets_2_METdown_100/CH.All_ASIMOV.dat
./MakeAsimovData_ForDanielasFiles.awk ../Files4topSM_11dec2014/Ht+Lt_700_NbbJets_2_METup_100/CH.All.dat > ../Files4topSM_11dec2014/Ht+Lt_700_NbbJets_2_METup_100/CH.All_ASIMOV.dat
./MakeAsimovData_ForDanielasFiles.awk ../Files4topSM_11dec2014/Ht+Lt_700_NbbJets_3/CH.All.dat > ../Files4topSM_11dec2014/Ht+Lt_700_NbbJets_3/CH.All_ASIMOV.dat
./MakeAsimovData_ForDanielasFiles.awk ../Files4topSM_11dec2014/Ht+Lt_700_NbbJets_3_METup_40/CH.All.dat > ../Files4topSM_11dec2014/Ht+Lt_700_NbbJets_3_METup_40/CH.All_ASIMOV.dat
