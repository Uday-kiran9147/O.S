
a=1
b=1
c=2
d=0
echo Enter number 
read n
echo $a
echo $b
while ((c<n))

do 
d=$((a+b))
echo $d
a=$b
b=$d
c=$((c+1))
done
