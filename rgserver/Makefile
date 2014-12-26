rg_server:objs/main.o objs/scheduler.o objs/startRegist.o objs/ds_server.o objs/rg_server.o objs/po_sock.o objs/util.o objs/relist.o objs/polist.o 
	gcc objs/main.o objs/shceduler.o objs/startRegist.o objs/ds_server.o objs/rg_server.o objs/po_sock.o objs/util.o objs/relist.o objs/polist.o -lpthread -o rg_server
objs/main.o:src/main.c
	gcc -c src/main.c -o objs/main.o
objs/scheduler.o:src/scheduler.c
	gcc -c src/scheduler.c -o objs/shceduler.o
objs/startRegist.o:src/startRegist.c
	gcc -c src/startRegist.c -o objs/startRegist.o
objs/ds_server.o:src/ds_server.c
	gcc -c src/ds_server.c -o objs/ds_server.o
objs/rg_server.o:src/rg_server.c
	gcc -c src/rg_server.c -o objs/rg_server.o
objs/po_sock.o:src/po_sock.c
	gcc -c src/po_sock.c -o objs/po_sock.o
objs/util.o:src/util.c
	gcc -c src/util.c -o objs/util.o
objs/relist.o:src/relist.c
	gcc -c src/relist.c -o objs/relist.o
objs/polist.o:src/polist.c
	gcc -c src/polist.c -o objs/polist.o
clean:
	rm  objs/*.o rg_server
