
import Char

main = do cs <- getContents
          putStr $ rstrip cs

rstrip :: String -> String
rstrip = reverse . lstrip . reverse

lstrip :: String -> String
lstrip = dropWhile isSpace
