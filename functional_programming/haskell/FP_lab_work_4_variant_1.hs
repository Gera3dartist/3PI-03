
-- Лабораторна 4: типи і класи типів
-- Варіант 1

------- Завдання 1 -------

-- обчислення площі фігури (для мітки через розмір одного символу та їх кількість)

data Font = Font { name :: String, size :: Int} deriving (Show)
data Point = Point Float Float deriving (Show)

data Shape = Label {start_point :: Point, font :: Font, row :: Int} deriving (Show)

area :: Shape -> Int
area (Label _ (Font _ size) row) = size * row

-- Usage example: 
-- let lab = Label {start_point=(Point 0 0), font=Font {name="Whatever", size=10}, row=7}
-- area lab