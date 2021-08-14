
import System
import List

main = do args <- getArgs
          cs <- getContents
          putStr $ lineSort cs

lineSort :: String -> String
lineSort cs = List.sort cs
