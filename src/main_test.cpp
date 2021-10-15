// C++ program to implement Quick Hull algorithm
// to find convex hull.
#include<bits/stdc++.h>
using namespace std;

// iPair is integer pairs
#define iPair pair<int, int>

// Stores the result (points of convex hull)
set<iPair> hull;



// End points of line L are p1 and p2. side can have value
// 1 or -1 specifying each of the parts made by the line L
void quickHull(iPair a[], int n, iPair p1, iPair p2, int side)
{

	p1 = 
	{
		hull.insert(p1);
		hull.insert(p2);
		cout << "p1 = " << p1.first << ", " << p1.second << endl;
		cout << "p2 = " << p2.first << ", " << p2.second << endl;
		return;
	}

	// Recur for the two parts divided by a[ind]
	quickHull(a, n, a[ind], p1, -findSide(a[ind], p1, p2));
	quickHull(a, n, a[ind], p2, -findSide(a[ind], p2, p1));
}

void printHull(iPair a[], int n)
{
	// a[i].second -> y-coordinate of the ith point
	if (n < 3)
	{
		cout << "Convex hull not possible\n";
		return;
	}

	// Finding the point with minimum and
	// maximum x-coordinate
	int min_x = 0, max_x = 0;
	for (int i=1; i<n; i++)
	{
		if (a[i].first < a[min_x].first)
			min_x = i;
		if (a[i].first > a[max_x].first)
			max_x = i;
	}

	// Recursively find convex hull points on
	// one side of line joining a[min_x] and
	// a[max_x]
	quickHull(a, n, a[min_x], a[max_x], 1);

	// Recursively find convex hull points on
	// other side of line joining a[min_x] and
	// a[max_x]
	quickHull(a, n, a[min_x], a[max_x], -1);

	cout << "The points in Convex Hull are:\n";
	while (!hull.empty())
	{
		cout << "(" <<( *hull.begin()).first << ", "
			<< (*hull.begin()).second << ") ";
		hull.erase(hull.begin());
	}
}

// Driver code
int main()
{
	// iPair a[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
	// 		{0, 0}, {1, 2}, {3, 1}, {3, 3}};
	iPair a[] = {{0, 0}, {0, 2}, {2, 2}, {2, 0},
			{1, 1}, {-1, -1}};

	int n = sizeof(a)/sizeof(a[0]);
	printHull(a, n);
	return 0;
}
