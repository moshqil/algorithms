#include <iostream>
#include <cmath>
#include <tuple>
#include <vector>
using namespace std;

bool close_to_0(long long value) {
    return abs(value) < 0.0000001;
}

class Vector {
public:
    long long x, y, r, alpha;
    Vector(const long long& x, const long long& y) : x(x), y(y), r(sqrt(x * x + y * y)), alpha(atan2(y, x)) {}
    Vector operator+ (const Vector& other) const {
        return Vector(this->x + other.x, this->y + other.y);
    }
    Vector operator- (const Vector& other) const {
        return Vector(this->x - other.x, this->y - other.y);
    }
    Vector operator* (long long& other) const {
        return Vector(this->x * other, this->y * other);
    }
    long long operator* (const Vector& other) const {
        return (this->x * other.x) + (this->y * other.y);
    }
    long long operator% (const Vector& other) const {
        return (this->x * other.y) - (this->y * other.x);
    }
    Vector normalise() const {
        return Vector(this->x / this->r, this->y / this->r);
    }
};

class Point {
public:
    long long x, y;
    Point(const long long& x, const long long& y) : x(x), y(y) {}
    bool operator== (const Point& other) const {
        return this->x == other.x && this->y == other.y;
    }
    Vector operator- (const Point& other) const {
        return Vector(this->x - other.x, this->y - other.y);
    }
};

class Line {
public:
    long long a, b, c;
    Line(const long long& a, const long long& b, const long long& c) : a(a), b(b), c(c) {}
    Line(const Point& A, const Point&B) {
        Vector l = A - B;
        l = Vector(l.y, -l.x);
        this->a = l.x;
        this->b = l.y;
        this->c = -(l.x * A.x + l.y * A.y);
    }
    tuple<int, Point> intersect (const Line& other) const {
        long long k = this->a * other.b - other.a * this->b;
        if (k != 0) {
            return {0, Point((other.c * this->b - other.b * this->c) / k, (other.a * this->c - other.c * this->a) / k)};
        }
        Point p = {0, 0};
        if (this->a == 0 and other.a == 0) {
            if (this->c * other.b == this->b * other.c) {
                return {2, p};
            }
            return {1, p};
        }
        if (this->b == 0 and other.b == 0) {
            if (this->c * other.a == this->a * other.c) {
                return {2, p};
            }
            return {1, p};
        }
        if (this->c * other.a == this->a * other.c) {
            return {2, p};
        }
        return {1, p};
    }
};


bool is_in_segment(Point& A, Point& B, Point& C) {
    Vector v1 = A - B;
    Vector v2 = A - C;
    if (close_to_0(v1 % v2) && (v1 * v2 <= 0)) {
        return true;
    }
    return false;
}

int main() {
    vector<Point*> a;
    int n; cin >> n;
    long long x, y;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        auto * p = new Point {x, y};
        a.push_back(p);
    }
    a.push_back(a[0]);
    long long ans = 0;
    for (int i = 1; i < a.size(); i++) {
        ans += ((a[i]->x - a[i - 1]->x) * (a[i]->y + a[i - 1]->y));
    }
    ans = abs(ans);
    cout << ans / 2;
    if (ans % 2 == 1) {
        cout << ".5";
    }
    cout << endl;
}
