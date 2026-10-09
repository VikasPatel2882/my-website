int minInsertions(char* s) {
    int res = 0;
    int need = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            if (need % 2 != 0) {
                res++;
                need--;
            }
            need += 2;
        } else {
            need--;

            if (need < 0) {
                res++;
                need = 1;
            }
        }
    }

    return res + need;
}