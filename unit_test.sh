#!/bin/sh
i=1
err=0
while [ $i -ne $1 ]
do
    rand1=`./bigrand.sh $i`
    rand2=`./bigrand.sh $i`
    echo "Num 1 : $rand1 | Num 2 : $rand2"
    echo "$rand1 * $rand2">tmpfile
    sysres=`bc < tmpfile | sed 's/\\\//g'|tr -d "\n"`
    usrres=`./a.out $rand1 $rand2`
    if [ "$sysres" != "$usrres" ]
    then
	err=$(( $err + 1 ))
	echo "Erreur au test $i
	sys : $sysres
	usr : $usrres" 1>&2
    fi
    i=$(( $i + 1 ))
done
if [ $err -eq 0 ]
then
    :
else
    echo "Echecs : $err" > 2
fi