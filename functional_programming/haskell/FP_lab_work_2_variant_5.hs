
-- Лабораторна 1
-- Варіант 5

------- Завдання 1 -------

-- 1.5. Чи є список поліндром
is_polindrome :: [Char] -> Bool
is_polindrome [] = True
is_polindrome alist = alist == reverse alist


is_polindrome2 :: [Char] -> Bool
is_polindrome2 [] = True
is_polindrome2 [_] = True
is_polindrome2 (x:xs) = x == (last xs)  && is_polindrome2 (init xs)


------- Завдання 2 -------

-- 2.5 Обєднати зі змішуванням двох списків довжиною n1 та n2. Вихідний список має довжину 2 * n,  де n = min(n1, n2)
-- Наприклад "abcde" та 123 перетворюються на "a1b2c3"

mix2lists :: [a] -> [a] -> [a]
mix2lists [] _ = []
mix2lists _ [] = []
mix2lists (x1:tail1) (x2:tail2) = x1 : x2 : (mix2lists tail1 tail2)
