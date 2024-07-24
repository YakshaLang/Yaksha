(class Student ( name:str age:i32))
(class Spaceship ( name:str class_:str))
(def main () (block (let myship:../test_data/compiler_tests/test4.yaka:::Spaceship (call Spaceship)) (defer (del myship)) (let a:i32 10) (while (expr (!= a 0)) do (block (expression (call print a)) (expression (call print "\n")) (expression (assign a (- a 1))))) (return 0)))

