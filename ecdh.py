from os import urandom
import subprocess
import hashlib

class ECDH:
    def __init__(self) -> None:
        self.curve = 'secp256k1'
        self.p = 0xffffffff00000001000000000000000000000000ffffffffffffffffffffffff
        self.a = 0xffffffff00000001000000000000000000000000fffffffffffffffffffffffc
        self.b = 0x5ac635d8aa3a93e7b3ebbd55769886bc651d06b0cc53b0f63bce3c3e27d2604b
        self.n = 0xffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551
        self.h = 0x1
        self.G = (0x6b17d1f2e12c4247f8bce6e563a440f277037d812deb33a0f4a13945d898c296, 0x4fe342e2fe1a7f9b8ee7eb4a7c0f9e162bce33576b315ececbb6406837bf51f5)
        
    def generate_key(self):
        # Generate user's privKey
        self.d = int.from_bytes(urandom(256), 'little')
        
        # Generate pubKey from privKey
        out = subprocess.run(f"./ECDH/key_generate {self.d}".split(), capture_output=True).stdout[:-2].decode()
        self.P = out.replace(".", " ")
        return self.d, self.P
        
    def exchange_key(self, other_pubKey):
        # Perform ECDH key exchange
        shared_key = subprocess.run(f"./ECDH/key_exchange {self.d} {other_pubKey}".split(), capture_output=True).stdout[:-2].decode()
        return hashlib.sha256(shared_key.encode()).hexdigest()