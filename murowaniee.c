void murowanie(FILE *in, FILE *out,int wiersze,int kolumny) {
    char labirynt[100][100];

    fgetc(in);

    for (int i = 0; i < wiersze; i++) {
        fgets(labirynt[i], sizeof(labirynt[i]), in);
    }

    int zmiany;
    int maksymalnaIteracja = 10000;
    int iteracja = 0;

    do {
        zmiany = 0;
        for (int i = 0; i < wiersze; i++) {
            for (int j = 0; j < kolumny; j++) {
                if (labirynt[i][j] == 'P' || labirynt[i][j] == 'K') {
                    continue;
                }

                int sasiedzi = 0;
                if (i > 0 && labirynt[i - 1][j] == 'X') sasiedzi++;
                if (i < wiersze - 1 && labirynt[i + 1][j] == 'X') sasiedzi++;
                if (j > 0 && labirynt[i][j - 1] == 'X') sasiedzi++;
                if (j < kolumny - 1 && labirynt[i][j + 1] == 'X') sasiedzi++;

                if (sasiedzi == 3) {
                    labirynt[i][j] = 'X';
                    zmiany++;
                }
            }
        }
        iteracja++;
    } while (zmiany != 0 && iteracja < maksymalnaIteracja);

    for (int i = 0; i < wiersze; i++) {
        fprintf(out, "%s", labirynt[i]);
    }
}
