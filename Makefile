all:
	@gcc Iperfer_server.c Iperfer_client.c main.c -o /usr/local/sbin/Iperfer -g
	@echo "create Iperfer_server to /usr/local/sbin/"
clean:
	@rm -rf /usr/local/sbin/Iperfer
	@echo "rm Iperfer_server from /usr/local/sbin/"