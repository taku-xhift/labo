use Inline CPP => <<'END_OF_CPP';

void greet() {
    std::cout << "Hello" << std::endl;
}

END_OF_CPP

greet;
