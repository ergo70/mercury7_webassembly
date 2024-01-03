#include <iostream>
#include <emscripten.h>
#include "libmercury++.h"

using namespace std;

extern "C" EMSCRIPTEN_KEEPALIVE int wasm_mercury(double *msa_mz, double *msa_abundance, const unsigned int *composition, const int charge, const double limit);

/*int main()
{
    vector<double> msa_mz, msa_abundance;
    vector<unsigned int> composition(mercury::MAX_ELEMENTS);

    composition = {14, 20, 0, 4, 0, 0, 0, 0}; // C20H14O4

    int r = mercury::mercury(msa_mz, msa_abundance, composition, 0, 0.0001); // C20H14O4

    cout << "C20H14O4" << endl;

    for (size_t i = 0; i < msa_mz.size(); i++)
    {
        cout << "m/z: " << msa_mz[i] << ", rel. Abundance: " << msa_abundance[i] * 100.0 << " %" << endl;
    }

    return r;
}*/

extern "C" EMSCRIPTEN_KEEPALIVE int wasm_mercury(double *msa_mz, double *msa_abundance, const unsigned int *composition, const int charge, const double limit)
{
    vector<double> v_msa_mz, v_msa_abundance;
    vector<unsigned int> v_composition(composition, composition+mercury::MAX_ELEMENTS);

    //v_composition.insert(v_composition.begin(), composition[0], composition[sz_composition]);

    //for (size_t i = 0; i < sz_composition; i++)
    //{
    //    v_composition[i] = composition[i];
    //}

    int r = mercury::mercury(v_msa_mz, v_msa_abundance, v_composition, charge, limit);

    copy(v_msa_mz.begin(), v_msa_mz.end(), msa_mz);
    copy(v_msa_abundance.begin(), v_msa_abundance.end(), msa_abundance);

    if (r < 0)
        return r;

    return v_msa_mz.size();
}
