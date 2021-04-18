#include <pybind11/pybind11.h>
#include "uECC.h"

using namespace std;
class Cle
{
public:
    void init(string key)
    {
        this->privateKey = key;
        const uint8_t *intCastedPrivateKey = reinterpret_cast<const uint8_t *>(key.c_str());
        const int curvePublicKeySize = uECC_curve_public_key_size(uECC_secp256k1());
        uint8_t *publicKeySized = new uint8_t(curvePublicKeySize);
        uECC_compute_public_key(intCastedPrivateKey, publicKeySized, uECC_secp256k1());
        this->publicKey = std::string(publicKeySized, publicKeySized + curvePublicKeySize);
    }

    string getPrivateKey()
    {
        return this->privateKey;
    }
    string getPublicKey()
    {
        return this->publicKey;
    }

private:
    string privateKey;
    string publicKey;
};

namespace py = pybind11;

PYBIND11_MODULE(cle, m)
{
    py::class_<Cle>(m, "Cle", py::dynamic_attr())
        .def(py::init())
        .def("init", &Cle::init)
        .def("get_private_key", &Cle::getPrivateKey)
        .def("get_public_key", &Cle::getPublicKey);
}
