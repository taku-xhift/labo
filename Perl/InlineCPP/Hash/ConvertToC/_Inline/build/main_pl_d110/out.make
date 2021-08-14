/usr/bin/perl.exe /usr/lib/perl5/5.8/ExtUtils/xsubpp  -typemap /usr/lib/perl5/5.8/ExtUtils/typemap   main_pl_d110.xs > main_pl_d110.xsc && mv main_pl_d110.xsc main_pl_d110.c
gcc -c  -I/cygdrive/d/PersonalTool/xyzzy/laboratory/Perl/InlineCPP/Hash/ConvertToC -DPERL_USE_SAFE_PUTENV -fno-strict-aliasing -pipe -I/usr/local/include -DUSEIMPORTLIB -O3   -DVERSION=\"0.00\" -DXS_VERSION=\"0.00\"  "-I/usr/lib/perl5/5.8/cygwin/CORE"   main_pl_d110.c
Running Mkbootstrap for main_pl_d110 ()
chmod 644 main_pl_d110.bs
rm -f blib/arch/auto/main_pl_d110/main_pl_d110.dll
LD_RUN_PATH="" ld2  -s -L/usr/local/lib main_pl_d110.o  -o blib/arch/auto/main_pl_d110/main_pl_d110.dll  /usr/lib/perl5/5.8/cygwin/CORE/libperl.dll.a    
gcc -shared -o  main_pl_d110.dll -Wl,--out-implib=libmain_pl_d110.dll.a -Wl,--export-all-symbols -Wl,--enable-auto-import -Wl,--stack,8388608 -Wl,--enable-auto-image-base \
-s -L/usr/local/lib main_pl_d110.o  /usr/lib/perl5/5.8/cygwin/CORE/libperl.dll.a
Creating library file: libmain_pl_d110.dll.a
main_pl_d110.o:main_pl_d110.c:(.text+0x40f): undefined reference to `_print'
collect2: ld returned 1 exit status
perlld: *** system() failed to execute
gcc -shared -o  main_pl_d110.dll -Wl,--out-implib=libmain_pl_d110.dll.a -Wl,--export-all-symbols -Wl,--enable-auto-import -Wl,--stack,8388608 -Wl,--enable-auto-image-base \
-s -L/usr/local/lib main_pl_d110.o  /usr/lib/perl5/5.8/cygwin/CORE/libperl.dll.a

make: *** [blib/arch/auto/main_pl_d110/main_pl_d110.dll] Error 2
