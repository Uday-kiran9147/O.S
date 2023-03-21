
echo Enter number
read a
rev=0
b=0
r=$a
while [ $a -gt 0 ]
do 
b=`expr $a % 10`
temp=`expr $rev \* 10`
rev=`expr  + $b
a=`expr $a / 10`
done
echo Result $rev
