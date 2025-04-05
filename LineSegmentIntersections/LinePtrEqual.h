#ifndef LINE_PTR_EQUAL_H
#define LINE_PTR_EQUAL_H
struct LinePtrEqual {
    bool operator()(const std::shared_ptr<Line>& a, const std::shared_ptr<Line>& b) const {
	if (!a || !b) 
	    return a == b;
	return *a == *b;  // Ensure `operator==` is implemented in `Line`
    }
};
#endif //LINE_PTR_EQUAL_H
