

-- file: ch03/BookStore.hs
data BookInfo = Book Integer String [String]
                deriving (Show)

data MagazineInfo = Magazine Int String [String]
                    deriving (Show)


myInfo = Book 978013572455 "Algebra of Programming"
         ["Richard Bird", "Oege de Moor"]



data Customer = Customer {
              customerID        :: CustomerID
            , customerName      :: String
            , customerAddress   :: Address
                         } deriving (Show)


