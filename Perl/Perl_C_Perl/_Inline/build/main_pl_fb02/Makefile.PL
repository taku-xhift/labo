use ExtUtils::MakeMaker;
my %options = %{
{
  'TYPEMAPS' => [
    '/usr/lib/perl5/5.8/ExtUtils/typemap'
  ],
  'NAME' => 'main_pl_fb02',
  'INC' => '-I/cygdrive/d/PersonalTool/xyzzy/laboratory/Perl/Perl_C_Perl',
  'VERSION' => '0.00'
}
};
WriteMakefile(%options);

# Remove the Makefile dependency. Causes problems on a few systems.
sub MY::makefile { '' }
