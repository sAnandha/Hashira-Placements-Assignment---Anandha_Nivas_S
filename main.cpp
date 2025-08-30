#include <bits/stdc++.h>
using namespace std;

// Convert string number from given base to decimal
long long convertToDecimal(const string &val, int base) {
    long long num = 0;
    for (char c : val) {
        int digit;
        if (isdigit(c)) digit = c - '0';
        else digit = tolower(c) - 'a' + 10; // handle hex/base>10
        num = num * base + digit;
    }
    return num;
}

// Lagrange interpolation function
long double lagrange(const vector<pair<long double,long double>>& pts, long double x) {
    int k = pts.size();
    long double result = 0.0;
    for (int i = 0; i < k; i++) {
        long double term = pts[i].second;
        for (int j = 0; j < k; j++) {
            if (i != j) {
                term *= (x - pts[j].first) / (pts[i].first - pts[j].first);
            }
        }
        result += term;
    }
    return result;
}

int main() {
    // -------- Test Case 1 --------
    cout << "Test Case 1" << endl;
    int n = 4, k = 3;

    // Manually parsed JSON points
    vector<pair<long double,long double>> points;
    points.push_back({1, convertToDecimal("4", 10)});     // (1,4)
    points.push_back({2, convertToDecimal("111", 2)});   // (2,7)
    points.push_back({3, convertToDecimal("12", 10)});   // (3,12)
    points.push_back({6, convertToDecimal("213", 4)});   // (6,39)

    // Build polynomial from first k points
    vector<pair<long double,long double>> basePoints(points.begin(), points.begin()+k);

    // Verify all shares
    for (auto &p : points) {
        long double expected = lagrange(basePoints, p.first);
        if (fabsl(expected - p.second) < 1e-6) {
            cout << "Share (" << p.first << ", " << p.second << ") ✅ VALID" << endl;
        } else {
            cout << "Share (" << p.first << ", " << p.second << ") ❌ INVALID" << endl;
        }
    }

    cout << "\n";

    // -------- Test Case 2 --------
    cout << "Test Case 2" << endl;
    n = 10; k = 7;
    points.clear();

    points.push_back({1, convertToDecimal("13444211440455345511", 6)});
    points.push_back({2, convertToDecimal("aed7015a346d635", 15)});
    points.push_back({3, convertToDecimal("6aeeb69631c227c", 15)});
    points.push_back({4, convertToDecimal("e1b5e05623d881f", 16)});
    points.push_back({5, convertToDecimal("316034514573652620673", 8)});
    points.push_back({6, convertToDecimal("2122212201122002221120200210011020220200", 3)});
    points.push_back({7, convertToDecimal("20120221122211000100210021102001201112121", 3)});
    points.push_back({8, convertToDecimal("20220554335330240002224253", 6)});
    points.push_back({9, convertToDecimal("45153788322a1255483", 12)});
    points.push_back({10, convertToDecimal("1101613130313526312514143", 7)});

    basePoints.assign(points.begin(), points.begin()+k);

    // Verify all shares
    for (auto &p : points) {
        long double expected = lagrange(basePoints, p.first);
        if (fabsl(expected - p.second) < 1e-6) {
            cout << "Share (" << p.first << ", " << fixed << setprecision(0) << p.second << ") ✅ VALID" << endl;
        } else {
            cout << "Share (" << p.first << ", " << fixed << setprecision(0) << p.second << ") ❌ INVALID" << endl;
        }
    }

    return 0;
}
