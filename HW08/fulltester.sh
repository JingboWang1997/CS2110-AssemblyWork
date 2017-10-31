#!/bin/bash

#Create the new fulltester folder from imagetester
mkdir fulltester

cp ./examples/diddy/diddy.bmp ./bmptoc
cp ./examples/balloon/balloon.bmp ./bmptoc
cp ./examples/smugcat/smugcat.bmp ./bmptoc
cp ./examples/smwabridged/smwabridged.bmp ./bmptoc


#Make and run the original c files
cd bmptoc
make clean
make
./bmptoc diddy.bmp
./bmptoc balloon.bmp
./bmptoc smugcat.bmp
./bmptoc smwabridged.bmp

echo "[MAKE] New c files have been created successfully"

#Move the new c files to fulltester & clean up the trash
rm bmptoc
mv diddy.h ./../fulltester
mv diddy.c ./../fulltester
mv balloon.h ./../fulltester
mv balloon.c ./../fulltester
mv smugcat.h ./../fulltester
mv smugcat.c ./../fulltester
mv smwabridged.h ./../fulltester
mv smwabridged.c ./../fulltester
rm *.o
rm *.bmp

cd ..

#Copy in the test file & the answer files
cp test/fulltester.c ./fulltester
cp test/diddy/diddyAnswer.h ./fulltester
cp test/diddy/diddyAnswer.c ./fulltester
cp test/balloon/balloonAnswer.h ./fulltester
cp test/balloon/balloonAnswer.c ./fulltester
cp test/smugcat/smugcatAnswer.h ./fulltester
cp test/smugcat/smugcatAnswer.c ./fulltester
cp test/smwabridged/smwabridgedAnswer.h ./fulltester
cp test/smwabridged/smwabridgedAnswer.c ./fulltester

#Make and run the fulltester.c
cd fulltester
gcc fulltester.c    diddyAnswer.c diddy.c    balloonAnswer.c balloon.c    smugcatAnswer.c smugcat.c   smwabridgedAnswer.c smwabridged.c      -o fulltester

./fulltester

# Notify the user of the result of the tests
if [ $? != 4 ]; then
    echo "
*** FAILED: $?/4 tests passed ***"
else
    echo "
*** SUCCESS: 4/4 tests passed ***"
fi

cd ..

# Remove the test folder after completion
rm -r fulltester

#result=0
# echo $result
