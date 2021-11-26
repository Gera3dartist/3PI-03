main :: IO ()
-- main = putStrLn "Hello, World!"
main = do
    putStrLn "Hello what is your name?"
    name <- getLine
    putStrLn ("Your name is " ++ name ++ ", welcome!")