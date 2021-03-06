
data Anchor = A {aUrl   :: String,
                 aLabel :: String }

compileAnchor :: Anchor -> String
compileAnchor (A { aUrl = u, aLabel = l }) =
                "<a href=\"" ++ u ++ "\">" ++ l ++ "</a>"

anchorUrl :: Anchor -> String
anchorUrl (A { aUrl = u }) = u

href :: Anchor
href = A "http://example.com/" "Support Page"

main = do print (aLabel href) -- Support Page と出力される
          print $ compileAnchor (A "http://example.com" "HomePage")
          print $ anchorUrl (A "http://example.com" "HomePage")

