(define-module (mod-guile)
  #:use-module (system foreign))

(define request_rec-fields
  (list
   '*           ; 0  apr_pool_t * pool
   '*           ; 1  conn_rec * connection
   '*           ; 2  server
   '*           ; 3  next
   '*           ; 4  prev
   '*           ; 5  main
   '*           ; 6  the_request
   int          ; 7  assbackwards
   int          ; 8  proxyreq
   int          ; 9  header_only
   int          ; 10 proto_num
   *            ; 11 protocol
   *            ; 12 hostname
   int64        ; 13 request_time
   '*           ; 14 status_line
   int          ; 15 status
   int          ; 16 method_number
   '*           ; 17 method
   int64        ; 18 allowed
   '*           ; 19 allowed_xmethods
   '*           ; 20 allowed_methods
   int64        ; 21 sent_bodyct
   int64        ; 22 bytes_send
   int64        ; 23 mtime
   '*           ; 24 range
   int64        ; 25 clength
   int          ; 26 chunked
   int          ; 27 read_body
   int          ; 28 read_chunked
   unsigned-int ; 29 expecting_100
   '*           ; 30 kept_body
   '*           ; 31 body_table
   int64        ; 32 remaining
   int64        ; 33 read_length
   '*
   '*
   '*
   '*
   '*

   '*
   '*
   '*

   '*

   '*
   '*
   '*
   '*
   '*
   '*
   '*
   '*
   '*

   int
   int

   '*
   '*

   '*

   '*

   '*

   '*
   '*
   '*
   '*

   int
   int

   '*

   '*

   int64
   ))

(define-public (hello)
  "sup, man")

(define (request_rec->request foreign-request_rec*)
  "HI")
