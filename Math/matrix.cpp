template<class T> struct Mat {
    int n, m; 
    vector<vector<T>> a;
    vector<Mat> mat;   
    Mat() : Mat(0){}
    Mat(int _n, int _m) : n(_n), m(_m), a(_n, vector<T>(_m, T(0))){}
    Mat(int _n) : n(_n), m(_n), a(_n, vector<T>(_n, T(0))){}
    Mat(vector<vector<T>> x) : n(x.size()), m(x[0].size()), a(x){}
    inline const vector<T> &operator[](int k) const {
        return a[k];
    } //x * mat -> [from][to] | mat * x -> [to][from]
    inline vector<T> &operator[](int k) {
        return a[k];
    }
    Mat &operator+=(const Mat &b) {
        assert(n == b.n && m == b.m);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                (*this)[i][j] += b[i][j];
        return (*this);
    }
    Mat &operator-=(const Mat &b) {
        assert(n == b.n && m == b.m);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                (*this)[i][j] -= b[i][j];
        return (*this);
    }
    Mat &operator*=(const Mat &b) {
        assert(m == b.n);
        int f = m;
        m = b.m;
        vector<vector<T>> ret(n, vector<T>(m, 0));
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                for(int k = 0; k < f; k++)
                    ret[i][j] = (ret[i][j] + (*this)[i][k] * b[k][j]);
        a.swap(ret);
        return (*this);
    }
    Mat operator^(long long p) const {
  		assert(p >= 0);
  		Mat a(this -> n), b(*this);
  		a.id();
  		while (p) {
  			if (p & 1) a = a * b;
  			b = b * b;
  			p >>= 1;
  		}
  		return a;
    }
    Mat operator+(const Mat &b) const {
        return (Mat(*this) += b);
    }
    Mat operator-(const Mat &b) const {
        return (Mat(*this) -= b);
    }
    Mat operator*(const Mat &b) const {
        return (Mat(*this) *= b);
    }
    T determinant() {
        Mat b(*this);
        assert(n == m);
        T ret = 1;
        for(int i = 0; i < m; i++) {
            int idx = -1;
            for(int j = i; j < m; j++) {
                if(b[j][i] != 0)
                    idx = j;
            }
            if(idx == -1)
                return T(0);
            if(i != idx) {
                ret *= -1;
                swap(b[i], b[idx]);
            }
            T vv = b[i][i];
            ret *= vv;
            for(int j = 0; j < m; j++) {
                b[i][j] /= vv;
            }
            for(int j = i + 1; j < m; j++) {
                T a = b[j][i];
                for(int k = 0; k < m; k++) {
                    b[j][k] -= b[i][k] * a;
                }
            }
        }
        return ret;
    }
    void id() {
        for (int i = 0 ; i < n ; i ++) a[i][i] = T(1);
    }
};
