#!/bin/bash

echo "Running tests..."
echo

DATA_DIR="test-data"

TEST_COUNT=0
FAILED_COUNT=0
for f in $(ls $DATA_DIR)
do
    ((TEST_COUNT++))

    WC_COUNT=`wc $DATA_DIR/$f   | sed -e 's/[[:blank:]]//g'`
    MY_COUNT=`./wc $DATA_DIR/$f | sed -e 's/[[:blank:]]//g'`

    if [ "$WC_COUNT" != "$MY_COUNT" ]
    then
        echo $f "FAILED TEST"
        ((FAILED_COUNT++))
    fi
done

echo
echo $TEST_COUNT tests run
echo $FAILED_COUNT failed
