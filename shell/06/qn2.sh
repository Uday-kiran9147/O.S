
echo "Leap Year Question"
echo "Give input"
read year
if [ `expr $year % 4 ` -eq 0 ]
then
    echo "$year is leap year"
else
    echo "$year is not leap year"
fi
