

$nonNamedHash = {"one => 1"};
$nonNamedHash->{"two"} = 2;


push(@array, $nonNamedHash);


$nonNamedHash = ();
$nonNamedHash->{"two"} = 4;

push(@array, $nonNamedHash);





if (@array[0]->{"two"} == 2) {
    print @array[0]->{"two"};
}

print @array[1]->{"two"};

