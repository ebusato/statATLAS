

awk -F "Name|=|FileName|HistoPath|IsSignal|LowSigma|HighValue|Profile|RebinUser" '
{
  gsub("\"","",$0); 
  gsub(">","",$0); 

  if(index($0,"<Channel")) {
    histoName=$6;
  }
  else if(index($0,"<Sample")) {
    if(index($0,"IsSignal")) {
    #if(index($0,"SignalSF")) {
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
      printf "\n+bg %s ",$3
    } 
    fileName="../FilesSgluon_23Sept2014/XMLs/Outputs/"$5;
    #fileName="../FilesSameSignTops_2June2014/"$5;
    system("./ReadYieldAndStatUncert -i "fileName" -h "histoName);
  } 
  #else if(index($0,"<GlobalSyst")&&!index($0,"CRreal")&&!index($0,"CRfake")&&!index($0,"MC")&&!index($0,"stat1")&&!index($0,"stat2")&&!index($0,"stat3")&&!index($0,"stat4")) {
  else if(index($0,"<GlobalSyst")) {
    print ".syst "$3" "$9" "$7
  }
  else if(index($0,"<Data")) {
    printf "\n+data "
    fileName="../FilesSgluon_23Sept2014/XMLs/Outputs/"$5;
    #print fileName;
    system("./ReadYieldAndStatUncert -i "fileName" -h "histoName" -onlyYield");
    print "\n"
  }
}
' $1 
