module Example 1 where



f1 x y = x + y


sum` :: [Int] -> Int
sum` []  = 0
sum` (x:xs) = x  + sum` xs


sump :: [Int] -> Int
sump []  = 0
sump (x:xs) = if x > 0 then 1 + sump xs 
	                   else sump xs



sumev :: [Int] -> Int
sumev []  = 0
sumev (x:xs) = if event x then x + sumev xs 
	                      else sumev xs


product` :: [Int] -> Int
product` []  = 1
product` (x:xs) = x * product' xs


len` :: [Int] -> Int
len` [] = 0
len` (x: xs) = 1 + len` xs

-- [1,2,3,4] -> [(1,2), (3,4)]
-- [1,2,3,4,5] -> [(1,2), (3,4)]

totwice :: [a] -> [(a,a)]
totwice [] = []
totwice [x1:xs] = (x1:x2) : totwice xs
totwice (x1:x2:xs) = (x1:x2) : totwice xs


to2lists :: [a] -> ([a], [a])
to2lists [] = ([], [])
to2lists list = to2 list [] []


to2 [] l1 l2          =  (l1, l2)
to2 [x] l1 l2         =  to2 [] x:l1 l2
to2 (x1:x2:xs) l1 l2  =  to2 xs (x1:l1) (x2:l2)


mytake n l  = myt n l 0 []

myt n (x:xs) k l1 = if k < n then myt n xs (k+1) ( l1++[x])
                             else l1

-- Function of higher order

hf :: (Int -> Int) -> Int -> Int
hf f x = f x * x

g x = x + x



f1 :: Int -> Int -> Int
f1 x y = x + y

ff1 = f1 	-- partially defined function
ff2 = f1 1  -- partially defined function with some argument
-- ff2 6 => f1 1 6


