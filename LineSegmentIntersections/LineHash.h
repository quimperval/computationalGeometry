
  struct LineHash{                                                /**                                                          * without the const in this method operator() we would have the below error in compilation:                             * /usr/include/c++/11/bits/hashtable_policy.h:1217:23: error:                                                           * /usr/include/c++/11/bits/hashtable_policy.h:1217:23: error: static assertion failed: hash function must be invocable with an argument of key type                                 * 1217 |         static_assert(__is_invocable<const _Hash&, const _Key&>{},                                             *                                                           */                                                             std::size_t operator()(const Line& l) const {                                                                               //^ - bitwise xor operator
                return std::hash<float>()(l.getP1()->getX()) ^                                                                              std::hash<float>()(l.getP1()->getX()) ^                     std::hash<float>()(l.getP2()->getX()) ^                     std::hash<float>()(l.getP2()->getX())
                    ;                                                   }                                                   };
