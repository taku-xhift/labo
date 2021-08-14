


-- Quick sort in haskell


{--
  -- ˆê”Ê“I‚È‚à‚Ì
  qsort [] = []
  qsort (x:xs) = qsort(filter(< x)xs) ++ [x] ++ qsort(filter (>= x) xs)
--}


-- Progrqaming in haskell ‚Ì‚à‚Ì
-- ‚æ‚è qsort ‚Ì“à—e‚ðŽ¦‚µ‚½‚à‚Ì
qsort [] = []
qsort (x:xs) = qsort smaller ++ [x] ++ qsort larger
               where
                 smaller = [a | a <- xs, a <= x]
                 larger = [b | b <- xs, b > x]


