#include <time.h> /* used to seed random generator */
#include "m4sta.h"
namespace m4sta {
// Missing dependencies declarations:
/// Returns mv - mv.
mv subtract_dont_mangle_1_returns_mv(const mv &a, const mv &b);

/**
Generates a random versor.
The scale is uniformly distributed over the interval [0 1).
The maximum non-zero grade-part is 'grade'.
Only the basis vectors marked in 'basisVectorBitmap' will be used to generate the
versor/blade. Use 'basisVectorBitmap = -1' (the default) to use all basisvectors.

Returns random_versor_dont_mangle_2_returns_mv_ex(arg1, scale, grade, basisVectorBitmap, 0.01, scale * 4.0);
*/
mv random_versor_dont_mangle_2_returns_mv(double scale, int grade, int basisVectorBitmap = -1);

/**
This version of random_versor_dont_mangle_2_returns_mv() has extra arguments which help to avoid 
near-singular blades / versors.

Near-singular blades / versors are avoid by testing the norm and largest coordinate
of the random blade / versor. If the test does not pass, the function recursively
tries to generate another random blade / versor.

'minimumNorm' is the minimum allowed norm of the blade/versor before scaling. 
'minimumNorm' must be > 0.0 for versors.

'largestCoordinate' is the largest coordinate allowed after scaling.
*/
mv random_versor_dont_mangle_2_returns_mv_ex(double scale, int grade, int basisVectorBitmap, double minimumNorm, double largestCoordinate);

/// Returns mv + mv.
mv add_dont_mangle_3_returns_mv(const mv &a, const mv &b);
/// Returns geometric product of mv and mv.
mv gp_dont_mangle_6_returns_mv(const mv &a, const mv &b);
/// Returns norm of mv using default metric.
scalar norm_dont_mangle_7(const mv &a);
/// internal conversion function (this is just a pass through)
double norm_dont_mangle_7_returns_scalar(const mv &a);
/// Returns geometric product of mv and double.
mv gp_dont_mangle_8(const mv &a, const double b);
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
mv subtract_dont_mangle_1_returns_mv(const mv &a, const mv &b)
{
	int aidx = 0, bidx = 0, cidx = 0;
	int gu = a.gu() | b.gu();
	double c[16];
	
	if (a.gu() & 1) {
		if (b.gu() & 1) {
			sub2_0_0(a.getC() + aidx, b.getC() + bidx, c + cidx);
			bidx += 1;
		}
		else copyGroup_0(a.getC() + aidx, c + cidx);
		aidx += 1;
		cidx += 1;
	}
	else if (b.gu() & 1) {
		neg_0(b.getC() + bidx, c + cidx);
		bidx += 1;
		cidx += 1;
	}
	
	if (a.gu() & 2) {
		if (b.gu() & 2) {
			sub2_1_1(a.getC() + aidx, b.getC() + bidx, c + cidx);
			bidx += 4;
		}
		else copyGroup_1(a.getC() + aidx, c + cidx);
		aidx += 4;
		cidx += 4;
	}
	else if (b.gu() & 2) {
		neg_1(b.getC() + bidx, c + cidx);
		bidx += 4;
		cidx += 4;
	}
	
	if (a.gu() & 4) {
		if (b.gu() & 4) {
			sub2_2_2(a.getC() + aidx, b.getC() + bidx, c + cidx);
			bidx += 6;
		}
		else copyGroup_2(a.getC() + aidx, c + cidx);
		aidx += 6;
		cidx += 6;
	}
	else if (b.gu() & 4) {
		neg_2(b.getC() + bidx, c + cidx);
		bidx += 6;
		cidx += 6;
	}
	
	if (a.gu() & 8) {
		if (b.gu() & 8) {
			sub2_3_3(a.getC() + aidx, b.getC() + bidx, c + cidx);
			bidx += 4;
		}
		else copyGroup_3(a.getC() + aidx, c + cidx);
		aidx += 4;
		cidx += 4;
	}
	else if (b.gu() & 8) {
		neg_3(b.getC() + bidx, c + cidx);
		bidx += 4;
		cidx += 4;
	}
	
	if (a.gu() & 16) {
		if (b.gu() & 16) {
			sub2_4_4(a.getC() + aidx, b.getC() + bidx, c + cidx);
		}
		else copyGroup_4(a.getC() + aidx, c + cidx);
		cidx += 1;
	}
	else if (b.gu() & 16) {
		neg_4(b.getC() + bidx, c + cidx);
		cidx += 1;
	}
	return mv(gu, c);
}


mv random_versor_dont_mangle_2_returns_mv(double scale, int grade, int basisVectorBitmap) {
	double minimumNorm = 0,01.0;
	double largestCoordinate = 4.0;
	return random_versor_dont_mangle_2_returns_mv_ex(scale, grade, basisVectorBitmap, minimumNorm, scale * largestCoordinate);
}

mv random_versor_dont_mangle_2_returns_mv_ex(double scale, int _grade, int basisVectorBitmap, 
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
	n2 = norm_dont_mangle_7_returns_scalar(*IR1);
	if ((double)fabs(n2) > minimumNorm * minimumNorm) {
		if (n2 != 0.0) {
			mul = scale * genrand() / n2;
			if (IR1->largestCoordinate() * mul < largestCoordinate)
				return gp_dont_mangle_8(*IR1, mul);
		}
		else if (IR1->largestCoordinate() < largestCoordinate)
			return *IR1;
	}
	
	// try again:
	return random_versor_dont_mangle_2_returns_mv_ex(scale, _grade, basisVectorBitmap, minimumNorm, largestCoordinate); 
}
mv add_dont_mangle_3_returns_mv(const mv &a, const mv &b)
{
	int aidx = 0, bidx = 0, cidx = 0;
	int gu = a.gu() | b.gu();
	double c[16];
	
	if (a.gu() & 1) {
		if (b.gu() & 1) {
			add2_0_0(a.getC() + aidx, b.getC() + bidx, c + cidx);
			bidx += 1;
		}
		else copyGroup_0(a.getC() + aidx, c + cidx);
		aidx += 1;
		cidx += 1;
	}
	else if (b.gu() & 1) {
		copyGroup_0(b.getC() + bidx, c + cidx);
		bidx += 1;
		cidx += 1;
	}
	
	if (a.gu() & 2) {
		if (b.gu() & 2) {
			add2_1_1(a.getC() + aidx, b.getC() + bidx, c + cidx);
			bidx += 4;
		}
		else copyGroup_1(a.getC() + aidx, c + cidx);
		aidx += 4;
		cidx += 4;
	}
	else if (b.gu() & 2) {
		copyGroup_1(b.getC() + bidx, c + cidx);
		bidx += 4;
		cidx += 4;
	}
	
	if (a.gu() & 4) {
		if (b.gu() & 4) {
			add2_2_2(a.getC() + aidx, b.getC() + bidx, c + cidx);
			bidx += 6;
		}
		else copyGroup_2(a.getC() + aidx, c + cidx);
		aidx += 6;
		cidx += 6;
	}
	else if (b.gu() & 4) {
		copyGroup_2(b.getC() + bidx, c + cidx);
		bidx += 6;
		cidx += 6;
	}
	
	if (a.gu() & 8) {
		if (b.gu() & 8) {
			add2_3_3(a.getC() + aidx, b.getC() + bidx, c + cidx);
			bidx += 4;
		}
		else copyGroup_3(a.getC() + aidx, c + cidx);
		aidx += 4;
		cidx += 4;
	}
	else if (b.gu() & 8) {
		copyGroup_3(b.getC() + bidx, c + cidx);
		bidx += 4;
		cidx += 4;
	}
	
	if (a.gu() & 16) {
		if (b.gu() & 16) {
			add2_4_4(a.getC() + aidx, b.getC() + bidx, c + cidx);
		}
		else copyGroup_4(a.getC() + aidx, c + cidx);
		cidx += 1;
	}
	else if (b.gu() & 16) {
		copyGroup_4(b.getC() + bidx, c + cidx);
		cidx += 1;
	}
	return mv(gu, c);
}
mv gp_dont_mangle_6_returns_mv(const mv &a, const mv &b)
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
scalar norm_dont_mangle_7(const mv &a)
{
	double c[1];
	double n2 = 0.0;
	int idx = 0;
	
	if (a.gu() & 1) { /* group 0 (grade 0) */
		c[0] = 0.0;
		gp_default_0_0_0(a.getC() + idx, a.getC() + idx, c);
		n2 += c[0];
		idx += 1;
	}
	
	if (a.gu() & 2) { /* group 1 (grade 1) */
		c[0] = 0.0;
		gp_default_1_1_0(a.getC() + idx, a.getC() + idx, c);
		n2 += c[0];
		idx += 4;
	}
	
	if (a.gu() & 4) { /* group 2 (grade 2) */
		c[0] = 0.0;
		gp_default_2_2_0(a.getC() + idx, a.getC() + idx, c);
		n2 -= c[0];
		idx += 6;
	}
	
	if (a.gu() & 8) { /* group 3 (grade 3) */
		c[0] = 0.0;
		gp_default_3_3_0(a.getC() + idx, a.getC() + idx, c);
		n2 -= c[0];
		idx += 4;
	}
	
	if (a.gu() & 16) { /* group 4 (grade 4) */
		c[0] = 0.0;
		gp_default_4_4_0(a.getC() + idx, a.getC() + idx, c);
		n2 += c[0];
	}
	return scalar(scalar::coord_scalar,
			((n2 < 0.0) ? ::sqrt(-n2) : ::sqrt(n2)) // scalar
		);
}
double norm_dont_mangle_7_returns_scalar(const mv &a) {
	scalar tmp(norm_dont_mangle_7(a));
	return tmp.m_c[0];
}
mv gp_dont_mangle_8(const mv &a, const double b)
{
	double c[16];
	const double* _a[5];
	const double* _b[1] = {&b};
	a.expand(_a);
	m4sta::zero_16(c);
	if (a.gu() & 1) {
			gp_default_0_0_0(_a[0], _b[0], c + 0);
	}
	if (a.gu() & 2) {
			gp_default_1_0_1(_a[1], _b[0], c + 1);
	}
	if (a.gu() & 4) {
			gp_default_2_0_2(_a[2], _b[0], c + 5);
	}
	if (a.gu() & 8) {
			gp_default_3_0_3(_a[3], _b[0], c + 11);
	}
	if (a.gu() & 16) {
			gp_default_4_0_4(_a[4], _b[0], c + 15);
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
			A = gp_dont_mangle_6_returns_mv(bv[i], bv[j]);
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
		A = random_versor_dont_mangle_2_returns_mv(genrand(), (int)(genrand() * 4,5.0), basisVectorBitmap);
		
		str = A.toString("%2.20e");
		
		try {
			B = parse(str);
		} catch (const std::string &exStr) {
			printf("parse() test failed (%s)\n", exStr.c_str());
			return 0; // failure
		}
		
		C = subtract_dont_mangle_1_returns_mv(A, B);

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

int test_gp_dont_mangle_9(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B, C, D, E, V1, V2;
	int i;
	int o;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		o = (genrand() < 0,5.0) ? 0 : 1; // even or odd?
		A = random_versor_dont_mangle_2_returns_mv(genrand(), ((int)(genrand() * 4,5.0) & 0xFFFE) + o, basisVectorBitmap);
		B = random_versor_dont_mangle_2_returns_mv(genrand(), ((int)(genrand() * 4,5.0) & 0xFFFE) + o, basisVectorBitmap);
		C = random_versor_dont_mangle_2_returns_mv(genrand(), ((int)(genrand() * 4,5.0) & 0xFFFE) + o, basisVectorBitmap);
		
		{ // test (A+B) C = A C + B C
			// D = A + B
			D = add_dont_mangle_3_returns_mv(A, B);
			// V1 = D C
			V1 = gp(D, C);
			// D = A C
			D = gp(A, C);
			// E = B C
			E = gp(B, C);
			// V2 = D + E
			V2 = add_dont_mangle_3_returns_mv(D, E);
			// test equality
			D = subtract_dont_mangle_1_returns_mv(V1, V2);
			// use mv_largestCoordinate() to verify
			if (D.largestCoordinate() > 1E-11) {
				printf("gp() test failed on '(A+B) C = A C + B C' (dif=%e)\n", (double)D.largestCoordinate());
				return 0; // failure
			}
		}
		
		{ // test A (B+C) = A B + A C
			// D = B + C
			D = add_dont_mangle_3_returns_mv(B, C);
			// V1 = A D
			V1 = gp(A, D);
			// D = A B
			D = gp(A, B);
			// E = A C
			E = gp(A, C);
			// V2 = D + E
			V2 = add_dont_mangle_3_returns_mv(D, E);
			// test equality
			D = subtract_dont_mangle_1_returns_mv(V1, V2);
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
			D = subtract_dont_mangle_1_returns_mv(V1, V2);
			// use largestCoordinate() to verify
			if (D.largestCoordinate() > 1E-12) {
				printf("gp() test failed on 'A (B C) = (A B) C' (dif=%e)\n", (double)D.largestCoordinate());
				return 0; // failure
			}
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
	if (!m4sta::test_gp_dont_mangle_9(NB_TESTS_SCALER)) retVal = -1;

	if (retVal != 0) printf("Test failed.\n");
	else printf("Done.\n");	

	return retVal;
}
