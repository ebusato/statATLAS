
awk '
BEGIN {section="";}
{
  if($1=="+bg" || $1=="+data") {
    print "\n"$0;
    section="other";
  }
  else if($1=="+sig") {
    print "\n"$1" "$2" "$3"\n";
    section="sig";
  }

  if(section=="other" && index($1,".syst")) 
    print $0;
}
' $1
