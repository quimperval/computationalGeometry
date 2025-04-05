
  struct LineHash{                                                /**                                                          * without the const in this method operator() we would have the below error in compilation:                             * /usr/include/c++/11/bits/hashtable_policy.h:1217:23: error:                                                           * /usr/include/c++/11/bits/hashtable_policy.h:1217:23: error: static assertion failed: hash function must be invocable with an argument of key type                                 * 1217 |         static_assert(__is_invocable<const _Hash&, const _Key&>{},                                             *                                                           */                                                  
    std::size_t operator()(const Line& l) const {
    std::size_t h1 = std::hash<float>()(l.getP1()->getX());
    std::size_t h2 = std::hash<float>()(l.getP1()->getY());
    std::size_t h3 = std::hash<float>()(l.getP2()->getX());
    std::size_t h4 = std::hash<float>()(l.getP2()->getY());

    return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
    }
};
