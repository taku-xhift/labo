/usr/bin/perl.exe /usr/lib/perl5/5.8/ExtUtils/xsubpp  -typemap /usr/lib/perl5/5.8/ExtUtils/typemap   main_pl_a37f.xs > main_pl_a37f.xsc && mv main_pl_a37f.xsc main_pl_a37f.c
gcc -c  -I/cygdrive/d/PersonalTool/xyzzy/laboratory/Perl/InlineCPP/Hash/ConvertToC -DPERL_USE_SAFE_PUTENV -fno-strict-aliasing -pipe -I/usr/local/include -DUSEIMPORTLIB -O3   -DVERSION=\"0.00\" -DXS_VERSION=\"0.00\"  "-I/usr/lib/perl5/5.8/cygwin/CORE"   main_pl_a37f.c
main_pl_a37f.xs:56: error: parse error before "return"
make: *** [main_pl_a37f.o] Error 1
