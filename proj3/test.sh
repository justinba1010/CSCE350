# The most garbage autotester ever
python3 ./pythongen.py > inputs.txt
echo  Generated Inputs
cat inputs.txt
python3 ./pythonsolve.py < inputs.txt > pythonout.txt
echo  Generated correct solutions 
g++ baum.cc
./a.out pentest < inputs.txt > pentest.txt
echo  Generated pen and paper algorithm solutions 
./a.out karat karatsuba < inputs.txt > karatsuba.txt
echo   Generated karatsuba algorithm solutions 

# To test
# ./test.sh && diff pythonout.txt pentest.txt && diff pythonout.txt karatsuba.txt
PEN=$(diff pythonout.txt pentest.txt)
KARAT=$(diff pythonout.txt karatsuba.txt)

if [ $PEN ]; then
  echo   Pen Test is a failure 
else
  echo  Pent Test is good 
fi
if [ $KARAT ]; then
  echo  Karatsuba is a failure 
else
  echo  Karatsuba is good 
fi
