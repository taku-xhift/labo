use PMPCServer::MODEL::PMPCTeamSelectModel qw(get(\%\%) put(\%\%));

my %command = (
'TeamSpecificData' => {
'teamid' => 100,
}
);
my %output;
PMPCServer::MODEL::PMPCTeamSelectModel::get(%command, %output);
