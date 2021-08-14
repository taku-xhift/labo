
tabStop = 8

main :: IO ()
main = getContents >>= putStr . expand

expand :: String -> String
expand = concatMap expandTab

expandTab :: Char -> String
expandTab '\t'  = replicate tabStop ' '
expandTab c     = [c]

