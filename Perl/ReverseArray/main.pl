@week = ('Sun', 'Mon', 'Tue');

#while (<>) { push (@buf, @week); }
#while (@buf) { print pop(@buf); }

#for ($i = 0; $i < 3; ++$i) {
#    $temp = pop(@week);
#    if ($temp =~ /sun/) {
#        print $temp;
#    }
#}

while ($week = pop(@week)) {
    if ($week =~ /Mon/) {
        print $week;
        last;
    }
    print "breakCheck\n"
}


