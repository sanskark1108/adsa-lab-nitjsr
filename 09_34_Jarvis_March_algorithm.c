#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Point;

// To find orientation of ordered triplet (p, q, r).
// Returns:
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y)*(r.x - q.x) - (q.x - p.x)*(r.y - q.y);
    if (val == 0) return 0;
    return (val > 0)? 1 : 2;
}

void convexHull(Point points[], int n) {
    if (n < 3) {
        printf("Convex hull not possible\n");
        return;
    }

    int hull[n];   // Indices of hull points
    int hullCount = 0;

    // Find the leftmost point
    int leftmost = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[leftmost].x)
            leftmost = i;

    int p = leftmost, q;
    do {
        hull[hullCount++] = p;

        q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            // If i is more counterclockwise than current q, update q
            if (orientation(points[p], points[i], points[q]) == 2)
                q = i;
        }

        p = q;

    } while (p != leftmost);  // While we don't come back to first point

    printf("Points in Convex Hull:\n");
    for (int i = 0; i < hullCount; i++)
        printf("(%d, %d)\n", points[hull[i]].x, points[hull[i]].y);
}

int main() {
    Point points[] = {{0, 3}, {2, 2}, {1, 1}, {2, 1},
                      {3, 0}, {0, 0}, {3, 3}};
    int n = sizeof(points)/sizeof(points[0]);
    convexHull(points, n);
    return 0;
}
