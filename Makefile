a.out: main.o zczyt.o dzielenie.o odczyt.o
	$(CC) $^

main.o: zczyt.h
tab.o: zczyt.h
ruch.o: zczyt.h