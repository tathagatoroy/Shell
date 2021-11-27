shell: sh.o overkill.o fg.o execute.o bg.o echo.o kjob.o pinfo.o readline.o relative.o test.o parse.o jobs.o
	 gcc -o shell sh.o overkill.o fg.o execute.o bg.o kjob.o echo.o pinfo.o jobs.o readline.o relative.o test.o parse.o
sh.o: sh.c
	gcc -c -O -w sh.c
parse.o: parse.c
	gcc -c -O -w parse.c
bg.o: bg.c
	gcc -c -O -w bg.c
fg.o: fg.c
	gcc -c -O -w fg.c
overkill.o: overkill.c
	gcc -c -O -w overkill.c
kjob.o: kjob.c
	gcc -c -O -w kjob.c
jobs.o: jobs.c
	gcc -c -O -w jobs.c
execute.o: execute.c
		 gcc -c -O -w execute.c
echo.o: echo.c
	   gcc -c -O -w echo.c
pinfo.o: pinfo.c
		gcc -c -O -w pinfo.c
readline.o: readline.c
		  gcc -c -O -w readline.c
relative.o: relative.c
		  gcc -c -O -w relative.c
test.o: test.c
	   gcc -c -O -w relative.c
	   

	   


