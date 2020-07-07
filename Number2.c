/* 20165153 이재성
	멀티미디어 과제 2-2번
*/

#define _CRT_SECURE_NO_WARNINGS		// 오류를 출력하지 않게 하는 define
#include <stdio.h>	
#include <math.h>					// 불확실성를 구하는데 있어 사용할 log함수를 위한 Math
#include <string.h>
#define SIZE 2048					// SIZE에 2048을 define으로 저장

// 확률 p를 인자로 받고 불확실성을 반환하는 getUncertainty 함수
double getUncertainty(double p) { return -(log(p) / log(2)); }

int main(int argc, char* argv[]) {
	char buffer[SIZE];			// 파일의 내용 저장할 buffer
	int size = 0;				// 파일의 크기를 저장할 size
	double entropy = 0;			// 엔트로피를 저장할 entropy

	int cnt = 0;				// 반복되는 기호의 개수를 저장할 cnt
	char result[SIZE] = "";		// 새로운 기호로 이루어진 결과를 저장할 문자열 result
	int resultSize = 0;			// result의 실 크기를 저장할 resultSize
	int resultArr[5][100] = { {0} };	// 기호들이 얼마나 반복되는지 저장할 resultArr 이차원 배열
										// 행의 크기는 A~E(5개) 열의 크기는 넉넉하게 100으로 선언

	FILE* fp = fopen("assignment2_text.txt", "r");	// fopen을 통해 파일을 연다.

	if (fp == NULL) { return 0; } // 파일을 여는데 실패하면 return 0;

	while (fgets(buffer, SIZE, fp) != NULL) {}	//  fgets를 통해 파일을 읽는다.

	fseek(fp, 0, SEEK_END);		// 파일 포인터를 끝으로 이동
	size = ftell(fp);			// 파일 크기를 저장
	fseek(fp, 0, SEEK_SET);		// 파일 포인터를 처음으로 이동

	cnt = 1;			// 반복문이 두번째 문자부터 시작하게 하기위해 cnt를 1로 초기화
	for (int i = 1; i <= size; i++) {	// 반복문을 통해 새로운 기호를 만든다
		int num = 0;				// 임시 정수형 변수 num
		char temp[10] = "";			// 문자열을 저장할 temp
		char intTemp[10] = "";		// 정수로 된 문자열을 저장할 intTemp

		if (buffer[i-1] == buffer[i]) {	// 앞문자와 같다면 
			cnt++;						// cnt 증가
		}
		else {						// 앞의 문자와 다르다면
			// 앞문자의 기호를 파악한다 (A~E), num은 resultArr의 행에서 사용
			if		(buffer[i - 1] == 65) num = 0;	// A	
			else if (buffer[i - 1] == 66) num = 1;  // B
			else if (buffer[i - 1] == 67) num = 2;	// C
			else if (buffer[i - 1] == 68) num = 3;  // D
			else if (buffer[i - 1] == 69) num = 4;  // E
		
			temp[0] = buffer[i - 1];	// buffer[i-1]은 문자이기 때문에 temp의 첫번째 인덱스로 초기화
			strcat(result, temp);		// strcat을 통해 result 문자열에 이어 붙여준다.		

			sprintf(intTemp, "%d", cnt);	// sprintf를 통해 반복을 통해 저장된 cnt를 intTemp에 문자열로 저장
			strcat(result, intTemp);	// 다시 strcat을 통해 result 문자열에 이어 붙여준다.

			resultArr[num][cnt -1]++;	// num 값을 통해 A~E까지의 문자를 알고 cnt -1(인덱스)위치에 값을 증가시킨다.
			cnt = 1;				// else쪽의 제어문으로 오고, 값을 저장했으니 다시 cnt를 1로 초기화
			resultSize++;			// resultSize의 크기를 증가시킨다.
		}
	}

	printf("런랭스 부호화 결과 : %s\n결과의 길이 : %d\n", result, resultSize);		// result 내용과 크기 출력
	printf("result문자열의 길이 : %d\n\n\n", strlen(result));		// result의 진짜 크기

	printf("\t발생확률\t\t불확실성 \n");			// 각 기호의 발생확률과 불확실성 출력
	for (int i = 0, c = 65; i < sizeof(resultArr) / sizeof(resultArr[0]); i++) {		// 중첩 반복문을 통해 발생확률과 불확실성 출력 및 엔트로피 계산
		for (int j = 0; j < sizeof(resultArr[0]) / sizeof(int); j++) {
			if (resultArr[i][j] == 0) continue;		// 값이 0이라면 다시 반복
			else {
				// 2차원 배열 중에서도 값이 1 이상인 값만 출력, '기호숫자' 형태의 기호로 출력해준다.
				printf("기호 %c%-2d %2d / %3d = %.5lf\t%.5lf\n", (char)c, j + 1 ,resultArr[i][j], resultSize,
					resultArr[i][j] /(double) resultSize, getUncertainty(resultArr[i][j] / (double)resultSize));
				// 중첩반복문이 출력할때마다 기호는 중복되지 않으므로 여기서 엔트로피를 계산해준다.
				entropy += (resultArr[i][j] / (double)resultSize) * (getUncertainty(resultArr[i][j] / (double)resultSize));	// 반복하면서 엔트로피 계산
			}
		}
		c++;	// 안쪽의 반복문은 문자 하나에 대한(행) 배열만을 출력하므로(열) c(문자)값을 증가시켜준다 
	}
	
	printf("\n엔트로피 : %.5lf\n", entropy);	// 엔트로피 출력
	
	

	system("pause");	// system(pause)
	return 0;			// return 0
}