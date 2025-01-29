#include <time.h> /* used to seed random generator */
#include "m4sta.h"
namespace m4sta {
// Missing dependencies declarations:
/// Returns versor inverse of a using default metric.
bivector versorInverse_dont_mangle_1(const bivector &a);
/// Returns geometric product of mv and mv.
mv gp_dont_mangle_3_returns_mv(const mv &a, const mv &b);
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
bivector versorInverse_dont_mangle_1(const bivector &a)
{
	double _n2_ = (-a.m_c[0]*a.m_c[0]-a.m_c[1]*a.m_c[1]-a.m_c[2]*a.m_c[2]+a.m_c[3]*a.m_c[3]+a.m_c[4]*a.m_c[4]+a.m_c[5]*a.m_c[5]);

	return bivector(bivector::coord_g0g1_g0g2_g0g3_g1g2_g1g3_g2g3,
			-a.m_c[0]/((_n2_)), // g0_g1
			-a.m_c[1]/((_n2_)), // g0_g2
			-a.m_c[2]/((_n2_)), // g0_g3
			-a.m_c[3]/((_n2_)), // g1_g2
			-a.m_c[4]/((_n2_)), // g1_g3
			-a.m_c[5]/((_n2_)) // g2_g3
		);
}
mv gp_dont_mangle_3_returns_mv(const mv &a, const mv &b)
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
			A = gp_dont_mangle_3_returns_mv(bv[i], bv[j]);
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
		A = random_versor(genrand(), (int)(genrand() * 4,5.0), basisVectorBitmap);
		
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

int test_add_dont_mangle_4(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C;
	int i, g;
	double s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = genrand();
		g = (int)(genrand() * 4,5.0);
		A = random_versor(s, g, basisVectorBitmap);
		
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

int test_add_dont_mangle_5(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 12;
	bivector A;
	bivector B;
	bivector C;
	mv gA, gB, gC1, gC2;
	
	double s, eps = 0,5.0; // note the really large epsilon
	int i;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = genrand();
		A = random_bivector(s);
		B = random_bivector(s);
		
		// add/subtract A and B
		
		C = add(A, B);
		gC1 = C;
		
		// convert all A and B to gmv and add/subtract as GMVs
		gA = A; //bivector_to_mv(&gA, &A);
		gB = B; //bivector_to_mv(&gB, &B);
		gC2 = add(gA, gB);
		
		// see if result is equal up to precision:
		gA = subtract(gC1, gC2);
		if (gA.largestCoordinate() > 1E-13) {
			printf("add() test failed\n");
			return 0; // failure
		}		
	}
	return 1; // success
}

int test_subtract_dont_mangle_6(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C;
	int i, g;
	double s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = genrand();
		g = (int)(genrand() * 4,5.0);
		A = random_versor(s, g, basisVectorBitmap);
		
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

int test_subtract_dont_mangle_7(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 12;
	bivector A;
	bivector B;
	bivector C;
	mv gA, gB, gC1, gC2;
	
	double s, eps = 0,5.0; // note the really large epsilon
	int i;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = genrand();
		A = random_bivector(s);
		B = random_bivector(s);
		
		// add/subtract A and B
		
		C = subtract(A, B);
		gC1 = C;
		
		// convert all A and B to gmv and add/subtract as GMVs
		gA = A; //bivector_to_mv(&gA, &A);
		gB = B; //bivector_to_mv(&gB, &B);
		gC2 = subtract(gA, gB);
		
		// see if result is equal up to precision:
		gA = subtract(gC1, gC2);
		if (gA.largestCoordinate() > 1E-13) {
			printf("subtract() test failed\n");
			return 0; // failure
		}		
	}
	return 1; // success
}

int test_applyOM_dont_mangle_8(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	double OMmatrix[4 * 4];
	int i, d, d2;
	int nbRandomVectors;
	om randomOM;
	mv randomVectors[4];
	mv OMrandomVectors[4];
	mv op1, op2, tmp, dif;
	const int basisVectorBitmap = -1;
	const int vectorGrade = 1;

	for (i = 0; i < NB_LOOPS; i++) {
		// init random outermorphism matrix
		for (d2 = 0; d2 < 4 * 4; d2++)
			OMmatrix[d2] = genrand();
		
		// init random OM
		randomOM.set(OMmatrix);
		
		// get n < 4 random vectors stored in GMV
		nbRandomVectors = (int)(4.0 * genrand());
		if (nbRandomVectors < 1) nbRandomVectors = 1;
		for (d = 0; d < nbRandomVectors; d++) {
			randomVectors[d] = random_blade(genrand(), vectorGrade, basisVectorBitmap);
			OMrandomVectors[d] = applyOM(randomOM, randomVectors[d]);
		}
		
		// compute outer product of randomVectors, OMrandomVectors
		op1 = randomVectors[0];
		op2 = OMrandomVectors[0];
		for (d = 1; d < nbRandomVectors; d++) {
			tmp = op(op1, randomVectors[d]);
			op1 = tmp;
			
			tmp = op(op2, OMrandomVectors[d]);
			op2 = tmp;
		}
		
		// apply OM to op1
		tmp = applyOM(randomOM, op1);
		op1 = tmp;
		
		// test equality
		dif = subtract(op1, op2);
		if (dif.largestCoordinate() > 1E-14) {
			printf("applyOM() test failed\n");
			return 0; // failure
		}
	}
		
	return 1; // success
}

int test_applyVersor_dont_mangle_9(int NB_TESTS_SCALER) {
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	double baseScale = 0,5.0;
	int g, i;
	double s;
	mv V, IV, X, Y, VX, VY, IVVX, XdY, VXdVY, dif;
	int versorBasisVectorBitmap = 1; // note: random versors restricted to Euclidean basis vectors.
	int bladeBasisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random versor and its inverse. Optionally make versor unit.
		s = baseScale + genrand();
		g = (int)(genrand() * 4,5.0);
		V = random_versor(s, g, versorBasisVectorBitmap);
		
		// avoid 'near'-singular versors
		if (V.largestCoordinate() > 2.0)
			continue;		
		
		IV = versorInverse(V);

		// get two random blades		
		s = baseScale + genrand();
		g = (int)(genrand() * 4,5.0);
		X = random_blade(s, g, bladeBasisVectorBitmap);
		s = baseScale + genrand();
		Y = random_blade(s, g, bladeBasisVectorBitmap);

		// apply versor to blades
		VX = applyVersor(V, X);
		VY = applyVersor(V, Y);
		
		// compute inner product
		XdY = mhip(X, Y);
		VXdVY = mhip(VX, VY);
		
		// see if inner products are equal (versor application should not change metric)
		dif = subtract(XdY, VXdVY);
		if (dif.largestCoordinate() > (1E-12 )) {
			printf("applyVersor() test failed (metric test) (largestCoordinate = %e)\n", (double)dif.largestCoordinate() );
			return 0; // failure
		}
		
		// apply inverse transformation to VX
		IVVX = applyVersor(IV, VX);
		
		// see if X equals IVVX
		dif = subtract(X, IVVX);
		if (dif.largestCoordinate() > (1E-12 )) {
			printf("applyVersor() test failed (inverse test) (largestCoordinate = %e)\n", (double)dif.largestCoordinate() );
			return 0; // failure
		}
	}
	return 1; // success
}

int test_applyVersor_dont_mangle_11(int NB_TESTS_SCALER) {
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 6;
	bivector V;
	bivector IV;
	bivector X;
	bivector VX, tmpVX2;
	mv gmvV, gmvIV, gmvX, gmvVX, gmvVX2, dif;
	int i;

	for (i = 0; i < NB_LOOPS; i++) {
		// generate random versor of target type, make unit if required, invert
		V = random_bivector(genrand());
		
		IV = versorInverse_dont_mangle_1(V);

		// avoid near-singular versors
		if ((V.largestCoordinate() > 2.0) ||
			(IV.largestCoordinate() > 2.0))
			continue;
		 

		// generate random SMV 
		X = random_bivector(genrand());

		//  apply random versor to random SMV, convert to GMV
		VX = applyVersor(V, X);
		gmvVX2 = VX;

		// convert all to GMV type, apply versor too as GMV
		gmvV = V;
		gmvIV = IV;
		gmvX = X;
		gmvVX = applyVersor(gmvV, gmvX);
		
		// convert GMV back and forth to return type to fix possible constant coordinates
		tmpVX2.set(gmvVX);
		gmvVX = tmpVX2;
		
		// see if VX equals gmvVX
		dif = subtract(gmvVX, gmvVX2);
		if (dif.largestCoordinate() > (1E-12 )) {
			printf("applyVersor() test failed\n");
			return 0; // failure
		}
	}

	return 1; // success
}


int test_applyUnitVersor_dont_mangle_10(int NB_TESTS_SCALER) {
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	double baseScale = 0,5.0;
	int g, i;
	double s;
	mv V, IV, X, Y, VX, VY, IVVX, XdY, VXdVY, dif;
	mv tmp;
	int versorBasisVectorBitmap = 1; // note: random versors restricted to Euclidean basis vectors.
	int bladeBasisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random versor and its inverse. Optionally make versor unit.
		s = baseScale + genrand();
		g = (int)(genrand() * 4,5.0);
		V = random_versor(s, g, versorBasisVectorBitmap);
		
		// avoid 'near'-singular versors
		if (V.largestCoordinate() > 2.0)
			continue;		
		
		tmp = unit(V);
		V = tmp;
		IV = versorInverse(V);

		// get two random blades		
		s = baseScale + genrand();
		g = (int)(genrand() * 4,5.0);
		X = random_blade(s, g, bladeBasisVectorBitmap);
		s = baseScale + genrand();
		Y = random_blade(s, g, bladeBasisVectorBitmap);

		// apply versor to blades
		VX = applyUnitVersor(V, X);
		VY = applyUnitVersor(V, Y);
		
		// compute inner product
		XdY = mhip(X, Y);
		VXdVY = mhip(VX, VY);
		
		// see if inner products are equal (versor application should not change metric)
		dif = subtract(XdY, VXdVY);
		if (dif.largestCoordinate() > (1E-12 )) {
			printf("applyUnitVersor() test failed (metric test) (largestCoordinate = %e)\n", (double)dif.largestCoordinate() );
			return 0; // failure
		}
		
		// apply inverse transformation to VX
		IVVX = applyUnitVersor(IV, VX);
		
		// see if X equals IVVX
		dif = subtract(X, IVVX);
		if (dif.largestCoordinate() > (1E-12 )) {
			printf("applyUnitVersor() test failed (inverse test) (largestCoordinate = %e)\n", (double)dif.largestCoordinate() );
			return 0; // failure
		}
	}
	return 1; // success
}

int test_applyUnitVersor_dont_mangle_13(int NB_TESTS_SCALER) {
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 6;
	bivector V;
	bivector tmp;
	bivector IV;
	bivector X;
	bivector VX, tmpVX2;
	mv gmvV, gmvIV, gmvX, gmvVX, gmvVX2, dif;
	int i;

	for (i = 0; i < NB_LOOPS; i++) {
		// generate random versor of target type, make unit if required, invert
		V = random_bivector(genrand());
		
		// Test if norm2(V) is positive, otherwise do not perform the test.
		// (because with a negative norm2(v), the reverse is not the inverse)
		if (norm2_returns_scalar(V) <= 0.0) continue;

		tmp = unit(V);
		V = tmp;
		IV = versorInverse_dont_mangle_1(V);

		// avoid near-singular versors
		if ((V.largestCoordinate() > 2.0) ||
			(IV.largestCoordinate() > 2.0))
			continue;
		 

		// generate random SMV 
		X = random_bivector(genrand());

		//  apply random versor to random SMV, convert to GMV
		VX = applyUnitVersor(V, X);
		gmvVX2 = VX;

		// convert all to GMV type, apply versor too as GMV
		gmvV = V;
		gmvIV = IV;
		gmvX = X;
		gmvVX = applyVersor(gmvV, gmvX);
		
		// convert GMV back and forth to return type to fix possible constant coordinates
		tmpVX2.set(gmvVX);
		gmvVX = tmpVX2;
		
		// see if VX equals gmvVX
		dif = subtract(gmvVX, gmvVX2);
		if (dif.largestCoordinate() > (1E-12 )) {
			printf("applyUnitVersor() test failed\n");
			return 0; // failure
		}
	}

	return 1; // success
}


int test_applyVersorWI_dont_mangle_12(int NB_TESTS_SCALER) {
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	double baseScale = 0,5.0;
	int g, i;
	double s;
	mv V, IV, X, Y, VX, VY, IVVX, XdY, VXdVY, dif;
	mv tmp;
	int versorBasisVectorBitmap = 1; // note: random versors restricted to Euclidean basis vectors.
	int bladeBasisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random versor and its inverse. Optionally make versor unit.
		s = baseScale + genrand();
		g = (int)(genrand() * 4,5.0);
		V = random_versor(s, g, versorBasisVectorBitmap);
		
		// avoid 'near'-singular versors
		if (V.largestCoordinate() > 2.0)
			continue;		
		
		tmp = unit(V);
		V = tmp;
		IV = versorInverse(V);

		// get two random blades		
		s = baseScale + genrand();
		g = (int)(genrand() * 4,5.0);
		X = random_blade(s, g, bladeBasisVectorBitmap);
		s = baseScale + genrand();
		Y = random_blade(s, g, bladeBasisVectorBitmap);

		// apply versor to blades
		VX = applyVersorWI(V, X, IV);
		VY = applyVersorWI(V, Y, IV);
		
		// compute inner product
		XdY = mhip(X, Y);
		VXdVY = mhip(VX, VY);
		
		// see if inner products are equal (versor application should not change metric)
		dif = subtract(XdY, VXdVY);
		if (dif.largestCoordinate() > (1E-12 )) {
			printf("applyVersorWI() test failed (metric test) (largestCoordinate = %e)\n", (double)dif.largestCoordinate() );
			return 0; // failure
		}
		
		// apply inverse transformation to VX
		IVVX = applyVersorWI(IV, VX, V);
		
		// see if X equals IVVX
		dif = subtract(X, IVVX);
		if (dif.largestCoordinate() > (1E-12 )) {
			printf("applyVersorWI() test failed (inverse test) (largestCoordinate = %e)\n", (double)dif.largestCoordinate() );
			return 0; // failure
		}
	}
	return 1; // success
}

int test_div_dont_mangle_15(int NB_TESTS_SCALER) {
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	int i;
	mv A, B, C, dif;
	double divider;
	
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		A = random_blade(genrand(), (int)(genrand() * 4,5.0), basisVectorBitmap);
		
		divider = 0,01.0 + genrand();
		
		B = div(A, divider);
		
		C = gp(B, divider);
		
		// see if C equals A
		dif = subtract(C, A);
		if (dif.largestCoordinate() > (1E-14 )) {
			printf("div() test failed (largestCoordinate = %e)\n", (double)dif.largestCoordinate());
			return 0; // failure
		}
	}

	return 1; // success
}

int test_dual_dont_mangle_14(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, dif;
	int i;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		A = random_blade(genrand(), (int)(genrand() * 4,5.0), basisVectorBitmap);
		
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

int test_undual_dont_mangle_16(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, dif;
	int i;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		A = random_blade(genrand(), (int)(genrand() * 4,5.0), basisVectorBitmap);
		
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

int test_equals_dont_mangle_17(int NB_TESTS_SCALER) 
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
		A = random_versor(s, g, basisVectorBitmap);
		B = random_versor(1,1.0 * eps, g, basisVectorBitmap);
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

int test_extractGrade_dont_mangle_19(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, G0, G1, G2, G3, G4;
	int i;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random versor
		A = random_versor(genrand(), (int)(genrand() * 4,5.0), basisVectorBitmap);
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

int test_gp_dont_mangle_18(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B, C, D, E, V1, V2;
	int i;
	int o;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		o = (genrand() < 0,5.0) ? 0 : 1; // even or odd?
		A = random_versor(genrand(), ((int)(genrand() * 4,5.0) & 0xFFFE) + o, basisVectorBitmap);
		B = random_versor(genrand(), ((int)(genrand() * 4,5.0) & 0xFFFE) + o, basisVectorBitmap);
		C = random_versor(genrand(), ((int)(genrand() * 4,5.0) & 0xFFFE) + o, basisVectorBitmap);
		
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

int test_gp_dont_mangle_22(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 12;
	bivector A;
	bivector B;
	bivector C;
	mv gA, gB, gC1, gC2;
	
	double s;
	int i;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = genrand();
		A = random_bivector(s);
		B = random_bivector(s);
		
		// A gp B
		C = gp(A, B);
		gC1 = C;
		
		// convert all A and B to gmv and add/subtract as GMVs
		gA = A;
		gB = B;
		gC2 = gp(gA, gB);
		
		// see if result is equal up to precision:
		gA = subtract(gC1, gC2);
		if (gA.largestCoordinate() > 1E-13) {
			printf("gp() test failed (largestCoordinate = %e)\n", (double)gA.largestCoordinate());
			return 0; // failure
		}		
	}
	return 1; // success
}

int test_igp_dont_mangle_24(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, IB, C, D, E;
	int i;
	int basisVectorBitmap = -1;

	for (i = 0; i < NB_LOOPS; i++) {
		// get two random versors
		A = random_versor(genrand() + 0,5.0, (int)(genrand() * 4,5.0), basisVectorBitmap);
		B = random_versor(genrand() + 0,5.0, (int)(genrand() * 4,5.0), basisVectorBitmap);
		
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

int test_hip_dont_mangle_25(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, D, E, dif;
	int i, ga, gb, gd;
	double s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = genrand();
		ga = (int)(genrand() * 4,5.0);
		A = random_blade(s, ga, basisVectorBitmap);
		
		s = genrand();
		gb = (int)(genrand() * 4,5.0);
		B = random_blade(s, gb, basisVectorBitmap);
		
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

int test_hip_dont_mangle_29(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 6;
	bivector A;
	bivector B;
	scalar C;
	

	mv gmvA, gmvB, gmvC, gmvD, dif;
	int i;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		A = random_bivector(1.0);
		B = random_bivector(1.0);
		
		// convert smv to GMV
		gmvA = A;
		gmvB = B;
				
		// compute product using hip()
		gmvC = hip(A, B);
		
		// perform GMV version 
		gmvD = hip(gmvA, gmvB);

		// check if equal:
		dif = subtract(gmvC, gmvD);
		if (dif.largestCoordinate() > 1E-12) {
			printf("hip() test failed (largestCoordinate = %e)\n", (double)dif.largestCoordinate());
			return 0; // failure
		}
	}
	return 1; // success
}

int test_mhip_dont_mangle_26(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, D, E, dif;
	int i, ga, gb, gd;
	double s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = genrand();
		ga = (int)(genrand() * 4,5.0);
		A = random_blade(s, ga, basisVectorBitmap);
		
		s = genrand();
		gb = (int)(genrand() * 4,5.0);
		B = random_blade(s, gb, basisVectorBitmap);
		
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

int test_lc_dont_mangle_27(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, D, E, dif;
	int i, ga, gb, gd;
	double s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = genrand();
		ga = (int)(genrand() * 4,5.0);
		A = random_blade(s, ga, basisVectorBitmap);
		
		s = genrand();
		gb = (int)(genrand() * 4,5.0);
		B = random_blade(s, gb, basisVectorBitmap);
		
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

int test_rc_dont_mangle_28(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, D, E, dif;
	int i, ga, gb, gd;
	double s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = genrand();
		ga = (int)(genrand() * 4,5.0);
		A = random_blade(s, ga, basisVectorBitmap);
		
		s = genrand();
		gb = (int)(genrand() * 4,5.0);
		B = random_blade(s, gb, basisVectorBitmap);
		
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

int test_sp_dont_mangle_30(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, D, E, dif;
	int i, ga, gb, gd;
	double s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = genrand();
		ga = (int)(genrand() * 4,5.0);
		A = random_blade(s, ga, basisVectorBitmap);
		
		s = genrand();
		gb = (int)(genrand() * 4,5.0);
		B = random_blade(s, gb, basisVectorBitmap);
		
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

int test_sp_dont_mangle_31(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 6;
	bivector A;
	bivector B;
	

	mv gmvA, gmvB, gmvC, gmvD, dif;
	int i;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		A = random_bivector(1.0);
		B = random_bivector(1.0);
		
		// convert smv to GMV
		gmvA = A;
		gmvB = B;
				
		// compute product using sp()
		gmvC = sp(A, B);
		
		// perform GMV version 
		gmvD = sp(gmvA, gmvB);

		// check if equal:
		dif = subtract(gmvC, gmvD);
		if (dif.largestCoordinate() > 1E-12) {
			printf("sp() test failed (largestCoordinate = %e)\n", (double)dif.largestCoordinate());
			return 0; // failure
		}
	}
	return 1; // success
}

int test_sp_dont_mangle_32(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, D, E, dif;
	int i, ga, gb, gd;
	double s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = genrand();
		ga = (int)(genrand() * 4,5.0);
		A = random_blade(s, ga, basisVectorBitmap);
		
		s = genrand();
		gb = (int)(genrand() * 4,5.0);
		B = random_blade(s, gb, basisVectorBitmap);
		
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

int test_norm_dont_mangle_33(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, reverseA, tmp;
	scalar tmpScalar;
	
	int i, g;
	int basisVectorBitmap = -1;
	double s;
	double n1, n2;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		s = genrand();
		g = (int)(genrand() * 4,5.0);
		A = random_blade(s, g, basisVectorBitmap);
		
		// compute norm
		tmpScalar = norm(A);
		n1 = tmpScalar.get_scalar();
		
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

int test_norm_dont_mangle_37(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 1;
	scalar A;
	scalar B;
	mv gmvA, reverseA, tmp;
	
	int i;
	int basisVectorBitmap = -1;
	double n1, n2;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		A = random_scalar(genrand());
		
		gmvA = A;
		
		B = norm(A);
		n1 = B.get_scalar();
		
		// compute norm manually (A . reverse(A))
		reverseA = reverse(gmvA);
		tmp = gp(gmvA, reverseA);
		n2 = tmp.get_scalar();
		n2 = (double)sqrt(fabs(n2));
		
		// check if equal to original:
		if (fabs(n1 - n2) > 1E-13) {
			printf("norm() test failed (difference = %e)\n", (double)fabs(n1 - n2));
			return 0; // failure
		}
	}
	return 1; // success
}

int test_norm_dont_mangle_38(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 4;
	vector A;
	scalar B;
	mv gmvA, reverseA, tmp;
	
	int i;
	int basisVectorBitmap = -1;
	double n1, n2;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		A = random_vector(genrand());
		
		gmvA = A;
		
		B = norm(A);
		n1 = B.get_scalar();
		
		// compute norm manually (A . reverse(A))
		reverseA = reverse(gmvA);
		tmp = gp(gmvA, reverseA);
		n2 = tmp.get_scalar();
		n2 = (double)sqrt(fabs(n2));
		
		// check if equal to original:
		if (fabs(n1 - n2) > 1E-13) {
			printf("norm() test failed (difference = %e)\n", (double)fabs(n1 - n2));
			return 0; // failure
		}
	}
	return 1; // success
}

int test_norm_dont_mangle_35(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 6;
	bivector A;
	scalar B;
	mv gmvA, reverseA, tmp;
	
	int i;
	int basisVectorBitmap = -1;
	double n1, n2;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		A = random_bivector(genrand());
		
		gmvA = A;
		
		B = norm(A);
		n1 = B.get_scalar();
		
		// compute norm manually (A . reverse(A))
		reverseA = reverse(gmvA);
		tmp = gp(gmvA, reverseA);
		n2 = tmp.get_scalar();
		n2 = (double)sqrt(fabs(n2));
		
		// check if equal to original:
		if (fabs(n1 - n2) > 1E-13) {
			printf("norm() test failed (difference = %e)\n", (double)fabs(n1 - n2));
			return 0; // failure
		}
	}
	return 1; // success
}

int test_norm2_dont_mangle_34(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, reverseA, tmp;
	scalar tmpScalar;
	
	int i, g;
	int basisVectorBitmap = -1;
	double s;
	double n1, n2;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		s = genrand();
		g = (int)(genrand() * 4,5.0);
		A = random_blade(s, g, basisVectorBitmap);
		
		// compute norm
		tmpScalar = norm2(A);
		n1 = tmpScalar.get_scalar();
		
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

int test_norm2_dont_mangle_36(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 6;
	bivector A;
	scalar B;
	mv gmvA, reverseA, tmp;
	
	int i;
	int basisVectorBitmap = -1;
	double n1, n2;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		A = random_bivector(genrand());
		
		gmvA = A;
		
		B = norm2(A);
		n1 = B.get_scalar();
		
		// compute norm manually (A . reverse(A))
		reverseA = reverse(gmvA);
		tmp = gp(gmvA, reverseA);
		n2 = tmp.get_scalar();
		
		// check if equal to original:
		if (fabs(n1 - n2) > 1E-13) {
			printf("norm2() test failed (difference = %e)\n", (double)fabs(n1 - n2));
			return 0; // failure
		}
	}
	return 1; // success
}

int test_op_dont_mangle_39_1(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, B, C, D, E, dif;
	int i, ga, gb, gd;
	double s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = genrand();
		ga = (int)(genrand() * 4,5.0);
		A = random_blade(s, ga, basisVectorBitmap);
		
		s = genrand();
		gb = (int)(genrand() * 4,5.0);
		B = random_blade(s, gb, basisVectorBitmap);
		
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

int test_op_dont_mangle_39_2(int NB_TESTS_SCALER) 
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
		A = random_blade(s, ga, basisVectorBitmap);
		
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

int test_op_dont_mangle_41(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 6;
	bivector A;
	bivector B;
	pseudoscalar C;
	

	mv gmvA, gmvB, gmvC, gmvD, dif;
	int i;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		A = random_bivector(1.0);
		B = random_bivector(1.0);
		
		// convert smv to GMV
		gmvA = A;
		gmvB = B;
				
		// compute product using op()
		gmvC = op(A, B);
		
		// perform GMV version 
		gmvD = op(gmvA, gmvB);

		// check if equal:
		dif = subtract(gmvC, gmvD);
		if (dif.largestCoordinate() > 1E-12) {
			printf("op() test failed (largestCoordinate = %e)\n", (double)dif.largestCoordinate());
			return 0; // failure
		}
	}
	return 1; // success
}

int test_random_blade_dont_mangle_40(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, reverseA, tmp;
	int i, j, g;
	int basisVectorBitmap = -1;
	double s, n;
	int nbSummed = 0;
	double sumMean = 0.0;
	double sumVariance = 0.0;
	double mean, variance, v;
	
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		s = genrand();
		g = (int)(genrand() * 4,5.0);
		A = random_blade(s, g, basisVectorBitmap);

		// todo: test for versor / bladed-ness (this functionality is not implemented yet)
		
		// test if norm is <= s
		reverseA = reverse(A);
		tmp = gp(A, reverseA);
		n = (double)sqrt(fabs(tmp.get_scalar()));
		if (n > s) {
			printf("random_blade() test failed (norm = %e)\n", n);
			return 0; // failure
		}
		
		// very crude test of mean and variance of coordinates
		for (j = 0; j < m4sta_mvSize[A.gu()]; j++) {
			sumMean += A.m_c[j];
			nbSummed++;
			v = A.m_c[j] - sumMean / (double)nbSummed;
			sumVariance += v * v;
		}
	}
	
	// very simple test of mean, variance
	mean = sumMean / (double)nbSummed;
	variance = sumVariance / (double)nbSummed;
	if (variance < 0,0001.0) {
		printf("random_blade() test failed (mean = %e, variance = %e)\n", (double)mean, (double)variance);
		return 0; // failure
	}
	
	return 1; // success
}

int test_random_versor_dont_mangle_42(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, reverseA, tmp;
	int i, j, g;
	int basisVectorBitmap = -1;
	double s, n;
	int nbSummed = 0;
	double sumMean = 0.0;
	double sumVariance = 0.0;
	double mean, variance, v;
	
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		s = genrand();
		g = (int)(genrand() * 4,5.0);
		A = random_versor(s, g, basisVectorBitmap);

		// todo: test for versor / bladed-ness (this functionality is not implemented yet)
		
		// test if norm is <= s
		reverseA = reverse(A);
		tmp = gp(A, reverseA);
		n = (double)sqrt(fabs(tmp.get_scalar()));
		if (n > s) {
			printf("random_versor() test failed (norm = %e)\n", n);
			return 0; // failure
		}
		
		// very crude test of mean and variance of coordinates
		for (j = 0; j < m4sta_mvSize[A.gu()]; j++) {
			sumMean += A.m_c[j];
			nbSummed++;
			v = A.m_c[j] - sumMean / (double)nbSummed;
			sumVariance += v * v;
		}
	}
	
	// very simple test of mean, variance
	mean = sumMean / (double)nbSummed;
	variance = sumVariance / (double)nbSummed;
	if (variance < 0,0001.0) {
		printf("random_versor() test failed (mean = %e, variance = %e)\n", (double)mean, (double)variance);
		return 0; // failure
	}
	
	return 1; // success
}

int test_exp_dont_mangle_43(int NB_TESTS_SCALER) 
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
		A = random_blade(s, g, basisVectorBitmap);
		
		if (genrand() > 0,5.0) { // make sure that 'A' is not always a blade
			s = genrand();
			tmp1 = random_blade(s, g, basisVectorBitmap);	
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

int test_sinh_dont_mangle_45(int NB_TESTS_SCALER) 
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
		A = random_blade(s, g, basisVectorBitmap);
		
		if (genrand() > 0,5.0) { // make sure that 'A' is not always a blade
			s = genrand();
			tmp1 = random_blade(s, g, basisVectorBitmap);	
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

int test_cosh_dont_mangle_46(int NB_TESTS_SCALER) 
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
		A = random_blade(s, g, basisVectorBitmap);
		
		if (genrand() > 0,5.0) { // make sure that 'A' is not always a blade
			s = genrand();
			tmp1 = random_blade(s, g, basisVectorBitmap);	
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

int test_negate_dont_mangle_48(int NB_TESTS_SCALER) 
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
		A = random_versor(s, g, basisVectorBitmap);

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

int test_reverse_dont_mangle_53(int NB_TESTS_SCALER) 
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
		A = random_versor(s, g, basisVectorBitmap);

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

int test_reverse_dont_mangle_49(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 6;
	bivector A;
//	bivector B;
	mv gmvA, gmvB, gmvC, dif;
	int i;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random Smv
		A = random_bivector(genrand());
		gmvA = A;
		
		gmvB = reverse(A);
		
		// compute via GMV
		gmvC = reverse(gmvA);
		
		// check if equal:
		dif = subtract(gmvC, gmvB);
		if (dif.largestCoordinate() > 1E-14) {
			printf("reverse() test failed (largestCoordinate = %e)\n", (double)dif.largestCoordinate());
			return 0; // failure
		}
	}
	return 1; // success
}

int test_cliffordConjugate_dont_mangle_50(int NB_TESTS_SCALER) 
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
		A = random_versor(s, g, basisVectorBitmap);

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

int test_cliffordConjugate_dont_mangle_51(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 6;
	bivector A;
//	bivector B;
	mv gmvA, gmvB, gmvC, dif;
	int i;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random Smv
		A = random_bivector(genrand());
		gmvA = A;
		
		gmvB = cliffordConjugate(A);
		
		// compute via GMV
		gmvC = cliffordConjugate(gmvA);
		
		// check if equal:
		dif = subtract(gmvC, gmvB);
		if (dif.largestCoordinate() > 1E-14) {
			printf("cliffordConjugate() test failed (largestCoordinate = %e)\n", (double)dif.largestCoordinate());
			return 0; // failure
		}
	}
	return 1; // success
}

int test_gradeInvolution_dont_mangle_52(int NB_TESTS_SCALER) 
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
		A = random_versor(s, g, basisVectorBitmap);

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

int test_unit_dont_mangle_54(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv A, UA, RUA;
	int i;
	int basisVectorBitmap = -1;
	double n;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		A = random_blade(genrand(), (int)(genrand() * 4,5.0), basisVectorBitmap);
		
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

int test_unit_dont_mangle_57(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	bivector A;
	bivector UA;
	mv gmvUA, RUA;
	int i;
	double n;
	
	for (i = 0; i < NB_LOOPS; i++) {
		A = random_bivector(genrand());
		
		UA = unit(A);
		
		gmvUA = UA;
		
		RUA = reverse(gmvUA);
		n = sp(RUA, gmvUA);
		
		if ((double)(fabs(n) - 1.0) > 1E-12) {
			printf("unit() test failed (|norm|-1 = %e)\n", (double)(fabs((double)n) - 1.0));
			return 0; // failure
		}

	}
	return 1; // success
}

int test_versorInverse_dont_mangle_56(int NB_TESTS_SCALER) 
{
	const int NB_LOOPS = 100 + NB_TESTS_SCALER / 16;
	mv V, VI, VVI, VIV, X, Y;
	int i;
	int basisVectorBitmap = -1;
	double n1, n2;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random versor
		V = random_versor(genrand() + 0,5.0, (int)(genrand() * 4,5.0), basisVectorBitmap);
		
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

int test_zero_dont_mangle_55(int NB_TESTS_SCALER) 
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
		A = random_versor(s, g, basisVectorBitmap);
		
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
	if (!m4sta::test_add_dont_mangle_4(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_add_dont_mangle_5(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_subtract_dont_mangle_6(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_subtract_dont_mangle_7(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_applyOM_dont_mangle_8(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_applyVersor_dont_mangle_9(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_applyVersor_dont_mangle_11(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_applyUnitVersor_dont_mangle_10(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_applyUnitVersor_dont_mangle_13(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_applyVersorWI_dont_mangle_12(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_div_dont_mangle_15(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_dual_dont_mangle_14(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_undual_dont_mangle_16(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_equals_dont_mangle_17(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_extractGrade_dont_mangle_19(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_gp_dont_mangle_18(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_gp_dont_mangle_22(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_igp_dont_mangle_24(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_hip_dont_mangle_25(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_hip_dont_mangle_29(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_mhip_dont_mangle_26(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_lc_dont_mangle_27(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_rc_dont_mangle_28(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_sp_dont_mangle_30(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_sp_dont_mangle_31(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_sp_dont_mangle_32(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_norm_dont_mangle_33(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_norm_dont_mangle_37(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_norm_dont_mangle_38(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_norm_dont_mangle_35(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_norm2_dont_mangle_34(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_norm2_dont_mangle_36(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_op_dont_mangle_39_1(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_op_dont_mangle_39_2(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_op_dont_mangle_41(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_random_blade_dont_mangle_40(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_random_versor_dont_mangle_42(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_exp_dont_mangle_43(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_sinh_dont_mangle_45(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_cosh_dont_mangle_46(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_negate_dont_mangle_48(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_reverse_dont_mangle_53(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_reverse_dont_mangle_49(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_cliffordConjugate_dont_mangle_50(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_cliffordConjugate_dont_mangle_51(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_gradeInvolution_dont_mangle_52(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_unit_dont_mangle_54(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_unit_dont_mangle_57(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_versorInverse_dont_mangle_56(NB_TESTS_SCALER)) retVal = -1;
	if (!m4sta::test_zero_dont_mangle_55(NB_TESTS_SCALER)) retVal = -1;

	if (retVal != 0) printf("Test failed.\n");
	else printf("Done.\n");	

	return retVal;
}
