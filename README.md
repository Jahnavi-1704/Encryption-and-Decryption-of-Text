# Encryption-and-Decryption-of-Text
-This program applies ASCII armouring for encryption and decryption of large text files using dynamic memory allocation.

-Upon encoding the plaintext a sequence of numbers is generated based on a key. If both the sender and receiver possess the same key, then the sender can generate the ciphertext by exclusive-ORing the plaintext with the generated sequence of bits, and the receiver can then recover the plaintext by, once again, exclusive-ORing the plaintext with the identical generated sequence of bits. 

-It uses an 8-bit unsigned integral key which acts as a unique stream cipher. This key is to be shared by both the sender and the receiver. 

-This project implements 2 functions: one function encodes the plaintext message and converts the resulting ciphertext to ASCII armour, a second function converts the ASCII armour back into the ciphertext and then decodes the ciphertext back into the plaintext. 

This program involves-

Dynmaic memory allocation

OOP Principles- Modularity

STL container classes- Arrays

C++ Libraries- String library, math library, ctype library

Flow of Control

Iterators, Functions
