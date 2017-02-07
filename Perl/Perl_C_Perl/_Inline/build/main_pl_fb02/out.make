/usr/bin/perl.exe /usr/lib/perl5/5.8/ExtUtils/xsubpp  -typemap /usr/lib/perl5/5.8/ExtUtils/typemap   main_pl_fb02.xs > main_pl_fb02.xsc && mv main_pl_fb02.xsc main_pl_fb02.c
gcc -c  -I/cygdrive/d/PersonalTool/xyzzy/laboratory/Perl/Perl_C_Perl -DPERL_USE_SAFE_PUTENV -fno-strict-aliasing -pipe -I/usr/local/include -DUSEIMPORTLIB -O3   -DVERSION=\"0.00\" -DXS_VERSION=\"0.00\"  "-I/usr/lib/perl5/5.8/cygwin/CORE"   main_pl_fb02.c
main_pl_fb02.xs:10: error: conflicting types for 'c_func_2'
main_pl_fb02.xs:7: error: previous implicit declaration of 'c_func_2' was here
make: *** [main_pl_fb02.o] Error 1
