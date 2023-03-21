
echo enter size of n
read n
i=0
sum=0
while [ $i -le $((n-1)) ]
do
read nu
sum=$((sum+nu))
i=$((i+1))
done
echo $sum

