bool cmp(array<int,3> &p, array<int,3> &q) {    
	if (p[0] / BLOCK_SIZE != q[0] / BLOCK_SIZE) return p < q;    
	return (p[0] / BLOCK_SIZE & 1) ? (p[1] < q[1]) : (p[1] > q[1]);
}
int x = 0, y = -1;
for(auto &[l, r, u, i]: q) {
    while(x > l) x --, insert(x);
    while(y < r) y ++, insert(y);
    while(x < l) erase(x), x ++;
    while(y > r) erase(y), y --;
}
