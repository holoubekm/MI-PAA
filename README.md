# MI-KRY Course
## Pokročilá kryptologie
### CTU / ČVUT FIT

### Bonus 1 - Debian OpenSSL vulnerability
Attack on the DSA given the signed document and knowledge the signature was performed on the system with Debian OpenSSL vulnerability 

For mathematical background please refer here: https://plog.sesse.net/blog/tech/2008-05-14-17-21_some_maths.html

* `workplace` - this folder contains all source codes and partiall resources
* `solution` - this folder contains solution, generated nonces and program able to find private key using these nonces.

```
# Values extracted from the public key
p = 0x00af144ae2b1e1aec726b6532409eb58f9030fdf8357ea45a191a0903334b95da48b0464944b7a7186d83efac96ddf795f17c1b9e2155c47aae3508321a72724cb502c5b5616e890aab35cdd339dda8bf9a6eca788933e8aecee989031af8f887864189d25c0e366038e1e16018688893fc82ddfb88dc35fcbc16e355ba2bccc59
q = 0x00a645825b7a45e43e3d4d0a0aa7448a7149e6d187
g = 0x3d1690094ebd2c5da6ff2110ab9340e2d51856186101219b4d8cde5ae7feaea6a8dabf34bf0457d612f9a5525c117a9c6652f8ac5f63d19c39efd0a8641f1982b427d82427177057039fefcc705c4fa0c37e1f0e084ad6dc0d436a52ab832b8af221e6f9daf59354423c20b626ed590dd6b7bc34076525f74ec03208adb7fb67
#Hash of the file as OpenSSL used SHA1 as a default in 2008
SHA1(m) = 0x74f61ebadc8d61184fb426ab65ce3344ad249255

# x is the private key
# r, s are two numbers from the public signature
# k is a random nonce - number used once
r = (g^k mod p) mod q
s = (k^-1 (H(m) + xr)) mod q


i = s * k mod q
j = i - SHA1(m) mod q
k = j * r^-1 mod q

# Attack: If you can guess k, you can also find the private (secret) key x. 
# It's actually quite trivial; take s, multiplied by k:
# Steps to attack:

s*k mod q = (H(m) + xr) mod q

# Subtract H(m):

(s*k - H(m)) mod q = xr mod q

# Multiply by r^-1:

(s*k - H(m))(r^-1) mod q = x

# And voila. x is between 0 and q, so we can drop the mod on the right-hand side.

```

#### What do we have
Everything is stored in the `assignment.zip`

* `test.txt` - file to be signed using DSA
* `test.sign_ok` - signature of the file above on the system **without** vulnerability
* `test.sign_leak` - signature of the file above on the system **with** vulnerability
* `openss-dsa-test.txt` - some examples of OpenSSL commands 
* `dsapub.pem` - public key

Out task is to find the `dsapriv.pem` private key given all above.

We can take an advantage of several assumptions. The system in 2008 was probably 32bit. Thus we have to download an old OpenSSL implementation. It doesn't matter hether patched or not.

#### Process of breaking OpenSSL

From the signature equations follows that if we know the nonce `k` we are effectively able to compute the private key `x`.

##### How to find nonce used to sign a file?
Debian OpenSSL vulnerability weakened random number generator used to generate a nonce. One source of entropy was due to mistake commented out of the source codes. The only one source of entropy was `PID` of current process.

If we were able to get source code of OpenSSL with a vulnerability inside and somehow enforce the current `PID`, we could compute signature and match it against the `test.sign_leak` contents.

The OpenSSL uses the `getpid` function returning `PID` of the current process. 

Int the `workplace/chroot` folder there is a chroot enviroment with a patched `getpid` function in `getpid-preload` folder. Value returned from the function can be dynamically set using environmental variable `MAGICPID` .

##### Let's generate all signatures using all the nonces
After enumerating all 32 768 `PIDs` we get all 32 768 distincive (presumably) values of `k` used as a nonce in the `DSA`. Let make a simple `bash` loop enumerating interval <0, 65536) and for each computing signature and storing it along the `k` in one file. Running it in the chroot environment allows patchen OpenSSL library to use our implementation of `getpid` and using exactl value set in the loop. All outputs for the `i386` arch are stored in the `workplace/k.txt` file.  

After collection all the possible values of `nonce = k`, we can extract the `r` value from the public signature `6ca9ef20ba1fa11fb0129b323776069b6c7ec7a5`. For the given file we can compute SHA1 hash and try to compute it's signature for all values of `k`. 

Do to so, go to the `find_matching_k`, replace al values for `k` in the array, compile and run the output.

```bash
cd find_matching_k
make && ./poly


Found the matching k: [12791] for the extracted r: [6ca9ef20ba1fa11fb0129b323776069b6c7ec7a5]
``` 

##### Hooray for Zoidberg!

Now when we have the nonce `k` used to sign the file, we can proceed to actually breaking the private key. Let's use equations stated in the beginning.

#### For the lazy ones
Navigate to the `solution/src` folder, build the file and run it. The program loads all values fpr `k` from the `ks.txt` file in the same folder. It tries to compute all `r` values and compare them to the hardcoded value. 

When the right value is found, private key `x` is computed and user is notified.

Now we can use OpenSSL to generate a new private key, then replace those values using hex editor with our results and enjoy that feeling.

Folder `dsakeys` contains private key computed during this challenge. Your can use it freely to sign a check new files.

Folder `new_message` contains new file signed using this generated private key as an example of our success.

### Task 1
Given a file containing 2B random number on each line find quality of the random number generator which created these outputs. Preferably do so using Statistical Test Suite (`STS`) created by `NIST`. 

#### Resources
* `8mhz.biz` - list of generated 2B values
* `datagen.sh` - script which takes `8mhz.biz` as an input and produces 16 files in the `data` directory. Each file contains values for a single bit (single row).
* `sts-2_1_2.zip` - test suite produced by the NIST.
* `nistspecialpublication800-22r1a.pdf` - a documentation for the suite

Results of the testing may be found in the `report.{pdf,odt}`

