
module FP_lab_work_3_variant_1
(reverse2
,mix_first_last
) where
-- Лабораторна 3: Функції вищого порядку
-- Варіант 1

------- Завдання 1 -------

-- Визначити вказані функції в кожному з завдань: 
-- a) без застосування 
-- б) з застосування функцій вищого порядку

-- 1.1. Переписати список справа наліво
reverse1 :: ([a] -> [a] -> [a]) -> [a] -> [a]
reverse1 afunc xs = afunc xs []

_reverse1 :: [a] -> [a] -> [a]
_reverse1 [] acc = acc
_reverse1 (x:xs) acc = _reverse1 xs (x:acc)

reverse2 :: [a] -> [a]
reverse2 xs = _rev2 xs []
    where
        _rev2 :: [a] -> [a] -> [a]
        _rev2 [] acc = acc
        _rev2 (y:ys) acc = _rev2 ys (y:acc)
        

------- Завдання 2 -------
-- 2.1. Перемішування списку з n елементів: після першого розмістити останній,
-- після другого - передостанній тощо. 
-- Наприклад вхідний список "abcde1234" має бути трансформований у "a1b2c3d4e"

mix_first_last :: [a] -> [a]
mix_first_last xs = _mix_first_last xs

mix_first_last_hf :: ([a]  -> [a]) -> [a] -> [a]
mix_first_last_hf afunc xs = afunc xs

_mix_first_last :: [a]  -> [a]
_mix_first_last [] = []
_mix_first_last [x] = [x]
_mix_first_last (x:xs) = x : last xs : _mix_first_last (init xs)