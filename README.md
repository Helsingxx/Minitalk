<h1> Description </h1>

```
This project was an implementation of how two processes can be used to communicate binary
data using signals. Two signals were used, SIGUSR1 to identify the 1s and SIGUSR2 to identify
the 0s.
These signals were then used to communicate data in the UTF-8 format.

Normal processes are not supposed to use system signals to communicate this way, but this was an
interesting proof-of-concept of how any two different objects that can be identified as different
can be used to codify any kind of data, and how signals could have been used for this approach.
```
