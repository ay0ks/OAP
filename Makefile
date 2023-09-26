.PHONY: all
all:
	gcc -shared -o libOAP.so OAP.c
	cp libOAP.so /usr/lib
	gcc OAP_test.c -lOAP -o oaptest