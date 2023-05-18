//  Defines the entry point for the console application
/*ECC parameters p,a,b, P (or G), n, h where p=h.n*/

/* Source, Sink */
#include "cryptopp/filters.h"

#include <ctime>
#include <iostream>
#include <string>
using namespace std;

/* Randomly generator*/
#include "cryptopp/osrng.h"
using CryptoPP::AutoSeededRandomPool;

/* Integer arithmatics*/
#include <cryptopp/integer.h>
using CryptoPP::Integer;
#include <cryptopp/nbtheory.h>
using CryptoPP::ModularSquareRoot;

#include <cryptopp/ecp.h>
#include <cryptopp/eccrypto.h>
using CryptoPP::ECP;    // Prime field p
using CryptoPP::ECIES;
using CryptoPP::ECPPoint;
using CryptoPP::DL_GroupParameters_EC;
using CryptoPP::DL_GroupPrecomputation;
using CryptoPP::DL_FixedBasePrecomputation;

#include <cryptopp/pubkey.h>
using CryptoPP::PublicKey;
using CryptoPP::PrivateKey;

/* standard curves*/
#include <cryptopp/asn.h>
#include <cryptopp/oids.h> // 
namespace ASN1 = CryptoPP::ASN1;
using CryptoPP::OID;

int main(int argc, char** argv) {

    // secp256r1 curve's params
    Integer p("ffffffff00000001000000000000000000000000ffffffffffffffffffffffffH");
    Integer a("ffffffff00000001000000000000000000000000fffffffffffffffffffffffcH");
    Integer b("5ac635d8aa3a93e7b3ebbd55769886bc651d06b0cc53b0f63bce3c3e27d2604bH");
    Integer n("ffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551H");
    Integer h("01H");

    CryptoPP::ECP curve256_params(p, a, b);

    // x, y: Base Point G
    Integer Gx("6b17d1f2e12c4247f8bce6e563a440f277037d812deb33a0f4a13945d898c296H");
    Integer Gy("4fe342e2fe1a7f9b8ee7eb4a7c0f9e162bce33576b315ececbb6406837bf51f5H");
    ECP::Point G(Gx, Gy);

    /* Set ECC parameters and subgroup <G>*/
    // CryptoPP::DL_GroupParameters_EC<ECP> curve256(eqcurve256,G,n,h);
    CryptoPP::DL_GroupParameters_EC< ECP > curve256;
    curve256.Initialize(curve256_params, G, n, h);

    // get privKey
    string privKey = argv[1];
    Integer d(privKey.c_str());

    // calculate pubKey from privKey
    ECP::Point P = curve256.GetCurve().ScalarMultiply(G, d); // P = d*G

    // print out Px, P.y
    cout << P.x << P.y << endl;

    return 0;
}