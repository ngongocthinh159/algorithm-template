int basis[d]; // basis[i] keeps the mask of the vector whose f value is i

int sz; // Current size of the basis

void insertVector(int mask) {
    for (int i = d - 1; i >= 0; i--) {
        if ((mask & 1 << i) == 0) continue; // continue if current mask can not settle the i-th bit

        // Current mask is a candiate to settle i-th bit

        if (!basis[i]) { // If there is no basis vector already settled the i-th bit, then choose this vector to be that vector -> Insert current mask to set of basis vectors
            basis[i] = mask;
            ++sz;

            return;
        }

        // Otherwise subtract the basis vector from this vector
        mask ^= basis[i];
    }
}

bool isInVectorSpace(int mask) {
    for (int i = d - 1; i >= 0; i--) {
        if ((mask & 1 << i) == 0) continue;

        if (!basis[i]) return false;

        mask ^= basis[i];
    }

    return true;
}