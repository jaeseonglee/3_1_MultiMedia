/* 20165153 ���缺
	��Ƽ�̵�� ���� 2-2��
*/

#define _CRT_SECURE_NO_WARNINGS		// ������ ������� �ʰ� �ϴ� define
#include <stdio.h>	
#include <math.h>					// ��Ȯ�Ǽ��� ���ϴµ� �־� ����� log�Լ��� ���� Math
#include <string.h>
#define SIZE 2048					// SIZE�� 2048�� define���� ����

// Ȯ�� p�� ���ڷ� �ް� ��Ȯ�Ǽ��� ��ȯ�ϴ� getUncertainty �Լ�
double getUncertainty(double p) { return -(log(p) / log(2)); }

int main(int argc, char* argv[]) {
	char buffer[SIZE];			// ������ ���� ������ buffer
	int size = 0;				// ������ ũ�⸦ ������ size
	double entropy = 0;			// ��Ʈ���Ǹ� ������ entropy

	int cnt = 0;				// �ݺ��Ǵ� ��ȣ�� ������ ������ cnt
	char result[SIZE] = "";		// ���ο� ��ȣ�� �̷���� ����� ������ ���ڿ� result
	int resultSize = 0;			// result�� �� ũ�⸦ ������ resultSize
	int resultArr[5][100] = { {0} };	// ��ȣ���� �󸶳� �ݺ��Ǵ��� ������ resultArr ������ �迭
										// ���� ũ��� A~E(5��) ���� ũ��� �˳��ϰ� 100���� ����

	FILE* fp = fopen("assignment2_text.txt", "r");	// fopen�� ���� ������ ����.

	if (fp == NULL) { return 0; } // ������ ���µ� �����ϸ� return 0;

	while (fgets(buffer, SIZE, fp) != NULL) {}	//  fgets�� ���� ������ �д´�.

	fseek(fp, 0, SEEK_END);		// ���� �����͸� ������ �̵�
	size = ftell(fp);			// ���� ũ�⸦ ����
	fseek(fp, 0, SEEK_SET);		// ���� �����͸� ó������ �̵�

	cnt = 1;			// �ݺ����� �ι�° ���ں��� �����ϰ� �ϱ����� cnt�� 1�� �ʱ�ȭ
	for (int i = 1; i <= size; i++) {	// �ݺ����� ���� ���ο� ��ȣ�� �����
		int num = 0;				// �ӽ� ������ ���� num
		char temp[10] = "";			// ���ڿ��� ������ temp
		char intTemp[10] = "";		// ������ �� ���ڿ��� ������ intTemp

		if (buffer[i-1] == buffer[i]) {	// �չ��ڿ� ���ٸ� 
			cnt++;						// cnt ����
		}
		else {						// ���� ���ڿ� �ٸ��ٸ�
			// �չ����� ��ȣ�� �ľ��Ѵ� (A~E), num�� resultArr�� �࿡�� ���
			if		(buffer[i - 1] == 65) num = 0;	// A	
			else if (buffer[i - 1] == 66) num = 1;  // B
			else if (buffer[i - 1] == 67) num = 2;	// C
			else if (buffer[i - 1] == 68) num = 3;  // D
			else if (buffer[i - 1] == 69) num = 4;  // E
		
			temp[0] = buffer[i - 1];	// buffer[i-1]�� �����̱� ������ temp�� ù��° �ε����� �ʱ�ȭ
			strcat(result, temp);		// strcat�� ���� result ���ڿ��� �̾� �ٿ��ش�.		

			sprintf(intTemp, "%d", cnt);	// sprintf�� ���� �ݺ��� ���� ����� cnt�� intTemp�� ���ڿ��� ����
			strcat(result, intTemp);	// �ٽ� strcat�� ���� result ���ڿ��� �̾� �ٿ��ش�.

			resultArr[num][cnt -1]++;	// num ���� ���� A~E������ ���ڸ� �˰� cnt -1(�ε���)��ġ�� ���� ������Ų��.
			cnt = 1;				// else���� ������� ����, ���� ���������� �ٽ� cnt�� 1�� �ʱ�ȭ
			resultSize++;			// resultSize�� ũ�⸦ ������Ų��.
		}
	}

	printf("������ ��ȣȭ ��� : %s\n����� ���� : %d\n", result, resultSize);		// result ����� ũ�� ���
	printf("result���ڿ��� ���� : %d\n\n\n", strlen(result));		// result�� ��¥ ũ��

	printf("\t�߻�Ȯ��\t\t��Ȯ�Ǽ� \n");			// �� ��ȣ�� �߻�Ȯ���� ��Ȯ�Ǽ� ���
	for (int i = 0, c = 65; i < sizeof(resultArr) / sizeof(resultArr[0]); i++) {		// ��ø �ݺ����� ���� �߻�Ȯ���� ��Ȯ�Ǽ� ��� �� ��Ʈ���� ���
		for (int j = 0; j < sizeof(resultArr[0]) / sizeof(int); j++) {
			if (resultArr[i][j] == 0) continue;		// ���� 0�̶�� �ٽ� �ݺ�
			else {
				// 2���� �迭 �߿����� ���� 1 �̻��� ���� ���, '��ȣ����' ������ ��ȣ�� ������ش�.
				printf("��ȣ %c%-2d %2d / %3d = %.5lf\t%.5lf\n", (char)c, j + 1 ,resultArr[i][j], resultSize,
					resultArr[i][j] /(double) resultSize, getUncertainty(resultArr[i][j] / (double)resultSize));
				// ��ø�ݺ����� ����Ҷ����� ��ȣ�� �ߺ����� �����Ƿ� ���⼭ ��Ʈ���Ǹ� ������ش�.
				entropy += (resultArr[i][j] / (double)resultSize) * (getUncertainty(resultArr[i][j] / (double)resultSize));	// �ݺ��ϸ鼭 ��Ʈ���� ���
			}
		}
		c++;	// ������ �ݺ����� ���� �ϳ��� ����(��) �迭���� ����ϹǷ�(��) c(����)���� ���������ش� 
	}
	
	printf("\n��Ʈ���� : %.5lf\n", entropy);	// ��Ʈ���� ���
	
	

	system("pause");	// system(pause)
	return 0;			// return 0
}