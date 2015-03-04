if [ $# -eq 2 ]; then
    host=$1
    port=$2
else
    host='127.0.0.1'
    port='8111'
fi

result=$(curl -X POST   --data-binary @../tests/wave/waveFiles/prosze32bit.wav http://${host}:${port}/api/execute | grep "RUN" | grep "ls"| wc -l)
if [ $result -eq 1 ];then
    echo "OK"
    exit 0
else
    echo "ERROR"
    exit 1
fi
