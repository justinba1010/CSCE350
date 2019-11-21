g++ -std=c++11 -Wall baum.cpp

./a.out < in1.txt > actual1.txt
./a.out < in2.txt > actual2.txt
diff actual1.txt out1.txt
ANSWER=$?

if [ $ANSWER -ne 0 ]; then
  echo Input 1 is wrong
else
  echo Input 1 is good
  diff actual2.txt out2.txt
  ANSWER2=$?
  if [ $ANSWER2 -ne 0 ]; then
    echo Input 2 is wrong
  else
    echo Input 2 is good
  fi
fi

