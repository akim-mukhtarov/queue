### About

Implementing generic queue - a FIFO (first-in, first-out) data structure.
The underlying container is a round buffer (`next` of `tail` is `head`)
but there are open questions about memory allocation:
- a continuous block, allocated on initialization?
- a list of blocks with fixed size?
- a forward list ?  

Well, we'll see
