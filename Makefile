launch:
	cc main.c -o launch
clean:
	rm launch
install: launch
	mv launch /usr/bin/launch
uninstall:
	rm /usr/bin/launch
