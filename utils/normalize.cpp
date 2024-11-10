void normalize(vector<int> &v) {
    vector<int> aux = v;
    sort(aux.begin(), aux.end());
    aux.erase(unique(aux.begin(), aux.end()), aux.end());
    for (int i = 0; i < v.size(); i++) v[i] = lower_bound(aux.begin(), aux.end(), v[i]) - aux.begin() + 1;
}
