use ExtUtils::MakeMaker;
my %options = %{
{
  'TYPEMAPS' => [],
  'NAME' => 'test_pl_346b',
  'CC' => 'g++',
  'LIBS' => [
    '-lstdc++ -L/lib/gcc/i686-pc-cygwin/3.4.4 -lLeagueMode -lstdc++ -lgcc'
  ],
  'INC' => '-I/cygdrive/d/PersonalTool/xyzzy/laboratory/Perl/LeagueModeTest -I/lib/gcc/i686-pc-cygwin/3.4.4/include',
  'VERSION' => '0.00'
}
};
WriteMakefile(%options);

# Remove the Makefile dependency. Causes problems on a few systems.
sub MY::makefile { '' }
