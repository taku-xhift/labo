

# Shishido ’Ç‹L
$filename = "Makefile";
if (-e $filename) {
    open(FH, "$filename") || die "Error: $filename $!\n";
    @fileline = <FH>;

    while ($line = shift(@fileline)) {
        if ($line =~ /LD_RUN_PATH/) {
            $line =~ s/\r//;
            $line =~ s/\n//;
            $line." lstdc++\n";
            push(@templine, $line);
        } else {
            push(@templine, $line);
        }
    }
    close (FH);

    print "fileRead is finished!!\n";

    open(FH, ">$filename");
    print FH '';
    close (FH);

    open(FH, ">>$filename");
#    while ($line = shift(@templine)) {
        print FH @templine;
#    }
    close (FH)
} else {
    print "can not open Makefile.";
}


