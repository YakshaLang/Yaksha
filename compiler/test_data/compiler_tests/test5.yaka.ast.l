(class Captain ( name:str age:int))
(class Spaceship ( name:str class_:str captain:../test_data/compiler_tests/test5.yaka:::Captain))
(def print_str_item ( item:str value:str) (block (expression (call print item)) (expression (call print ":\t")) (expression (call print value)) (expression (call print "\n")) (return 0)))
(def print_int_item ( item:str value:int) (block (expression (call print item)) (expression (call print ":\t")) (expression (call print value)) (expression (call print "\n")) (return 0)))
(def print_captain ( c:../test_data/compiler_tests/test5.yaka:::Captain) (block (expression (call print_str_item "Captain.Name" (get namec))) (expression (call print_int_item "Captain.Age" (get agec))) (return 0)))
(def print_ship ( s:../test_data/compiler_tests/test5.yaka:::Spaceship) (block (expression (call print_str_item "Name" (get names))) (expression (call print_str_item "Class" (get class_s))) (expression (call print_captain (get captains))) (return 0)))
(def main () (block (let myship:../test_data/compiler_tests/test5.yaka:::Spaceship (call Spaceship)) (expression (assign. (set namemyship) "USS Enterprise")) (expression (assign. (set class_myship) "Galaxy")) (expression (assign. (set captainmyship) (call Captain))) (expression (assign. (set name(get captainmyship)) "Picard")) (expression (assign. (set age(get captainmyship)) 59)) (defer (del myship)) (defer (del (get class_myship))) (defer (del (get namemyship))) (defer (del (get captainmyship))) (defer (del (get name(get captainmyship)))) (expression (call print_ship myship)) (return 0)))

