#include <stdio.h>
#include <stdlib.h>

typedef struct Point {
    int x, y;
} Point;

Point p0;

// Swap utility
void swap(Point *a, Point *b) {
    Point t = *a;
    *a = *b;
    *b = t;
}

// Orientation of three points
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y)*(r.x - q.x) - (q.x - p.x)*(r.y - q.y);
    if (val == 0) return 0; // colinear
    return (val > 0)? 1: 2; // clock or counterclockwise
}

// Distance squared
int distSq(Point p1, Point p2) {
    return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

// Comparison function for sorting
int cmp(const void *vp1, const void *vp2) {
    Point *p1 = (Point*)vp1;
    Point *p2 = (Point*)vp2;
    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;
    return (o == 2)? -1 : 1;
}

// Graham scan main
void convexHull(Point points[], int n) {
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++) {
        if ((points[i].y < ymin) || (points[i].y == ymin && points[i].x < points[min].x))
            ymin = points[i].y, min = i;
    }
    swap(&points[0], &points[min]);
    p0 = points[0];

    qsort(&points[1], n-1, sizeof(Point), cmp);

    Point stack[n];
    int top = -1;
    stack[++top] = points[0];
    stack[++top] = points[1];
    stack[++top] = points[2];

    for (int i = 3; i < n; i++) {
        while (top >= 1 && orientation(stack[top-1], stack[top], points[i]) != 2)
            top--;
        stack[++top] = points[i];
    }

    printf("Convex Hull points:\n");
    for (int i = 0; i <= top; i++)
        printf("(%d, %d)\n", stack[i].x, stack[i].y);
}

int main() {
    int n;
    printf("Enter number of points: ");
    scanf("%d", &n);
    Point points[n];
    printf("Enter points (x y):\n");
    for (int i = 0; i < n; i++)
        scanf("%d %d", &points[i].x, &points[i].y);

    convexHull(points, n);
    return 0;
}
