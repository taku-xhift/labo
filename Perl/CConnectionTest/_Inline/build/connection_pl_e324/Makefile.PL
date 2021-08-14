use ExtUtils::MakeMaker;
my %options = %{
{
  'TYPEMAPS' => [
    '/usr/lib/perl5/5.8/ExtUtils/typemap'
  ],
  'NAME' => 'connection_pl_e324',
  'INC' => '-I/cygdrive/d/PersonalTool/xyzzy/laboratory/Perl/CConnectionTest',
  'VERSION' => '0.00'
}
};
WriteMakefile(%options);

# Remove the Makefile dependency. Causes problems on a few systems.
sub MY::makefile { '' }
