/usr/bin/perl.exe /usr/lib/perl5/5.8/ExtUtils/xsubpp  -typemap /usr/lib/perl5/5.8/ExtUtils/typemap   connection_pl_e324.xs > connection_pl_e324.xsc && mv connection_pl_e324.xsc connection_pl_e324.c
gcc -c  -I/cygdrive/d/PersonalTool/xyzzy/laboratory/Perl/CConnectionTest -DPERL_USE_SAFE_PUTENV -fno-strict-aliasing -pipe -I/usr/local/include -DUSEIMPORTLIB -O3   -DVERSION=\"0.00\" -DXS_VERSION=\"0.00\"  "-I/usr/lib/perl5/5.8/cygwin/CORE"   connection_pl_e324.c
connection_pl_e324.xs: In function `greet':
connection_pl_e324.xs:7: error: missing terminating " character
connection_pl_e324.xs:8: error: missing terminating " character
connection_pl_e324.xs:9: error: parse error before '}' token
make: *** [connection_pl_e324.o] Error 1
