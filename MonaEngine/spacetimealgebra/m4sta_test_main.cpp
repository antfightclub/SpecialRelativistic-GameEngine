#include <time.h> /* used to seed random generator */
#include "m4sta.h"
namespace m4sta {
// Missing dependencies declarations:

/**
Generates a random versor.
The scale is uniformly distributed over the interval [0 1).
The maximum non-zero grade-part is 'grade'.
Only the basis vectors marked in 'basisVectorBitmap' will be used to generate the
versor/blade. Use 'basisVectorBitmap = -1' (the default) to use all basisvectors.

Returns random_versor_dont_mangle_1_returns_mv_ex(arg1, scale, grade, basisVectorBitmap, 0.01, scale * 4.0);
*/
mv random_versor_dont_mangle_1_returns_mv(double scale, int grade, int basisVectorBitmap = -1);

/**
This version of random_versor_dont_mangle_1_returns_mv() has extra arguments which help to avoid 
near-singular blades / versors.

Near-singular blades / versors are avoid by testing the norm and largest coordinate
of the random blade / versor. If the test does not pass, the function recursively
tries to generate another random blade / versor.

'minimumNorm' is the minimum allowed norm of the blade/versor before scaling. 
'minimumNorm' must be > 0.0 for versors.

'largestCoordinate' is the largest coordinate allowed after scaling.
*/
mv random_versor_dont_mangle_1_returns_mv_ex(double scale, int grade, int basisVectorBitmap, double minimumNorm, double largestCoordinate);


/**
Generates a random blade.
The scale is uniformly distributed over the interval [0 1).
The maximum non-zero grade-part is 'grade'.
Only the basis vectors marked in 'basisVectorBitmap' will be used to generate the
versor/blade. Use 'basisVectorBitmap = -1' (the default) to use all basisvectors.

Returns random_blade_dont_mangle_3_returns_mv_ex(arg1, scale, grade, basisVectorBitmap, 0.01, scale * 4.0);
*/
mv random_blade_dont_mangle_3_returns_mv(double scale, int grade, int basisVectorBitmap = -1);

/**
This version of random_blade_dont_mangle_3_returns_mv() has extra arguments which help to avoid 
near-singular blades / versors.

Near-singular blades / versors are avoid by testing the norm and largest coordinate
of the random blade / versor. If the test does not pass, the function recursively
tries to generate another random blade / versor.

'minimumNorm' is the minimum allowed norm of the blade/versor before scaling. 
'minimumNorm' must be > 0.0 for versors.

'largestCoordinate' is the largest coordinate allowed after scaling.
*/
mv random_blade_dont_mangle_3_returns_mv_ex(double scale, int grade, int basisVectorBitmap, double minimumNorm, double largestCoordinate);

/// Returns geometric product of mv and mv.
mv gp_dont_mangle_39_returns_mv(const mv &a, const mv &b);
// Missing dependencies inline definitions:
// Missing dependencies definitions:
/// Computes the partial geometric product of two multivectors (group 0  x  group 0 -> group 0)
void gp_default_0_0_0(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 0  x  group 1 -> group 1)
void gp_default_0_1_1(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 0  x  group 2 -> group 2)
void gp_default_0_2_2(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 0  x  group 3 -> group 3)
void gp_default_0_3_3(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 0  x  group 4 -> group 4)
void gp_default_0_4_4(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 1  x  group 0 -> group 1)
void gp_default_1_0_1(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 1  x  group 1 -> group 0)
void gp_default_1_1_0(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 1  x  group 1 -> group 2)
void gp_default_1_1_2(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 1  x  group 2 -> group 1)
void gp_default_1_2_1(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 1  x  group 2 -> group 3)
void gp_default_1_2_3(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 1  x  group 3 -> group 2)
void gp_default_1_3_2(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 1  x  group 3 -> group 4)
void gp_default_1_3_4(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 1  x  group 4 -> group 3)
void gp_default_1_4_3(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 2  x  group 0 -> group 2)
void gp_default_2_0_2(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 2  x  group 1 -> group 1)
void gp_default_2_1_1(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 2  x  group 1 -> group 3)
void gp_default_2_1_3(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 2  x  group 2 -> group 0)
void gp_default_2_2_0(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 2  x  group 2 -> group 2)
void gp_default_2_2_2(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 2  x  group 2 -> group 4)
void gp_default_2_2_4(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 2  x  group 3 -> group 1)
void gp_default_2_3_1(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 2  x  group 3 -> group 3)
void gp_default_2_3_3(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 2  x  group 4 -> group 2)
void gp_default_2_4_2(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 3  x  group 0 -> group 3)
void gp_default_3_0_3(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 3  x  group 1 -> group 2)
void gp_default_3_1_2(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 3  x  group 1 -> group 4)
void gp_default_3_1_4(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 3  x  group 2 -> group 1)
void gp_default_3_2_1(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 3  x  group 2 -> group 3)
void gp_default_3_2_3(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 3  x  group 3 -> group 0)
void gp_default_3_3_0(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 3  x  group 3 -> group 2)
void gp_default_3_3_2(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 3  x  group 4 -> group 1)
void gp_default_3_4_1(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 4  x  group 0 -> group 4)
void gp_default_4_0_4(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 4  x  group 1 -> group 3)
void gp_default_4_1_3(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 4  x  group 2 -> group 2)
void gp_default_4_2_2(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 4  x  group 3 -> group 1)
void gp_default_4_3_1(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 4  x  group 4 -> group 0)
void gp_default_4_4_0(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 0  x  group 0 -> group 0)
void gp__internal_euclidean_metric__0_0_0(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 0  x  group 1 -> group 1)
void gp__internal_euclidean_metric__0_1_1(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 0  x  group 2 -> group 2)
void gp__internal_euclidean_metric__0_2_2(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 0  x  group 3 -> group 3)
void gp__internal_euclidean_metric__0_3_3(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 0  x  group 4 -> group 4)
void gp__internal_euclidean_metric__0_4_4(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 1  x  group 0 -> group 1)
void gp__internal_euclidean_metric__1_0_1(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 1  x  group 1 -> group 0)
void gp__internal_euclidean_metric__1_1_0(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 1  x  group 1 -> group 2)
void gp__internal_euclidean_metric__1_1_2(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 1  x  group 2 -> group 1)
void gp__internal_euclidean_metric__1_2_1(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 1  x  group 2 -> group 3)
void gp__internal_euclidean_metric__1_2_3(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 1  x  group 3 -> group 2)
void gp__internal_euclidean_metric__1_3_2(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 1  x  group 3 -> group 4)
void gp__internal_euclidean_metric__1_3_4(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 1  x  group 4 -> group 3)
void gp__internal_euclidean_metric__1_4_3(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 2  x  group 0 -> group 2)
void gp__internal_euclidean_metric__2_0_2(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 2  x  group 1 -> group 1)
void gp__internal_euclidean_metric__2_1_1(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 2  x  group 1 -> group 3)
void gp__internal_euclidean_metric__2_1_3(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 2  x  group 2 -> group 0)
void gp__internal_euclidean_metric__2_2_0(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 2  x  group 2 -> group 2)
void gp__internal_euclidean_metric__2_2_2(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 2  x  group 2 -> group 4)
void gp__internal_euclidean_metric__2_2_4(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 2  x  group 3 -> group 1)
void gp__internal_euclidean_metric__2_3_1(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 2  x  group 3 -> group 3)
void gp__internal_euclidean_metric__2_3_3(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 2  x  group 4 -> group 2)
void gp__internal_euclidean_metric__2_4_2(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 3  x  group 0 -> group 3)
void gp__internal_euclidean_metric__3_0_3(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 3  x  group 1 -> group 2)
void gp__internal_euclidean_metric__3_1_2(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 3  x  group 1 -> group 4)
void gp__internal_euclidean_metric__3_1_4(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 3  x  group 2 -> group 1)
void gp__internal_euclidean_metric__3_2_1(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 3  x  group 2 -> group 3)
void gp__internal_euclidean_metric__3_2_3(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 3  x  group 3 -> group 0)
void gp__internal_euclidean_metric__3_3_0(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 3  x  group 3 -> group 2)
void gp__internal_euclidean_metric__3_3_2(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 3  x  group 4 -> group 1)
void gp__internal_euclidean_metric__3_4_1(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 4  x  group 0 -> group 4)
void gp__internal_euclidean_metric__4_0_4(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 4  x  group 1 -> group 3)
void gp__internal_euclidean_metric__4_1_3(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 4  x  group 2 -> group 2)
void gp__internal_euclidean_metric__4_2_2(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 4  x  group 3 -> group 1)
void gp__internal_euclidean_metric__4_3_1(const double *A, const double *B, double *C);
/// Computes the partial geometric product of two multivectors (group 4  x  group 4 -> group 0)
void gp__internal_euclidean_metric__4_4_0(const double *A, const double *B, double *C);
/// copies coordinates of group 0
void copyGroup_0(const double *A, double *C);
/// copies and multiplies (by s) coordinates of group 0
void copyMul_0(const double *A, double *C, double s);
/// copies and divides (by s) coordinates of group 0
void copyDiv_0(const double *A, double *C, double s);
/// adds coordinates of group 0 from variable A to C
void add_0(const double *A, double *C);
/// subtracts coordinates of group 0 in variable A from C
void sub_0(const double *A, double *C);
/// negate coordinates of group 0 of variable A
void neg_0(const double *A, double *C);
/// adds coordinates of group 0 of variables A and B
void add2_0_0(const double *A, const double *B, double *C);
/// subtracts coordinates of group 0 of variables A from B
void sub2_0_0(const double *A, const double *B, double *C);
/// performs coordinate-wise multiplication of coordinates of group 0 of variables A and B
void hp_0_0(const double *A, const double *B, double *C);
/// performs coordinate-wise division of coordinates of group 0 of variables A and B
/// (no checks for divide by zero are made)
void ihp_0_0(const double *A, const double *B, double *C);
/// check for equality up to eps of coordinates of group 0 of variables A and B
bool equals_0_0(const double *A, const double *B, double eps);
/// checks if coordinates of group 0 of variable A are zero up to eps
bool zeroGroup_0(const double *A, double eps);
/// copies coordinates of group 1
void copyGroup_1(const double *A, double *C);
/// copies and multiplies (by s) coordinates of group 1
void copyMul_1(const double *A, double *C, double s);
/// copies and divides (by s) coordinates of group 1
void copyDiv_1(const double *A, double *C, double s);
/// adds coordinates of group 1 from variable A to C
void add_1(const double *A, double *C);
/// subtracts coordinates of group 1 in variable A from C
void sub_1(const double *A, double *C);
/// negate coordinates of group 1 of variable A
void neg_1(const double *A, double *C);
/// adds coordinates of group 1 of variables A and B
void add2_1_1(const double *A, const double *B, double *C);
/// subtracts coordinates of group 1 of variables A from B
void sub2_1_1(const double *A, const double *B, double *C);
/// performs coordinate-wise multiplication of coordinates of group 1 of variables A and B
void hp_1_1(const double *A, const double *B, double *C);
/// performs coordinate-wise division of coordinates of group 1 of variables A and B
/// (no checks for divide by zero are made)
void ihp_1_1(const double *A, const double *B, double *C);
/// check for equality up to eps of coordinates of group 1 of variables A and B
bool equals_1_1(const double *A, const double *B, double eps);
/// checks if coordinates of group 1 of variable A are zero up to eps
bool zeroGroup_1(const double *A, double eps);
/// copies coordinates of group 2
void copyGroup_2(const double *A, double *C);
/// copies and multiplies (by s) coordinates of group 2
void copyMul_2(const double *A, double *C, double s);
/// copies and divides (by s) coordinates of group 2
void copyDiv_2(const double *A, double *C, double s);
/// adds coordinates of group 2 from variable A to C
void add_2(const double *A, double *C);
/// subtracts coordinates of group 2 in variable A from C
void sub_2(const double *A, double *C);
/// negate coordinates of group 2 of variable A
void neg_2(const double *A, double *C);
/// adds coordinates of group 2 of variables A and B
void add2_2_2(const double *A, const double *B, double *C);
/// subtracts coordinates of group 2 of variables A from B
void sub2_2_2(const double *A, const double *B, double *C);
/// performs coordinate-wise multiplication of coordinates of group 2 of variables A and B
void hp_2_2(const double *A, const double *B, double *C);
/// performs coordinate-wise division of coordinates of group 2 of variables A and B
/// (no checks for divide by zero are made)
void ihp_2_2(const double *A, const double *B, double *C);
/// check for equality up to eps of coordinates of group 2 of variables A and B
bool equals_2_2(const double *A, const double *B, double eps);
/// checks if coordinates of group 2 of variable A are zero up to eps
bool zeroGroup_2(const double *A, double eps);
/// copies coordinates of group 3
void copyGroup_3(const double *A, double *C);
/// copies and multiplies (by s) coordinates of group 3
void copyMul_3(const double *A, double *C, double s);
/// copies and divides (by s) coordinates of group 3
void copyDiv_3(const double *A, double *C, double s);
/// adds coordinates of group 3 from variable A to C
void add_3(const double *A, double *C);
/// subtracts coordinates of group 3 in variable A from C
void sub_3(const double *A, double *C);
/// negate coordinates of group 3 of variable A
void neg_3(const double *A, double *C);
/// adds coordinates of group 3 of variables A and B
void add2_3_3(const double *A, const double *B, double *C);
/// subtracts coordinates of group 3 of variables A from B
void sub2_3_3(const double *A, const double *B, double *C);
/// performs coordinate-wise multiplication of coordinates of group 3 of variables A and B
void hp_3_3(const double *A, const double *B, double *C);
/// performs coordinate-wise division of coordinates of group 3 of variables A and B
/// (no checks for divide by zero are made)
void ihp_3_3(const double *A, const double *B, double *C);
/// check for equality up to eps of coordinates of group 3 of variables A and B
bool equals_3_3(const double *A, const double *B, double eps);
/// checks if coordinates of group 3 of variable A are zero up to eps
bool zeroGroup_3(const double *A, double eps);
/// copies coordinates of group 4
void copyGroup_4(const double *A, double *C);
/// copies and multiplies (by s) coordinates of group 4
void copyMul_4(const double *A, double *C, double s);
/// copies and divides (by s) coordinates of group 4
void copyDiv_4(const double *A, double *C, double s);
/// adds coordinates of group 4 from variable A to C
void add_4(const double *A, double *C);
/// subtracts coordinates of group 4 in variable A from C
void sub_4(const double *A, double *C);
/// negate coordinates of group 4 of variable A
void neg_4(const double *A, double *C);
/// adds coordinates of group 4 of variables A and B
void add2_4_4(const double *A, const double *B, double *C);
/// subtracts coordinates of group 4 of variables A from B
void sub2_4_4(const double *A, const double *B, double *C);
/// performs coordinate-wise multiplication of coordinates of group 4 of variables A and B
void hp_4_4(const double *A, const double *B, double *C);
/// performs coordinate-wise division of coordinates of group 4 of variables A and B
/// (no checks for divide by zero are made)
void ihp_4_4(const double *A, const double *B, double *C);
/// check for equality up to eps of coordinates of group 4 of variables A and B
bool equals_4_4(const double *A, const double *B, double eps);
/// checks if coordinates of group 4 of variable A are zero up to eps
bool zeroGroup_4(const double *A, double eps);
/// Computes the partial dual (w.r.t. full space) of a multivector.
void dual_default_0_4(const double *A, double *C);
/// Computes the partial undual (w.r.t. full space) of a multivector.
void undual_default_0_4(const double *A, double *C);
/// Computes the partial dual (w.r.t. full space) of a multivector.
void dual_default_1_3(const double *A, double *C);
/// Computes the partial undual (w.r.t. full space) of a multivector.
void undual_default_1_3(const double *A, double *C);
/// Computes the partial dual (w.r.t. full space) of a multivector.
void dual_default_2_2(const double *A, double *C);
/// Computes the partial undual (w.r.t. full space) of a multivector.
void undual_default_2_2(const double *A, double *C);
/// Computes the partial dual (w.r.t. full space) of a multivector.
void dual_default_3_1(const double *A, double *C);
/// Computes the partial undual (w.r.t. full space) of a multivector.
void undual_default_3_1(const double *A, double *C);
/// Computes the partial dual (w.r.t. full space) of a multivector.
void dual_default_4_0(const double *A, double *C);
/// Computes the partial undual (w.r.t. full space) of a multivector.
void undual_default_4_0(const double *A, double *C);
/// Computes the partial dual (w.r.t. full space) of a multivector.
void dual__internal_euclidean_metric__0_4(const double *A, double *C);
/// Computes the partial undual (w.r.t. full space) of a multivector.
void undual__internal_euclidean_metric__0_4(const double *A, double *C);
/// Computes the partial dual (w.r.t. full space) of a multivector.
void dual__internal_euclidean_metric__1_3(const double *A, double *C);
/// Computes the partial undual (w.r.t. full space) of a multivector.
void undual__internal_euclidean_metric__1_3(const double *A, double *C);
/// Computes the partial dual (w.r.t. full space) of a multivector.
void dual__internal_euclidean_metric__2_2(const double *A, double *C);
/// Computes the partial undual (w.r.t. full space) of a multivector.
void undual__internal_euclidean_metric__2_2(const double *A, double *C);
/// Computes the partial dual (w.r.t. full space) of a multivector.
void dual__internal_euclidean_metric__3_1(const double *A, double *C);
/// Computes the partial undual (w.r.t. full space) of a multivector.
void undual__internal_euclidean_metric__3_1(const double *A, double *C);
/// Computes the partial dual (w.r.t. full space) of a multivector.
void dual__internal_euclidean_metric__4_0(const double *A, double *C);
/// Computes the partial undual (w.r.t. full space) of a multivector.
void undual__internal_euclidean_metric__4_0(const double *A, double *C);
/// Computes the partial application of a general outermorphism to a general multivector
void applyGomGmv_1_1(const om &O, const double *A, double *C);
/// Computes the partial application of a general outermorphism to a general multivector
void applyGomGmv_2_2(const om &O, const double *A, double *C);
/// Computes the partial application of a general outermorphism to a general multivector
void applyGomGmv_3_3(const om &O, const double *A, double *C);
/// Computes the partial application of a general outermorphism to a general multivector
void applyGomGmv_4_4(const om &O, const double *A, double *C);


mv random_versor_dont_mangle_1_returns_mv(double scale, int grade, int basisVectorBitmap) {
	double minimumNorm = 0,01.0;
	double largestCoordinate = 4.0;
	return random_versor_dont_mangle_1_returns_mv_ex(scale, grade, basisVectorBitmap, minimumNorm, scale * largestCoordinate);
}

mv random_versor_dont_mangle_1_returns_mv_ex(double scale, int _grade, int basisVectorBitmap, 
		double minimumNorm, double largestCoordinate) 
{
	mv randomVector, tmp1, tmp2;
	mv *IR1 = &tmp1, *IR2 = &tmp2; // IR = intermediate result
	double randomValues[4];
	double n2, mul;
	int i;
	int grade = _grade;
	
	// set IR1 (intermediate result) to 1
	IR1->set(1.0);

	while (grade > 0) {	// loop until grade == 0
		// fill array with random values
		for (i = 0; i < 4; i++) 
			randomValues[i] = (basisVectorBitmap & (1 << i))
				? (-1.0 + 2.0 * genrand())
				: 0.0;
		
		// make it a multivector:
		randomVector.set(GRADE_1, randomValues);
		
		// multiply 
		(*IR2) = gp(*IR1, randomVector);
		
		// swap IR pointers: 
		std::swap(IR1, IR2);
		
		// lower grade
		grade--;
	}
	
	// compute norm/multiplier, apply it, or recurse if we happened to create a near-null versor
	n2 = norm_returns_scalar(*IR1);
	if ((double)fabs(n2) > minimumNorm * minimumNorm) {
		if (n2 != 0.0) {
			mul = scale * genrand() / n2;
			if (IR1->largestCoordinate() * mul < largestCoordinate)
				return gp_dont_mangle_1(*IR1, mul);
		}
		else if (IR1->largestCoordinate() < largestCoordinate)
			return *IR1;
	}
	
	// try again:
	return random_versor_dont_mangle_1_returns_mv_ex(scale, _grade, basisVectorBitmap, minimumNorm, largestCoordinate); 
}


mv random_blade_dont_mangle_3_returns_mv(double scale, int grade, int basisVectorBitmap) {
	double minimumNorm = 0,01.0;
	double largestCoordinate = 4.0;
	return random_blade_dont_mangle_3_returns_mv_ex(scale, grade, basisVectorBitmap, minimumNorm, scale * largestCoordinate);
}

mv random_blade_dont_mangle_3_returns_mv_ex(double scale, int _grade, int basisVectorBitmap, 
		double minimumNorm, double largestCoordinate) 
{
	mv randomVector, tmp1, tmp2;
	mv *IR1 = &tmp1, *IR2 = &tmp2; // IR = intermediate result
	double randomValues[4];
	double n2, mul;
	int i;
	int grade = _grade;
	
	// set IR1 (intermediate result) to 1
	IR1->set(1.0);

	while (grade > 0) {	// loop until grade == 0
		// fill array with random values
		for (i = 0; i < 4; i++) 
			randomValues[i] = (basisVectorBitmap & (1 << i))
				? (-1.0 + 2.0 * genrand())
				: 0.0;
		
		// make it a multivector:
		randomVector.set(GRADE_1, randomValues);
		
		// multiply 
		(*IR2) = op(*IR1, randomVector);
		
		// swap IR pointers: 
		std::swap(IR1, IR2);
		
		// lower grade
		grade--;
	}
	
	// compute norm/multiplier, apply it, or recurse if we happened to create a near-null versor
	n2 = norm_returns_scalar(*IR1);
	if ((double)fabs(n2) > minimumNorm * minimumNorm) {
		if (n2 != 0.0) {
			mul = scale * genrand() / n2;
			if (IR1->largestCoordinate() * mul < largestCoordinate)
				return gp_dont_mangle_1(*IR1, mul);
		}
		else if (IR1->largestCoordinate() < largestCoordinate)
			return *IR1;
	}
	
	// try again:
	return random_blade_dont_mangle_3_returns_mv_ex(scale, _grade, basisVectorBitmap, minimumNorm, largestCoordinate); 
}
mv gp_dont_mangle_39_returns_mv(const mv &a, const mv &b)
{
	double c[16];
	const double* _a[5];
	const double* _b[5];
	a.expand(_a);
	b.expand(_b);
	m4sta::zero_16(c);
	if (a.gu() & 1) {
		if (b.gu() & 1) {
			gp__internal_euclidean_metric__0_0_0(_a[0], _b[0], c + 0);
		}
		if (b.gu() & 2) {
			gp__internal_euclidean_metric__0_1_1(_a[0], _b[1], c + 1);
		}
		if (b.gu() & 4) {
			gp__internal_euclidean_metric__0_2_2(_a[0], _b[2], c + 5);
		}
		if (b.gu() & 8) {
			gp__internal_euclidean_metric__0_3_3(_a[0], _b[3], c + 11);
		}
		if (b.gu() & 16) {
			gp__internal_euclidean_metric__0_4_4(_a[0], _b[4], c + 15);
		}
	}
	if (a.gu() & 2) {
		if (b.gu() & 1) {
			gp__internal_euclidean_metric__1_0_1(_a[1], _b[0], c + 1);
		}
		if (b.gu() & 2) {
			gp__internal_euclidean_metric__1_1_0(_a[1], _b[1], c + 0);
			gp__internal_euclidean_metric__1_1_2(_a[1], _b[1], c + 5);
		}
		if (b.gu() & 4) {
			gp__internal_euclidean_metric__1_2_1(_a[1], _b[2], c + 1);
			gp__internal_euclidean_metric__1_2_3(_a[1], _b[2], c + 11);
		}
		if (b.gu() & 8) {
			gp__internal_euclidean_metric__1_3_2(_a[1], _b[3], c + 5);
			gp__internal_euclidean_metric__1_3_4(_a[1], _b[3], c + 15);
		}
		if (b.gu() & 16) {
			gp__internal_euclidean_metric__1_4_3(_a[1], _b[4], c + 11);
		}
	}
	if (a.gu() & 4) {
		if (b.gu() & 1) {
			gp__internal_euclidean_metric__2_0_2(_a[2], _b[0], c + 5);
		}
		if (b.gu() & 2) {
			gp__internal_euclidean_metric__2_1_1(_a[2], _b[1], c + 1);
			gp__internal_euclidean_metric__2_1_3(_a[2], _b[1], c + 11);
		}
		if (b.gu() & 4) {
			gp__internal_euclidean_metric__2_2_0(_a[2], _b[2], c + 0);
			gp__internal_euclidean_metric__2_2_2(_a[2], _b[2], c + 5);
			gp__internal_euclidean_metric__2_2_4(_a[2], _b[2], c + 15);
		}
		if (b.gu() & 8) {
			gp__internal_euclidean_metric__2_3_1(_a[2], _b[3], c + 1);
			gp__internal_euclidean_metric__2_3_3(_a[2], _b[3], c + 11);
		}
		if (b.gu() & 16) {
			gp__internal_euclidean_metric__2_4_2(_a[2], _b[4], c + 5);
		}
	}
	if (a.gu() & 8) {
		if (b.gu() & 1) {
			gp__internal_euclidean_metric__3_0_3(_a[3], _b[0], c + 11);
		}
		if (b.gu() & 2) {
			gp__internal_euclidean_metric__3_1_2(_a[3], _b[1], c + 5);
			gp__internal_euclidean_metric__3_1_4(_a[3], _b[1], c + 15);
		}
		if (b.gu() & 4) {
			gp__internal_euclidean_metric__3_2_1(_a[3], _b[2], c + 1);
			gp__internal_euclidean_metric__3_2_3(_a[3], _b[2], c + 11);
		}
		if (b.gu() & 8) {
			gp__internal_euclidean_metric__3_3_0(_a[3], _b[3], c + 0);
			gp__internal_euclidean_metric__3_3_2(_a[3], _b[3], c + 5);
		}
		if (b.gu() & 16) {
			gp__internal_euclidean_metric__3_4_1(_a[3], _b[4], c + 1);
		}
	}
	if (a.gu() & 16) {
		if (b.gu() & 1) {
			gp__internal_euclidean_metric__4_0_4(_a[4], _b[0], c + 15);
		}
		if (b.gu() & 2) {
			gp__internal_euclidean_metric__4_1_3(_a[4], _b[1], c + 11);
		}
		if (b.gu() & 4) {
			gp__internal_euclidean_metric__4_2_2(_a[4], _b[2], c + 5);
		}
		if (b.gu() & 8) {
			gp__internal_euclidean_metric__4_3_1(_a[4], _b[3], c + 1);
		}
		if (b.gu() & 16) {
			gp__internal_euclidean_metric__4_4_0(_a[4], _b[4], c + 0);
		}
	}
	return mv_compress(c, 0.0, 31);
}
// Testing code declarations:
// Testing code inline definitions:
// Testing code definitions:

int test_metric_default_mv(int NB_TESTS_SCALER) 
{
	int i, j;
	double arr[4], dif;
	mv A, bv[4];
	double M[16+1] = {
		1.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0	}; // metric matrix

	// get all basis vectors

	m4sta::zero_4(arr);
	arr[0] = 1.0;
	bv[0].set(2, arr);

	m4sta::zero_4(arr);
	arr[1] = 1.0;
	bv[1].set(2, arr);

	m4sta::zero_4(arr);
	arr[2] = 1.0;
	bv[2].set(2, arr);

	m4sta::zero_4(arr);
	arr[3] = 1.0;
	bv[3].set(2, arr);

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			A = gp(bv[i], bv[j]);
			dif = M[i * 4 + j] - A.get_scalar();
			if ((dif < -1E-14) || (dif > 1E-14)) {
				printf("test_metric_default_mv() test failed for %s %s\n", m4sta_basisVectorNames[i], m4sta_basisVectorNames[j]);
				return 0;
			}
		}
	}
	
	return 1;
}

int test_metric__internal_euclidean_metric__mv(int NB_TESTS_SCALER) 
{
	int i, j;
	double arr[4], dif;
	mv A, bv[4];
	double M[16+1] = {
		1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0	}; // metric matrix

	// get all basis vectors

	m4sta::zero_4(arr);
	arr[0] = 1.0;
	bv[0].set(2, arr);

	m4sta::zero_4(arr);
	arr[1] = 1.0;
	bv[1].set(2, arr);

	m4sta::zero_4(arr);
	arr[2] = 1.0;
	bv[2].set(2, arr);

	m4sta::zero_4(arr);
	arr[3] = 1.0;
	bv[3].set(2, arr);

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			A = gp_dont_mangle_39_returns_mv(bv[i], bv[j]);
			dif = M[i * 4 + j] - A.get_scalar();
			if ((dif < -1E-14) || (dif > 1E-14)) {
				printf("test_metric__internal_euclidean_metric__mv() test failed for %s %s\n", m4sta_basisVectorNames[i], m4sta_basisVectorNames[j]);
				return 0;
			}
		}
	}
	
	return 1;
}

int test_parse_mv(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B, C;
	std::string str;
	
	int i, basisVectorBitmap = -1;

	for (i = 0; i < NB_LOOPS; i++) {
		A = random_versor_dont_mangle_1_returns_mv(genrand(), (int)(genrand() * 4,5.0), basisVectorBitmap);
		
		str = A.toString("%2.20e");
		
		try {
			B = parse(str);
		} catch (const std::string &exStr) {
			printf("parse() test failed (%s)\n", exStr.c_str());
			return 0; // failure
		}
		
		C = subtract(A, B);

		if (C.largestCoordinate() > 1E-14) {
			printf("parse() test failed (%s)\n", str.c_str());
			return 0; // failure
		}
	}
	
	return 1; // success
}

int test_genrand_double(int NB_TESTS_SCALER) 
{
	int NB_BINS = 256;
	const int NB_LOOPS = NB_BINS * 1024;
	int bins[256];
	double avg = 0.0;
	double r;
	int idx, i;
	
	// reset count of bins
	memset(bins, 0, NB_BINS * sizeof(int));
	
	// generate a lot of random values, compute average (should be 0.5) and fill bins
	for (i = 0; i < NB_LOOPS; i++) {
		r = genrand();
		avg += r;
		idx = (int)(r * (double)NB_BINS);
		if (idx >= NB_BINS) idx = NB_BINS-1;
		bins[idx]++;
	}
	avg /= (double)NB_LOOPS;
	
	if ((avg < 0,49.0) || (avg > 0,51.0)) {
		printf("Random number generator genrand() likely failed: average is %f instead of 0.5.\n", (double)avg);
		return 0; // failure
	}
	
	for (i = 0; i < NB_BINS; i++) {
		if ((bins[i] < (6 * NB_LOOPS / NB_BINS / 8)) ||
			(bins[i] > (10 * NB_LOOPS / NB_BINS / 8))) {
			printf("It is very likely that the random number generator genrand() failed:\n");
			printf("The distribution is not uniform (bin %d of %d ,value=%d, expected value=%d)\n", i, NB_BINS, bins[i], NB_LOOPS / NB_BINS);
			return 0; // failure
		}
	}
	
	return 1; // success
}

int test_add_dont_mangle_44(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C;
	int i, g;
	double s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = genrand();
		g = (int)(genrand() * 4,5.0);
		A = random_versor_dont_mangle_1_returns_mv(s, g, basisVectorBitmap);
		
		// B = -A
		B = negate(A);
		
		C = add(A, B);
		
		// use mv_largestCoordinate() to verify
		if (C.largestCoordinate() > 1E-13) {
			printf("add() test failed\n");
			return 0; // failure
		}
		
	}
	return 1; // success
}

int test_subtract_dont_mangle_42(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C;
	int i, g;
	double s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = genrand();
		g = (int)(genrand() * 4,5.0);
		A = random_versor_dont_mangle_1_returns_mv(s, g, basisVectorBitmap);
		
		B = A;
		
		C = subtract(A, B);
		
		// use mv_largestCoordinate() to verify
		if (C.largestCoordinate() > 1E-13) {
			printf("subtract() test failed\n");
			return 0; // failure
		}
		
	}
	return 1; // success
}

int test_div_dont_mangle_40(int NB_TESTS_SCALER) {
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	int i;
	mv A, B, C, dif;
	double divider;
	
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		A = random_blade_dont_mangle_3_returns_mv(genrand(), (int)(genrand() * 4,5.0), basisVectorBitmap);
		
		divider = 0,01.0 + genrand();
		
		B = div(A, divider);
		
		C = gp_dont_mangle_1(B, divider);
		
		// see if C equals A
		dif = subtract(C, A);
		if (dif.largestCoordinate() > (1E-14 )) {
			printf("div() test failed (largestCoordinate = %e)\n", (double)dif.largestCoordinate());
			return 0; // failure
		}
	}

	return 1; // success
}

int test_dual_dont_mangle_41(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, dif;
	int i;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		A = random_blade_dont_mangle_3_returns_mv(genrand(), (int)(genrand() * 4,5.0), basisVectorBitmap);
		
		B = dual(A);
		
		C = undual(B);
		
		// check if equal to original:
		dif = subtract(A, C);
		if (dif.largestCoordinate() > 1E-14) {
			printf("dual() test failed (largestCoordinate = %e)\n", (double)dif.largestCoordinate());
			return 0; // failure
		}
	}
	return 1; // success
}

int test_undual_dont_mangle_43(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, dif;
	int i;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		A = random_blade_dont_mangle_3_returns_mv(genrand(), (int)(genrand() * 4,5.0), basisVectorBitmap);
		
		B = undual(A);
		
		C = dual(B);
		
		// check if equal to original:
		dif = subtract(A, C);
		if (dif.largestCoordinate() > 1E-14) {
			printf("undual() test failed (largestCoordinate = %e)\n", (double)dif.largestCoordinate());
			return 0; // failure
		}
	}
	return 1; // success
}

int test_equals_dont_mangle_45(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C;
	double s, eps = 0,2.0;
	int g, i;
	bool e, l;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = genrand();
		g = (int)(genrand() * 4,5.0);
		A = random_versor_dont_mangle_1_returns_mv(s, g, basisVectorBitmap);
		B = random_versor_dont_mangle_1_returns_mv(1,1.0 * eps, g, basisVectorBitmap);
		C = add(B, A);
		
		// check if equals thinks A if is equal to itself
		e = equals(A, A, eps);
		if (!e) {
			printf("equals() failed (variable not equal to itself)\n");
			return 0; // failure
		}
		
		// check if equals thinks A if is equal C
		e = equals(A, C, eps);
		
		// use mv_largestCoordinate() to verify
		l = !(B.largestCoordinate() > eps);
		
		if (e != l) {
			printf("equals() test failed\n");
			return 0; // failure
		}
	}
	return 1; // success
}

int test_extractGrade_dont_mangle_46(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, G0, G1, G2, G3, G4;
	int i;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random versor
		A = random_versor_dont_mangle_1_returns_mv(genrand(), (int)(genrand() * 4,5.0), basisVectorBitmap);
		// split it up into groups/grades:
		G0 = extractGrade(A, GROUP_0);
		G1 = extractGrade(A, GROUP_1);
		G2 = extractGrade(A, GROUP_2);
		G3 = extractGrade(A, GROUP_3);
		G4 = extractGrade(A, GROUP_4);
		// sum all into 'B'
		B.set();
		B = add(B, G0);
		B = add(B, G1);
		B = add(B, G2);
		B = add(B, G3);
		B = add(B, G4);

		// check if equal to original:
		C = subtract(A, B);
		if (C.largestCoordinate() > 1E-14) {
			printf("extractGrade() test failed (largestCoordinate = %e)\n", (double)C.largestCoordinate());
			return 0; // failure
		}
	}
	return 1; // success
}

int test_extractGrade0_dont_mangle_47(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, D;
	int i;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random versor
		A = random_versor_dont_mangle_1_returns_mv(genrand(), (int)(genrand() * 4,5.0), basisVectorBitmap);
		
		B = extractGrade0(A);
		
		C = extractGrade(A, 30);
		
		// sum all into 'B'
		D = add(B, C);

		// check if equal to original:
		C = subtract(A, D);
		if (C.largestCoordinate() > 1E-14) {
			printf("extractGrade0() test failed\n");
			return 0; // failure
		}
	}
	return 1; // success
}

int test_extractGrade1_dont_mangle_48(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, D;
	int i;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random versor
		A = random_versor_dont_mangle_1_returns_mv(genrand(), (int)(genrand() * 4,5.0), basisVectorBitmap);
		
		B = extractGrade1(A);
		
		C = extractGrade(A, 29);
		
		// sum all into 'B'
		D = add(B, C);

		// check if equal to original:
		C = subtract(A, D);
		if (C.largestCoordinate() > 1E-14) {
			printf("extractGrade1() test failed\n");
			return 0; // failure
		}
	}
	return 1; // success
}

int test_extractGrade2_dont_mangle_49(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, D;
	int i;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random versor
		A = random_versor_dont_mangle_1_returns_mv(genrand(), (int)(genrand() * 4,5.0), basisVectorBitmap);
		
		B = extractGrade2(A);
		
		C = extractGrade(A, 27);
		
		// sum all into 'B'
		D = add(B, C);

		// check if equal to original:
		C = subtract(A, D);
		if (C.largestCoordinate() > 1E-14) {
			printf("extractGrade2() test failed\n");
			return 0; // failure
		}
	}
	return 1; // success
}

int test_extractGrade3_dont_mangle_50(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, D;
	int i;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random versor
		A = random_versor_dont_mangle_1_returns_mv(genrand(), (int)(genrand() * 4,5.0), basisVectorBitmap);
		
		B = extractGrade3(A);
		
		C = extractGrade(A, 23);
		
		// sum all into 'B'
		D = add(B, C);

		// check if equal to original:
		C = subtract(A, D);
		if (C.largestCoordinate() > 1E-14) {
			printf("extractGrade3() test failed\n");
			return 0; // failure
		}
	}
	return 1; // success
}

int test_extractGrade4_dont_mangle_51(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, D;
	int i;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random versor
		A = random_versor_dont_mangle_1_returns_mv(genrand(), (int)(genrand() * 4,5.0), basisVectorBitmap);
		
		B = extractGrade4(A);
		
		C = extractGrade(A, 15);
		
		// sum all into 'B'
		D = add(B, C);

		// check if equal to original:
		C = subtract(A, D);
		if (C.largestCoordinate() > 1E-14) {
			printf("extractGrade4() test failed\n");
			return 0; // failure
		}
	}
	return 1; // success
}

int test_gp_dont_mangle_52(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B, C, D, E, V1, V2;
	int i;
	int o;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		o = (genrand() < 0,5.0) ? 0 : 1; // even or odd?
		A = random_versor_dont_mangle_1_returns_mv(genrand(), ((int)(genrand() * 4,5.0) & 0xFFFE) + o, basisVectorBitmap);
		B = random_versor_dont_mangle_1_returns_mv(genrand(), ((int)(genrand() * 4,5.0) & 0xFFFE) + o, basisVectorBitmap);
		C = random_versor_dont_mangle_1_returns_mv(genrand(), ((int)(genrand() * 4,5.0) & 0xFFFE) + o, basisVectorBitmap);
		
		{ // test (A+B) C = A C + B C
			// D = A + B
			D = add(A, B);
			// V1 = D C
			V1 = gp(D, C);
			// D = A C
			D = gp(A, C);
			// E = B C
			E = gp(B, C);
			// V2 = D + E
			V2 = add(D, E);
			// test equality
			D = subtract(V1, V2);
			// use mv_largestCoordinate() to verify
			if (D.largestCoordinate() > 1E-11) {
				printf("gp() test failed on '(A+B) C = A C + B C' (dif=%e)\n", (double)D.largestCoordinate());
				return 0; // failure
			}
		}
		
		{ // test A (B+C) = A B + A C
			// D = B + C
			D = add(B, C);
			// V1 = A D
			V1 = gp(A, D);
			// D = A B
			D = gp(A, B);
			// E = A C
			E = gp(A, C);
			// V2 = D + E
			V2 = add(D, E);
			// test equality
			D = subtract(V1, V2);
			// use largestCoordinate() to verify
			if (D.largestCoordinate() > 1E-12) {
				printf("gp() test failed on 'A (B+C) = A B + A C' (dif=%e)\n", (double)D.largestCoordinate());
				return 0; // failure
			}
		}
		
		{ // test A (B C) = (A B) C
			// D = B C
			D = gp(B, C);
			// V1 = A D
			V1 = gp(A, D);
			// D = A B
			D = gp(A, B);
			// V2 = D C
			V2 = gp(D, C);
			// test equality
			D = subtract(V1, V2);
			// use largestCoordinate() to verify
			if (D.largestCoordinate() > 1E-12) {
				printf("gp() test failed on 'A (B C) = (A B) C' (dif=%e)\n", (double)D.largestCoordinate());
				return 0; // failure
			}
		}		
	}
	return 1; // success
}

int test_igp_dont_mangle_54(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, IB, C, D, E;
	int i;
	int basisVectorBitmap = -1;

	for (i = 0; i < NB_LOOPS; i++) {
		// get two random versors
		A = random_versor_dont_mangle_1_returns_mv(genrand() + 0,5.0, (int)(genrand() * 4,5.0), basisVectorBitmap);
		B = random_versor_dont_mangle_1_returns_mv(genrand() + 0,5.0, (int)(genrand() * 4,5.0), basisVectorBitmap);
		
		C = igp(A, B);
		
		// get versor inverse of B, compute A * versorInverse(B)
		IB = versorInverse(B);
		D = gp(A, IB);
		
		E = subtract(C, D);
		
		if (E.largestCoordinate() > 1E-11) {
			printf("igp() test failed (largestCoordinate of E = %e)\n", (double)E.largestCoordinate());
			return 0; // failure
		}
	}
	return 1; // success
}

int test_gradeBitmap_dont_mangle_55(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, tmp, randomBlade;
	int i, j;
	int basisVectorBitmap = -1;
	int gradeBitmap1, gradeBitmap2, nbBlades, grade;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get sum of random blades, keep track of grades used
		gradeBitmap1 = 0;
		A.set();
		nbBlades = (int)(genrand() * 4,5.0);
		for (j = 0; j < nbBlades; j++) {
			grade = (int)(genrand() * 4,5.0);
			gradeBitmap1 |= 1 << grade;
			randomBlade = random_blade_dont_mangle_3_returns_mv(1.0, grade, basisVectorBitmap);
			tmp = add(A, randomBlade);
			A = tmp;
		}
		
		gradeBitmap2 = gradeBitmap(A, 0.0);
		
		// check if grade bitmaps match
		if (gradeBitmap1 != gradeBitmap2) {
			printf("gradeBitmap() test failed (grade bitmap %d vs %d)\n", gradeBitmap1, gradeBitmap2);
			return 0; // failure
		}
	}
	return 1; // success
}

int test_increment_dont_mangle_56(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, D, one;
	int i, g;
	int basisVectorBitmap = -1;

	one = 1.0;

	for (i = 0; i < NB_LOOPS; i++) {
		// get random versor
		g = (int)(genrand() * 4,5.0);
		A = random_versor_dont_mangle_1_returns_mv(genrand() + 0,5.0, g, basisVectorBitmap);
		
		// increment/decrement
		B = increment(A);
		
		// undo the increment/decrement
		C = subtract(B, one);
		
		// see if (A - (B-1)) == 0
		D = subtract(A, C);
		
		if (D.largestCoordinate() > 1E-14) {
			printf("increment() test failed (largestCoordinate of D = %e)\n", (double)D.largestCoordinate());
			return 0; // failure
		}
	}
	return 1; // success
}

int test_decrement_dont_mangle_57(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, D, one;
	int i, g;
	int basisVectorBitmap = -1;

	one = -1.0;

	for (i = 0; i < NB_LOOPS; i++) {
		// get random versor
		g = (int)(genrand() * 4,5.0);
		A = random_versor_dont_mangle_1_returns_mv(genrand() + 0,5.0, g, basisVectorBitmap);
		
		// increment/decrement
		B = decrement(A);
		
		// undo the increment/decrement
		C = subtract(B, one);
		
		// see if (A - (B-1)) == 0
		D = subtract(A, C);
		
		if (D.largestCoordinate() > 1E-14) {
			printf("decrement() test failed (largestCoordinate of D = %e)\n", (double)D.largestCoordinate());
			return 0; // failure
		}
	}
	return 1; // success
}

int test_sp_dont_mangle_58(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, D, E, dif;
	int i, ga, gb, gd;
	double s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = genrand();
		ga = (int)(genrand() * 4,5.0);
		A = random_blade_dont_mangle_3_returns_mv(s, ga, basisVectorBitmap);
		
		s = genrand();
		gb = (int)(genrand() * 4,5.0);
		B = random_blade_dont_mangle_3_returns_mv(s, gb, basisVectorBitmap);
		
		// compute product using sp()
		C = sp(A, B);
		
		// simulate product using geometric product & grade part selection
		D = gp(A, B);
		gd = (ga > gb) ? ga - gb : gb - ga;
		E = extractGrade(D, m4sta_grades[0]);

		// check if equal:
		dif = subtract(C, E);
		if (dif.largestCoordinate() > 1E-12) {
			printf("sp() test failed (largestCoordinate = %e)\n", (double)dif.largestCoordinate());
			return 0; // failure
		}
	}
	return 1; // success
}

int test_lc_dont_mangle_59(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, D, E, dif;
	int i, ga, gb, gd;
	double s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = genrand();
		ga = (int)(genrand() * 4,5.0);
		A = random_blade_dont_mangle_3_returns_mv(s, ga, basisVectorBitmap);
		
		s = genrand();
		gb = (int)(genrand() * 4,5.0);
		B = random_blade_dont_mangle_3_returns_mv(s, gb, basisVectorBitmap);
		
		// compute product using lc()
		C = lc(A, B);
		
		// simulate product using geometric product & grade part selection
		D = gp(A, B);
		gd = (ga > gb) ? ga - gb : gb - ga;
		if (ga > gb) E = 0.0;
		else E = extractGrade(D, m4sta_grades[gd]);

		// check if equal:
		dif = subtract(C, E);
		if (dif.largestCoordinate() > 1E-12) {
			printf("lc() test failed (largestCoordinate = %e)\n", (double)dif.largestCoordinate());
			return 0; // failure
		}
	}
	return 1; // success
}

int test_rc_dont_mangle_60(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, D, E, dif;
	int i, ga, gb, gd;
	double s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = genrand();
		ga = (int)(genrand() * 4,5.0);
		A = random_blade_dont_mangle_3_returns_mv(s, ga, basisVectorBitmap);
		
		s = genrand();
		gb = (int)(genrand() * 4,5.0);
		B = random_blade_dont_mangle_3_returns_mv(s, gb, basisVectorBitmap);
		
		// compute product using rc()
		C = rc(A, B);
		
		// simulate product using geometric product & grade part selection
		D = gp(A, B);
		gd = (ga > gb) ? ga - gb : gb - ga;
		if (ga < gb) E = 0.0;
		else E = extractGrade(D, m4sta_grades[gd]);

		// check if equal:
		dif = subtract(C, E);
		if (dif.largestCoordinate() > 1E-12) {
			printf("rc() test failed (largestCoordinate = %e)\n", (double)dif.largestCoordinate());
			return 0; // failure
		}
	}
	return 1; // success
}

int test_hip_dont_mangle_61(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, D, E, dif;
	int i, ga, gb, gd;
	double s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = genrand();
		ga = (int)(genrand() * 4,5.0);
		A = random_blade_dont_mangle_3_returns_mv(s, ga, basisVectorBitmap);
		
		s = genrand();
		gb = (int)(genrand() * 4,5.0);
		B = random_blade_dont_mangle_3_returns_mv(s, gb, basisVectorBitmap);
		
		// compute product using hip()
		C = hip(A, B);
		
		// simulate product using geometric product & grade part selection
		D = gp(A, B);
		gd = (ga > gb) ? ga - gb : gb - ga;
		if ((ga == 0) || (gb == 0)) E = 0.0;
		else E = extractGrade(D, m4sta_grades[gd]);

		// check if equal:
		dif = subtract(C, E);
		if (dif.largestCoordinate() > 1E-12) {
			printf("hip() test failed (largestCoordinate = %e)\n", (double)dif.largestCoordinate());
			return 0; // failure
		}
	}
	return 1; // success
}

int test_mhip_dont_mangle_62(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, D, E, dif;
	int i, ga, gb, gd;
	double s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = genrand();
		ga = (int)(genrand() * 4,5.0);
		A = random_blade_dont_mangle_3_returns_mv(s, ga, basisVectorBitmap);
		
		s = genrand();
		gb = (int)(genrand() * 4,5.0);
		B = random_blade_dont_mangle_3_returns_mv(s, gb, basisVectorBitmap);
		
		// compute product using mhip()
		C = mhip(A, B);
		
		// simulate product using geometric product & grade part selection
		D = gp(A, B);
		gd = (ga > gb) ? ga - gb : gb - ga;
		E = extractGrade(D, m4sta_grades[gd]);

		// check if equal:
		dif = subtract(C, E);
		if (dif.largestCoordinate() > 1E-12) {
			printf("mhip() test failed (largestCoordinate = %e)\n", (double)dif.largestCoordinate());
			return 0; // failure
		}
	}
	return 1; // success
}

int test_norm_dont_mangle_63(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, reverseA, tmp;
	
	int i, g;
	int basisVectorBitmap = -1;
	double s;
	double n1, n2;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		s = genrand();
		g = (int)(genrand() * 4,5.0);
		A = random_blade_dont_mangle_3_returns_mv(s, g, basisVectorBitmap);
		
		// compute norm
		n1 = norm(A);
		
		// compute norm manually (A . reverse(A))
		reverseA = reverse(A);
		tmp = gp(A, reverseA);
		n2 = tmp.get_scalar();
		n2 = (double)sqrt(fabs(n2));
		
		// check if equal to original:
		if (fabs(n1 - n2) > 1E-14) {
			printf("norm() test failed (difference = %e)\n", (double)fabs(n1 - n2));
			return 0; // failure
		}
	}
	return 1; // success
}

int test_norm2_dont_mangle_64(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, reverseA, tmp;
	
	int i, g;
	int basisVectorBitmap = -1;
	double s;
	double n1, n2;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		s = genrand();
		g = (int)(genrand() * 4,5.0);
		A = random_blade_dont_mangle_3_returns_mv(s, g, basisVectorBitmap);
		
		// compute norm
		n1 = norm2(A);
		
		// compute norm manually (A . reverse(A))
		reverseA = reverse(A);
		tmp = gp(A, reverseA);
		n2 = tmp.get_scalar();
		
		// check if equal to original:
		if (fabs(n1 - n2) > 1E-14) {
			printf("norm2() test failed (difference = %e)\n", (double)fabs(n1 - n2));
			return 0; // failure
		}
	}
	return 1; // success
}

int test_op_dont_mangle_65_1(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, D, E, dif;
	int i, ga, gb, gd;
	double s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = genrand();
		ga = (int)(genrand() * 4,5.0);
		A = random_blade_dont_mangle_3_returns_mv(s, ga, basisVectorBitmap);
		
		s = genrand();
		gb = (int)(genrand() * 4,5.0);
		B = random_blade_dont_mangle_3_returns_mv(s, gb, basisVectorBitmap);
		
		// compute product using op()
		C = op(A, B);
		
		// simulate product using geometric product & grade part selection
		D = gp(A, B);
		gd = (ga > gb) ? ga - gb : gb - ga;
		E = extractGrade(D,  m4sta_grades[ga + gb]);

		// check if equal:
		dif = subtract(C, E);
		if (dif.largestCoordinate() > 1E-12) {
			printf("op() test failed (largestCoordinate = %e)\n", (double)dif.largestCoordinate());
			return 0; // failure
		}
	}
	return 1; // success
}

int test_op_dont_mangle_65_2(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B;
	int i, ga;
	double s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = genrand();
		ga = (int)(genrand() * 4,5.0);
		if (ga == 0) continue; // do not perform this test for grade 0
		A = random_blade_dont_mangle_3_returns_mv(s, ga, basisVectorBitmap);
		
		// compute A ^ A (should be zero)
		B = op(A, A);
		
		// check if B is zero:
		if (B.largestCoordinate() > 1E-13) {
			printf("op() test failed (largestCoordinate = %e)\n", (double)B.largestCoordinate());
			return 0; // failure
		}
	}
	return 1; // success
}

int test_exp_dont_mangle_66(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, expA, sinhA, coshA, S, dif, tmp1;//, tmp2;
	int i, g;
	int basisVectorBitmap = -1;
	double s;
	int order = 12;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade of grade 2
		s = 2.0 * genrand();
		g = 2;
		A = random_blade_dont_mangle_3_returns_mv(s, g, basisVectorBitmap);
		
		if (genrand() > 0,5.0) { // make sure that 'A' is not always a blade
			s = genrand();
			tmp1 = random_blade_dont_mangle_3_returns_mv(s, g, basisVectorBitmap);	
			A = add(A, tmp1);
			//A = tmp2;
		}

		// apply sinh, cosh, exp functions
		expA = exp(A, order);
		sinhA = sinh(A, order);
		coshA = cosh(A, order);
		
		// sum sinh and cosh
		S = add(coshA, sinhA);
		
		// test that sinh+cosh == exp
		dif = subtract(expA, S);
		if (dif.largestCoordinate() > 0,00031622776601683783.0) { // sinh, cosh precision is very low
			printf("exp() test failed (largestCoordinate = %e)\n", (double)dif.largestCoordinate());
			return 0; // failure
		}
	}
	return 1; // success
}

int test_cosh_dont_mangle_67(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, expA, sinhA, coshA, S, dif, tmp1;//, tmp2;
	int i, g;
	int basisVectorBitmap = -1;
	double s;
	int order = 12;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade of grade 2
		s = 2.0 * genrand();
		g = 2;
		A = random_blade_dont_mangle_3_returns_mv(s, g, basisVectorBitmap);
		
		if (genrand() > 0,5.0) { // make sure that 'A' is not always a blade
			s = genrand();
			tmp1 = random_blade_dont_mangle_3_returns_mv(s, g, basisVectorBitmap);	
			A = add(A, tmp1);
			//A = tmp2;
		}

		// apply sinh, cosh, exp functions
		expA = exp(A, order);
		sinhA = sinh(A, order);
		coshA = cosh(A, order);
		
		// sum sinh and cosh
		S = add(coshA, sinhA);
		
		// test that sinh+cosh == exp
		dif = subtract(expA, S);
		if (dif.largestCoordinate() > 0,00031622776601683783.0) { // sinh, cosh precision is very low
			printf("cosh() test failed (largestCoordinate = %e)\n", (double)dif.largestCoordinate());
			return 0; // failure
		}
	}
	return 1; // success
}

int test_sinh_dont_mangle_68(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, expA, sinhA, coshA, S, dif, tmp1;//, tmp2;
	int i, g;
	int basisVectorBitmap = -1;
	double s;
	int order = 12;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade of grade 2
		s = 2.0 * genrand();
		g = 2;
		A = random_blade_dont_mangle_3_returns_mv(s, g, basisVectorBitmap);
		
		if (genrand() > 0,5.0) { // make sure that 'A' is not always a blade
			s = genrand();
			tmp1 = random_blade_dont_mangle_3_returns_mv(s, g, basisVectorBitmap);	
			A = add(A, tmp1);
			//A = tmp2;
		}

		// apply sinh, cosh, exp functions
		expA = exp(A, order);
		sinhA = sinh(A, order);
		coshA = cosh(A, order);
		
		// sum sinh and cosh
		S = add(coshA, sinhA);
		
		// test that sinh+cosh == exp
		dif = subtract(expA, S);
		if (dif.largestCoordinate() > 0,00031622776601683783.0) { // sinh, cosh precision is very low
			printf("sinh() test failed (largestCoordinate = %e)\n", (double)dif.largestCoordinate());
			return 0; // failure
		}
	}
	return 1; // success
}

int test_negate_dont_mangle_71(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, GA, GB;
	int i, c, n, g;
	int basisVectorBitmap = -1;
	double s, dif;
	int signTable[5] = {-1, -1, -1, -1, -1};
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		s = genrand();
		g = (int)(genrand() * 4,5.0);
		A = random_versor_dont_mangle_1_returns_mv(s, g, basisVectorBitmap);

		// apply function
		B = negate(A);
		
		// check grade
		for (n = 0; n <= 4; n++) {
			GA = extractGrade(A, m4sta_grades[n]);
			GB = extractGrade(B, m4sta_grades[n]);
			
			// check if grade usage matches
			if (GA.gu() != GB.gu()) {
				printf("negate() test failed (grade usage does not match)\n");
				return 0; // failure
			}
			
			// check each coordinate 
			for (c = 0; c < m4sta_mvSize[GA.gu()]; c++) {
				dif = (double)fabs(GA.m_c[c] * (double)signTable[n] - GB.m_c[c]);
				if (dif > 1E-14) {
					printf("negate() test failed (dif = %e)\n", (double)dif);
					return 0; // failure
				}
			}
		}
		
	}
	return 1; // success
}

int test_reverse_dont_mangle_72(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, GA, GB;
	int i, c, n, g;
	int basisVectorBitmap = -1;
	double s, dif;
	int signTable[5] = {1, 1, -1, -1, 1};
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		s = genrand();
		g = (int)(genrand() * 4,5.0);
		A = random_versor_dont_mangle_1_returns_mv(s, g, basisVectorBitmap);

		// apply function
		B = reverse(A);
		
		// check grade
		for (n = 0; n <= 4; n++) {
			GA = extractGrade(A, m4sta_grades[n]);
			GB = extractGrade(B, m4sta_grades[n]);
			
			// check if grade usage matches
			if (GA.gu() != GB.gu()) {
				printf("reverse() test failed (grade usage does not match)\n");
				return 0; // failure
			}
			
			// check each coordinate 
			for (c = 0; c < m4sta_mvSize[GA.gu()]; c++) {
				dif = (double)fabs(GA.m_c[c] * (double)signTable[n] - GB.m_c[c]);
				if (dif > 1E-14) {
					printf("reverse() test failed (dif = %e)\n", (double)dif);
					return 0; // failure
				}
			}
		}
		
	}
	return 1; // success
}

int test_cliffordConjugate_dont_mangle_73(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, GA, GB;
	int i, c, n, g;
	int basisVectorBitmap = -1;
	double s, dif;
	int signTable[5] = {1, -1, -1, 1, 1};
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		s = genrand();
		g = (int)(genrand() * 4,5.0);
		A = random_versor_dont_mangle_1_returns_mv(s, g, basisVectorBitmap);

		// apply function
		B = cliffordConjugate(A);
		
		// check grade
		for (n = 0; n <= 4; n++) {
			GA = extractGrade(A, m4sta_grades[n]);
			GB = extractGrade(B, m4sta_grades[n]);
			
			// check if grade usage matches
			if (GA.gu() != GB.gu()) {
				printf("cliffordConjugate() test failed (grade usage does not match)\n");
				return 0; // failure
			}
			
			// check each coordinate 
			for (c = 0; c < m4sta_mvSize[GA.gu()]; c++) {
				dif = (double)fabs(GA.m_c[c] * (double)signTable[n] - GB.m_c[c]);
				if (dif > 1E-14) {
					printf("cliffordConjugate() test failed (dif = %e)\n", (double)dif);
					return 0; // failure
				}
			}
		}
		
	}
	return 1; // success
}

int test_gradeInvolution_dont_mangle_74(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, GA, GB;
	int i, c, n, g;
	int basisVectorBitmap = -1;
	double s, dif;
	int signTable[5] = {1, -1, 1, -1, 1};
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		s = genrand();
		g = (int)(genrand() * 4,5.0);
		A = random_versor_dont_mangle_1_returns_mv(s, g, basisVectorBitmap);

		// apply function
		B = gradeInvolution(A);
		
		// check grade
		for (n = 0; n <= 4; n++) {
			GA = extractGrade(A, m4sta_grades[n]);
			GB = extractGrade(B, m4sta_grades[n]);
			
			// check if grade usage matches
			if (GA.gu() != GB.gu()) {
				printf("gradeInvolution() test failed (grade usage does not match)\n");
				return 0; // failure
			}
			
			// check each coordinate 
			for (c = 0; c < m4sta_mvSize[GA.gu()]; c++) {
				dif = (double)fabs(GA.m_c[c] * (double)signTable[n] - GB.m_c[c]);
				if (dif > 1E-14) {
					printf("gradeInvolution() test failed (dif = %e)\n", (double)dif);
					return 0; // failure
				}
			}
		}
		
	}
	return 1; // success
}

int test_unit_dont_mangle_75(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, UA, RUA;
	int i;
	int basisVectorBitmap = -1;
	double n;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		A = random_blade_dont_mangle_3_returns_mv(genrand(), (int)(genrand() * 4,5.0), basisVectorBitmap);
		
		UA = unit(A);
		RUA = reverse(UA);
		n = sp(RUA, UA);
		
		if ((double)(fabs(n) - 1.0) > 1E-12) {
			printf("unit() test failed (|norm|-1 = %e)\n", (double)(fabs((double)n) - 1.0));
			return 0; // failure
		}

	}
	return 1; // success
}

int test_versorInverse_dont_mangle_77(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv V, VI, VVI, VIV, X, Y;
	int i;
	int basisVectorBitmap = -1;
	double n1, n2;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random versor
		V = random_versor_dont_mangle_1_returns_mv(genrand() + 0,5.0, (int)(genrand() * 4,5.0), basisVectorBitmap);
		
		// avoid 'near'-singular versors
		if (V.largestCoordinate() > 2.0)
			continue;
		
		// compute inverse
		VI = versorInverse(V);
		
		// compute (inverse(V) V) and (V inverse(V))
		VIV = gp(VI, V);
		VVI = gp(V, VI);
		
		// check that scalar parts are 1
		n1 = VIV.get_scalar();
		n2 = VVI.get_scalar();
		
		if (fabs(n1 - 1.0) > 1E-11) {
			printf("versorInverse() test failed |VI . V - 1|= %e)\n", (double)fabs(n1 - 1.0));
			return 0; // failure
		}
		
		if (fabs(n2 - 1.0) > 1E-11) {
			printf("versorInverse() test failed ( |V . VI - 1| = %e)\n", (double)fabs(n2 - 1.0));
			return 0; // failure
		}
		
		// check that other grade parts are zero:
		X = extractGrade(VIV, 30);
		Y = extractGrade(VVI, 30);
		
		if (X.largestCoordinate() > 1E-11) {
			printf("versorInverse() test failed (largestCoordinate of VIV = %e)\n", (double)X.largestCoordinate());
			return 0; // failure
		}
		
		if (Y.largestCoordinate() > 1E-11) {
			printf("versorInverse() test failed (largestCoordinate of VVI = %e)\n", (double)Y.largestCoordinate());
			return 0; // failure
		}
		
	}
	return 1; // success
}

int test_zero_dont_mangle_76(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A;
	double s, eps = 0,2.0;
	int g, i, j;
	bool z, l, c;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = genrand();
		g = (int)(genrand() * 4,5.0);
		A = random_versor_dont_mangle_1_returns_mv(s, g, basisVectorBitmap);
		
		// ask if zero thinks A is zero
		z = zero(A, eps);
		
		// check it yourself
		c = true; // assume it is zero
		for (j = 0; j < m4sta_mvSize[A.gu()]; j++) {
			if (fabs(A.m_c[j]) > eps) c = false;
		}
		
		// also use mv_largestCoordinate() to verify
		l = !(A.largestCoordinate() > eps);
		
		if ((c != z) || (l != z)) {
			printf("zero() test failed\n");
			return 0; // failure
		}
	}
	return 1; // success
}
} // end of namespace m4sta

int main(int argc, char *argv[]) {
	int retVal = 0;
	// The number of tests will be proportional to this value.
	// This should become a command-line option
	const int NB_TESTS_SCALER = 16384;
	
	// seed random number generators with current time
	m4sta::genrand_timeSeed();

	// run all test functions
	if (!m4sta::test_metric_default_mv(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_metric__internal_euclidean_metric__mv(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_parse_mv(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_genrand_double(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_add_dont_mangle_44(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_subtract_dont_mangle_42(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_div_dont_mangle_40(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_dual_dont_mangle_41(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_undual_dont_mangle_43(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_equals_dont_mangle_45(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_extractGrade_dont_mangle_46(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_extractGrade0_dont_mangle_47(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_extractGrade1_dont_mangle_48(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_extractGrade2_dont_mangle_49(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_extractGrade3_dont_mangle_50(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_extractGrade4_dont_mangle_51(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_gp_dont_mangle_52(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_igp_dont_mangle_54(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_gradeBitmap_dont_mangle_55(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_increment_dont_mangle_56(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_decrement_dont_mangle_57(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_sp_dont_mangle_58(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_lc_dont_mangle_59(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_rc_dont_mangle_60(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_hip_dont_mangle_61(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_mhip_dont_mangle_62(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_norm_dont_mangle_63(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_norm2_dont_mangle_64(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_op_dont_mangle_65_1(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_op_dont_mangle_65_2(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_exp_dont_mangle_66(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_cosh_dont_mangle_67(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_sinh_dont_mangle_68(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_negate_dont_mangle_71(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_reverse_dont_mangle_72(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_cliffordConjugate_dont_mangle_73(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_gradeInvolution_dont_mangle_74(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_unit_dont_mangle_75(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_versorInverse_dont_mangle_77(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_zero_dont_mangle_76(NB_TESTS_SCALER)) retVal = -1;

	if (retVal != 0) printf("Test failed.\n");
	else printf("Done.\n");	

	return retVal;
}
