module FP_lab_work_3_variant_5
(count_subseq

) where

import Data.List
-- Лабораторна 3: Функції вищого порядку
-- Варіант 5

------- Завдання 1 -------

-- Визначити вказані функції в кожному з завдань: 
-- a) без застосування 
-- б) з застосування функцій видого порядку

-- 1.5. Визначити довжину послідовності тотожних елементів списку, напр.:
-- "aaabbcaadddd" -> [('a', 3), ('b', 2), ('c', 1), ('a', 2), ('d', 4)]

-- a) без застосування 
count_subseq :: Eq a => [a] -> [(a, Int)]
count_subseq  lst = map (\seq -> (head seq, length seq)) (group lst)

-- б) з застосування функцій видого порядку
count_subseq' :: Eq a => [a] -> ([a]->(a, Int))-> [(a, Int)]
count_subseq' lst func = map func (group lst)

totuple :: [a] -> (a, Int)
totuple xs = (head xs, length xs)



------- Завдання 2 -------
-- 2.5. знайти найбільший спільний дільник двох чисел

-- a) без застосування 
gcd'' :: Integral i => i -> i -> i
gcd'' 0 b = abs b
gcd'' a b = gcd'' (abs (b `mod` a)) (abs a)

-- б) з застосування функцій видого порядку
lab_gcd :: Int -> Int  -> (Int -> Int -> Int) -> Int
lab_gcd 0 0 _ = error  "gcd 0 0 is undefined"
lab_gcd x y func = func (abs x) (abs y)
          
gcd' :: Int -> Int -> Int
gcd' x 0 = x
gcd' x y = gcd' y (x `rem` y)

