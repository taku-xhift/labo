/* ���C�u�����R�[�h */
int traverseWith(int array[], size_t length, 
				 int (*callback)(int index, int item, void *param), 
				 void *param)
{
	int exitCode = 0;
	for (int i = 0; i < length; i++) {
		exitCode = callback(i, array[i], param);
		if (exitCode) { 
			break;
		}
	}
	return exitCode;
}

/* �A�v���P�[�V�����R�[�h */
int search (int index, int item, void *param)
{
	if (item > 5) {
		*(int *)param = index;
		return 1;
	} else {
		return 0;
	}
}


int main()
{
	/* ���C�u�������Ăяo���{�� */
	int index;
	int found;
	found = traverseWith(array, length, search, &index);
	if (found) {
		printf("Item %d\n", index);
	} else {
		printf("Not found\n");
	}

	return 0;
}
