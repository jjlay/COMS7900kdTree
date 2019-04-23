

for pid in $(ps -ef | grep `whoami` | grep \<defunct\> | awk '{print $3}'); do kill -9 $pid || true ; done


