#ifndef LINE_PTR_HASH
#define LINE_PTR_HASH
struct LinePtrHash {
    std::size_t operator()(const std::shared_ptr<Line>& l) const {
        if (!l) return 0;
        std::size_t h1 = std::hash<float>()(l->getP1()->getX());
        std::size_t h2 = std::hash<float>()(l->getP1()->getY());
        std::size_t h3 = std::hash<float>()(l->getP2()->getX());
        std::size_t h4 = std::hash<float>()(l->getP2()->getY());

        return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
    }
};
#endif


