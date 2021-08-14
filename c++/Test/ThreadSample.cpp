//マルチスレッドプログラムと mutex の使い方
#include <stdio.h>
#include <windows.h>
#include <process.h>

HANDLE	hMutex; //ミューテックスのハンドル
int main(void);

int count1 = 0; //mutex で変数を保護する
int count2 = 0; //保護しない

unsigned int __stdcall func1(void* pParam)
{
	int	i;
	//while(1){
	for (int j = 0; j < 10; ++j) {
		WaitForSingleObject(hMutex,INFINITE); //mutex 間は他のスレッドから変数を変更できない
		printf("count1:");
		for(i=0;i<10;i++){
			printf("%d:",count1);
			count1++;
			Sleep(50);
		}
		printf("\n");
		ReleaseMutex(hMutex);

		//mutex で変数を保護しないと他のスレッドから変数を変更できる
		printf("count2:");
		for(i=0;i<10;i++){
			printf("%d:",count2);
			count2++;
			Sleep(50);
		}
		printf("\n");
	}

	return 0;
}

unsigned int __stdcall func2(void* pParam)
{
	//while(1){
	for (int j = 0; j < 10; ++j) {
		//mutex で  count1 を保護
		WaitForSingleObject(hMutex,INFINITE);
		count1=0;
		ReleaseMutex(hMutex);

		count2=0;
	}

	return 0;
}

int main(void){
	HANDLE	hThread[2];
	unsigned int thID[2];

	hMutex = CreateMutex(NULL,FALSE,NULL);	//ミューテックス生成

	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, func1, NULL, 0, &(thID[0]));	//スレッド１作成
	hThread[1] = (HANDLE)_beginthreadex(NULL, 0, func2, NULL, 0, &(thID[1]));	//スレッド２作成

	//スレッド１、２終了待ち
	DWORD result = WaitForMultipleObjects(2,hThread,TRUE,INFINITE);

	//ハンドルクローズ
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(hMutex);

	return 0;
}

