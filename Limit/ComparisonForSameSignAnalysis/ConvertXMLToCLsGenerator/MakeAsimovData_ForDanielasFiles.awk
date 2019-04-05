
awk '
BEGIN {sum=0.}

{
  if($1=="+bg") {
    sum+=$3;
  }

  if($1!="+data") 
    print $0
}
END {
    print "\n+data "sum
}
' $1
