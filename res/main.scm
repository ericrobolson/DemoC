;; Flags for running the game
(define gsys-quit #f)
(define gsys-repl #t)
(define gsys-hot-reload #t)

(load "./hi.scm")

;; Tells the engine to exist
(define (sys-exit)
	(set! gsys-quit #t))

(define (hi-there)
	(+ 1 2 3 4))