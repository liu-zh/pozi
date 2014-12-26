st_client:objs/main.o objs/obtain_service.o objs/dirlist.o objs/po_sock.o  objs/st_client.o objs/util.o objs/polist.o 
	gcc objs/main.o  objs/obtain_service.o objs/dirlist.o objs/po_sock.o objs/st_client.o objs/util.o objs/polist.o -lpthread -o st_client
objs/main.o:src/main.c
	gcc -c src/main.c -o objs/main.o
objs/obtain_service.o:src/obtain_service.c
	gcc -c src/obtain_service.c -o objs/obtain_service.o
objs/dirlist.o:src/dirlist.c
	gcc -c src/dirlist.c -o objs/dirlist.o
objs/po_sock.o:src/po_sock.c 
	gcc -c src/po_sock.c -o objs/po_sock.o
objs/st_client.o:src/st_client.c
	gcc -c src/st_client.c -o objs/st_client.o
objs/util.o:src/util.c
	gcc -c src/util.c -o objs/util.o
objs/polist.o:src/polist.c
	gcc -c src/polist.c -o objs/polist.o
clean:
	rm  objs/*.o st_client
