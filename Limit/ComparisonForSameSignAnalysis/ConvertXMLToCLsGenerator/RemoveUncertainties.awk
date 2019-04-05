
awk '
{
  if($1=="+sig" || $1=="+bg") {
    print $1" "$2" "$3"\n"
  }
  else if($1=="+data") {
    print $1" "$2"\n"
  }
}
' $1
