#!/bin/sh

pid=$(ps | grep $1 | grep -v grep | grep -v monitor.sh| awk '{print $1}')
while true
do
    time=$(date "+%Y-%m-%d %H:%M:%S")
    echo $time >> monitor.log
    echo =================== >> monitor.log
    cat /proc/$pid/status | grep VmRSS >> monitor.log
    ls /proc/$pid/fd >> monitor.log
    top -n 1 | grep $1 | grep -v grep >> monitor.log
    sleep 5
done
