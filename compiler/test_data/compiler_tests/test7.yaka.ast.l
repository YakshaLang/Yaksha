(def main () (block (let a:Array[Array[int]] ) (let b:Array[int] ) (defer (del a)) (defer (del b)) (expression (call arrput b 1)) (expression (call arrput a b)) (expression (call print (get[] (get[] a 0) 0))) (expression (call print "\n")) (expression (assign[] (set[] (get[] a 0) 0) 100)) (expression (call print (get[] (get[] a 0) 0))) (expression (call print "\n")) (return 0)))

