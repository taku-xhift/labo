
import Random

main = do g <- getStdGen
          let ns = take 3 (randoms g)
          print (ns :: [Int])

