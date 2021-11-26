
-- Лабораторна 1

-- Варіант 5

------- Завдання 1 -------


-- 1.5. ([Char],[Double],[(Bool,Integer)])

-- ("foo", [1.1, 2.1], [(True, 2), (False, 3)])

------- Завдання 2 -------

-- 2.5 Функцiя визначає, чи належить кругу дана точка. Точка задається
-- координатами, круг – координатами центра та радiусом.

point_belongs_to_circle :: ((Double, Double), (Double, Double), Double) -> Bool
point_belongs_to_circle ((xc, yc), (xp, yp), radius) = sqrt ((xp - xc)^2 + (yp - yc)^2) < radius
