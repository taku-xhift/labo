/usr/bin/perl.exe /usr/lib/perl5/5.8/ExtUtils/xsubpp  -typemap /usr/lib/perl5/5.8/ExtUtils/typemap   main_pl_b7cd.xs > main_pl_b7cd.xsc && mv main_pl_b7cd.xsc main_pl_b7cd.c
gcc -c  -I/cygdrive/d/PersonalTool/xyzzy/laboratory/Perl/InlineCPP/Hash/ConvertToC -DPERL_USE_SAFE_PUTENV -fno-strict-aliasing -pipe -I/usr/local/include -DUSEIMPORTLIB -O3   -DVERSION=\"0.00\" -DXS_VERSION=\"0.00\"  "-I/usr/lib/perl5/5.8/cygwin/CORE"   main_pl_b7cd.c
main_pl_b7cd.xs: In function `dump_hash':
main_pl_b7cd.xs:18: error: `ReciprocateData' undeclared (first use in this function)
main_pl_b7cd.xs:18: error: (Each undeclared identifier is reported only once
main_pl_b7cd.xs:18: error: for each function it appears in.)
main_pl_b7cd.xs:18: error: `data' undeclared (first use in this function)
make: *** [main_pl_b7cd.o] Error 1
