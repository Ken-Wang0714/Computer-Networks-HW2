all:
	@gcc Iperfer_server.c Iperfer_client.c main.c -o /usr/local/sbin/Iperfer -g
	@echo "create Iperfer to /usr/local/sbin/"
clean:
	@rm -rf /usr/local/sbin/Iperfer
	@echo "rm Iperfer from /usr/local/sbin/"
