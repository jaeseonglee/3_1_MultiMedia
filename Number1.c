/* 20165153 이재성
	멀티미디어 과제 2-1번
*/

#define _CRT_SECURE_NO_WARNINGS		// 오류를 출력하지 않게 하는 define
#include <stdio.h>	
#include <math.h>					// 불확실성를 구하는데 있어 사용할 log함수를 위한 Math
#define SIZE 2048					// SIZE에 2048을 define으로 저장

// 확률 p를 인자로 받고 불확실성을 반환하는 getUncertainty 함수
double getUncertainty(double p) { return -(log(p) / log(2)); }

int main(int argc, char* argv[]) {	// main
	char buffer[SIZE];			// 파일의 내용 저장할 buffer
	int arr[5] = { 0 };			// 5개의 문자 개수를 저장할 배열 arr
	int size = 0;				// 파일의 크기를 저장할 size
	double entropy = 0;			// 엔트로피를 저장할 entropy

	FILE* fp = fopen("assignment2_text.txt", "r");	// fopen을 통해 파일을 연다.
	
	if (fp == NULL) { return 0; } // 파일을 여는데 실패하면 return 0;

	while (fgets(buffer, SIZE, fp) != NULL) { }	//  fgets를 통해 파일을 읽는다.

	fseek(fp, 0, SEEK_END);		// 파일 포인터를 끝으로 이동
	size = ftell(fp);			// 파일 크기를 저장
	fseek(fp, 0, SEEK_SET);		// 파일 포인터를 처음으로 이동

	for (int i = 0; i < size; i++) {	// 반복문을 통해 기호의 개수 계산
		if		(buffer[i] == 65) arr[0]++;	// A
		else if (buffer[i] == 66) arr[1]++;	// B
		else if (buffer[i] == 67) arr[2]++;	// C
		else if (buffer[i] == 68) arr[3]++;	// D
		else if (buffer[i] == 69) arr[4]++;	// E
	}

	printf("\t발생확률\t\t불확실성 \n");			// 각 기호의 발생확률과 불확실성 출력
	for (int i = 0, c = 65; i < sizeof(arr) / sizeof(int); i++) {	// 배열의 길이만큼 반복
		printf("기호 %c %4d / %d = %.5lf\t%.5lf\n", (char)c++, arr[i], size, arr[i] / (double)size, getUncertainty(arr[i] / (double)size));
		entropy	+= (arr[i] / (double)size) * (getUncertainty(arr[i] / (double)size));	// 반복하면서 엔트로피 계산
	}

	printf("\n엔트로피 : %.5lf\n", entropy);	// 엔트로피 출력

	fclose(fp);	// fclose를 통해 파일을 닫음
	system("pause");// system(pause)
	return 0;		// return 0
}