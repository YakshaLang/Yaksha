(def main () (block (let a:Array[Array[i32]] ) (let b:Array[i32] ) (defer (del a)) (defer (del b)) (expression (call arrput b 1)) (expression (call arrput a b)) (expression (call print (get[] (get[] a 0) 0))) (expression (call print "\n")) (expression (assign[] (set[] (get[] a 0) 0) 100)) (expression (call print (get[] (get[] a 0) 0))) (expression (call print "\n")) (return 0)))

