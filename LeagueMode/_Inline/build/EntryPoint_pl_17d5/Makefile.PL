use ExtUtils::MakeMaker;
my %options = %{
{
  'TYPEMAPS' => [
    '/usr/lib/perl5/5.8/ExtUtils/typemap'
  ],
  'NAME' => 'EntryPoint_pl_17d5',
  'CC' => 'g++',
  'LIBS' => [
    '-lstdc++'
  ],
  'VERSION' => '0.00'
}
};
WriteMakefile(%options);

# Remove the Makefile dependency. Causes problems on a few systems.
sub MY::makefile { '' }
