# SECP256K1 - ALREADY COMPILED TAR FILE

Genesys-Core from v1.4 + now required secp256k1 before compiling the
daemon ( genesysd ).

You can download the .tar file and decompress it - no need to compile it.

wget ---------------------------------------------

tar xvf secp256k1_compiled.tar

And thats it! the .tar file will be decompressed to the folder "secp256k1"
You can now just compile your "genesysd" daemon as usually.

--------------------------------------------------------------------------------------------------------------------------------

In Case you want to Compile the secp256k1 yourself, we have a working version for Genesys-Core.
Source code in /GenesysCoin/src/secp256k1

Read the "Readme File" for Instructions.
