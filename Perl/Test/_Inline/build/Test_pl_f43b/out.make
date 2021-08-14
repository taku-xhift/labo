/usr/bin/perl.exe /usr/lib/perl5/5.8/ExtUtils/xsubpp  -typemap /usr/lib/perl5/5.8/ExtUtils/typemap   Test_pl_f43b.xs > Test_pl_f43b.xsc && mv Test_pl_f43b.xsc Test_pl_f43b.c
gcc -c  -I/cygdrive/d/PersonalTool/xyzzy/laboratory/Perl/Test -DPERL_USE_SAFE_PUTENV -fno-strict-aliasing -pipe -I/usr/local/include -DUSEIMPORTLIB -O3   -DVERSION=\"0.00\" -DXS_VERSION=\"0.00\"  "-I/usr/lib/perl5/5.8/cygwin/CORE"   Test_pl_f43b.c
Test_pl_f43b.xs: In function `dump_hash':
Test_pl_f43b.xs:22: error: parse error before ';' token
make: *** [Test_pl_f43b.o] Error 1
