All: heap1 heap2 heap3
heap1: heap1.c
	gcc -std=c99 -o heap1 heap1.c
heap2: heap2.c
	gcc -std=c99 -m32 -o heap2 heap2.c
heap3: heap3.c
	gcc -std=c99 -m32 -o heap3 heap3.c
