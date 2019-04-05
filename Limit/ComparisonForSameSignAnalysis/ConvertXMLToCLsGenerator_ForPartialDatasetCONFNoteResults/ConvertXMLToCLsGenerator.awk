

awk -F "Name|=|FileName|HistoPath|IsSignal|LowSigma|HighValue|Profile|RebinUser" '
{
  gsub("\"","",$0); 
  gsub(">","",$0); 

  if(index($0,"<Channel")) {
    histoName=$6;
  }
  else if(index($0,"<Sample")) {
    if(index($0,"SignalSF")) {
      printf "\n+sig %s",$3
    } 
    else {
      printf "\n+bg %s",$3
    } 
    fileName="../FilesCONF_10June2014/XMLs/"$5;
    #print "fileName "$3"="fileName
    system("./ReadYieldAndStatUncert -i "fileName" -h "histoName);
  } 
  else if(index($0,"<GlobalSyst")) {
    print ".syst "$3" "$9" "$7
  }
  else if(index($0,"<Data")) {
    printf "\n+data "
    fileName="../FilesCONF_10June2014/XMLs/"$5;
    #print "fileName Data="fileName;
    system("./ReadYieldAndStatUncert -i "fileName" -h "histoName" -onlyYield");
    print "\n"
  }
}
' $1 
