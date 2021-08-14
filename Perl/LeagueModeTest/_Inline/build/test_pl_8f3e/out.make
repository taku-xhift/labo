/usr/bin/perl.exe /usr/lib/perl5/5.8/ExtUtils/xsubpp    test_pl_8f3e.xs > test_pl_8f3e.xsc && mv test_pl_8f3e.xsc test_pl_8f3e.c
g++ -c  -I/cygdrive/d/PersonalTool/xyzzy/laboratory/Perl/LeagueModeTest -I/lib/gcc/i686-pc-cygwin/3.4.4/include -DPERL_USE_SAFE_PUTENV -fno-strict-aliasing -pipe -I/usr/local/include -DUSEIMPORTLIB -O3   -DVERSION=\"0.00\" -DXS_VERSION=\"0.00\"  "-I/usr/lib/perl5/5.8/cygwin/CORE"   test_pl_8f3e.c
Running Mkbootstrap for test_pl_8f3e ()
chmod 644 test_pl_8f3e.bs
rm -f blib/arch/auto/test_pl_8f3e/test_pl_8f3e.dll
LD_RUN_PATH="" ld2  -s -L/usr/local/lib test_pl_8f3e.o  -o blib/arch/auto/test_pl_8f3e/test_pl_8f3e.dll  /usr/lib/perl5/5.8/cygwin/CORE/libperl.dll.a -L/lib/gcc/i686-pc-cygwin/3.4.4 -lLeagueMode -lstdc++ -lgcc   
gcc -shared -o  test_pl_8f3e.dll -Wl,--out-implib=libtest_pl_8f3e.dll.a -Wl,--export-all-symbols -Wl,--enable-auto-import -Wl,--stack,8388608 -Wl,--enable-auto-image-base \
-s -L/usr/local/lib test_pl_8f3e.o  /usr/lib/perl5/5.8/cygwin/CORE/libperl.dll.a -L/lib/gcc/i686-pc-cygwin/3.4.4 -lLeagueMode -lstdc++ -lgcc
Creating library file: libtest_pl_8f3e.dll.a
mv test_pl_8f3e.dll libtest_pl_8f3e.dll.a blib/arch/auto/test_pl_8f3e/
chmod 755 blib/arch/auto/test_pl_8f3e/test_pl_8f3e.dll
cp test_pl_8f3e.bs blib/arch/auto/test_pl_8f3e/test_pl_8f3e.bs
chmod 644 blib/arch/auto/test_pl_8f3e/test_pl_8f3e.bs
