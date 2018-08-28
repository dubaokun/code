for pid in $(pgrep $1); do echo -n "${pid} " ; ps -p ${pid} -o lstart | grep -v "START" ; done
