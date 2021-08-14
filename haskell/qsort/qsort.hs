


-- Quick sort in haskell


{--
  -- ��ʓI�Ȃ���
  qsort [] = []
  qsort (x:xs) = qsort(filter(< x)xs) ++ [x] ++ qsort(filter (>= x) xs)
--}


-- Progrqaming in haskell �̂���
-- ��� qsort �̓��e������������
qsort [] = []
qsort (x:xs) = qsort smaller ++ [x] ++ qsort larger
               where
                 smaller = [a | a <- xs, a <= x]
                 larger = [b | b <- xs, b > x]


