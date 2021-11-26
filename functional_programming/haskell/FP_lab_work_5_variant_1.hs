import Control.Monad(replicateM)
import FP_lab_work_3_variant_1

-- Лабораторна 5: розробка прикладних програм мовою haskell
-- Варіант 1


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
    putStrLn "Please enter the size of your list"
    times <- readLn
    ns <- replicateM times 
                     (do putStrLn "please enter the next number: "
                         readLn :: IO Int)
    let reversed = reverse2 ns
    print reversed