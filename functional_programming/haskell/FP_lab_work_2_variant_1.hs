
-- Лабораторна 1
-- Варіант 1

------- Завдання 1 -------

-- 1.1. Знайти останній елеmeнт списку
findlast :: [Integer] -> Integer
findlast [] = error "last of empty list"
findlast [x] = x
findlast (h:tail) = findlast tail


-- 1.1. Знайти останній елеmeнт списку
findlast2 :: [Integer] -> Integer
findlast2 seq = last seq



------- Завдання 2 -------

-- 2.1 Видалити зі списку елементи з i-го по k-й включно, наприклад при i=2, k=4 "asdfghj" -> "aghj"
remove_subset :: (Integer, Integer, [Char]) -> [Char]
remove_subset (from, to, list) = _remove_subset (from, to, list, 1)

_remove_subset :: (Integer, Integer, [Char], Integer) -> [Char]
_remove_subset (from, to, _, _)
    | from < 0 || to < 0 = error "from and to must be positive numbers"
    | from > to = error "from must be less than to"
_remove_subset (_, _, [], _) = []
_remove_subset (from, to, (x:xs), start) = if not (inrange(start, from, to)) then  x : _remove_subset (from, to, xs, start+1)
                             else _remove_subset (from, to, xs, start+1)


-- helpers
inrange :: (Integer, Integer, Integer) -> Bool; inrange (x, y, z) = min z y  <= x &&  max z y >= x
