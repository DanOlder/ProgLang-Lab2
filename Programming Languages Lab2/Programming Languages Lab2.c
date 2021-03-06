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
int wordleng[7], rwordleng, maxl;
int count;
int kollet;

void leng() {
	for (int i = 0; i != count + 1; i++) {
		wordleng[i] = strlen(word[i]);
	}
	maxl = 0;
	for (int i = 0; i != count + 1; i++) {
		if (maxl < wordleng[i]) maxl = wordleng[i];
	}
	rwordleng = strlen(rword);
}

int proverka() {
	int acount = count + 1;

	int ost = 0;
	for (int j = 1; j != rwordleng + 1; j++)
	{
		int sum = 0;
		for (int i = 0; i != acount; i++) {
			if (wordleng[i] - j < 0) continue;
			int k;
			for (k = 0; word[i][wordleng[i] - j] != tab[k].let; k++);
			sum += tab[k].num;
		}
		sum += ost;
		if (j == rwordleng && sum > 9 && maxl == rwordleng) return 0;
		int k;
		for (k = 0; rword[rwordleng - j] != tab[k].let; k++);
		if (sum % 10 != tab[k].num) return 0;
		else ost = sum / 10;
	}

	for (int i = 0; i != acount; i++) {
		for (int j = 0; j != wordleng[i]; j++) {
			int k;
			for (k = 0; word[i][j] != tab[k].let; k++);
			printf("%d", tab[k].num);
		}
		if (i != count) printf(" + ");
	}
	printf(" = ");
	for (int j = 0; j != rwordleng; j++) {
		int k;
		for (k = 0; rword[j] != tab[k].let; k++);
		printf("%d", tab[k].num);
	}
	printf("\n");

	return 1;
}

int perebor(int q) {
	for (int nmb = 0; nmb < 10; nmb++) {
		//�������� �� ���������� � �� ������ ����� 0
		if (tab[q].ved == 1 && nmb == 0) continue;
		int contin = 0;
		for (int i = q; i != kollet; i++) {
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

	count = 0;	//���-�� ���� -1

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

	for (int i = 0; tab[i].let != '\0'; i++) {
		kollet++;
	}

	leng();

	if (perebor(kollet - 1) != 3) printf("BibleThump\n\n");

	cur_time = clock() - cur_time;
	printf("Process time in ticks: %ld\n", cur_time);
	printf("Process time in seconds: %f\n", (double)cur_time / CLOCKS_PER_SEC);
}