#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct table {
	char let;
	int num;
	int ved;
}tab[10];

char word[7][12], rword[12];
int count;

int kol_let() {
	int kol = 0;
	for (int i = 0; tab[i].let != '\0'; i++) {
		kol++;
	}
	return kol;
}

int proverka() {
	char chis[7][10];
	char res[10] = { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' };
	int ichis[7] = { 0, 0, 0, 0, 0, 0, 0 };
	int ires = 0;

	for (int i = 0; i < 7; i++) {
		memset(chis[i], '\0', 10);
	}

	int acount = count + 1;

	for (int i = 0; i != acount; i++) {
		for (int j = 0; word[i][j] != '\0'; j++) {
			int k;
			for (k = 0; word[i][j] != tab[k].let; k++);
			chis[i][j] = tab[k].num + 48;
		}
	}
	for (int j = 0; rword[j] != '\0'; j++) {
		int k;
		for (k = 0; rword[j] != tab[k].let; k++);
		res[j] = tab[k].num + 48;
	}

	for (int i = 0; i != acount; i++) {//
		ichis[i] = atoi(chis[i]);
	}
	ires = atoi(res);

	int itogo = 0;
	for (int i = 0; i != acount; i++) {
		itogo += ichis[i];
	}
	if (itogo == ires) {
		printf("PogChamp:\n");
		for (int i = 0; i != acount; i++) {
			printf("%d", ichis[i]);
			if (i != count) printf(" + ");
		}
		printf(" = %d\n\n", ires);
		return 1;
	}

	return 0;
}

int perebor(int q) {
	for (int nmb = 0; nmb < 10; nmb++) {
		//проверка на совпадения и на первую цифру 0
		if (tab[q].ved == 1 && nmb == 0) continue;
		int contin = 0;
		for (int i = q; i != kol_let(); i++) {
			if (tab[i].num == nmb) {
				contin = 1;
				break;
			}
		}
		if (contin == 1) continue;
		//

		tab[q].num = nmb;

		if (q > 0) {
			if (perebor(q - 1) == 3)return 3;
		}
		else
			if (proverka()) return 3;
	}
}

void ins(clock_t* cur_time) {
	char str[100];
	fgets(str, 100, stdin);
	printf("\n");

	*cur_time = clock();

	count = 0;	//кол-во слов -1

	for (int i = 0, j = 0; ; i++) {
		if (str[i] == ' ') continue;
		if (str[i] != '+' && str[i] != '=') {
			word[count][j] = str[i];
			//
			int stop = 0, p = 0;
			for (; tab[p].let != NULL; p++) {
				if (tab[p].let == str[i]) {
					stop = 1;
					break;
				}
			}
			if (stop != 1) {
				tab[p].let = str[i];
				if (j == 0) tab[p].ved = 1;
				else tab[p].ved = 0;
			}
			//
			j++;
		}
		if (str[i] == '+') {
			count++;
			j = 0;
		}
		if (str[i] == '=') {
			for (int u = i + 1, j = 0; str[u] != '\n'; u++) {
				if (str[u] != ' ') {
					rword[j] = str[u];
					//
					int stop = 0, p = 0;
					for (; tab[p].let != NULL; p++) {
						if (tab[p].let == str[u]) {
							stop = 1;
							break;
						}
					}
					if (stop != 1) {
						tab[p].let = str[u];
						if (j == 0) tab[p].ved = 1;
						else tab[p].ved = 0;
					}
					//
					j++;
				}
			}
			break;
		}
	}
}

int main()
{
	clock_t cur_time = 0;

	printf("Enter your rebus:\n\n");
	ins(&cur_time);

	if (perebor(kol_let() - 1) != 3) printf("BibleThump\n\n");

	cur_time = clock() - cur_time;
	printf("Process time in ticks: %ld\n", cur_time);
	printf("Process time in seconds: %f\n", (double)cur_time / CLOCKS_PER_SEC);
}