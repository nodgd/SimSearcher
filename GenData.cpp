#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <set>

using namespace std;

const char FILE_NAME[] = "data2.in";
const int N = 1000;
const int Z = 95;
const int MAX_LEN = 10;

void genWord(char * word) {
    int j = 0;
    while (j < MAX_LEN) {
        int t;
        do {
            t = rand() % (Z + 1);
        } while (j == 0 && t == Z);
        if (t == Z) {
            word[j] = 0;
            break;
        } else {
            word[j] = ' ' + t;
            j ++;
        }
    }
}

int main() {
    srand(time(0));
    FILE * f = fopen(FILE_NAME, "w");
    set < string > dict;
    for (int i = 0; i < N; i ++) {
        if (i % (N / 100) == 0) {
            printf("%d / %d\n", i, N);
        }
        static char word[MAX_LEN + 4];
        do {
            genWord(word);
        } while (dict.find(string(word)) != dict.end());
        dict.insert(string(word));
    }
    for (set < string > :: iterator ite = dict.begin(); ite != dict.end(); ite ++) {
        fprintf(f, "%s\n", ite -> c_str());
    }
    fclose(f);
    return 0;
}
