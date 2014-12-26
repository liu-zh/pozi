st_server:objs/main.o objs/ft_server.o objs/dirlist.o objs/connpool.o objs/dblist.o  objs/dbaccess.o objs/st_server.o objs/po_sock.o  objs/st_client.o objs/util.o objs/polist.o 
	gcc objs/main.o objs/ft_server.o objs/dirlist.o objs/connpool.o objs/dblist.o objs/dbaccess.o objs/st_server.o objs/po_sock.o objs/st_client.o objs/util.o objs/polist.o -L/usr/lib/mysql -lpthread -lmysqlclient -o st_server
objs/main.o:src/main.c
	gcc -c src/main.c -o objs/main.o
objs/ft_server.o:src/ft_server.c
	gcc -c src/ft_server.c -o objs/ft_server.o
objs/connpool.o:src/connpool.c
	gcc -c -I/usr/include src/connpool.c -o objs/connpool.o
objs/dirlist.o:src/dirlist.c
	gcc -c src/dirlist.c -o objs/dirlist.o
objs/dblist.o:src/dblist.c
	gcc -c -I/usr/include src/dblist.c -o objs/dblist.o
objs/dbaccess.o:src/dbaccess.c
	gcc -c -I/usr/include src/dbaccess.c -o objs/dbaccess.o
objs/st_server.o:src/st_server.c
	gcc -c src/st_server.c -o objs/st_server.o
objs/po_sock.o:src/po_sock.c
	gcc -c src/po_sock.c -o objs/po_sock.o
objs/st_client.o:src/st_client.c
	gcc -c src/st_client.c -o objs/st_client.o
objs/util.o:src/util.c
	gcc -c src/util.c -o objs/util.o
objs/polist.o:src/polist.c
	gcc -c src/polist.c -o objs/polist.o
clean:
	rm  objs/*.o st_server
