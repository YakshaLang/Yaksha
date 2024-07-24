(def main () (block (let a:Array[i32] ) (defer (del a)) (expression (call arrput a 1)) (expression (call arrput a 2)) (expression (call arrput a 3)) (expression (call print (get[] a 0))) (expression (assign[] (set[] a (+ 0 0)) 0)) (expression (call print (get[] a 0))) (expression (call print "\n")) (return 0)))

