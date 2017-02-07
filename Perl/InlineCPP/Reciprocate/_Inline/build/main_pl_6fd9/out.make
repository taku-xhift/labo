/usr/bin/perl.exe /usr/lib/perl5/5.8/ExtUtils/xsubpp  -typemap /usr/lib/perl5/5.8/ExtUtils/typemap   main_pl_6fd9.xs > main_pl_6fd9.xsc && mv main_pl_6fd9.xsc main_pl_6fd9.c
g++ -c  -I/cygdrive/d/PersonalTool/xyzzy/laboratory/Perl/InlineCPP/Reciprocate -I/cygdrive/d/PersonalTool/xyzzy/laboratory/Perl/InlineCPP/Reciprocate/ -DPERL_USE_SAFE_PUTENV -fno-strict-aliasing -pipe -I/usr/local/include -DUSEIMPORTLIB -O3   -DVERSION=\"0.00\" -DXS_VERSION=\"0.00\"  "-I/usr/lib/perl5/5.8/cygwin/CORE"   main_pl_6fd9.c
Running Mkbootstrap for main_pl_6fd9 ()
chmod 644 main_pl_6fd9.bs
rm -f blib/arch/auto/main_pl_6fd9/main_pl_6fd9.dll
LD_RUN_PATH="" ld2  -s -L/usr/local/lib main_pl_6fd9.o  -o blib/arch/auto/main_pl_6fd9/main_pl_6fd9.dll  /usr/lib/perl5/5.8/cygwin/CORE/libperl.dll.a -L/lib/gcc/i686-pc-cygwin/3.4.4 -lmylib -lstdc++ -lMacro   
gcc -shared -o  main_pl_6fd9.dll -Wl,--out-implib=libmain_pl_6fd9.dll.a -Wl,--export-all-symbols -Wl,--enable-auto-import -Wl,--stack,8388608 -Wl,--enable-auto-image-base \
-s -L/usr/local/lib main_pl_6fd9.o  /usr/lib/perl5/5.8/cygwin/CORE/libperl.dll.a -L/lib/gcc/i686-pc-cygwin/3.4.4 -lmylib -lstdc++ -lMacro
Creating library file: libmain_pl_6fd9.dll.a
mv main_pl_6fd9.dll libmain_pl_6fd9.dll.a blib/arch/auto/main_pl_6fd9/
chmod 755 blib/arch/auto/main_pl_6fd9/main_pl_6fd9.dll
cp main_pl_6fd9.bs blib/arch/auto/main_pl_6fd9/main_pl_6fd9.bs
chmod 644 blib/arch/auto/main_pl_6fd9/main_pl_6fd9.bs
