a.out: main.o wymiary.o dzielenie.o decoding.o
	$(CC) $^

main.o: funkcje.h
wymiary.o.o: funkcje.h
dzielenie.o: funkcje.h
decoding.o: funkcje.h
