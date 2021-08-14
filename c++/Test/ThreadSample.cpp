//�}���`�X���b�h�v���O������ mutex �̎g����
#include <stdio.h>
#include <windows.h>
#include <process.h>

HANDLE	hMutex; //�~���[�e�b�N�X�̃n���h��
int main(void);

int count1 = 0; //mutex �ŕϐ���ی삷��
int count2 = 0; //�ی삵�Ȃ�

unsigned int __stdcall func1(void* pParam)
{
	int	i;
	//while(1){
	for (int j = 0; j < 10; ++j) {
		WaitForSingleObject(hMutex,INFINITE); //mutex �Ԃ͑��̃X���b�h����ϐ���ύX�ł��Ȃ�
		printf("count1:");
		for(i=0;i<10;i++){
			printf("%d:",count1);
			count1++;
			Sleep(50);
		}
		printf("\n");
		ReleaseMutex(hMutex);

		//mutex �ŕϐ���ی삵�Ȃ��Ƒ��̃X���b�h����ϐ���ύX�ł���
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
		//mutex ��  count1 ��ی�
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

	hMutex = CreateMutex(NULL,FALSE,NULL);	//�~���[�e�b�N�X����

	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, func1, NULL, 0, &(thID[0]));	//�X���b�h�P�쐬
	hThread[1] = (HANDLE)_beginthreadex(NULL, 0, func2, NULL, 0, &(thID[1]));	//�X���b�h�Q�쐬

	//�X���b�h�P�A�Q�I���҂�
	DWORD result = WaitForMultipleObjects(2,hThread,TRUE,INFINITE);

	//�n���h���N���[�Y
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(hMutex);

	return 0;
}

