# Cryptography 

This is a document for basic understanding in **cryptography**, not a deep dive 
into the mathematics behind the scenes. It will provice a clear overview of the procesess and steps 
used for securig or hashing data.

--- 

## Hashing

Is the procesess of taking data and transforming it into a **deterministic, fix-length** value called the
**digest** via a **hashing-algorithm** which is mostly a mathemtical formula. 

So called **collisions** happen which means that different inputs produce the same output. This is not 
avoidable since, the number of outputs are limited.

In theory, hashing should be impossible to revert, but can be brute-forced.

- Typical algorithms: SHA224, SHA3-224, SHA3-512, SHA246.

---

## Encryption

**Encryption** is the procesess of using mathemtical operations to transform plain, readable text into something unintelligible.
This encrypted message can then be **decrypted** (transform into the original form) if a **key** is known.

--- 

## Secret Keys

Any binariy sequence used in cryptography is a **key**. A **secret** is only know to the own machine of for the machine
involded in a certain interaction. Keys are pseudo-unique and generated via specific algorithms, and they are used in combination
with cryptographic algorithms to generate different outputs given the same data.

- A `n`-size keys means the number of bits used for the sequence.
- Keys are mostly generated in pairs for asymetric encryption.

---
 
## Symmetric Cryptography

Uses the same keys to perform and reverse or verify an operation.

Mostly used for: 

- Symmetric encryption
- Message Authentication 
- Pseudo Random Functions

### Symmetric Encryption

Is encryption involing a known secret key by both parties in a communication. The problem arises when delaing on how to 
share the key in secret.

### MAC & HMAC

**Message Authentication Code** is a concept combining a meesage witha secret key before hashing used for integrity and authentication.

1. Message data is hashed along the secret key.
2. Data is transmited with the hash alongside.
3. The interlocutor also has the same secret key and when the data arrives, the hash is re-computed with the secret key.
4. Integrity and authentication is verified.

A **HMAC** is just an standard way of combining the message with the secret key.

--- 

## Psedu Random Functions

They transform a **secret** and a **label** into a deterministic, arbitrary-length value indistinguishable from random data.

They are used for: 

- Generate unlimited keys from a single secret key.
- Generate psudo-random numbers. 

--- 

## Key Derivation Function

It is a PRF but more secure and computationaly expensive. It requieres a **salt** which is an extra secret to be added.

Used for: 

- Making password storage more secure and adding a second layer of security.

--- 

## Asymetric Cryptography

Different keys, a pulbic and a private key are used to perform and reverse/verify/complete an operation.

The main operations are: encryption (RSA), signatures (DSA) and key exchanges (DH).

### Asymetric Encryption

The public key is used for the encryption and the private key of the other party is used for the decryption.

### Sigantures

Operations that guarantees data has not changed since it was signed.

The private key is used for the creatation and the public key for the verification.

#### RSA Signature Verification

- The data is hashed and the digest is encryptd with the private key. 
- On the other end, the same data is hashed again and the signature is decrypted with the public key.
- If both digest math then the data has not been manipulated.

--- 

## Key Exchange

--- 

