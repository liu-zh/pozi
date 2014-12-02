st_server:main.o st_server.o po_sock.o  st_client.o util.o polist.o 
	gcc main.o st_server.o po_sock.o st_client.o util.o polist.o -lpthread -o st_server
main.o:src/main.c
	gcc -c src/main.c
st_server.o:src/st_server.c
	gcc -c src/st_server.c
po_sock.o:src/po_sock.c
	gcc -c src/po_sock.c
st_client.o:src/st_client.c
	gcc -c src/st_client.c
util.o:src/util.c
	gcc -c src/util.c
polist.o:src/polist.c
	gcc -c src/polist.c
clean:
	rm  *.o st_server
