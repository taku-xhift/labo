


data Person = P String Int --���O�A�N��̂���B
setName :: String -> Person -> Object Person
setName str (P n a) = Obj (P str a)

setAge :: Int -> Person -> Object Person
setAge i (P n a) = Obj (P n i)

getName :: Object Person -> String
getName (Obj (P n a)) =  n 

getAge :: Object Person -> Int
getAge (Obj (P n a)) =  a





data Object a = Obj a       --�uObject a�v�Ƃ����^�̃f�[�^�\���q(a�͌^�ϐ�)
instance Monad Object where -- �uObject�v�̓��i�h�B�܂�uObject�v�͌^�\���q�B
  return x = Obj x          --  return �� ����^X(x�̌^)�̃f�[�^���󂯎���āA
                            --  Object X�^�̃f�[�^�����. 
  (Obj x) >>= f = f x       --  ���Z�q�u>>=�v�� �����ɁuObject X�v�^�A�E���ɁuX->Object Y�v
                            --  ���Ƃ��āA�uObject Y�v�^�̃f�[�^��Ԃ��B






main = do  let saito = return (P "" 0) >>= setName "Saito" >>= setAge 40 
	   putStrLn $ getName saito 
	   print $ getAge $ saito >>= setAge 41



