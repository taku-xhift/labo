/usr/bin/perl.exe /usr/lib/perl5/5.10/ExtUtils/xsubpp  -typemap /usr/lib/perl5/5.10/ExtUtils/typemap   HelloWorld_pl_9fcc.xs > HelloWorld_pl_9fcc.xsc && mv HelloWorld_pl_9fcc.xsc HelloWorld_pl_9fcc.c
g++ -c   -DPERL_USE_SAFE_PUTENV -U__STRICT_ANSI__ -fno-strict-aliasing -pipe -fstack-protector -I/usr/local/include -DUSEIMPORTLIB -O3   -DVERSION=\"0.00\" -DXS_VERSION=\"0.00\"  "-I/usr/lib/perl5/5.10/i686-cygwin/CORE"   HelloWorld_pl_9fcc.c
cc1plus: error: unrecognized command line option "-fstack-protector"
make: *** [HelloWorld_pl_9fcc.o] Error 1
