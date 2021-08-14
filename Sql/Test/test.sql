select shohin_mei, torokubi, hanbai_tanka,
    sum(hanbai_tanka) over(
        order by coalesce(torokubi, cast('0001-01-01' as date))
    ) as current_sum_tanka
from Shohin;
