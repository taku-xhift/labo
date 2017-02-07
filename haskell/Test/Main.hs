module Main where -- 名前空間みたいなもの




data Person = P String Int --名前、年齢のつもり。
setName :: String -> Person -> Object Person
setName str (P n a) = Obj (P str a)

setAge :: Int -> Person -> Object Person
setAge i (P n a) = Obj (P n i)

getName :: Object Person -> String
getName (Obj (P n a)) =  n

getAge :: Object Person -> Int
getAge (Obj (P n a)) =  a





data Object a = Obj a       --「Object a」という型のデータ構成子(aは型変数)
instance Monad Object where -- 「Object」はモナド。つまり「Object」は型構成子。
  return x = Obj x          --  return は ある型X(xの型)のデータを受け取って、
                            --  Object X型のデータを作る.
  (Obj x) >>= f = f x       --  演算子「>>=」は 左側に「Object X」型、右側に「X->Object Y」
                            --  をとって、「Object Y」型のデータを返す。






main = do  let saito = return (P "" 0) >>= setName "Saito" >>= setAge 40
	   putStrLn $ getName saito
	   print $ getAge $ saito >>= setAge 41



