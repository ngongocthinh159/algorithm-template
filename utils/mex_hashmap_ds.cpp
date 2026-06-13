struct MexDS {
    unordered_map<int,int> f;
    int mex;
    MexDS() {
        mex = 0;
    }
    void insert(int x) {
        f[x]++;
        while (f[mex] != 0) mex++;
    }
    void remove(int x) {
        f[x]--;
        if (f[x] == 0 && x <= mex - 1) mex = x;
    }
    int queryMex() {
        return mex;
    }
};
int main() {
    MexDS mds;
    
    mds.insert(0);
    mds.insert(1);
    mds.insert(2);
    cout << mds.queryMex() << nline; // return 3

    mds.remove(1);
    cout << mds.queryMex() << nline; // return 1

    return 0;
}