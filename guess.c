#include <stdio.h>
#include <stdlib.h>
#include <unac.h>

#define WLEN 5



int len(char *w){
        int l = -1;
        while(w[++l]);
        return l;
}

int hasC(char *w, char c){
        int l = 0;
        while(w[l]){
                if(w[l] == c)
                        return 1;
                ++l;
        }
        return 0;
}

int equals(char *w1, char *w2){
	int l1 = 0, l2 = 0;
	while(w1[l1] && w2[l2] && w1[l1] == w2[l2])
		++l1, ++l2;
	return w1[l1] == w2[l2];
}

char *fill(char *f, int l){
	int lf = len(f);
	char *r = malloc(l*sizeof(char));
	if(lf > l)
		lf = l;
	if(lf < l)
		for(int i = lf; i < l; ++i)
			r[i] = '.';
	for(int i = 0; i < lf; ++i)
		r[i] = f[i];
	return r;
}

size_t getLineCount(FILE *fp){
	size_t lines = 0;
	while(!feof(fp)){
		char ch = fgetc(fp);
		if(ch == '\n') lines++;
	}
	rewind(fp);
	return ++lines;
}


int main(int argc, char *argv[]){
	
	char *green = ".....";
	char *yellow = ".....";
	char *black = ".....";
	int print = 0;


	for(int i = 1; i < argc; ++i){
		if(equals(argv[i], "-g")){
			++i;
			green = fill(argv[i], len(argv[i]));
		}
		if(equals(argv[i], "-y")){
			++i;
			yellow = fill(argv[i], len(argv[i]));
		}
		if(equals(argv[i], "-b")){
			++i;
			black = fill(argv[i], len(argv[i]));
		}
		if(equals(argv[i], "-p"))
			print = 1;
	}
	
	int gl = len(green), yl = len(yellow), bl = len(black);
	
	FILE *fp = fopen(argv[1], "r");
	FILE *sol;
	if(equals(argv[1], "sol.txt"))
		sol = fopen("sol2.txt", "w");
	else
		sol = fopen("sol.txt", "w");

	int lc = getLineCount(fp);

	for(int l = 0; l < lc; ++l){
		char *word;
		size_t len = 0;
		len = getline(&word, &len, fp);
		unac_string("UTF-8", word, len, &word, &len);
		word[len--] = '\0';
		int found = 1;
		
		for(int i = 0; i < gl; ++i)
			if(green[i] != '.' && word[i] != green[i]){
				found = 0;
				break;
			}

		if(found){
			for(int i = 0; i < yl; ++i)
				if(yellow[i] != '.' && !hasC(word, yellow[i]) || word[i] == yellow[i]){
					found = 0;
					break;
				}

			if(found){
				for(int i = 0; i < bl; ++i)
					if(hasC(word, black[i])){
						found = 0;
						break;
					}
			}
		}

		if(found){
			fputs(word, sol);
			if(print)
				printf("%s", word);
		}
	}

	fclose(fp);
	if(equals(argv[1], "sol.txt"))
		rename("sol2.txt", "sol.txt");
	fclose(sol);

	return 0;
}
