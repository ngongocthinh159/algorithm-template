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

    friend istream& operator >> (istream& is, Point& p) {
        is >> p.x >> p.y;
        return is;
    }

    friend ostream& operator << (ostream& os, Point& p) {
        os << p.x << " " << p.y;
        return os;
    }

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

    double dist(const Point& q) const {
        return (*this - q).len();
    }

    double mandist(const Point& q) const {
        return abs(x - q.x) + abs(y - q.y);
    }
};

/**
 * ########### Line
 */
struct Line {
    double a, b, c;
    Point A, B;

    Line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}

    Line(Point _A, Point _B) : A(_A), B(_B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);
    }

    Line(Point P, double k) {
        if (k == DBL_MAX) { // case line is orthogonal with x-axis (equation: x = p.x)
            a = 1;
            b = 0;
            c = -P.x;
            return;
        }
        a = -k;
        b = 1;
        c = k * P.x - P.y;
    }

    double f(const Point& P) {
        return a * P.x + b * P.y + c;
    }

    // calculate distance from a point to line if already has the line object
    double distFromPoint(const Point& p, Point &projectedPoint) const { // projectedPoint is projection of point p into current line
        double k = - (p.x * a + p.y * b + c) / (a * a + b * b);
        projectedPoint = p + Point(k * a, k * b);
        return abs(k) * sqrt(a * a + b * b);
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
double distToLine(Point p, Point a, Point b, Point &c) { // c is projection of point p into line (a, b)
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

    Circle(double _x = 0, double _y = 0, double _r = 0) : Point(_x, _y), r(_r) {}

    Circle(Point _p, double _r) : Point(_p), r(_r) {}

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

/**
 * ########### Polygon
 */
using Polygon = vector<Point>;

double signedArea(const Polygon& p) {
    double area = 0;
    for (int j, i = 0; i < (int) p.size(); i++) {
        j = (i + 1) % (int) p.size();
        area += p[i].cross(p[j]);
    }
    return area / 2.00;
}

double area(const Polygon& p) {
    return fabs(signedArea(p));
}

// check if rotation from vector ab -> vector ac is ccw 
// (the rotation angle is always took the less than 180 direction according to cross product)
int ccw(Point a, Point b, Point c) {
    return cmp((b - a).cross(c - a), 0);
}

bool isConvex(const Polygon& p) { // set of points must be already sorted by convex edges ccw or cw
    int sz = p.size();
    if (sz < 3) 
        return false;
    int turn = ccw(p[0], p[1], p[2]);
    for (int i = 1; i < sz; i++)
        if (ccw(p[i], p[(i+1) % sz], p[(i+2) % sz]) * turn < 0)
            return false;
    return true;
}

void convexHullGraham(Polygon& pts) {
    // choose pivot: lowest y, x
    Point pivot = pts[0];
    for (int i = 1; i < (int) pts.size(); i++)
        if (pivot.y > pts[i].y
                || (pivot.y == pts[i].y && pivot.x > pts[i].x))
            pivot = pts[i];
    
    // sort remaining points based on angle with pivot and Ox axis, tie break with smaller distance first
    sort(pts.begin(), pts.end(), [&](Point& p, Point& q) {
        int is_ccw = ccw(pivot, p, q);
        if (is_ccw > 0) return true;
        return is_ccw == 0 && (p - pivot).norm() < (q - pivot).norm();
    });
    pts.erase(unique(pts.begin(), pts.end()), pts.end()); // remove duplicate points
    if (pts.size() < 3) return;

    // find convex hull
    int n = 0;
    for (int i = 0; i < (int) pts.size(); i++) {
        while (n >= 2 && ccw(pts[n - 2], pts[n - 1], pts[i]) <= 0) n--;
        pts[n++] = pts[i];
    }
    pts.resize(n);
}

void convexHullMonotoneChain(Polygon& pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());

    Polygon up, down;
    for (int i = 0; i < (int) pts.size(); i++) {
        while ((int) up.size() >= 2 && ccw(up[up.size() - 2], up[up.size() - 1], pts[i]) >= 0)
            up.pop_back();
        up.push_back(pts[i]);

        while ((int) down.size() >= 2 && ccw(down[down.size() - 2], down[down.size() - 1], pts[i]) <= 0)
            down.pop_back();
        down.push_back(pts[i]);
    }
    pts = down;
    for (int i = up.size() - 2; i > 0; i--)
        pts.push_back(up[i]);
}
