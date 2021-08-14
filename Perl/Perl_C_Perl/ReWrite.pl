use Inline C => <<'END_C';

void c_func_2(SV* text) {
    Inline_Stack_Vars;
    Inline_Stack_Push(newSVpvf("Plus an extra line"));
    Inline_Stack_Done;
    perl_call_pv("main::perl_sub_1", 0);
    Inline_Stack_Void;
}

void c_func_1(SV* text) {
    c_func_2(text);
}
END_C

c_func_1('This is the first line');
c_func_2('This is the second line');

sub perl_sub_1 {
    print map "$_\n", @_;
}


