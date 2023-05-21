;a) sum of two vectors
(defun sum2 (a b)
    (cond 
        ((null a) 0)
        ((null b) 0)
        (t (+ (car a) (car b) (sum2 (cdr a) (cdr b))))
    )
)

(print (sum2 '(1 2 3 4) '(-1 0 3 2)))