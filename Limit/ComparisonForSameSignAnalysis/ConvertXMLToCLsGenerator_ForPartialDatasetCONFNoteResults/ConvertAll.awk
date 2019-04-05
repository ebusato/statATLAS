
make clean
make NOM=ReadYieldAndStatUncert

dir="../FilesCONF_10June2014/XMLs/"
allfiles=$dir"CH*.xml"

ls $allfiles > allfiles.txt

awk '{fileName=$1; sub("XMLs","DAT",fileName); sub(".xml",".dat",fileName); system("./ConvertXMLToCLsGenerator.awk "$1" > "fileName)}' allfiles.txt

rm -f allfiles.txt