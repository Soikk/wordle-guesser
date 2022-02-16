#include <stdio.h>
#include <stdlib.h>
#include <unac.h>


int len(char *w){
        int l = -1;
        while(w[++l]);
        return l;
}

char *minimize(char *w){
	int l = len(w);
	char *r = malloc(l*sizeof(char));
	for(int i = 0; i < l; ++i)
		if(w[i] >= 'A' && w[i] <= 'Z')
			r[i] = w[i] - 'A' + 'a';
		else
			r[i] = w[i];
	r[l] = '\0';
	return r;
}

int hasC(char *w, char c){
        int i = 0;
        while(w[i]){
		if(w[i] == c)
			return 1;
		++i;
        }
        return 0;
}

char *append(char *w, char c){
	int l = len(w);
	char *r = malloc((l+1)*sizeof(char));
	for(int i = 0; i < l; ++i)
		r[i] = w[i];
	r[l] = c;
	r[l+1] = '\0';
	return r;
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
		//word = minimize(word);
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
				for(int i = 0; i < bl; ++i){
					if(!hasC(green, black[i]) && !hasC(yellow, black[i])){
						if(hasC(word, black[i])){
							found = 0;
							break;
						}
					}else{
						if(black[i] != '.' && !hasC(word, black[i]) || word[i] == black[i]){
							found = 0;
							break;
						}
					}
				}
			}
		}

		if(found){
			fputs(word, sol);
			if(print)
				printf("%s", word);
		}
		//printf("check\n\n");
	}

	fclose(fp);
	if(equals(argv[1], "sol.txt"))
		rename("sol2.txt", "sol.txt");
	fclose(sol);

	return 0;
}
