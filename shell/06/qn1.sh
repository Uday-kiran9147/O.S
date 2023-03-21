
echo "Give input"
read a
if [ `expr $a % 2` == 0 ]
then
   echo "$a is even"
else 
   echo "$a is Odd"
fi