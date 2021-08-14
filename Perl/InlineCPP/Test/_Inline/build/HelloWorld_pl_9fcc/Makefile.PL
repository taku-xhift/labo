use ExtUtils::MakeMaker;
my %options = %{       
{
  'TYPEMAPS' => [
    '/usr/lib/perl5/5.10/ExtUtils/typemap'
  ],
  'NAME' => 'HelloWorld_pl_9fcc',
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
