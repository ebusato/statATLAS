
awk '
BEGIN {
  sum=0;
}

{
  if($1=="+bg") {
    sum+=$3;
  }

  print $0
}

END {
  printf "\n+data %.0f\n", sum;
}
' $1