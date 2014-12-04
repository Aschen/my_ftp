my_ftp
======

A basic ftp server and client.

Functionnality
--------------
 
  * Multi clients
  * cd ls pwd get put help quit commands are handled.
  * Chroot users inside directory (where you run the server)

Informations
------------

  * Only for testing purpose, don't run it on a remote server
  * Not RFC compliant !!

Examples
--------

Run the server
```
./server 4242
```

Connect with client
```
./client 127.0.0.1 4242
```
