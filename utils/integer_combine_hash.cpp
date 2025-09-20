
// Used to combine multiple integers (< 10) into a single hash
// Used with unordered_map and unordered_set
// General step: 
// + define object struct that needed to be hashed
// + define hash functor for that object -> call IntegerCombineHash
//      + any field of the object is not integer must converted into integer first
// + define equality functor for that object
// + define unordered_set/map with hash and equality functor


struct IntegerCombineHash {
    // SplitMix64 for scrambling (defense against adversarial collisions)
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    // Boost-style hash_combine for multiple integers
    template <typename T>
    static void hash_combine(size_t& seed, const T& v) {
        seed ^= std::hash<T>()(v) + 0x9e3779b97f4a7c15 + (seed << 6) + (seed >> 2);
    }

    // Variadic template: combine multiple integers into a single hash
    template <typename... Args>
    size_t operator()(const tuple<Args...>& tup) const {
        size_t seed = 0;
        std::apply([&](const auto&... args) {
            (hash_combine(seed, args), ...);  // fold expression
        }, tup);

        // scramble final hash with SplitMix64
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(seed + FIXED_RANDOM);
    }
};

// === unordered_set Usage
struct Packet {
    int s, d, t;
};

// Equality functor
struct PacketEqual {
    bool operator()(const Packet& a, const Packet& b) const {
        return a.s == b.s && a.d == b.d && a.t == b.t;
    }
};

// Hash functor
struct PacketHash {
    size_t operator()(const Packet& p) const {
        return IntegerCombineHash{}(make_tuple(p.s, p.d, p.t));
    }
};

unordered_set<Packet, PacketHash, PacketEqual> S;


// === unordered_map Usage
// unordered_map<key, value, hash, equal>
unordered_map<Packet, string, PacketHash, PacketEqual> packetMap;

