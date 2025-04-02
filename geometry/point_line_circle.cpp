/**
 * ########### Point and Vector
 */
const double EPS = 1e-9;
int cmp(double x, double y) {
    if (x < y - EPS) return -1;
    if (x > y + EPS) return 1;
    return 0;
}

struct Point {
    double x, y;

    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}

    int cmp(const Point& q) const {
        int cmp_x = ::cmp(x, q.x);
        if (cmp_x != 0) 
            return cmp_x;
        return ::cmp(y, q.y);
    }

    // operator overload to compare to Point objects with >, <, >=,..
#define op(X) bool operator X (const Point& q) const { return cmp(q) X 0; };
    op(>) op(<) op(==) op(>=) op(<=) op(!=)
#undef op

    // plus/minus two vectors
#define op(X) Point operator X (const Point &q) const { return Point(x X q.x, y X q.y); };
    op(+) op(-)
#undef op

    // scale vector
#define op(X) Point operator X (double k) const { return Point(x X k, y X k); };
    op(*) op(/)
#undef op

    double dot(const Point& q) const {
        return x * q.x + y * q.y;
    }

    double cross(const Point& q) const {
        return x * q.y - y * q.x;
    }

    double norm() { // dai luong the hien do lon, co the dung cong thuc khac
        return x * x + y * y;
    }

    double len() {
        return sqrt(norm());
    }

    Point rotate(double alpha) { // Proof: https://matthew-brett.github.io/teaching/rotation_2d.html
        double cosa = cos(alpha);
        double sina = sin(alpha);
        return Point(x * cosa - y * sina, x * sina + y * cosa);
    }
};

/**
 * ########### Line
 */
struct Line {
    double a, b, c;
    Point A, B;

    Line(double a, double b, double c) : a(a), b(b), c(c) {}

    Line(Point A, Point B) : A(A), B(B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);
    }

    Line(Point P, double k) {
        if (k == DBL_MAX) { // case line is orthogonal with x-axis
            a = 1;
            b = 0;
            c = - (a * p.x + b * p.y);
            return;
        }
        a = -k;
        b = 1;
        c = k * P.x - P.y;
    }

    double f(Point A) {
        return a * A.x + b * A.y + c;
    }

    double distFromPoint(const Point& p) const {
        return abs(p.x * a + p.y * b + c) / sqrt(a * a + b * b);
    }
};

bool areParallel(Line l1, Line l2) {
    return cmp(l1.a * l2.b, l1.b * l2.a) == 0;
}

bool areSame(Line l1, Line l2) {
    return areParallel(l1, l2) && cmp(l1.b * l2.c, l2.b * l1.c) == 0 
        && cmp(l1.c * l2.a, l2.c * l1.a) == 0;
}

bool areIntersect(Line l1, Line l2, Point &p) { // p is the intersect point (if have)
    if (areParallel(l1, l2)) return false;
    double d = l1.a * l2.b - l2.a * l1.b;
    double dx = l1.b * l2.c - l2.b * l1.c;
    double dy = l1.c * l2.a - l2.c * l1.a;
    p = Point(dx / d, dy / d);
    return true;
}

// calculate distance from point p to line if know two points belongs to line (a, b)
double distToLine(Point p, Point a, Point b, Point &c) { // c is projection of point p into line (a, b) (if have)
    Point ap = p - a, ab = b - a;
    double k = ap.dot(ab) / ab.norm();
    c = a + (ab * k);
    return (p - c).len();
}

/**
 * ########### Circle
 */
struct Circle : Point {
    double r;

    Circle(double x = 0, double y = 0, double r = 0) : Point(x, y), r(r) {}

    Circle(Point p, double r) : Point(p), r(r) {}

    bool contains(Point p) { // return true if point p is inside the circle
        return (*this - p).len() <= r + EPS;
    }

    bool intersect(Point p) { // return true if point p intersect with circle
        return ::cmp((*this - p).len(), r) == 0;
    }
};

vector<Point> intersection(Line l, Circle cir) {
    double r = cir.r;
    double a = l.a, b = l.b, c = l.c + l.a * cir.x + l.b * cir.y;
    vector<Point> res;

    double x0 = -a * c / (a * a + b * b);
    double y0 = -b * c / (a * a + b * b);

    if (c*c > r*r*(a*a + b * b) + EPS)
        return res;
    else if (fabs(c*c - r*r*(a*a + b*b)) < EPS) {
        res.push_back(Point(x0, y0) + Point(cir.x, cir.y));
        return res;
    }

    double d = r * r - c * c / (a * a + b * b);
    double mult = sqrt(d / (a * a + b * b));
    double ax, ay, bx, by;
    ax = x0 + b * mult;
    bx = x0 - b * mult;
    ay = y0 - a * mult;
    by = y0 + a * mult;

    res.push_back(Point(ax, ay) + Point(cir.x, cir.y));
    res.push_back(Point(bx, by) + Point(cir.x, cir.y));
    return res;
}
