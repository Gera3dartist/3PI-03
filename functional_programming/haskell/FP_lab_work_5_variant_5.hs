import FP_lab_work_3_variant_5

-- Лабораторна 5: розробка прикладних програм мовою haskell
-- Варіант 5


------- Завдання 1 -------
-- Реалізувати та скомпілювати одну з програм з лабороторної роботи №3 для свого варіанту
-- з введенням
--      а) з клавіатури
--      б) з файлу
-- з виведенням
--      в) на екран
--      г) у файл



main :: IO ()
main = do
    putStrLn "Please enter a word to count the subsequence"
    aword <- getLine
    let reversed = count_subseq aword
    print reversed