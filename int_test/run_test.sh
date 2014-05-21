#!/bin/bash
function cleanDB  {
sleep 1
if [ -d ../Debug/atabox.db ]; then
        rm -r ../Debug/atabox.db
    fi
    if [ -d atabox.db ]; then
            rm -r atabox.db
        fi
}
cleanDB
../Debug/atabox-server&
sleep 1
test_sctipts=(
    test_method_int_test.sh
    add_method_int_test.sh
    execute_method_int_test.sh
    list_method_int_test.sh
)
for int_test in ${test_sctipts[*]}; do
    echo "Script ${int_test}"
    timeout -s SIGTERM 36 ./$int_test
    if [ $? -ne 0 ]; then
        echo "Test script ${int_test} failed!"
        pkill  -9 -f atabox-server
        cleanDB
        exit 1
    fi
done
echo "All test passed!"
pkill  -9 -f atabox-server
cleanDB
rm *.log
exit 0


