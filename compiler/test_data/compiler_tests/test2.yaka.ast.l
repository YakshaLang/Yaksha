(def factorial ( x:i32) (block (if (expr (<= x 0)) then (block (return 1))) (return (* x (call factorial (- x 1))))))
(def on_end ( n:i32) (block (expression (call print n)) (expression (call print " From defer --> Program Completed\n")) (return 0)))
(def main () (block (defer (group (call on_end 1))) (defer (group (call on_end 2))) (let a:i32 10) (let b:str "b") (while (expr (> a 0)) do (block (expression (call print (call factorial a))) (expression (call print "\n")) (expression (assign a (- a 1))) (expression (assign b (+ "a" b))))) (expression (call print b)) (expression (call print "\n")) (return 0)))

