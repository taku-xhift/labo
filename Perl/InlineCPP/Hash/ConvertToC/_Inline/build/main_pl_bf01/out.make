/usr/bin/perl.exe /usr/lib/perl5/5.8/ExtUtils/xsubpp  -typemap /usr/lib/perl5/5.8/ExtUtils/typemap   main_pl_bf01.xs > main_pl_bf01.xsc && mv main_pl_bf01.xsc main_pl_bf01.c
gcc -c  -I/cygdrive/d/PersonalTool/xyzzy/laboratory/Perl/InlineCPP/Hash/ConvertToC -DPERL_USE_SAFE_PUTENV -fno-strict-aliasing -pipe -I/usr/local/include -DUSEIMPORTLIB -O3   -DVERSION=\"0.00\" -DXS_VERSION=\"0.00\"  "-I/usr/lib/perl5/5.8/cygwin/CORE"   main_pl_bf01.c
main_pl_bf01.xs: In function `dump_hash':
main_pl_bf01.xs:27: error: `temp' undeclared (first use in this function)
main_pl_bf01.xs:27: error: (Each undeclared identifier is reported only once
main_pl_bf01.xs:27: error: for each function it appears in.)
make: *** [main_pl_bf01.o] Error 1
