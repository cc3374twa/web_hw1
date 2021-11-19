all:	
	gcc -o client_deliver client_deliver.c
	gcc -o testserver testserver.c
clean: 
	rm -rf client_deliver testserver GetFileFromClient.txt