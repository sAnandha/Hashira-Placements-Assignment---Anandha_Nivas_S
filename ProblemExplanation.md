
# 📘 Polynomial Share Verification – Problem Explanation

This project deals with **verifying secret shares of a polynomial function**. The idea is inspired by **Shamir’s Secret Sharing (SSS)**, where a secret is split into multiple parts (shares), and only a subset of them is needed to reconstruct the original secret.

We are given multiple "shares" in the form of points on a polynomial. Each share contains:

* An **x-coordinate** (the position of the share)
* A **y-coordinate** (the value of the polynomial at that x)

Our job is to verify whether all given shares **belong to the same polynomial** or not.

---

## 🔎 What We Need to Do

1. Take a set of **shares** as input (each share has an x and y).
2. Reconstruct the polynomial using only a minimum number of shares (`k`).
3. Use this reconstructed polynomial to check if the other shares also lie on it.
4. Output whether each share is **VALID** or **INVALID**.

---

## 📌 What It Requires

* **Precision with large numbers**: Shares may be very large integers or decimals (up to 20 digits or more).
* **Base conversions**: Shares may be given in different number systems (binary, octal, hexadecimal, etc.), so conversion to decimal is needed first.
* **Mathematical tools**:

  * **Lagrange Interpolation** → to reconstruct the polynomial.
  * **Determinants or matrices (alternative methods)** → can also be used for polynomial reconstruction.

---

## ⚙️ How We Need to Process

1. **Input Representation**

   * Shares are provided (sometimes in JSON, sometimes as raw data).
   * Each share looks like:

     ```
     (x, y_in_base, base)
     ```

     Example: `(2, "111", 2)` → means at `x = 2`, y is `"111"` in base 2 → decimal value = 7.

2. **Convert All Shares to Decimal**

   * Since bases differ, the first step is to convert all y-values to decimal.

3. **Select Minimum k Shares**

   * To reconstruct a polynomial of degree `k-1`, we only need `k` shares.
   * Example: if k = 3, we can fully reconstruct a quadratic polynomial.

4. **Reconstruct Polynomial**

   * Use **Lagrange Interpolation Formula**:

     * It uniquely defines a polynomial passing through the chosen `k` points.

5. **Verification of All Shares**

   * For each share `(x, y)` given:

     * Compute the expected y-value from the polynomial.
     * Compare with the actual y-value (after base conversion).
     * If they match → share is **VALID**.
     * Otherwise → share is **INVALID**.

---

## 🛠️ Methods to Process

### 1. **Lagrange Interpolation (Preferred)**

* Uses the mathematical formula for polynomial reconstruction.
* Advantage: Direct, works with fractional/decimal results, reliable.
* Complexity: **O(k²)** for reconstruction.

### 2. **Matrix Method (Alternative)**

* Solve a system of equations using determinants (Cramer’s rule) or Gaussian elimination.
* Advantage: More general, useful for exact systems.
* Disadvantage: Heavy for large inputs, less efficient.

### 3. **Direct Verification without Polynomial (Not feasible)**

* Just checking pairwise differences doesn’t guarantee correctness.
* ❌ Doesn’t detect wrong ordering or mismatched curves.

---

## ❓ Why Lagrange Interpolation is Used

* Works directly with floating-point or high-precision numbers.
* Efficient for small k (which is the usual case in secret sharing).
* Naturally fits the "reconstruct from subset of points" requirement.
* Avoids solving large matrix equations, making implementation simpler.

---

## 🔄 The Process in a Nutshell

1. **Input Handling**: Read n shares.
2. **Base Conversion**: Convert all y-values into decimal.
3. **Reconstruction**: Choose first k shares to build the polynomial.
4. **Validation**: For each share, calculate expected y-value → compare with actual.
5. **Output**: Print whether each share is VALID ✅ or INVALID ❌.

---

## 🎯 Output

For each input share:

* If the point lies on the reconstructed polynomial → ✅ **VALID**
* Otherwise → ❌ **INVALID**

Example:

```
Input Shares:
(1, 4) 
(2, "111" in base 2 → 7) 
(3, 12) 
(6, "213" in base 4 → 39)

Output:
Share (1, 4) ✅ VALID
Share (2, 7) ✅ VALID
Share (3, 12) ✅ VALID
Share (6, 39) ✅ VALID
```

