use ExtUtils::MakeMaker;
my %options = %{
{
  'TYPEMAPS' => [
    '/usr/lib/perl5/5.8/ExtUtils/typemap'
  ],
  'NAME' => 'main_pl_20f3',
  'CC' => 'g++',
  'LIBS' => [
    '-lstdc++ -L/lib/gcc/i686-pc-cygwin/3.4.4 /cygdrive/d/PersonalTool/xyzzy/laboratory/Perl/InlineCPP/Include/ -lmylib -lstdc++ -lMacro'
  ],
  'INC' => '-I/cygdrive/d/PersonalTool/xyzzy/laboratory/Perl/InlineCPP/Reciprocate -I/cygdrive/d/PersonalTool/xyzzy/laboratory/Perl/InlineCPP/Reciprocate/',
  'VERSION' => '0.00'
}
};
WriteMakefile(%options);

# Remove the Makefile dependency. Causes problems on a few systems.
sub MY::makefile { '' }
