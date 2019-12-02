#!/bin/sh

pid=$(ps | grep $1 | grep -v grep | grep -v monitor.sh| awk '{print $1}')
while true
do
    time=$(date "+%Y-%m-%d %H:%M:%S")
    echo $time >> monitor.log
    echo =================== >> monitor.log
    cat /proc/$pid/status | grep VmRSS >> monitor.log
    free >> monitor.log
    fd_count=$(ls /proc/$pid/fd | wc -l)
    echo "fd: "$fd_count >> monitor.log
    echo "  PID  PPID USER     STAT   VSZ %VSZ CPU %CPU COMMAND" >> monitor.log
    top -n 1 | grep $1 | grep -v grep >> monitor.log
    sleep 3
done
