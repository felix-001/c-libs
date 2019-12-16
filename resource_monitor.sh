#!/bin/sh

#output=/mnt/mmc0/monitor.log
output=/dev/tty
while true
do
    pid=$(ps | grep $1 | grep -v grep | grep -v monitor.sh| grep -v gdb| awk '{print $1}')
    if [ ! -n "$pid" ];then
    	echo "process exit, exit monitor"
    	exit 1
    fi
    time=$(date "+%Y-%m-%d %H:%M:%S")
    mem=$(cat /proc/$pid/status | grep VmRSS | awk {'print $2'})
    echo "["$time"] mem: " $mem>> $output
    system_free_mem=$(free | sed -n '2p' | awk '{print $4}')
    echo "["$time"]" system free mem: $system_free_mem >> $output
    fd_count=$(ls /proc/$pid/fd | wc -l)
    echo "["$time"] fd: " $fd_count >> $output
    cpu_usage=$(top -n 1 | grep $1 | grep -v grep | grep -v gdb | awk '{print $9}')
    echo "["$time"] cpu_usage: " $cpu_usage >> $output
    sleep 3
done
