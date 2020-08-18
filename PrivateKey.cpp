#include "PrivateKey.h"

PrivateKey::PrivateKey()
{
}

PrivateKey::PrivateKey(cpp_int inp_secret)
{
    S256Point genPoint = S256Point(cpp_int{ "0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798" },
        cpp_int{ "0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8" });

    this->secret = inp_secret;
    this->pub_key = inp_secret * genPoint;
}

Signature PrivateKey::sign(cpp_int z)
{
    S256Point genPoint = S256Point(cpp_int{ "0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798" },
        cpp_int{ "0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8" });
    cpp_int N{ "0xfffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141" };

    cpp_int k = this->random_int();
    cpp_int r = (k * genPoint).getX().getNum();
    cpp_int k_inv = ipow(k, N - 2, N);
    cpp_int s = ((z + r * this->secret) * k_inv) % N;
    if (s > N / 2)
        s = N - s;
    return Signature(r, s);
}

cpp_int PrivateKey::random_int()
{
    boost::random::mt19937 gen;
    boost::random::uniform_int_distribution<> dist(1);
    return cpp_int(dist(gen));
}
