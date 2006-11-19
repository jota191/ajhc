module FrontEnd.Syn.Options(parseOptions) where


import Text.ParserCombinators.ReadP
import Char
import List



parseOptions :: String -> [(String,String)]
parseOptions s = case readP_to_S parse s of
    os -> head $ sortBy (\x y -> compare (negate $ length x) (negate $ length y)) [ x | (x,_) <- os ]

token x = x >>= \r -> spaces >> return r

parse = do
    spaces
    many (token pragma)


spaces = do
    skipSpaces
    optional (comment >> spaces)

pragma = do
    string "{-#"
    skipSpaces
    nn <- munch1 (\c -> isAlpha c || c == '_')
    skipSpaces
    body <- manyTill get (string "#-}")
    return $ (nn,body)


comment = line +++ block where
    line = do
        string "--"
        manyTill get (char '\n')
        return ()
    block = do
        string "{-"
        satisfy (/= '#')
        manyTill get (string "-}")
        return ()


