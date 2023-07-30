# Sample YakshaLisp lisp file
(def x 1)    # define x to 1
(println "Hello world")
(println x)  # print x

# variable argument function !
# currently only last arg can be variable..
(defun add_all (a &b)
    (+ a (if b (reduce + b) 0))
    )

(println "(add_all 1 2 3 4 5 6)")
(println (add_all 1 2 3 4 5 6))

(println "(add_all 3)")
(println (add_all 3))

# below should fail saying too few arguments
# (println "(add_all)")
# (println (add_all))
