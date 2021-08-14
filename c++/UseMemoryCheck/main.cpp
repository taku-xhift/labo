
#include <iostream>

#include <windows.h>

int WorkSize(void) {
    typedef struct {
        DWORD  cb;
        DWORD  PageFaultCount;
        SIZE_T PeakWorkingSetSize;
        SIZE_T WorkingSetSize;
        SIZE_T QuotaPeakPagedPoolUsage;
        SIZE_T QuotaPagedPoolUsage;
        SIZE_T QuotaPeakNonPagedPoolUsage;
        SIZE_T QuotaNonPagedPoolUsage;
        SIZE_T PagefileUsage;
        SIZE_T PeakPagefileUsage;
    } info_t;
    typedef BOOL(WINAPI*func_t)(HANDLE,info_t*,DWORD);
    static func_t func; static enum { FIRST,OK,ERR } flag;
    static HANDLE proc; info_t info; HINSTANCE dll;
    if (flag==FIRST) {
        if ((dll=LoadLibraryA("psapi"))==0) { flag=ERR; return 0; }
        func=(func_t)GetProcAddress(dll,"GetProcessMemoryInfo");
        if (func==0) { flag=ERR; return 0; }
        proc=GetCurrentProcess(); flag=OK;
    }
    if (flag==ERR) return 0;
    func(proc,&info,sizeof info); return(int)info.WorkingSetSize;
}

class Sample {
public:
//static int sample;
};
//int Sample::sample = 0;

int main()
{

//	static int sample = 0;

//	printf("%d\n", sample);
//	printf("%d\n", Sample::sample);
//	printf("4\n");

	//std::cout << sample << std::endl;

	std::cout << WorkSize() << std::endl;

	return 0;
}
