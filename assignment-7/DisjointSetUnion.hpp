#ifndef DISJOINT_SET_UNION_HPP
#define DISJOINT_SET_UNION_HPP

struct dsu_node {
	dsu_node* origin = nullptr;
	int weight = 1;
};

dsu_node* root(dsu_node* x) {
	if (x->origin == nullptr) {
		return x;
	}
	return x->origin = root(x->origin);
}

dsu_node* root(dsu_node& x) {
	if (x.origin == nullptr) {
		return &x;
	}
	return x.origin = root(x.origin);
}

bool unite(dsu_node& a, dsu_node& b) {

	dsu_node* ra = root(a);
	dsu_node* rb = root(b);

	if (ra == rb) {
		return false;
	}

	if (ra->weight > rb->weight) {
		rb->origin = ra;
		ra->weight += rb->weight;
	} else {
		ra->origin = rb;
		rb->weight += ra->weight;
	}
	return true;
}

#endif
