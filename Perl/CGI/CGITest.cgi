use CGI;
use Inline CPP => <<'END_OF_CPP';

void greet(char* strings_) {
    std::cout << strings_ << std::endl;
}

END_OF_CPP

my $query = CGI->new();
my $name = "name";

greet($query->param('png') + "");
#greet($name);
#greet('png');
