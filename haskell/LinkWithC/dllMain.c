#include <windows.h>
#include <Rts.h>

extern void __stginit_Adder(void);

static char* args[] = { "ghcDll", NULL };
                       /* ����: argv��NULL�ŏI����Ă��Ȃ���΂Ȃ�Ȃ� */
BOOL
STDCALL
DllMain
   ( HANDLE hModule
   , DWORD reason
   , void* reserved
   )
{
  if (reason == DLL_PROCESS_ATTACH) {
      /* ���̎��_��RTS��DLL�̓��[�h����Ă���͂������A�N������K�v������B*/
      startupHaskell(1, args, __stginit_Adder);
      return TRUE;
  }
  return TRUE;
}
