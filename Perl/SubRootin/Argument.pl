

sub function($@) {
    my @array = $_[1];
    print "test\n";
#    print $temp, "\n";
#    print @array;
    print $array[0], "\n";
#    print "$array[1]";
}


my @array = (1,2);
my %hash = ("test" => 3);
#print $hash{"test"};

&function($hash{"test"}, @array);
print $array[0];
