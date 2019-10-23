# Linux-Shell
in order to run the make file, simply type "make"
if it compiles correctly without errrors, then you can type ./myshell to run the program.
if you want to run the program with a file, type ./myshell <filename>

RANDOM ERRORS
I do randomly get seg faults that are probably segfaults. But I worked throught them and they started to work again. But it did seg fault again randomly. But it was working perfectly before the segault(so I know I atleast got it to work properly). So I am not sure if you will get a seg fault when you run it or not. But that is with the & sign. 
I commented out the line that gives the seg fault So that you can see that it works correctly, might just see some ("directory does not exist") lines as well. That line is line 179 in myShell.c

I no longer get a seg fault with my pipes. The only issue with pipes is it set up correctly, but I must be missing one thing because it does not print out the actual output. it just returns to the line. if I comment out the close standard output line, it prints out and verifies that it runs through the code. But I am not sure why the output does not come through when the line is not commented out.

I randomly get AbortTrap 6 errors. When strings are too long. I am not sure how to fix this, but things should work with items less that 10 letters. such as "echo hello"

Everything else worked on my computer, 

Thanks!
