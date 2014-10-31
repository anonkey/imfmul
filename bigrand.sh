
echo |awk "{srand()}"
echo|awk "{getline seed < \"seed.txt\";
	for (i=0; i < $1; i++)
	{
	    printf(\"%d\", int((10000000*rand() ) % 10))
        }
   print srand() > \"seed.txt\"}"
