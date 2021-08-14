#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(void)
{
  wchar_t *ws = L"テストtestてすと";
  char ms[100];
  int len;

  setlocale( LC_CTYPE, "jpn" );

  len = wcstombs( ms, ws, 100 );
  printf( "マルチバイト文字長は %dバイト\n", len );
  printf( "マルチバイト文字は %s\n", ms );

  return 0;
}