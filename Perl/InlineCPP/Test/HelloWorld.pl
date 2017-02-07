


use Inline CPP => <<'END_OF_CPP';

void greet() {
    std::cout << "Hello World!!" << std::endl;
}
END_OF_CPP

greet;


#
#use Inline CPP;
#
#greet;
#
#__END__
#__CPP__
#
#void greet() {
#    std::cout << "Hello World!!" << std::endl;
#}
#
