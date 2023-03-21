echo Enter Table Number :
read n
i=1
for ((i=1;i<=10;i++))
do 
    echo $n x $i =`expr $n \* $i`
done
