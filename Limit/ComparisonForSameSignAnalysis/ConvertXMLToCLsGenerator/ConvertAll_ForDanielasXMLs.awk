
make clean
make NOM=ReadYieldAndStatUncert

#dir="../Files4topContactInt_11dec2014/Ht*/"
dir="../Files4topSM_11dec2014/Ht*/"
allfiles=$dir"*.xml"

ls $allfiles > allfiles.txt

awk '{fileName=$1; sub(".xml",".dat",fileName); system("./ConvertXMLToCLsGenerator_ForDanielasXMLs.awk "$1" > "fileName)}' allfiles.txt

rm -f allfiles.txt
