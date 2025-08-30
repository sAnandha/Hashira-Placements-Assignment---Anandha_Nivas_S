
# 📘 Hashira Placements Assignment – Polynomial Verification

## 🔎 Code Walkthrough

### 1. `#include <bits/stdc++.h>`

Includes all standard C++ headers at once (`<iostream>`, `<vector>`, `<string>`, `<cmath>`, etc.).
Works with GCC/MinGW (used in Dev-C++).

---

### 2. Convert Base → Decimal

```cpp
long long convertToDecimal(const string &val, int base) {
    long long num = 0;
    for (char c : val) {
        int digit;
        if (isdigit(c)) digit = c - '0';
        else digit = tolower(c) - 'a' + 10; // for bases > 10 (hex, base-15, etc.)
        num = num * base + digit;
    }
    return num;
}
```

* Converts a number (stored as string) from any given base into decimal.
* Examples:

  * `"111"` in base 2 → **7**
  * `"213"` in base 4 → **39**
  * `"e1b5..."` in base 16 → big decimal number

---

### 3. Lagrange Interpolation

```cpp
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
```

Implements the **Lagrange Polynomial Formula**:

$$
P(x) = \sum_{i=0}^{k-1} y_i \prod_{j=0, j\neq i}^{k-1} \frac{x - x_j}{x_i - x_j}
$$

* **Input**: k base points `(x, y)`
* **Output**: Predicted y-value at `x`

This reconstructs the hidden polynomial.

---

### 4. Test Case 1 (Small Example)

```cpp
points.push_back({1, convertToDecimal("4", 10)});   // (1,4)
points.push_back({2, convertToDecimal("111", 2)}); // (2,7)
points.push_back({3, convertToDecimal("12", 10)}); // (3,12)
points.push_back({6, convertToDecimal("213", 4)}); // (6,39)
```

* Takes **k = 3** points to build the polynomial.
* Verifies the 4th point `(6, 39)` against it.
* ✅ All shares are valid.

---

### 5. Test Case 2 (Big Numbers)

```cpp
points.push_back({1, convertToDecimal("13444211440455345511", 6)});
points.push_back({2, convertToDecimal("aed7015a346d635", 15)});
points.push_back({3, convertToDecimal("6aeeb69631c227c", 15)});
...
points.push_back({10, convertToDecimal("1101613130313526312514143", 7)});
```

* Converts each `"value"` from its `"base"`.
* Builds polynomial from first **k = 7** points.
* Verifies all **n = 10** shares.

---

### 6. Verification Loop

```cpp
for (auto &p : points) {
    long double expected = lagrange(basePoints, p.first);
    if (fabsl(expected - p.second) < 1e-6) {
        cout << "Share (" << p.first << ", " << p.second << ") ✅ VALID\n";
    } else {
        cout << "Share (" << p.first << ", " << p.second << ") ❌ INVALID\n";
    }
}
```

* For each `(x, y)` share:

  * Compute expected `y` from reconstructed polynomial.
  * Compare with actual `y`.
* ✅ **If matches → VALID**
* ❌ **Else → INVALID**

---

## ⚡ What This Code Solves

✔ Reads **shares** (manually filled, not JSON-parsed here)
✔ Converts `"value"` in any base to **decimal**
✔ Reconstructs polynomial from **first k points**
✔ Verifies all given **n points**

---

