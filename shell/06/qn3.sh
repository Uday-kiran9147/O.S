
echo "a= "
read a
echo "b= "
read b
echo "What Operation Do you Want to Perform"
echo " +, - , / , * "
read o
if [ $o == "+" ]
then
    echo " a + b =  `expr $a + $b` "
fi
if [ $o == "-" ]
then
    echo " a - b =  `expr $a - $b` "
fi

if [ $o == "*" ]
then
    echo " a * b =  `expr $a \* $b` "
fi

if [ $o == "/" ]
then
    echo " a / b =  `expr $a / $b` "
fi

