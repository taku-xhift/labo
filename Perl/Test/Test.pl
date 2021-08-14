
use strict;
use warnings;
use Data::Dumper;

#%hash = ('hash1' => ('hash11' => "hash11", 'hash12' => "hash12"), 'hash2' => ('hash21' => "hash21", 'hash22' => "hash22"));
my $hash = {'HashArray' => [
    {'hash11' => "hash11", 'hash12' => "hash12"},
    {'hash21' => "hash21", 'hash22' => "hash22"},]
};

#print Dumper $hash{hash1}->{hash11};
print Dumper $hash;

