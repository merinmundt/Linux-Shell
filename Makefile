myshell: myShell.o
	gcc -o myshell myShell.c

clean: 
	$(RM) myShell