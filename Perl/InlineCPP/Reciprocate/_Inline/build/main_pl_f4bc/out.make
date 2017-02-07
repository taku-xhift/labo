/usr/bin/perl.exe /usr/lib/perl5/5.8/ExtUtils/xsubpp  -typemap /usr/lib/perl5/5.8/ExtUtils/typemap   main_pl_f4bc.xs > main_pl_f4bc.xsc && mv main_pl_f4bc.xsc main_pl_f4bc.c
g++ -c  -I/cygdrive/d/PersonalTool/xyzzy/laboratory/Perl/InlineCPP/Reciprocate -I/cygdrive/d/PersonalTool/xyzzy/laboratory/Perl/InlineCPP/Reciprocate/ -DPERL_USE_SAFE_PUTENV -fno-strict-aliasing -pipe -I/usr/local/include -DUSEIMPORTLIB -O3   -DVERSION=\"0.00\" -DXS_VERSION=\"0.00\"  "-I/usr/lib/perl5/5.8/cygwin/CORE"   main_pl_f4bc.c
Running Mkbootstrap for main_pl_f4bc ()
chmod 644 main_pl_f4bc.bs
rm -f blib/arch/auto/main_pl_f4bc/main_pl_f4bc.dll
LD_RUN_PATH="" ld2  -s -L/usr/local/lib main_pl_f4bc.o  -o blib/arch/auto/main_pl_f4bc/main_pl_f4bc.dll  /usr/lib/perl5/5.8/cygwin/CORE/libperl.dll.a -L/lib/gcc/i686-pc-cygwin/3.4.4 -lmylib -lstdc++ -lMacro   
gcc -shared -o  main_pl_f4bc.dll -Wl,--out-implib=libmain_pl_f4bc.dll.a -Wl,--export-all-symbols -Wl,--enable-auto-import -Wl,--stack,8388608 -Wl,--enable-auto-image-base \
-s -L/usr/local/lib main_pl_f4bc.o  /usr/lib/perl5/5.8/cygwin/CORE/libperl.dll.a -L/lib/gcc/i686-pc-cygwin/3.4.4 -lmylib -lstdc++ -lMacro
Creating library file: libmain_pl_f4bc.dll.a
mv main_pl_f4bc.dll libmain_pl_f4bc.dll.a blib/arch/auto/main_pl_f4bc/
chmod 755 blib/arch/auto/main_pl_f4bc/main_pl_f4bc.dll
cp main_pl_f4bc.bs blib/arch/auto/main_pl_f4bc/main_pl_f4bc.bs
chmod 644 blib/arch/auto/main_pl_f4bc/main_pl_f4bc.bs
