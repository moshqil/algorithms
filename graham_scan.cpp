#include <iostream>
#include <cmath>
#include <tuple>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

bool close_to_0(long long value) {
    return abs(value) < 0.00000000000001;
}

class Vector {
public:
    long long x, y;
    long double r, alpha, r2;
    Vector(const long long& x, const long long& y) : x(x), y(y), r(sqrt(x * x + y * y)), alpha(atan2(y, x)), r2(x * x + y * y) {
    }
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
    void print() {
        cout << x << ' ' << y << endl;
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
    vector<Point> a;
    int n; cin >> n;
    Point first = {10000, 10000};
    for (int i = 0; i < n; i++) {
        long long x, y; cin >> x >> y;
        if (y < first.y) {
            first = {x, y};
        } else if (y == first.y && x < first.x) {
            first = {x, y};
        }
        a.emplace_back(x, y);
    }
    sort(a.begin(), a.end(), [first](Point& f, Point& s) {
        if ((f - first) % (s - first) == 0) {
            return (f - first).r2 < (s - first).r2;
        }
        return (f - first) % (s - first) > 0;
    });
    a.push_back(first);
    vector<Point> result;
    result.push_back(a[0]);
    result.push_back(a[1]);
    for (int i = 2; i < a.size(); i++) {
        auto A = a[i];
        auto B = result[result.size() - 1];
        auto C = result[result.size() - 2];
        while ((B - C) % (A - B) <= 0) {
            result.pop_back();
            if (result.size() < 2) {
                break;
            }
            B = result[result.size() - 1];
            C = result[result.size() - 2];
        }
        result.push_back(A);
    }
    result.pop_back();
    //for (auto elem : result) {
    //    elem.print();
    //}
    result.push_back(result[0]);
    long double perimeter = 0;
    long long area = 0;
    for (int i = 1; i < result.size(); i++) {
        perimeter += (result[i] - result[i - 1]).r;
        area += ((result[i].x - result[i - 1].x) * (result[i].y + result[i - 1].y));
    }
    cout << perimeter << endl;
    area = abs(area);
    cout << area / 2;
    if (area % 2 == 1) {
        cout << ".5";
    }
    cout << endl;
}
