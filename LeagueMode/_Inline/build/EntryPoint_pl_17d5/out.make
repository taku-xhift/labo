/usr/bin/perl.exe /usr/lib/perl5/5.8/ExtUtils/xsubpp  -typemap /usr/lib/perl5/5.8/ExtUtils/typemap   EntryPoint_pl_17d5.xs > EntryPoint_pl_17d5.xsc && mv EntryPoint_pl_17d5.xsc EntryPoint_pl_17d5.c
g++ -c   -DPERL_USE_SAFE_PUTENV -fno-strict-aliasing -pipe -I/usr/local/include -DUSEIMPORTLIB -O3   -DVERSION=\"0.00\" -DXS_VERSION=\"0.00\"  "-I/usr/lib/perl5/5.8/cygwin/CORE"   EntryPoint_pl_17d5.c
Running Mkbootstrap for EntryPoint_pl_17d5 ()
chmod 644 EntryPoint_pl_17d5.bs
rm -f blib/arch/auto/EntryPoint_pl_17d5/EntryPoint_pl_17d5.dll
LD_RUN_PATH="" ld2  -s -L/usr/local/lib EntryPoint_pl_17d5.o  -o blib/arch/auto/EntryPoint_pl_17d5/EntryPoint_pl_17d5.dll  /usr/lib/perl5/5.8/cygwin/CORE/libperl.dll.a     -lstdc++
gcc -shared -o  EntryPoint_pl_17d5.dll -Wl,--out-implib=libEntryPoint_pl_17d5.dll.a -Wl,--export-all-symbols -Wl,--enable-auto-import -Wl,--stack,8388608 -Wl,--enable-auto-image-base \
-s -L/usr/local/lib EntryPoint_pl_17d5.o  /usr/lib/perl5/5.8/cygwin/CORE/libperl.dll.a -lstdc++
Creating library file: libEntryPoint_pl_17d5.dll.a
EntryPoint_pl_17d5.o:EntryPoint_pl_17d5.c:(.text+0x19): undefined reference to `_LeagueMode_TeamSelect'
EntryPoint_pl_17d5.o:EntryPoint_pl_17d5.c:(.text+0x30): undefined reference to `_LeagueMode_AutoGame'
EntryPoint_pl_17d5.o:EntryPoint_pl_17d5.c:(.text+0x149): undefined reference to `_LeagueMode_TeamSelect'
EntryPoint_pl_17d5.o:EntryPoint_pl_17d5.c:(.text+0x164): undefined reference to `_LeagueMode_AutoGame'
collect2: ld returned 1 exit status
perlld: *** system() failed to execute
gcc -shared -o  EntryPoint_pl_17d5.dll -Wl,--out-implib=libEntryPoint_pl_17d5.dll.a -Wl,--export-all-symbols -Wl,--enable-auto-import -Wl,--stack,8388608 -Wl,--enable-auto-image-base \
-s -L/usr/local/lib EntryPoint_pl_17d5.o  /usr/lib/perl5/5.8/cygwin/CORE/libperl.dll.a -lstdc++

make: *** [blib/arch/auto/EntryPoint_pl_17d5/EntryPoint_pl_17d5.dll] Error 2
