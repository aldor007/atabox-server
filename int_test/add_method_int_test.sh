if [ $# -eq 2 ]; then
    host=$1
    port=$2
    file_name=$3
else
    host='127.0.0.1'
    port='8111'
    file_name='prosze32bit.wav'
fi

curl_result=$(curl -X POST -v   --data-binary @../test/wave/waveFiles/${file_name} http://${host}:${port}/api/add\?name\=nastepna\&command\=ls)
result=$(echo ${curl_result}| grep "OK" | grep "ls"| wc -l)
echo $curl_result
if [ $result -eq 1 ];then
    echo "OK"
    exit 0
else
    echo "ERROR"
    exit 1
fi
