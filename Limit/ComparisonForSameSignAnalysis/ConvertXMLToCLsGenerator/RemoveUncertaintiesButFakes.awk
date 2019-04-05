
awk '
BEGIN {section="";}
{
  if(($1=="+sig" || $1=="+bg") && !index($2,"Fakes")) {
    print "\n"$1" "$2" "$3"\n";
    section="other";
  }
  else if(index($2,"Fakes")) {
    print "\n"$1" "$2" "$3" "$4;
    section="fakes";
  }
  else if($1=="+data") {
    print "\n"$1" "$2"\n";
    section="other";
  }

  #print "DEBUG", section;
  #print $0;

  if(section=="fakes" && index($1,".syst")) 
    print $0;
}
' $1
