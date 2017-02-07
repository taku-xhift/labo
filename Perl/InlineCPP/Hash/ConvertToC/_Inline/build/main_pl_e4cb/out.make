/usr/bin/perl.exe /usr/lib/perl5/5.8/ExtUtils/xsubpp  -typemap /usr/lib/perl5/5.8/ExtUtils/typemap   main_pl_e4cb.xs > main_pl_e4cb.xsc && mv main_pl_e4cb.xsc main_pl_e4cb.c
gcc -c  -I/cygdrive/d/PersonalTool/xyzzy/laboratory/Perl/InlineCPP/Hash/ConvertToC -DPERL_USE_SAFE_PUTENV -fno-strict-aliasing -pipe -I/usr/local/include -DUSEIMPORTLIB -O3   -DVERSION=\"0.00\" -DXS_VERSION=\"0.00\"  "-I/usr/lib/perl5/5.8/cygwin/CORE"   main_pl_e4cb.c
main_pl_e4cb.xs:10: error: parse error before '*' token
main_pl_e4cb.xs:10: error: conflicting types for 'converter'
main_pl_e4cb.xs:7: error: previous implicit declaration of 'converter' was here
main_pl_e4cb.xs: In function `converter':
main_pl_e4cb.xs:11: error: `ReciprocateData' undeclared (first use in this function)
main_pl_e4cb.xs:11: error: (Each undeclared identifier is reported only once
main_pl_e4cb.xs:11: error: for each function it appears in.)
main_pl_e4cb.xs:11: error: parse error before "data"
main_pl_e4cb.xs:44: error: `data' undeclared (first use in this function)
make: *** [main_pl_e4cb.o] Error 1
