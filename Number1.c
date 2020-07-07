/* 20165153 ���缺
	��Ƽ�̵�� ���� 2-1��
*/

#define _CRT_SECURE_NO_WARNINGS		// ������ ������� �ʰ� �ϴ� define
#include <stdio.h>	
#include <math.h>					// ��Ȯ�Ǽ��� ���ϴµ� �־� ����� log�Լ��� ���� Math
#define SIZE 2048					// SIZE�� 2048�� define���� ����

// Ȯ�� p�� ���ڷ� �ް� ��Ȯ�Ǽ��� ��ȯ�ϴ� getUncertainty �Լ�
double getUncertainty(double p) { return -(log(p) / log(2)); }

int main(int argc, char* argv[]) {	// main
	char buffer[SIZE];			// ������ ���� ������ buffer
	int arr[5] = { 0 };			// 5���� ���� ������ ������ �迭 arr
	int size = 0;				// ������ ũ�⸦ ������ size
	double entropy = 0;			// ��Ʈ���Ǹ� ������ entropy

	FILE* fp = fopen("assignment2_text.txt", "r");	// fopen�� ���� ������ ����.
	
	if (fp == NULL) { return 0; } // ������ ���µ� �����ϸ� return 0;

	while (fgets(buffer, SIZE, fp) != NULL) { }	//  fgets�� ���� ������ �д´�.

	fseek(fp, 0, SEEK_END);		// ���� �����͸� ������ �̵�
	size = ftell(fp);			// ���� ũ�⸦ ����
	fseek(fp, 0, SEEK_SET);		// ���� �����͸� ó������ �̵�

	for (int i = 0; i < size; i++) {	// �ݺ����� ���� ��ȣ�� ���� ���
		if		(buffer[i] == 65) arr[0]++;	// A
		else if (buffer[i] == 66) arr[1]++;	// B
		else if (buffer[i] == 67) arr[2]++;	// C
		else if (buffer[i] == 68) arr[3]++;	// D
		else if (buffer[i] == 69) arr[4]++;	// E
	}

	printf("\t�߻�Ȯ��\t\t��Ȯ�Ǽ� \n");			// �� ��ȣ�� �߻�Ȯ���� ��Ȯ�Ǽ� ���
	for (int i = 0, c = 65; i < sizeof(arr) / sizeof(int); i++) {	// �迭�� ���̸�ŭ �ݺ�
		printf("��ȣ %c %4d / %d = %.5lf\t%.5lf\n", (char)c++, arr[i], size, arr[i] / (double)size, getUncertainty(arr[i] / (double)size));
		entropy	+= (arr[i] / (double)size) * (getUncertainty(arr[i] / (double)size));	// �ݺ��ϸ鼭 ��Ʈ���� ���
	}

	printf("\n��Ʈ���� : %.5lf\n", entropy);	// ��Ʈ���� ���

	fclose(fp);	// fclose�� ���� ������ ����
	system("pause");// system(pause)
	return 0;		// return 0
}