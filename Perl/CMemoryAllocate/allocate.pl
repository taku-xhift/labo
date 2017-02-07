print greeting('Ingy');

use Inline C => <<'END_OF_C_CODE';

SV* greeting(SV* sv_name) {
    return (newSVpvf("Hello %s!\n", SvPV(sv_name, PL_na)));
}

END_OF_C_CODE
