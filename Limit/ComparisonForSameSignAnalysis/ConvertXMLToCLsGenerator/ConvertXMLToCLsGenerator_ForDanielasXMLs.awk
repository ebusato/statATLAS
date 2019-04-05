
awk -F "Name|=|FileName|HistoPath|IsSignal|LowSigma|HighValue|Profile|RebinUser|Histo" '
BEGIN{
  inputDir="";
}
{
  gsub("\"","",$0); 
  gsub(">","",$0); 

  if(index($0,"<Channel")) {
    histoName=$7;
    inputDir=$4;
    #print "inputDir="inputDir " histoName="histoName;
  }
  else if(index($0,"<Sample")) {
    if(index($0,"IsSignal")) {
      gsub("4t","",$3);
      printf "\n+sig %s",$3
    } 
    else {
      gsub(" ","",$3);
      gsub("\\\\","",$3);
      gsub("/","",$3);
      gsub("\\^","",$3);
      gsub("{","",$3);
      gsub("}","",$3);
      gsub("-","",$3);
      gsub("+","",$3);
      gsub("4t","",$3);
      printf "\n+bg %s ",$3
    } 
    #fileName="../Files4topContactInt_11dec2014/"inputDir $5;
    fileName="../Files4topSM_11dec2014/"inputDir $5;
    gsub(" ","",fileName);
    system("./ReadYieldAndStatUncert -i "fileName" -h "histoName);
  } 
  else if(index($0,"<GlobalSyst")) {
    print ".syst "$3" "$9" "$7
  }
  else if(index($0,"<Data")) {
    printf "\n+data "
    #fileName="../Files4topContactInt_11dec2014/"inputDir $5;
    fileName="../Files4topSM_11dec2014/"inputDir $5;
    gsub(" ","",fileName);
    system("./ReadYieldAndStatUncert -i "fileName" -h "histoName" -onlyYield");
    print "\n"
  }
}
' $1 
