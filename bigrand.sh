#!/bin/sh
if [ ! -e seed.txt ]
then
    ./stamp > seed.txt
fi
echo|awk "{getline seed < \"seed.txt\";
	print srand() > \"seed.txt\"
	for (i=0; i < $1; i++)
	{
	    printf(\"%d\", int((10000000*rand() ) % 10))
        }
    }"

