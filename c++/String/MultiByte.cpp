#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(void)
{
  wchar_t *ws = L"�e�X�gtest�Ă���";
  char ms[100];
  int len;

  setlocale( LC_CTYPE, "jpn" );

  len = wcstombs( ms, ws, 100 );
  printf( "�}���`�o�C�g�������� %d�o�C�g\n", len );
  printf( "�}���`�o�C�g������ %s\n", ms );

  return 0;
}