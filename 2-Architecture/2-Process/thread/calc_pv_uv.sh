/bin/sh
grep "Total get profile" info | awk -F 'pv count=[\\[\\]]' '{print $2}' | awk -F ']' '{print $1}' > pv
cat pv| awk '{sum+=$1} END {print "Sum = ", sum}' > total_pv
cat pv | awk '{sum+=$1} END {print "Average = ", sum/NR}' > per_pv

grep "Total get profile" info | awk -F 'uv count=[\\[\\]]' '{print $2}' | awk -F ']' '{print $1}' > uv
cat uv| awk '{sum+=$1} END {print "Sum = ", sum}' > total_uv
cat uv | awk '{sum+=$1} END {print "Average = ", sum/NR}' > per_uv
