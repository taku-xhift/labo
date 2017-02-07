#include <windows.h>
#include <Rts.h>

extern void __stginit_Adder(void);

static char* args[] = { "ghcDll", NULL };
                       /* 注意: argvはNULLで終わっていなければならない */
BOOL
STDCALL
DllMain
   ( HANDLE hModule
   , DWORD reason
   , void* reserved
   )
{
  if (reason == DLL_PROCESS_ATTACH) {
      /* この時点でRTSのDLLはロードされているはずだが、起動する必要がある。*/
      startupHaskell(1, args, __stginit_Adder);
      return TRUE;
  }
  return TRUE;
}
