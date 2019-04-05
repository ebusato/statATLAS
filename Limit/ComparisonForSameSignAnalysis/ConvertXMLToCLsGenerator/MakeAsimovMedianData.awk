
awk '
BEGIN {sum=0}

{
  if($1=="+bg") {
    sum+=$3;
  }

  if($1!="+data") 
    print $0
  else 
    print "+data "int(sum+1/3.-0.02*sum);
  
}
' $1
