rg_server:main.o startRegist.o ds_server.o rg_server.o po_sock.o util.o relist.o polist.o 
	gcc main.o startRegist.o ds_server.o rg_server.o po_sock.o util.o relist.o polist.o -lpthread -o rg_server
main.o:src/main.c
	gcc -c src/main.c
startRegist.o:src/startRegist.c
	gcc -c src/startRegist.c
ds_server.o:src/ds_server.c
	gcc -c src/ds_server.c
rg_server.o:src/rg_server.c
	gcc -c src/rg_server.c
po_sock.o:src/po_sock.c
	gcc -c src/po_sock.c
util.o:src/util.c
	gcc -c src/util.c
relist.o:src/relist.c
	gcc -c src/relist.c
polist.o:src/polist.c
	gcc -c src/polist.c
clean:
	rm  *.o rg_server
