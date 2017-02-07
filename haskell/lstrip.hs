
import Char

main = do cs <- getContents
          putStr $ lstrip cs

lstrip :: String -> String
lstrip = dropWhile isSpace
