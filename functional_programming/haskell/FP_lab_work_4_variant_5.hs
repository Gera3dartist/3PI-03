
-- Лабораторна 4: типи і класи типів
-- Варіант 5

------- Завдання 1 -------

-- отримання прямокутників що охоплюють кожну фігуру з даного списку

data Font = Font {name :: String, size :: Int} deriving (Show)
data Point = Point Float Float deriving (Show)

data Shape =  Сircle Point Float | Triangle Point Point Point | Rectangle Point Point | Label { base :: Point, font :: Font, row :: Int} deriving (Show)

bounding_box :: Shape -> Shape
bounding_box (Сircle (Point cx cy) r) = 
        (Rectangle (Point (cx - r) (cy - r)) (Point (cx + r) (cy + r)))
bounding_box (Triangle (Point x1 y1) (Point x2 y2) (Point x3 y3)) = 
        Rectangle _start _end
        where _start = Point (minimum [x1, x2, x3]) (minimum [y1, y2, y3])
              _end = Point (maximum [x1, x2, x3]) (maximum [y1, y2, y3])
bounding_box (Label (Point x y) (Font _ size) row) =
        (Rectangle (Point x y) (Point (x + (fromIntegral (row * size))) (y + (fromIntegral size))))



-- Usage example: 
-- let lab = Label {base=(Point 0 0), font=Font {name="Whatever", size=10}, row=7}
