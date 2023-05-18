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


int main(int argc, char* argv[])
{
    // Contruct  ECP(const Integer &modulus, const FieldElement &A, const FieldElement &B);
    // User Defined Domain Parameters for curve y^2 =x^3 + ax +b
    // Modulus p
    
    Integer p("ffffffff00000001000000000000000000000000ffffffffffffffffffffffffH");
    // Coefiction a
    Integer a("ffffffff00000001000000000000000000000000fffffffffffffffffffffffcH");
    // Coefiction b
    Integer b("5ac635d8aa3a93e7b3ebbd55769886bc651d06b0cc53b0f63bce3c3e27d2604bH");
    /* create a curve*/
    a %= p; b %= p; // a mod p, b mod p

    /* ECC curve */
    CryptoPP::ECP curve256_params(p, a, b); // buide curve y^2 =x^3 +ax +b
    /* subgroup <G> on curve */ 

    // x, y: Base Point G
    Integer Gx("6b17d1f2e12c4247f8bce6e563a440f277037d812deb33a0f4a13945d898c296H");
    Integer Gy("4fe342e2fe1a7f9b8ee7eb4a7c0f9e162bce33576b315ececbb6406837bf51f5H");
    // Creat point G
    ECP::Point G(Gx, Gy);
    // Oder n of group <G>
    Integer n("ffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551H");
    //Cofactors
    Integer h("01H");

    /* Set ECC parameters and subgroup <G>*/
    // CryptoPP::DL_GroupParameters_EC<ECP> curve256(eqcurve256,G,n,h);
    CryptoPP::DL_GroupParameters_EC<ECP> curve256;
    curve256.Initialize(curve256_params, G, n, h);

    /* Get curve paramaters p, a, b, G, n, h*/
    cout << "========== ECDH key exchange using secp256r1 curve ==========" << endl;
    cout <<"[+] Cofactor h = " << curve256.GetCofactor()<<endl;
    cout <<"[+] Subgroup Order n = " <<curve256.GetSubgroupOrder()<<endl;
    cout <<"[+] Gx = "<<curve256.GetSubgroupGenerator().x <<endl;
    cout <<"[+] Gy = "<<curve256.GetSubgroupGenerator().y<<endl;
    cout <<"[+] Coefficient  a = " << curve256.GetCurve().GetA() <<endl;
    cout <<"[+] Coefficient  b = " << curve256.GetCurve().GetB() <<endl;
    cout <<"[+] Prime number p = " << curve256.GetCurve().GetField().GetModulus() << endl;

    string input;
    cout << "> Enter your private key (in hex): ";
    cin >> input;

    // calculate you pubkey
    Integer priv(input.c_str()); priv %= p;
    ECP::Point H=curve256.GetCurve().ScalarMultiply(G,priv); // priv*P;
    cout << "[+] Your pubKey: " << endl;
    cout << "Px=" << H.x << endl;
    cout << "Py=" << H.y << endl;

    // input other pubkey
    cout << "[+] Enter other pubKey: " << endl;
    cout << "Ox = "; cin >> input;
    Integer ox(input.c_str());
    cout << "Oy = "; cin >> input;
    Integer oy(input.c_str());
    ECP::Point Other(ox, oy);

    // calculate shared key
    ECP::Point S=curve256.GetCurve().ScalarMultiply(Other,priv);
    cout << "[+] Shared key: ";
    cout << S.x << endl;
}