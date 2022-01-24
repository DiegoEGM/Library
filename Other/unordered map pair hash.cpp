//very useful to speed up string hashing with two bases!
struct HASH{
size_t operator()(const pair<int,int>&x)const{
    return hash<long long>()(((long long)x.first)^(((long long)x.second)<<32));
}};
unordered_map <pair<int, int>, int, HASH> M;
