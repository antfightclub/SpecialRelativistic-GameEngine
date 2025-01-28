/*
Gaigen 2.5 Test Suite
*/
/*
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <utility> // for std::swap
#include <time.h> /* used to seed random generator */
#include "m4sta.h"
namespace m4sta {

const int m4sta_spaceDim = 4;
const int m4sta_nbGroups = 5;
const bool m4sta_metricEuclidean = false;
const char *m4sta_basisVectorNames[4] = {
	"g0", "g1", "g2", "g3"
};
const int m4sta_grades[] = {GRADE_0, GRADE_1, GRADE_2, GRADE_3, GRADE_4, 0, 0, 0, 0, 0};
const int m4sta_groups[] = {GROUP_0, GROUP_1, GROUP_2, GROUP_3, GROUP_4};
const int m4sta_groupSize[5] = {
	1, 4, 6, 4, 1
};
const int m4sta_mvSize[32] = {
	0, 1, 4, 5, 6, 7, 10, 11, 4, 5, 8, 9, 10, 11, 14, 15, 1, 2, 5, 6, 
	7, 8, 11, 12, 5, 6, 9, 10, 11, 12, 15, 16};
const int m4sta_basisElements[16][5] = {
	{-1},
	{0, -1},
	{1, -1},
	{2, -1},
	{3, -1},
	{0, 1, -1},
	{0, 2, -1},
	{0, 3, -1},
	{1, 2, -1},
	{1, 3, -1},
	{2, 3, -1},
	{1, 2, 3, -1},
	{0, 1, 2, -1},
	{0, 1, 3, -1},
	{0, 2, 3, -1},
	{0, 1, 2, 3, -1}
};
const double m4sta_basisElementSignByIndex[16] =
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
const double m4sta_basisElementSignByBitmap[16] =
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
const int m4sta_basisElementIndexByBitmap[16] =
	{0, 1, 2, 5, 3, 6, 8, 12, 4, 7, 9, 13, 10, 14, 11, 15};
const int m4sta_basisElementBitmapByIndex[16] =
	{0, 1, 2, 4, 8, 3, 5, 9, 6, 10, 12, 14, 7, 11, 13, 15};
const int m4sta_basisElementGradeByBitmap[16] =
	{0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};
const int m4sta_basisElementGroupByBitmap[16] =
	{0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};

const char *g_m4staTypenames[] = 
{
	"mv",
	"double",
	"g0_t",
	"g1_t",
	"g2_t",
	"g3_t",
	"I_t",
	"scalar",
	"vector",
	"bivector",
	"trivector",
	"pseudoscalar",
	"evensubalgebra",
	"oddsubalgebra"
};
g0_t g0;
g1_t g1;
g2_t g2;
g3_t g3;
I_t I;


void ReportUsage::printReport(FILE *F /*= stdout*/, bool includeCount /* = true */) {
	fprintf(F, "Report usage is disabled");
}

/* 
These strings determine how the output of string() is formatted.
You can alter them at runtime using m4sta_setStringFormat().
*/
 
const char *m4sta_string_fp = "%2.2f"; 
const char *m4sta_string_start = ""; 
const char *m4sta_string_end = ""; 
const char *m4sta_string_mul = "*"; 
const char *m4sta_string_wedge = "^"; 
const char *m4sta_string_plus = " + "; 
const char *m4sta_string_minus = " - "; 

void m4sta_setStringFormat(const char *what, const char *format) {
 
	if (!strcmp(what, "fp")) 
		m4sta_string_fp = (format) ? format : "%2.2f"; 
	else if (!strcmp(what, "start")) 
		m4sta_string_start = (format) ? format : ""; 
	else if (!strcmp(what, "end")) 
		m4sta_string_end = (format) ? format : ""; 
	else if (!strcmp(what, "mul")) 
		m4sta_string_mul = (format) ? format : "*"; 
	else if (!strcmp(what, "wedge")) 
		m4sta_string_wedge = (format) ? format : "^"; 
	else if (!strcmp(what, "plus")) 
		m4sta_string_plus = (format) ? format : " + "; 
	else if (!strcmp(what, "minus")) 
		m4sta_string_minus = (format) ? format : " - ";
}



#ifdef WIN32
#define snprintf _snprintf
#pragma warning(disable:4996) /* quit your whining already */
#endif /* WIN32 */
const char *c_str(const mv &V, char *str, int maxLength, const char *fp) 
{
	int stdIdx = 0, l;
	char tmpBuf[256], tmpFloatBuf[256]; 
	int k = 0, bei, ia = 0, s = m4sta_mvSize[V.gu()], p = 0, cnt = 0;
	const double *c = V.getC();

	// set up the floating point precision
	if (fp == NULL) fp = m4sta_string_fp;

	// start the string
	l = snprintf(tmpBuf, 256, "%s", m4sta_string_start);
	if (stdIdx + l <= maxLength) {
		strcpy(str + stdIdx, tmpBuf);
		stdIdx += l;
	}
	else {
		snprintf(str, maxLength, "toString_mv: buffer too small");
		return str;
	}

	// print all coordinates
	for (int i = 0; i <= 5; i++) {
		if (V.gu() & (1 << i)) {
			for (int j = 0; j < m4sta_groupSize[i]; j++) {
				double coord = (double)m4sta_basisElementSignByIndex[ia] *c[k];
				/* goal: print [+|-]V.m_c[k][* basisVector1 ^ ... ^ basisVectorN] */			
				snprintf(tmpFloatBuf, 256, fp, (double)fabs(coord)); // cast to double to force custom float types to Plain Old Data
				if (atof(tmpFloatBuf) != 0.0) {
					l = 0;

					// print [+|-]
					l += snprintf(tmpBuf + l, 256-l, "%s", (coord >= 0.0) 
						? (cnt ? m4sta_string_plus : "")
						: m4sta_string_minus);
						
					// print obj.m_c[k]
					int dummyArg = 0; // prevents compiler warning on some platforms
					l += snprintf(tmpBuf + l, 256-l, tmpFloatBuf, dummyArg);

					if (i) { // if not grade 0, print [* basisVector1 ^ ... ^ basisVectorN]
						l += snprintf(tmpBuf + l, 256-l, "%s", m4sta_string_mul);

						// print all basis vectors
						bei = 0;
						while (m4sta_basisElements[ia][bei] >= 0) {
							l += snprintf(tmpBuf + l, 256-l, "%s%s", (bei) ? m4sta_string_wedge : "", 
							 m4sta_basisVectorNames[m4sta_basisElements[ia][bei]]);
							 bei++;
						}
					}

					// copy all to 'str'
					if (stdIdx + l <= maxLength) {
						strcpy(str + stdIdx, tmpBuf);
						stdIdx += l;
					}
					else {
						snprintf(str, maxLength, "toString_mv: buffer too small");
						return str;
					}
					cnt++;
				}
				k++; ia++;
			}
		}
		else ia += m4sta_groupSize[i];
	}

    // if no coordinates printed: 0
	l = 0;
	if (cnt == 0) {
		l += snprintf(tmpBuf + l, 256-l, "0");
	}

    // end the string
	l += snprintf(tmpBuf + l, 256-l, "%s", m4sta_string_end);
	if (stdIdx + l <= maxLength) {
		strcpy(str + stdIdx, tmpBuf);
		stdIdx += l;
		return str;
	}
	else {
		snprintf(str, maxLength, "toString(): buffer too small\n");
		return str;
	}
}

std::string toString(const mv & obj, const char *fp /* = NULL */) {
	std::string str;
	int strSize = 2048;
	while (strSize <= 1024 * 1024) {
		str.resize(strSize);
		c_str(obj, &(str[0]), strSize-1, fp);
		if (str.find("buffer too small") != std::string::npos) {
			strSize *= 2; // need larger buffer
			continue;
		}
		else break; // done
	}
	str.resize(strlen(&(str[0])));
	return str;
}

mv operator*(const mv &a, const mv &b) {
	return gp(a, b);
}
mv &operator*=(mv &a, const mv &b) {
	return (a = gp(a, b));
}
// def SB:
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
void gp_default_0_0_0(const double *A, const double *B, double *C) {
	C[0] += A[0]*B[0];
}
void gp_default_0_1_1(const double *A, const double *B, double *C) {
	C[0] += A[0]*B[0];
	C[1] += A[0]*B[1];
	C[2] += A[0]*B[2];
	C[3] += A[0]*B[3];
}
void gp_default_0_2_2(const double *A, const double *B, double *C) {
	C[0] += A[0]*B[0];
	C[1] += A[0]*B[1];
	C[2] += A[0]*B[2];
	C[3] += A[0]*B[3];
	C[4] += A[0]*B[4];
	C[5] += A[0]*B[5];
}
void gp_default_0_3_3(const double *A, const double *B, double *C) {
	gp_default_0_1_1(A, B, C);
}
void gp_default_0_4_4(const double *A, const double *B, double *C) {
	gp_default_0_0_0(A, B, C);
}
void gp_default_1_0_1(const double *A, const double *B, double *C) {
	C[0] += A[0]*B[0];
	C[1] += A[1]*B[0];
	C[2] += A[2]*B[0];
	C[3] += A[3]*B[0];
}
void gp_default_1_1_0(const double *A, const double *B, double *C) {
	C[0] += (A[0]*B[0]-A[1]*B[1]-A[2]*B[2]-A[3]*B[3]);
}
void gp_default_1_1_2(const double *A, const double *B, double *C) {
	C[0] += (A[0]*B[1]-A[1]*B[0]);
	C[1] += (A[0]*B[2]-A[2]*B[0]);
	C[2] += (A[0]*B[3]-A[3]*B[0]);
	C[3] += (A[1]*B[2]-A[2]*B[1]);
	C[4] += (A[1]*B[3]-A[3]*B[1]);
	C[5] += (A[2]*B[3]-A[3]*B[2]);
}
void gp_default_1_2_1(const double *A, const double *B, double *C) {
	C[0] += (A[1]*B[0]+A[2]*B[1]+A[3]*B[2]);
	C[1] += (A[0]*B[0]+A[2]*B[3]+A[3]*B[4]);
	C[2] += (A[0]*B[1]-A[1]*B[3]+A[3]*B[5]);
	C[3] += (A[0]*B[2]-A[1]*B[4]-A[2]*B[5]);
}
void gp_default_1_2_3(const double *A, const double *B, double *C) {
	C[0] += (A[1]*B[5]-A[2]*B[4]+A[3]*B[3]);
	C[1] += (A[0]*B[3]-A[1]*B[1]+A[2]*B[0]);
	C[2] += (A[0]*B[4]-A[1]*B[2]+A[3]*B[0]);
	C[3] += (A[0]*B[5]-A[2]*B[2]+A[3]*B[1]);
}
void gp_default_1_3_2(const double *A, const double *B, double *C) {
	C[0] += (-A[2]*B[1]-A[3]*B[2]);
	C[1] += (A[1]*B[1]-A[3]*B[3]);
	C[2] += (A[1]*B[2]+A[2]*B[3]);
	C[3] += (A[0]*B[1]-A[3]*B[0]);
	C[4] += (A[0]*B[2]+A[2]*B[0]);
	C[5] += (A[0]*B[3]-A[1]*B[0]);
}
void gp_default_1_3_4(const double *A, const double *B, double *C) {
	C[0] += (A[0]*B[0]-A[1]*B[3]+A[2]*B[2]-A[3]*B[1]);
}
void gp_default_1_4_3(const double *A, const double *B, double *C) {
	C[0] += A[0]*B[0];
	C[1] += A[3]*B[0];
	C[2] += -A[2]*B[0];
	C[3] += A[1]*B[0];
}
void gp_default_2_0_2(const double *A, const double *B, double *C) {
	C[0] += A[0]*B[0];
	C[1] += A[1]*B[0];
	C[2] += A[2]*B[0];
	C[3] += A[3]*B[0];
	C[4] += A[4]*B[0];
	C[5] += A[5]*B[0];
}
void gp_default_2_1_1(const double *A, const double *B, double *C) {
	C[0] += (-A[0]*B[1]-A[1]*B[2]-A[2]*B[3]);
	C[1] += (-A[0]*B[0]-A[3]*B[2]-A[4]*B[3]);
	C[2] += (-A[1]*B[0]+A[3]*B[1]-A[5]*B[3]);
	C[3] += (-A[2]*B[0]+A[4]*B[1]+A[5]*B[2]);
}
void gp_default_2_1_3(const double *A, const double *B, double *C) {
	C[0] += (A[3]*B[3]-A[4]*B[2]+A[5]*B[1]);
	C[1] += (A[0]*B[2]-A[1]*B[1]+A[3]*B[0]);
	C[2] += (A[0]*B[3]-A[2]*B[1]+A[4]*B[0]);
	C[3] += (A[1]*B[3]-A[2]*B[2]+A[5]*B[0]);
}
void gp_default_2_2_0(const double *A, const double *B, double *C) {
	C[0] += (A[0]*B[0]+A[1]*B[1]+A[2]*B[2]-A[3]*B[3]-A[4]*B[4]-A[5]*B[5]);
}
void gp_default_2_2_2(const double *A, const double *B, double *C) {
	C[0] += (A[1]*B[3]+A[2]*B[4]-A[3]*B[1]-A[4]*B[2]);
	C[1] += (-A[0]*B[3]+A[2]*B[5]+A[3]*B[0]-A[5]*B[2]);
	C[2] += (-A[0]*B[4]-A[1]*B[5]+A[4]*B[0]+A[5]*B[1]);
	C[3] += (-A[0]*B[1]+A[1]*B[0]+A[4]*B[5]-A[5]*B[4]);
	C[4] += (-A[0]*B[2]+A[2]*B[0]-A[3]*B[5]+A[5]*B[3]);
	C[5] += (-A[1]*B[2]+A[2]*B[1]+A[3]*B[4]-A[4]*B[3]);
}
void gp_default_2_2_4(const double *A, const double *B, double *C) {
	C[0] += (A[0]*B[5]-A[1]*B[4]+A[2]*B[3]+A[3]*B[2]-A[4]*B[1]+A[5]*B[0]);
}
void gp_default_2_3_1(const double *A, const double *B, double *C) {
	C[0] += (-A[3]*B[1]-A[4]*B[2]-A[5]*B[3]);
	C[1] += (-A[1]*B[1]-A[2]*B[2]-A[5]*B[0]);
	C[2] += (A[0]*B[1]-A[2]*B[3]+A[4]*B[0]);
	C[3] += (A[0]*B[2]+A[1]*B[3]-A[3]*B[0]);
}
void gp_default_2_3_3(const double *A, const double *B, double *C) {
	C[0] += (-A[0]*B[3]+A[1]*B[2]-A[2]*B[1]);
	C[1] += (-A[2]*B[0]+A[4]*B[3]-A[5]*B[2]);
	C[2] += (A[1]*B[0]-A[3]*B[3]+A[5]*B[1]);
	C[3] += (-A[0]*B[0]+A[3]*B[2]-A[4]*B[1]);
}
void gp_default_2_4_2(const double *A, const double *B, double *C) {
	C[0] += -A[5]*B[0];
	C[1] += A[4]*B[0];
	C[2] += -A[3]*B[0];
	C[3] += A[2]*B[0];
	C[4] += -A[1]*B[0];
	C[5] += A[0]*B[0];
}
void gp_default_3_0_3(const double *A, const double *B, double *C) {
	gp_default_1_0_1(A, B, C);
}
void gp_default_3_1_2(const double *A, const double *B, double *C) {
	C[0] += (-A[1]*B[2]-A[2]*B[3]);
	C[1] += (A[1]*B[1]-A[3]*B[3]);
	C[2] += (A[2]*B[1]+A[3]*B[2]);
	C[3] += (-A[0]*B[3]+A[1]*B[0]);
	C[4] += (A[0]*B[2]+A[2]*B[0]);
	C[5] += (-A[0]*B[1]+A[3]*B[0]);
}
void gp_default_3_1_4(const double *A, const double *B, double *C) {
	C[0] += (-A[0]*B[0]+A[1]*B[3]-A[2]*B[2]+A[3]*B[1]);
}
void gp_default_3_2_1(const double *A, const double *B, double *C) {
	C[0] += (-A[1]*B[3]-A[2]*B[4]-A[3]*B[5]);
	C[1] += (-A[0]*B[5]-A[1]*B[1]-A[2]*B[2]);
	C[2] += (A[0]*B[4]+A[1]*B[0]-A[3]*B[2]);
	C[3] += (-A[0]*B[3]+A[2]*B[0]+A[3]*B[1]);
}
void gp_default_3_2_3(const double *A, const double *B, double *C) {
	C[0] += (A[1]*B[2]-A[2]*B[1]+A[3]*B[0]);
	C[1] += (A[0]*B[2]+A[2]*B[5]-A[3]*B[4]);
	C[2] += (-A[0]*B[1]-A[1]*B[5]+A[3]*B[3]);
	C[3] += (A[0]*B[0]+A[1]*B[4]-A[2]*B[3]);
}
void gp_default_3_3_0(const double *A, const double *B, double *C) {
	gp_default_1_1_0(A, B, C);
}
void gp_default_3_3_2(const double *A, const double *B, double *C) {
	C[0] += (A[0]*B[3]-A[3]*B[0]);
	C[1] += (-A[0]*B[2]+A[2]*B[0]);
	C[2] += (A[0]*B[1]-A[1]*B[0]);
	C[3] += (A[2]*B[3]-A[3]*B[2]);
	C[4] += (-A[1]*B[3]+A[3]*B[1]);
	C[5] += (A[1]*B[2]-A[2]*B[1]);
}
void gp_default_3_4_1(const double *A, const double *B, double *C) {
	C[0] += -A[0]*B[0];
	C[1] += -A[3]*B[0];
	C[2] += A[2]*B[0];
	C[3] += -A[1]*B[0];
}
void gp_default_4_0_4(const double *A, const double *B, double *C) {
	gp_default_0_0_0(A, B, C);
}
void gp_default_4_1_3(const double *A, const double *B, double *C) {
	C[0] += -A[0]*B[0];
	C[1] += -A[0]*B[3];
	C[2] += A[0]*B[2];
	C[3] += -A[0]*B[1];
}
void gp_default_4_2_2(const double *A, const double *B, double *C) {
	C[0] += -A[0]*B[5];
	C[1] += A[0]*B[4];
	C[2] += -A[0]*B[3];
	C[3] += A[0]*B[2];
	C[4] += -A[0]*B[1];
	C[5] += A[0]*B[0];
}
void gp_default_4_3_1(const double *A, const double *B, double *C) {
	C[0] += A[0]*B[0];
	C[1] += A[0]*B[3];
	C[2] += -A[0]*B[2];
	C[3] += A[0]*B[1];
}
void gp_default_4_4_0(const double *A, const double *B, double *C) {
	C[0] += -A[0]*B[0];
}
void gp__internal_euclidean_metric__0_0_0(const double *A, const double *B, double *C) {
	C[0] += A[0]*B[0];
}
void gp__internal_euclidean_metric__0_1_1(const double *A, const double *B, double *C) {
	C[0] += A[0]*B[0];
	C[1] += A[0]*B[1];
	C[2] += A[0]*B[2];
	C[3] += A[0]*B[3];
}
void gp__internal_euclidean_metric__0_2_2(const double *A, const double *B, double *C) {
	C[0] += A[0]*B[0];
	C[1] += A[0]*B[1];
	C[2] += A[0]*B[2];
	C[3] += A[0]*B[3];
	C[4] += A[0]*B[4];
	C[5] += A[0]*B[5];
}
void gp__internal_euclidean_metric__0_3_3(const double *A, const double *B, double *C) {
	gp__internal_euclidean_metric__0_1_1(A, B, C);
}
void gp__internal_euclidean_metric__0_4_4(const double *A, const double *B, double *C) {
	gp__internal_euclidean_metric__0_0_0(A, B, C);
}
void gp__internal_euclidean_metric__1_0_1(const double *A, const double *B, double *C) {
	C[0] += A[0]*B[0];
	C[1] += A[1]*B[0];
	C[2] += A[2]*B[0];
	C[3] += A[3]*B[0];
}
void gp__internal_euclidean_metric__1_1_0(const double *A, const double *B, double *C) {
	C[0] += (A[0]*B[0]+A[1]*B[1]+A[2]*B[2]+A[3]*B[3]);
}
void gp__internal_euclidean_metric__1_1_2(const double *A, const double *B, double *C) {
	C[0] += (A[0]*B[1]-A[1]*B[0]);
	C[1] += (A[0]*B[2]-A[2]*B[0]);
	C[2] += (A[0]*B[3]-A[3]*B[0]);
	C[3] += (A[1]*B[2]-A[2]*B[1]);
	C[4] += (A[1]*B[3]-A[3]*B[1]);
	C[5] += (A[2]*B[3]-A[3]*B[2]);
}
void gp__internal_euclidean_metric__1_2_1(const double *A, const double *B, double *C) {
	C[0] += (-A[1]*B[0]-A[2]*B[1]-A[3]*B[2]);
	C[1] += (A[0]*B[0]-A[2]*B[3]-A[3]*B[4]);
	C[2] += (A[0]*B[1]+A[1]*B[3]-A[3]*B[5]);
	C[3] += (A[0]*B[2]+A[1]*B[4]+A[2]*B[5]);
}
void gp__internal_euclidean_metric__1_2_3(const double *A, const double *B, double *C) {
	C[0] += (A[1]*B[5]-A[2]*B[4]+A[3]*B[3]);
	C[1] += (A[0]*B[3]-A[1]*B[1]+A[2]*B[0]);
	C[2] += (A[0]*B[4]-A[1]*B[2]+A[3]*B[0]);
	C[3] += (A[0]*B[5]-A[2]*B[2]+A[3]*B[1]);
}
void gp__internal_euclidean_metric__1_3_2(const double *A, const double *B, double *C) {
	C[0] += (A[2]*B[1]+A[3]*B[2]);
	C[1] += (-A[1]*B[1]+A[3]*B[3]);
	C[2] += (-A[1]*B[2]-A[2]*B[3]);
	C[3] += (A[0]*B[1]+A[3]*B[0]);
	C[4] += (A[0]*B[2]-A[2]*B[0]);
	C[5] += (A[0]*B[3]+A[1]*B[0]);
}
void gp__internal_euclidean_metric__1_3_4(const double *A, const double *B, double *C) {
	C[0] += (A[0]*B[0]-A[1]*B[3]+A[2]*B[2]-A[3]*B[1]);
}
void gp__internal_euclidean_metric__1_4_3(const double *A, const double *B, double *C) {
	C[0] += A[0]*B[0];
	C[1] += -A[3]*B[0];
	C[2] += A[2]*B[0];
	C[3] += -A[1]*B[0];
}
void gp__internal_euclidean_metric__2_0_2(const double *A, const double *B, double *C) {
	C[0] += A[0]*B[0];
	C[1] += A[1]*B[0];
	C[2] += A[2]*B[0];
	C[3] += A[3]*B[0];
	C[4] += A[4]*B[0];
	C[5] += A[5]*B[0];
}
void gp__internal_euclidean_metric__2_1_1(const double *A, const double *B, double *C) {
	C[0] += (A[0]*B[1]+A[1]*B[2]+A[2]*B[3]);
	C[1] += (-A[0]*B[0]+A[3]*B[2]+A[4]*B[3]);
	C[2] += (-A[1]*B[0]-A[3]*B[1]+A[5]*B[3]);
	C[3] += (-A[2]*B[0]-A[4]*B[1]-A[5]*B[2]);
}
void gp__internal_euclidean_metric__2_1_3(const double *A, const double *B, double *C) {
	C[0] += (A[3]*B[3]-A[4]*B[2]+A[5]*B[1]);
	C[1] += (A[0]*B[2]-A[1]*B[1]+A[3]*B[0]);
	C[2] += (A[0]*B[3]-A[2]*B[1]+A[4]*B[0]);
	C[3] += (A[1]*B[3]-A[2]*B[2]+A[5]*B[0]);
}
void gp__internal_euclidean_metric__2_2_0(const double *A, const double *B, double *C) {
	C[0] += (-A[0]*B[0]-A[1]*B[1]-A[2]*B[2]-A[3]*B[3]-A[4]*B[4]-A[5]*B[5]);
}
void gp__internal_euclidean_metric__2_2_2(const double *A, const double *B, double *C) {
	C[0] += (-A[1]*B[3]-A[2]*B[4]+A[3]*B[1]+A[4]*B[2]);
	C[1] += (A[0]*B[3]-A[2]*B[5]-A[3]*B[0]+A[5]*B[2]);
	C[2] += (A[0]*B[4]+A[1]*B[5]-A[4]*B[0]-A[5]*B[1]);
	C[3] += (-A[0]*B[1]+A[1]*B[0]-A[4]*B[5]+A[5]*B[4]);
	C[4] += (-A[0]*B[2]+A[2]*B[0]+A[3]*B[5]-A[5]*B[3]);
	C[5] += (-A[1]*B[2]+A[2]*B[1]-A[3]*B[4]+A[4]*B[3]);
}
void gp__internal_euclidean_metric__2_2_4(const double *A, const double *B, double *C) {
	C[0] += (A[0]*B[5]-A[1]*B[4]+A[2]*B[3]+A[3]*B[2]-A[4]*B[1]+A[5]*B[0]);
}
void gp__internal_euclidean_metric__2_3_1(const double *A, const double *B, double *C) {
	C[0] += (-A[3]*B[1]-A[4]*B[2]-A[5]*B[3]);
	C[1] += (A[1]*B[1]+A[2]*B[2]-A[5]*B[0]);
	C[2] += (-A[0]*B[1]+A[2]*B[3]+A[4]*B[0]);
	C[3] += (-A[0]*B[2]-A[1]*B[3]-A[3]*B[0]);
}
void gp__internal_euclidean_metric__2_3_3(const double *A, const double *B, double *C) {
	C[0] += (-A[0]*B[3]+A[1]*B[2]-A[2]*B[1]);
	C[1] += (A[2]*B[0]-A[4]*B[3]+A[5]*B[2]);
	C[2] += (-A[1]*B[0]+A[3]*B[3]-A[5]*B[1]);
	C[3] += (A[0]*B[0]-A[3]*B[2]+A[4]*B[1]);
}
void gp__internal_euclidean_metric__2_4_2(const double *A, const double *B, double *C) {
	C[0] += -A[5]*B[0];
	C[1] += A[4]*B[0];
	C[2] += -A[3]*B[0];
	C[3] += -A[2]*B[0];
	C[4] += A[1]*B[0];
	C[5] += -A[0]*B[0];
}
void gp__internal_euclidean_metric__3_0_3(const double *A, const double *B, double *C) {
	gp__internal_euclidean_metric__1_0_1(A, B, C);
}
void gp__internal_euclidean_metric__3_1_2(const double *A, const double *B, double *C) {
	C[0] += (A[1]*B[2]+A[2]*B[3]);
	C[1] += (-A[1]*B[1]+A[3]*B[3]);
	C[2] += (-A[2]*B[1]-A[3]*B[2]);
	C[3] += (A[0]*B[3]+A[1]*B[0]);
	C[4] += (-A[0]*B[2]+A[2]*B[0]);
	C[5] += (A[0]*B[1]+A[3]*B[0]);
}
void gp__internal_euclidean_metric__3_1_4(const double *A, const double *B, double *C) {
	C[0] += (-A[0]*B[0]+A[1]*B[3]-A[2]*B[2]+A[3]*B[1]);
}
void gp__internal_euclidean_metric__3_2_1(const double *A, const double *B, double *C) {
	C[0] += (-A[1]*B[3]-A[2]*B[4]-A[3]*B[5]);
	C[1] += (-A[0]*B[5]+A[1]*B[1]+A[2]*B[2]);
	C[2] += (A[0]*B[4]-A[1]*B[0]+A[3]*B[2]);
	C[3] += (-A[0]*B[3]-A[2]*B[0]-A[3]*B[1]);
}
void gp__internal_euclidean_metric__3_2_3(const double *A, const double *B, double *C) {
	C[0] += (A[1]*B[2]-A[2]*B[1]+A[3]*B[0]);
	C[1] += (-A[0]*B[2]-A[2]*B[5]+A[3]*B[4]);
	C[2] += (A[0]*B[1]+A[1]*B[5]-A[3]*B[3]);
	C[3] += (-A[0]*B[0]-A[1]*B[4]+A[2]*B[3]);
}
void gp__internal_euclidean_metric__3_3_0(const double *A, const double *B, double *C) {
	C[0] += (-A[0]*B[0]-A[1]*B[1]-A[2]*B[2]-A[3]*B[3]);
}
void gp__internal_euclidean_metric__3_3_2(const double *A, const double *B, double *C) {
	C[0] += (A[0]*B[3]-A[3]*B[0]);
	C[1] += (-A[0]*B[2]+A[2]*B[0]);
	C[2] += (A[0]*B[1]-A[1]*B[0]);
	C[3] += (-A[2]*B[3]+A[3]*B[2]);
	C[4] += (A[1]*B[3]-A[3]*B[1]);
	C[5] += (-A[1]*B[2]+A[2]*B[1]);
}
void gp__internal_euclidean_metric__3_4_1(const double *A, const double *B, double *C) {
	gp__internal_euclidean_metric__1_4_3(A, B, C);
}
void gp__internal_euclidean_metric__4_0_4(const double *A, const double *B, double *C) {
	gp__internal_euclidean_metric__0_0_0(A, B, C);
}
void gp__internal_euclidean_metric__4_1_3(const double *A, const double *B, double *C) {
	C[0] += -A[0]*B[0];
	C[1] += A[0]*B[3];
	C[2] += -A[0]*B[2];
	C[3] += A[0]*B[1];
}
void gp__internal_euclidean_metric__4_2_2(const double *A, const double *B, double *C) {
	C[0] += -A[0]*B[5];
	C[1] += A[0]*B[4];
	C[2] += -A[0]*B[3];
	C[3] += -A[0]*B[2];
	C[4] += A[0]*B[1];
	C[5] += -A[0]*B[0];
}
void gp__internal_euclidean_metric__4_3_1(const double *A, const double *B, double *C) {
	gp__internal_euclidean_metric__4_1_3(A, B, C);
}
void gp__internal_euclidean_metric__4_4_0(const double *A, const double *B, double *C) {
	gp__internal_euclidean_metric__0_0_0(A, B, C);
}
void copyGroup_0(const double *A, double *C) {
	C[0] = A[0];
}
void copyMul_0(const double *A, double *C, double s) {
	C[0] = A[0]*s;
}
void copyDiv_0(const double *A, double *C, double s) {
	C[0] = A[0]/s;
}
void add_0(const double *A, double *C) {
	C[0] += A[0];
}
void sub_0(const double *A, double *C) {
	C[0] -= A[0];
}
void neg_0(const double *A, double *C) {
	C[0] = -A[0];
}
void add2_0_0(const double *A, const double *B, double *C) {
	C[0] = (A[0]+B[0]);
}
void sub2_0_0(const double *A, const double *B, double *C) {
	C[0] = (A[0]-B[0]);
}
void hp_0_0(const double *A, const double *B, double *C) {
	C[0] = A[0]*B[0];
}
void ihp_0_0(const double *A, const double *B, double *C) {
	C[0] = A[0]/((B[0]));
}
bool equals_0_0(const double *A, const double *B, double eps) {
		if (((A[0] - B[0]) < -eps) || ((A[0] - B[0]) > eps)) return false;
	return true;
}
bool zeroGroup_0(const double *A, double eps) {
		if ((A[0] < -eps) || (A[0] > eps)) return false;
		return true;
}
void copyGroup_1(const double *A, double *C) {
	C[0] = A[0];
	C[1] = A[1];
	C[2] = A[2];
	C[3] = A[3];
}
void copyMul_1(const double *A, double *C, double s) {
	C[0] = A[0]*s;
	C[1] = A[1]*s;
	C[2] = A[2]*s;
	C[3] = A[3]*s;
}
void copyDiv_1(const double *A, double *C, double s) {
	C[0] = A[0]/s;
	C[1] = A[1]/s;
	C[2] = A[2]/s;
	C[3] = A[3]/s;
}
void add_1(const double *A, double *C) {
	C[0] += A[0];
	C[1] += A[1];
	C[2] += A[2];
	C[3] += A[3];
}
void sub_1(const double *A, double *C) {
	C[0] -= A[0];
	C[1] -= A[1];
	C[2] -= A[2];
	C[3] -= A[3];
}
void neg_1(const double *A, double *C) {
	C[0] = -A[0];
	C[1] = -A[1];
	C[2] = -A[2];
	C[3] = -A[3];
}
void add2_1_1(const double *A, const double *B, double *C) {
	C[0] = (A[0]+B[0]);
	C[1] = (A[1]+B[1]);
	C[2] = (A[2]+B[2]);
	C[3] = (A[3]+B[3]);
}
void sub2_1_1(const double *A, const double *B, double *C) {
	C[0] = (A[0]-B[0]);
	C[1] = (A[1]-B[1]);
	C[2] = (A[2]-B[2]);
	C[3] = (A[3]-B[3]);
}
void hp_1_1(const double *A, const double *B, double *C) {
	C[0] = A[0]*B[0];
	C[1] = A[1]*B[1];
	C[2] = A[2]*B[2];
	C[3] = A[3]*B[3];
}
void ihp_1_1(const double *A, const double *B, double *C) {
	C[0] = A[0]/((B[0]));
	C[1] = A[1]/((B[1]));
	C[2] = A[2]/((B[2]));
	C[3] = A[3]/((B[3]));
}
bool equals_1_1(const double *A, const double *B, double eps) {
		if (((A[0] - B[0]) < -eps) || ((A[0] - B[0]) > eps)) return false;
		if (((A[1] - B[1]) < -eps) || ((A[1] - B[1]) > eps)) return false;
		if (((A[2] - B[2]) < -eps) || ((A[2] - B[2]) > eps)) return false;
		if (((A[3] - B[3]) < -eps) || ((A[3] - B[3]) > eps)) return false;
	return true;
}
bool zeroGroup_1(const double *A, double eps) {
		if ((A[0] < -eps) || (A[0] > eps)) return false;
		if ((A[1] < -eps) || (A[1] > eps)) return false;
		if ((A[2] < -eps) || (A[2] > eps)) return false;
		if ((A[3] < -eps) || (A[3] > eps)) return false;
		return true;
}
void copyGroup_2(const double *A, double *C) {
	C[0] = A[0];
	C[1] = A[1];
	C[2] = A[2];
	C[3] = A[3];
	C[4] = A[4];
	C[5] = A[5];
}
void copyMul_2(const double *A, double *C, double s) {
	C[0] = A[0]*s;
	C[1] = A[1]*s;
	C[2] = A[2]*s;
	C[3] = A[3]*s;
	C[4] = A[4]*s;
	C[5] = A[5]*s;
}
void copyDiv_2(const double *A, double *C, double s) {
	C[0] = A[0]/s;
	C[1] = A[1]/s;
	C[2] = A[2]/s;
	C[3] = A[3]/s;
	C[4] = A[4]/s;
	C[5] = A[5]/s;
}
void add_2(const double *A, double *C) {
	C[0] += A[0];
	C[1] += A[1];
	C[2] += A[2];
	C[3] += A[3];
	C[4] += A[4];
	C[5] += A[5];
}
void sub_2(const double *A, double *C) {
	C[0] -= A[0];
	C[1] -= A[1];
	C[2] -= A[2];
	C[3] -= A[3];
	C[4] -= A[4];
	C[5] -= A[5];
}
void neg_2(const double *A, double *C) {
	C[0] = -A[0];
	C[1] = -A[1];
	C[2] = -A[2];
	C[3] = -A[3];
	C[4] = -A[4];
	C[5] = -A[5];
}
void add2_2_2(const double *A, const double *B, double *C) {
	C[0] = (A[0]+B[0]);
	C[1] = (A[1]+B[1]);
	C[2] = (A[2]+B[2]);
	C[3] = (A[3]+B[3]);
	C[4] = (A[4]+B[4]);
	C[5] = (A[5]+B[5]);
}
void sub2_2_2(const double *A, const double *B, double *C) {
	C[0] = (A[0]-B[0]);
	C[1] = (A[1]-B[1]);
	C[2] = (A[2]-B[2]);
	C[3] = (A[3]-B[3]);
	C[4] = (A[4]-B[4]);
	C[5] = (A[5]-B[5]);
}
void hp_2_2(const double *A, const double *B, double *C) {
	C[0] = A[0]*B[0];
	C[1] = A[1]*B[1];
	C[2] = A[2]*B[2];
	C[3] = A[3]*B[3];
	C[4] = A[4]*B[4];
	C[5] = A[5]*B[5];
}
void ihp_2_2(const double *A, const double *B, double *C) {
	C[0] = A[0]/((B[0]));
	C[1] = A[1]/((B[1]));
	C[2] = A[2]/((B[2]));
	C[3] = A[3]/((B[3]));
	C[4] = A[4]/((B[4]));
	C[5] = A[5]/((B[5]));
}
bool equals_2_2(const double *A, const double *B, double eps) {
		if (((A[0] - B[0]) < -eps) || ((A[0] - B[0]) > eps)) return false;
		if (((A[1] - B[1]) < -eps) || ((A[1] - B[1]) > eps)) return false;
		if (((A[2] - B[2]) < -eps) || ((A[2] - B[2]) > eps)) return false;
		if (((A[3] - B[3]) < -eps) || ((A[3] - B[3]) > eps)) return false;
		if (((A[4] - B[4]) < -eps) || ((A[4] - B[4]) > eps)) return false;
		if (((A[5] - B[5]) < -eps) || ((A[5] - B[5]) > eps)) return false;
	return true;
}
bool zeroGroup_2(const double *A, double eps) {
		if ((A[0] < -eps) || (A[0] > eps)) return false;
		if ((A[1] < -eps) || (A[1] > eps)) return false;
		if ((A[2] < -eps) || (A[2] > eps)) return false;
		if ((A[3] < -eps) || (A[3] > eps)) return false;
		if ((A[4] < -eps) || (A[4] > eps)) return false;
		if ((A[5] < -eps) || (A[5] > eps)) return false;
		return true;
}
void copyGroup_3(const double *A, double *C) {
	copyGroup_1(A, C);
}
void copyMul_3(const double *A, double *C, double s) {
	copyMul_1(A, C, s);
}
void copyDiv_3(const double *A, double *C, double s) {
	copyDiv_1(A, C, s);
}
void add_3(const double *A, double *C) {
	add_1(A, C);
}
void sub_3(const double *A, double *C) {
	sub_1(A, C);
}
void neg_3(const double *A, double *C) {
	neg_1(A, C);
}
void add2_3_3(const double *A, const double *B, double *C) {
	add2_1_1(A, B, C);
}
void sub2_3_3(const double *A, const double *B, double *C) {
	sub2_1_1(A, B, C);
}
void hp_3_3(const double *A, const double *B, double *C) {
	hp_1_1(A, B, C);
}
void ihp_3_3(const double *A, const double *B, double *C) {
	ihp_1_1(A, B, C);
}
bool equals_3_3(const double *A, const double *B, double eps) {
	return equals_1_1(A, B, eps);
}
bool zeroGroup_3(const double *A, double eps) {
	return zeroGroup_1(A, eps);
}
void copyGroup_4(const double *A, double *C) {
	copyGroup_0(A, C);
}
void copyMul_4(const double *A, double *C, double s) {
	copyMul_0(A, C, s);
}
void copyDiv_4(const double *A, double *C, double s) {
	copyDiv_0(A, C, s);
}
void add_4(const double *A, double *C) {
	add_0(A, C);
}
void sub_4(const double *A, double *C) {
	sub_0(A, C);
}
void neg_4(const double *A, double *C) {
	neg_0(A, C);
}
void add2_4_4(const double *A, const double *B, double *C) {
	add2_0_0(A, B, C);
}
void sub2_4_4(const double *A, const double *B, double *C) {
	sub2_0_0(A, B, C);
}
void hp_4_4(const double *A, const double *B, double *C) {
	hp_0_0(A, B, C);
}
void ihp_4_4(const double *A, const double *B, double *C) {
	ihp_0_0(A, B, C);
}
bool equals_4_4(const double *A, const double *B, double eps) {
	return equals_0_0(A, B, eps);
}
bool zeroGroup_4(const double *A, double eps) {
	return zeroGroup_0(A, eps);
}
void dual_default_0_4(const double *A, double *C) {
	C[0] = -A[0];
}
void undual_default_0_4(const double *A, double *C) {
	C[0] = A[0];
}
void dual_default_1_3(const double *A, double *C) {
	C[0] = -A[0];
	C[1] = -A[3];
	C[2] = A[2];
	C[3] = -A[1];
}
void undual_default_1_3(const double *A, double *C) {
	C[0] = A[0];
	C[1] = A[3];
	C[2] = -A[2];
	C[3] = A[1];
}
void dual_default_2_2(const double *A, double *C) {
	C[0] = A[5];
	C[1] = -A[4];
	C[2] = A[3];
	C[3] = -A[2];
	C[4] = A[1];
	C[5] = -A[0];
}
void undual_default_2_2(const double *A, double *C) {
	C[0] = -A[5];
	C[1] = A[4];
	C[2] = -A[3];
	C[3] = A[2];
	C[4] = -A[1];
	C[5] = A[0];
}
void dual_default_3_1(const double *A, double *C) {
	undual_default_1_3(A, C);
}
void undual_default_3_1(const double *A, double *C) {
	dual_default_1_3(A, C);
}
void dual_default_4_0(const double *A, double *C) {
	undual_default_0_4(A, C);
}
void undual_default_4_0(const double *A, double *C) {
	dual_default_0_4(A, C);
}
void dual__internal_euclidean_metric__0_4(const double *A, double *C) {
	undual_default_0_4(A, C);
}
void undual__internal_euclidean_metric__0_4(const double *A, double *C) {
	undual_default_0_4(A, C);
}
void dual__internal_euclidean_metric__1_3(const double *A, double *C) {
	C[0] = A[0];
	C[1] = -A[3];
	C[2] = A[2];
	C[3] = -A[1];
}
void undual__internal_euclidean_metric__1_3(const double *A, double *C) {
	dual__internal_euclidean_metric__1_3(A, C);
}
void dual__internal_euclidean_metric__2_2(const double *A, double *C) {
	C[0] = -A[5];
	C[1] = A[4];
	C[2] = -A[3];
	C[3] = -A[2];
	C[4] = A[1];
	C[5] = -A[0];
}
void undual__internal_euclidean_metric__2_2(const double *A, double *C) {
	dual__internal_euclidean_metric__2_2(A, C);
}
void dual__internal_euclidean_metric__3_1(const double *A, double *C) {
	dual__internal_euclidean_metric__1_3(A, C);
}
void undual__internal_euclidean_metric__3_1(const double *A, double *C) {
	dual__internal_euclidean_metric__1_3(A, C);
}
void dual__internal_euclidean_metric__4_0(const double *A, double *C) {
	undual_default_0_4(A, C);
}
void undual__internal_euclidean_metric__4_0(const double *A, double *C) {
	undual_default_0_4(A, C);
}
void applyGomGmv_1_1(const om &O, const double *A, double *C) {
	C[0] = (A[0]*O.m_m1[0]+A[1]*O.m_m1[1]+A[2]*O.m_m1[2]+A[3]*O.m_m1[3]);
	C[1] = (A[0]*O.m_m1[4]+A[1]*O.m_m1[5]+A[2]*O.m_m1[6]+A[3]*O.m_m1[7]);
	C[2] = (A[0]*O.m_m1[8]+A[1]*O.m_m1[9]+A[2]*O.m_m1[10]+A[3]*O.m_m1[11]);
	C[3] = (A[0]*O.m_m1[12]+A[1]*O.m_m1[13]+A[2]*O.m_m1[14]+A[3]*O.m_m1[15]);
}
void applyGomGmv_2_2(const om &O, const double *A, double *C) {
	C[0] = (A[0]*O.m_m2[0]+A[1]*O.m_m2[1]+A[2]*O.m_m2[3]+A[3]*O.m_m2[2]+A[4]*O.m_m2[4]+A[5]*O.m_m2[5]);
	C[1] = (A[0]*O.m_m2[6]+A[1]*O.m_m2[7]+A[2]*O.m_m2[9]+A[3]*O.m_m2[8]+A[4]*O.m_m2[10]+A[5]*O.m_m2[11]);
	C[2] = (A[0]*O.m_m2[18]+A[1]*O.m_m2[19]+A[2]*O.m_m2[21]+A[3]*O.m_m2[20]+A[4]*O.m_m2[22]+A[5]*O.m_m2[23]);
	C[3] = (A[0]*O.m_m2[12]+A[1]*O.m_m2[13]+A[2]*O.m_m2[15]+A[3]*O.m_m2[14]+A[4]*O.m_m2[16]+A[5]*O.m_m2[17]);
	C[4] = (A[0]*O.m_m2[24]+A[1]*O.m_m2[25]+A[2]*O.m_m2[27]+A[3]*O.m_m2[26]+A[4]*O.m_m2[28]+A[5]*O.m_m2[29]);
	C[5] = (A[0]*O.m_m2[30]+A[1]*O.m_m2[31]+A[2]*O.m_m2[33]+A[3]*O.m_m2[32]+A[4]*O.m_m2[34]+A[5]*O.m_m2[35]);
}
void applyGomGmv_3_3(const om &O, const double *A, double *C) {
	C[0] = (A[0]*O.m_m3[15]+A[1]*O.m_m3[12]+A[2]*O.m_m3[13]+A[3]*O.m_m3[14]);
	C[1] = (A[0]*O.m_m3[3]+A[1]*O.m_m3[0]+A[2]*O.m_m3[1]+A[3]*O.m_m3[2]);
	C[2] = (A[0]*O.m_m3[7]+A[1]*O.m_m3[4]+A[2]*O.m_m3[5]+A[3]*O.m_m3[6]);
	C[3] = (A[0]*O.m_m3[11]+A[1]*O.m_m3[8]+A[2]*O.m_m3[9]+A[3]*O.m_m3[10]);
}
void applyGomGmv_4_4(const om &O, const double *A, double *C) {
	C[0] = A[0]*O.m_m4[0];
}
void mv::set() {
	setGroupUsage(0);
}
void mv::set(double val) {
	setGroupUsage(1);
	m_c[0] = val;
}
void mv::set(int gu, const double *arr) {
	setGroupUsage(gu);
	m4sta::copy_N(m_c, arr, m4sta_mvSize[gu]);

}
void mv::set(const mv &src) {
	setGroupUsage(src.gu());
	const double*srcC = src.getC();
	m4sta::copy_N(m_c, srcC, m4sta_mvSize[src.gu()]);

}
void g0_t::set(const mv &src) {
	const double *ptr = src.getC();

	if (src.gu() & 1) {
		ptr += 1;
	}
	if (src.gu() & 2) {
	}
	else {
	}
}
void g1_t::set(const mv &src) {
	const double *ptr = src.getC();

	if (src.gu() & 1) {
		ptr += 1;
	}
	if (src.gu() & 2) {
	}
	else {
	}
}
void g2_t::set(const mv &src) {
	const double *ptr = src.getC();

	if (src.gu() & 1) {
		ptr += 1;
	}
	if (src.gu() & 2) {
	}
	else {
	}
}
void g3_t::set(const mv &src) {
	const double *ptr = src.getC();

	if (src.gu() & 1) {
		ptr += 1;
	}
	if (src.gu() & 2) {
	}
	else {
	}
}
void I_t::set(const mv &src) {
	const double *ptr = src.getC();

	if (src.gu() & 1) {
		ptr += 1;
	}
	if (src.gu() & 2) {
		ptr += 4;
	}
	if (src.gu() & 4) {
		ptr += 6;
	}
	if (src.gu() & 8) {
		ptr += 4;
	}
	if (src.gu() & 16) {
	}
	else {
	}
}
void scalar::set(const mv &src) {
	const double *ptr = src.getC();

	if (src.gu() & 1) {
		m_c[0] = ptr[0];
	}
	else {
		m_c[0] = 0.0;
	}
}
void vector::set(const mv &src) {
	const double *ptr = src.getC();

	if (src.gu() & 1) {
		ptr += 1;
	}
	if (src.gu() & 2) {
		m_c[0] = ptr[0];
		m_c[1] = ptr[1];
		m_c[2] = ptr[2];
		m_c[3] = ptr[3];
	}
	else {
		m_c[0] = 0.0;
		m_c[1] = 0.0;
		m_c[2] = 0.0;
		m_c[3] = 0.0;
	}
}
void bivector::set(const mv &src) {
	const double *ptr = src.getC();

	if (src.gu() & 1) {
		ptr += 1;
	}
	if (src.gu() & 2) {
		ptr += 4;
	}
	if (src.gu() & 4) {
		m_c[0] = ptr[0];
		m_c[1] = ptr[1];
		m_c[2] = ptr[2];
		m_c[3] = ptr[3];
		m_c[4] = ptr[4];
		m_c[5] = ptr[5];
	}
	else {
		m_c[0] = 0.0;
		m_c[1] = 0.0;
		m_c[2] = 0.0;
		m_c[3] = 0.0;
		m_c[4] = 0.0;
		m_c[5] = 0.0;
	}
}
void trivector::set(const mv &src) {
	const double *ptr = src.getC();

	if (src.gu() & 1) {
		ptr += 1;
	}
	if (src.gu() & 2) {
		ptr += 4;
	}
	if (src.gu() & 4) {
		ptr += 6;
	}
	if (src.gu() & 8) {
		m_c[0] = ptr[0];
		m_c[1] = ptr[3];
		m_c[2] = -ptr[2];
		m_c[3] = ptr[1];
	}
	else {
		m_c[0] = 0.0;
		m_c[1] = 0.0;
		m_c[2] = 0.0;
		m_c[3] = 0.0;
	}
}
void pseudoscalar::set(const mv &src) {
	const double *ptr = src.getC();

	if (src.gu() & 1) {
		ptr += 1;
	}
	if (src.gu() & 2) {
		ptr += 4;
	}
	if (src.gu() & 4) {
		ptr += 6;
	}
	if (src.gu() & 8) {
		ptr += 4;
	}
	if (src.gu() & 16) {
		m_c[0] = ptr[0];
	}
	else {
		m_c[0] = 0.0;
	}
}
void evensubalgebra::set(const mv &src) {
	const double *ptr = src.getC();

	if (src.gu() & 1) {
		m_c[0] = ptr[0];
		ptr += 1;
	}
	else {
		m_c[0] = 0.0;
	}
	if (src.gu() & 2) {
		ptr += 4;
	}
	if (src.gu() & 4) {
		m_c[1] = ptr[0];
		m_c[2] = ptr[1];
		m_c[3] = ptr[2];
		m_c[4] = ptr[3];
		m_c[5] = ptr[4];
		m_c[6] = ptr[5];
		ptr += 6;
	}
	else {
		m_c[1] = 0.0;
		m_c[2] = 0.0;
		m_c[3] = 0.0;
		m_c[4] = 0.0;
		m_c[5] = 0.0;
		m_c[6] = 0.0;
	}
	if (src.gu() & 8) {
		ptr += 4;
	}
	if (src.gu() & 16) {
		m_c[7] = ptr[0];
	}
	else {
		m_c[7] = 0.0;
	}
}
void oddsubalgebra::set(const mv &src) {
	const double *ptr = src.getC();

	if (src.gu() & 1) {
		ptr += 1;
	}
	if (src.gu() & 2) {
		m_c[0] = ptr[0];
		m_c[1] = ptr[1];
		m_c[2] = ptr[2];
		m_c[3] = ptr[3];
		ptr += 4;
	}
	else {
		m_c[0] = 0.0;
		m_c[1] = 0.0;
		m_c[2] = 0.0;
		m_c[3] = 0.0;
	}
	if (src.gu() & 4) {
		ptr += 6;
	}
	if (src.gu() & 8) {
		m_c[4] = ptr[0];
		m_c[5] = ptr[3];
		m_c[6] = -ptr[2];
		m_c[7] = ptr[1];
	}
	else {
		m_c[4] = 0.0;
		m_c[5] = 0.0;
		m_c[6] = 0.0;
		m_c[7] = 0.0;
	}
}
void mv::set(const g0_t &src) {
	setGroupUsage(2);
	double *ptr = m_c;
	ptr[0] = 1.0;
	ptr[1] = ptr[2] = ptr[3] = 0.0;
}
void mv::set(const g1_t &src) {
	setGroupUsage(2);
	double *ptr = m_c;
	ptr[0] = ptr[2] = ptr[3] = 0.0;
	ptr[1] = 1.0;
}
void mv::set(const g2_t &src) {
	setGroupUsage(2);
	double *ptr = m_c;
	ptr[0] = ptr[1] = ptr[3] = 0.0;
	ptr[2] = 1.0;
}
void mv::set(const g3_t &src) {
	setGroupUsage(2);
	double *ptr = m_c;
	ptr[0] = ptr[1] = ptr[2] = 0.0;
	ptr[3] = 1.0;
}
void mv::set(const I_t &src) {
	setGroupUsage(16);
	double *ptr = m_c;
	ptr[0] = 1.0;
}
void mv::set(const scalar &src) {
	setGroupUsage(1);
	double *ptr = m_c;
	ptr[0] = src.m_c[0];
}
void mv::set(const vector &src) {
	setGroupUsage(2);
	double *ptr = m_c;
	ptr[0] = src.m_c[0];
	ptr[1] = src.m_c[1];
	ptr[2] = src.m_c[2];
	ptr[3] = src.m_c[3];
}
void mv::set(const bivector &src) {
	setGroupUsage(4);
	double *ptr = m_c;
	ptr[0] = src.m_c[0];
	ptr[1] = src.m_c[1];
	ptr[2] = src.m_c[2];
	ptr[3] = src.m_c[3];
	ptr[4] = src.m_c[4];
	ptr[5] = src.m_c[5];
}
void mv::set(const trivector &src) {
	setGroupUsage(8);
	double *ptr = m_c;
	ptr[0] = src.m_c[0];
	ptr[1] = src.m_c[3];
	ptr[2] = -src.m_c[2];
	ptr[3] = src.m_c[1];
}
void mv::set(const pseudoscalar &src) {
	setGroupUsage(16);
	double *ptr = m_c;
	ptr[0] = src.m_c[0];
}
void mv::set(const evensubalgebra &src) {
	setGroupUsage(21);
	double *ptr = m_c;
	ptr[0] = src.m_c[0];
	ptr += 1;
	ptr[0] = src.m_c[1];
	ptr[1] = src.m_c[2];
	ptr[2] = src.m_c[3];
	ptr[3] = src.m_c[4];
	ptr[4] = src.m_c[5];
	ptr[5] = src.m_c[6];
	ptr += 6;
	ptr[0] = src.m_c[7];
}
void mv::set(const oddsubalgebra &src) {
	setGroupUsage(10);
	double *ptr = m_c;
	ptr[0] = src.m_c[0];
	ptr[1] = src.m_c[1];
	ptr[2] = src.m_c[2];
	ptr[3] = src.m_c[3];
	ptr += 4;
	ptr[0] = src.m_c[4];
	ptr[1] = src.m_c[7];
	ptr[2] = -src.m_c[6];
	ptr[3] = src.m_c[5];
}

double mv::largestCoordinate() const {
	double maxValue = 0.0;
	int nbC = m4sta_mvSize[m_gu], i;
	for (i = 0; i < nbC; i++)
		if (fabs(m_c[i]) > maxValue) maxValue = fabs(m_c[i]);
	return maxValue;
}

double mv::largestBasisBlade(unsigned int &bm) const {
	int nc = m4sta_mvSize[gu()];
	double maxC = -1.0, C;

	int idx = 0;
	int group = 0;
	int i = 0;
	
	bm = 0;

	while (i < nc) {
		if (gu() & (1 << group)) {
			for (int j = 0; j < m4sta_groupSize[group]; j++) {
				C = fabs(m_c[i]);
				if (C > maxC) {
					maxC = C;
					bm = m4sta_basisElementBitmapByIndex[idx];
				}
				idx++;
				i++;
			}
		}
		else idx += m4sta_groupSize[group];
		group++;
	}

	return maxC;
} // end of mv::largestBasisBlade()



double _double(const mv &x) {
	return ((x.gu() & 1) != 0) ? x.getC()[0] : 0.0;
}


void mv::compress(double epsilon /*= 0.0*/) {
	set(mv_compress(m_c, epsilon, m_gu));
}

mv mv_compress(const double *c, double epsilon /*= 0.0*/, int gu /*= 31*/) {
	int i, j, ia = 0, ib = 0, f, s;
	int cgu = 0;
	double cc[16];

	// for all grade parts...
	for (i = 0; i < 5; i++) {
		// check if grade part has memory use:
		if (!(gu & (1 << i))) continue;

		// check if abs coordinates of grade part are all < epsilon
		s = m4sta_groupSize[i];
		j = ia + s;
		f = 0;
		for (; ia < j; ia++)
			if (fabs(c[ia]) > epsilon) {f = 1; break;}
		ia = j;
		if (f) {
			m4sta::copy_N(cc + ib, c + ia - s, s);
			ib += s;
			cgu |= (1 << i);
		}
	}
	
	return mv(cgu, cc);
}

mv mv_compress(int nbBlades, const unsigned int *bitmaps, const double *coords) {
	// convert basis blade compression to regular coordinate array:
	double A[16];
	for (int i = 0; i < 16; i++) A[i] = 0.0;

	for (int i = 0; i < nbBlades; i++) {
		A[m4sta_basisElementIndexByBitmap[bitmaps[i]]] = coords[i] * (double)m4sta_basisElementSignByBitmap[bitmaps[i]];		
	}

	return mv_compress(A);
}


void mv::expand(const double *ptrs[5], bool nulls /* = true */) const {
	const double *c = m_c; // this pointer gets incremented below
	
	if (m_gu & 1) {
		ptrs[0] =  c;
		c += 1;
	}
	else ptrs[0] = (nulls) ? NULL : nullFloats();
	if (m_gu & 2) {
		ptrs[1] =  c;
		c += 4;
	}
	else ptrs[1] = (nulls) ? NULL : nullFloats();
	if (m_gu & 4) {
		ptrs[2] =  c;
		c += 6;
	}
	else ptrs[2] = (nulls) ? NULL : nullFloats();
	if (m_gu & 8) {
		ptrs[3] =  c;
		c += 4;
	}
	else ptrs[3] = (nulls) ? NULL : nullFloats();
	if (m_gu & 16) {
		ptrs[4] =  c;
	}
	else ptrs[4] = (nulls) ? NULL : nullFloats();
}


void scalar::set()
{
	m_c[0] = 0.0;

}
void vector::set()
{
	m_c[0] = m_c[1] = m_c[2] = m_c[3] = 0.0;

}
void bivector::set()
{
	m_c[0] = m_c[1] = m_c[2] = m_c[3] = m_c[4] = m_c[5] = 0.0;

}
void trivector::set()
{
	m_c[0] = m_c[1] = m_c[2] = m_c[3] = 0.0;

}
void pseudoscalar::set()
{
	m_c[0] = 0.0;

}
void evensubalgebra::set()
{
	m_c[0] = m_c[1] = m_c[2] = m_c[3] = m_c[4] = m_c[5] = m_c[6] = m_c[7] = 0.0;

}
void oddsubalgebra::set()
{
	m_c[0] = m_c[1] = m_c[2] = m_c[3] = m_c[4] = m_c[5] = m_c[6] = m_c[7] = 0.0;

}

void scalar::set(const double scalarVal)
{
	m_c[0] = scalarVal;

}
void evensubalgebra::set(const double scalarVal)
{
	m_c[0] = scalarVal;
	m_c[1] = m_c[2] = m_c[3] = m_c[4] = m_c[5] = m_c[6] = m_c[7] = 0.0;

}

void scalar::set(const CoordinateOrder co, const double _scalar)
{
	m_c[0] = _scalar;

}
void vector::set(const CoordinateOrder co, const double _g0, const double _g1, const double _g2, const double _g3)
{
	m_c[0] = _g0;
	m_c[1] = _g1;
	m_c[2] = _g2;
	m_c[3] = _g3;

}
void bivector::set(const CoordinateOrder co, const double _g0_g1, const double _g0_g2, const double _g0_g3, const double _g1_g2, const double _g1_g3, const double _g2_g3)
{
	m_c[0] = _g0_g1;
	m_c[1] = _g0_g2;
	m_c[2] = _g0_g3;
	m_c[3] = _g1_g2;
	m_c[4] = _g1_g3;
	m_c[5] = _g2_g3;

}
void trivector::set(const CoordinateOrder co, const double _g1_g2_g3, const double _g0_g2_g3, const double _g1_g0_g3, const double _g0_g1_g2)
{
	m_c[0] = _g1_g2_g3;
	m_c[1] = _g0_g2_g3;
	m_c[2] = _g1_g0_g3;
	m_c[3] = _g0_g1_g2;

}
void pseudoscalar::set(const CoordinateOrder co, const double _g0_g1_g2_g3)
{
	m_c[0] = _g0_g1_g2_g3;

}
void evensubalgebra::set(const CoordinateOrder co, const double _scalar, const double _g0_g1, const double _g0_g2, const double _g0_g3, const double _g1_g2, const double _g1_g3, const double _g2_g3, const double _g0_g1_g2_g3)
{
	m_c[0] = _scalar;
	m_c[1] = _g0_g1;
	m_c[2] = _g0_g2;
	m_c[3] = _g0_g3;
	m_c[4] = _g1_g2;
	m_c[5] = _g1_g3;
	m_c[6] = _g2_g3;
	m_c[7] = _g0_g1_g2_g3;

}
void oddsubalgebra::set(const CoordinateOrder co, const double _g0, const double _g1, const double _g2, const double _g3, const double _g1_g2_g3, const double _g0_g2_g3, const double _g1_g0_g3, const double _g0_g1_g2)
{
	m_c[0] = _g0;
	m_c[1] = _g1;
	m_c[2] = _g2;
	m_c[3] = _g3;
	m_c[4] = _g1_g2_g3;
	m_c[5] = _g0_g2_g3;
	m_c[6] = _g1_g0_g3;
	m_c[7] = _g0_g1_g2;

}

void scalar::set(const CoordinateOrder co, const double *A)
{
	m_c[0] = A[0];

}
void vector::set(const CoordinateOrder co, const double *A)
{
	m_c[0] = A[0];
	m_c[1] = A[1];
	m_c[2] = A[2];
	m_c[3] = A[3];

}
void bivector::set(const CoordinateOrder co, const double *A)
{
	m_c[0] = A[0];
	m_c[1] = A[1];
	m_c[2] = A[2];
	m_c[3] = A[3];
	m_c[4] = A[4];
	m_c[5] = A[5];

}
void trivector::set(const CoordinateOrder co, const double *A)
{
	m_c[0] = A[0];
	m_c[1] = A[1];
	m_c[2] = A[2];
	m_c[3] = A[3];

}
void pseudoscalar::set(const CoordinateOrder co, const double *A)
{
	m_c[0] = A[0];

}
void evensubalgebra::set(const CoordinateOrder co, const double *A)
{
	m_c[0] = A[0];
	m_c[1] = A[1];
	m_c[2] = A[2];
	m_c[3] = A[3];
	m_c[4] = A[4];
	m_c[5] = A[5];
	m_c[6] = A[6];
	m_c[7] = A[7];

}
void oddsubalgebra::set(const CoordinateOrder co, const double *A)
{
	m_c[0] = A[0];
	m_c[1] = A[1];
	m_c[2] = A[2];
	m_c[3] = A[3];
	m_c[4] = A[4];
	m_c[5] = A[5];
	m_c[6] = A[6];
	m_c[7] = A[7];

}

void g0_t::set(const g0_t &a)
{

}
void g1_t::set(const g1_t &a)
{

}
void g2_t::set(const g2_t &a)
{

}
void g3_t::set(const g3_t &a)
{

}
void I_t::set(const I_t &a)
{

}
void scalar::set(const scalar &a)
{
	m_c[0] = a.m_c[0];

}
void vector::set(const vector &a)
{
	m_c[0] = a.m_c[0];
	m_c[1] = a.m_c[1];
	m_c[2] = a.m_c[2];
	m_c[3] = a.m_c[3];

}
void bivector::set(const bivector &a)
{
	m_c[0] = a.m_c[0];
	m_c[1] = a.m_c[1];
	m_c[2] = a.m_c[2];
	m_c[3] = a.m_c[3];
	m_c[4] = a.m_c[4];
	m_c[5] = a.m_c[5];

}
void trivector::set(const trivector &a)
{
	m_c[0] = a.m_c[0];
	m_c[1] = a.m_c[1];
	m_c[2] = a.m_c[2];
	m_c[3] = a.m_c[3];

}
void pseudoscalar::set(const pseudoscalar &a)
{
	m_c[0] = a.m_c[0];

}
void evensubalgebra::set(const evensubalgebra &a)
{
	m_c[0] = a.m_c[0];
	m_c[1] = a.m_c[1];
	m_c[2] = a.m_c[2];
	m_c[3] = a.m_c[3];
	m_c[4] = a.m_c[4];
	m_c[5] = a.m_c[5];
	m_c[6] = a.m_c[6];
	m_c[7] = a.m_c[7];

}
void oddsubalgebra::set(const oddsubalgebra &a)
{
	m_c[0] = a.m_c[0];
	m_c[1] = a.m_c[1];
	m_c[2] = a.m_c[2];
	m_c[3] = a.m_c[3];
	m_c[4] = a.m_c[4];
	m_c[5] = a.m_c[5];
	m_c[6] = a.m_c[6];
	m_c[7] = a.m_c[7];

}


double g0_t::largestCoordinate() const {
	double maxValue = 1.0;
	return maxValue;
}
double g0_t::largestBasisBlade(unsigned int &bm) const {
	double maxValue = 1.0;
	bm = 1;
	return maxValue;
}
double g1_t::largestCoordinate() const {
	double maxValue = 1.0;
	return maxValue;
}
double g1_t::largestBasisBlade(unsigned int &bm) const {
	double maxValue = 1.0;
	bm = 2;
	return maxValue;
}
double g2_t::largestCoordinate() const {
	double maxValue = 1.0;
	return maxValue;
}
double g2_t::largestBasisBlade(unsigned int &bm) const {
	double maxValue = 1.0;
	bm = 4;
	return maxValue;
}
double g3_t::largestCoordinate() const {
	double maxValue = 1.0;
	return maxValue;
}
double g3_t::largestBasisBlade(unsigned int &bm) const {
	double maxValue = 1.0;
	bm = 8;
	return maxValue;
}
double I_t::largestCoordinate() const {
	double maxValue = 1.0;
	return maxValue;
}
double I_t::largestBasisBlade(unsigned int &bm) const {
	double maxValue = 1.0;
	bm = 15;
	return maxValue;
}
double scalar::largestCoordinate() const {
	double maxValue = ::fabs(m_c[0]);
	return maxValue;
}
double scalar::largestBasisBlade(unsigned int &bm) const {
	double maxValue = ::fabs(m_c[0]);
	bm = 0;
	return maxValue;
}
double vector::largestCoordinate() const {
	double maxValue = ::fabs(m_c[0]);
	if (::fabs(m_c[1]) > maxValue) { maxValue = ::fabs(m_c[1]); }
	if (::fabs(m_c[2]) > maxValue) { maxValue = ::fabs(m_c[2]); }
	if (::fabs(m_c[3]) > maxValue) { maxValue = ::fabs(m_c[3]); }
	return maxValue;
}
double vector::largestBasisBlade(unsigned int &bm) const {
	double maxValue = ::fabs(m_c[0]);
	bm = 0;
	if (::fabs(m_c[1]) > maxValue) { maxValue = ::fabs(m_c[1]); bm = 2; }
	if (::fabs(m_c[2]) > maxValue) { maxValue = ::fabs(m_c[2]); bm = 4; }
	if (::fabs(m_c[3]) > maxValue) { maxValue = ::fabs(m_c[3]); bm = 8; }
	return maxValue;
}
double bivector::largestCoordinate() const {
	double maxValue = ::fabs(m_c[0]);
	if (::fabs(m_c[1]) > maxValue) { maxValue = ::fabs(m_c[1]); }
	if (::fabs(m_c[2]) > maxValue) { maxValue = ::fabs(m_c[2]); }
	if (::fabs(m_c[3]) > maxValue) { maxValue = ::fabs(m_c[3]); }
	if (::fabs(m_c[4]) > maxValue) { maxValue = ::fabs(m_c[4]); }
	if (::fabs(m_c[5]) > maxValue) { maxValue = ::fabs(m_c[5]); }
	return maxValue;
}
double bivector::largestBasisBlade(unsigned int &bm) const {
	double maxValue = ::fabs(m_c[0]);
	bm = 0;
	if (::fabs(m_c[1]) > maxValue) { maxValue = ::fabs(m_c[1]); bm = 5; }
	if (::fabs(m_c[2]) > maxValue) { maxValue = ::fabs(m_c[2]); bm = 9; }
	if (::fabs(m_c[3]) > maxValue) { maxValue = ::fabs(m_c[3]); bm = 6; }
	if (::fabs(m_c[4]) > maxValue) { maxValue = ::fabs(m_c[4]); bm = 10; }
	if (::fabs(m_c[5]) > maxValue) { maxValue = ::fabs(m_c[5]); bm = 12; }
	return maxValue;
}
double trivector::largestCoordinate() const {
	double maxValue = ::fabs(m_c[0]);
	if (::fabs(m_c[1]) > maxValue) { maxValue = ::fabs(m_c[1]); }
	if (::fabs(m_c[2]) > maxValue) { maxValue = ::fabs(m_c[2]); }
	if (::fabs(m_c[3]) > maxValue) { maxValue = ::fabs(m_c[3]); }
	return maxValue;
}
double trivector::largestBasisBlade(unsigned int &bm) const {
	double maxValue = ::fabs(m_c[0]);
	bm = 0;
	if (::fabs(m_c[1]) > maxValue) { maxValue = ::fabs(m_c[1]); bm = 13; }
	if (::fabs(m_c[2]) > maxValue) { maxValue = ::fabs(m_c[2]); bm = 11; }
	if (::fabs(m_c[3]) > maxValue) { maxValue = ::fabs(m_c[3]); bm = 7; }
	return maxValue;
}
double pseudoscalar::largestCoordinate() const {
	double maxValue = ::fabs(m_c[0]);
	return maxValue;
}
double pseudoscalar::largestBasisBlade(unsigned int &bm) const {
	double maxValue = ::fabs(m_c[0]);
	bm = 0;
	return maxValue;
}
double evensubalgebra::largestCoordinate() const {
	double maxValue = ::fabs(m_c[0]);
	if (::fabs(m_c[1]) > maxValue) { maxValue = ::fabs(m_c[1]); }
	if (::fabs(m_c[2]) > maxValue) { maxValue = ::fabs(m_c[2]); }
	if (::fabs(m_c[3]) > maxValue) { maxValue = ::fabs(m_c[3]); }
	if (::fabs(m_c[4]) > maxValue) { maxValue = ::fabs(m_c[4]); }
	if (::fabs(m_c[5]) > maxValue) { maxValue = ::fabs(m_c[5]); }
	if (::fabs(m_c[6]) > maxValue) { maxValue = ::fabs(m_c[6]); }
	if (::fabs(m_c[7]) > maxValue) { maxValue = ::fabs(m_c[7]); }
	return maxValue;
}
double evensubalgebra::largestBasisBlade(unsigned int &bm) const {
	double maxValue = ::fabs(m_c[0]);
	bm = 0;
	if (::fabs(m_c[1]) > maxValue) { maxValue = ::fabs(m_c[1]); bm = 3; }
	if (::fabs(m_c[2]) > maxValue) { maxValue = ::fabs(m_c[2]); bm = 5; }
	if (::fabs(m_c[3]) > maxValue) { maxValue = ::fabs(m_c[3]); bm = 9; }
	if (::fabs(m_c[4]) > maxValue) { maxValue = ::fabs(m_c[4]); bm = 6; }
	if (::fabs(m_c[5]) > maxValue) { maxValue = ::fabs(m_c[5]); bm = 10; }
	if (::fabs(m_c[6]) > maxValue) { maxValue = ::fabs(m_c[6]); bm = 12; }
	if (::fabs(m_c[7]) > maxValue) { maxValue = ::fabs(m_c[7]); bm = 15; }
	return maxValue;
}
double oddsubalgebra::largestCoordinate() const {
	double maxValue = ::fabs(m_c[0]);
	if (::fabs(m_c[1]) > maxValue) { maxValue = ::fabs(m_c[1]); }
	if (::fabs(m_c[2]) > maxValue) { maxValue = ::fabs(m_c[2]); }
	if (::fabs(m_c[3]) > maxValue) { maxValue = ::fabs(m_c[3]); }
	if (::fabs(m_c[4]) > maxValue) { maxValue = ::fabs(m_c[4]); }
	if (::fabs(m_c[5]) > maxValue) { maxValue = ::fabs(m_c[5]); }
	if (::fabs(m_c[6]) > maxValue) { maxValue = ::fabs(m_c[6]); }
	if (::fabs(m_c[7]) > maxValue) { maxValue = ::fabs(m_c[7]); }
	return maxValue;
}
double oddsubalgebra::largestBasisBlade(unsigned int &bm) const {
	double maxValue = ::fabs(m_c[0]);
	bm = 0;
	if (::fabs(m_c[1]) > maxValue) { maxValue = ::fabs(m_c[1]); bm = 2; }
	if (::fabs(m_c[2]) > maxValue) { maxValue = ::fabs(m_c[2]); bm = 4; }
	if (::fabs(m_c[3]) > maxValue) { maxValue = ::fabs(m_c[3]); bm = 8; }
	if (::fabs(m_c[4]) > maxValue) { maxValue = ::fabs(m_c[4]); bm = 14; }
	if (::fabs(m_c[5]) > maxValue) { maxValue = ::fabs(m_c[5]); bm = 13; }
	if (::fabs(m_c[6]) > maxValue) { maxValue = ::fabs(m_c[6]); bm = 11; }
	if (::fabs(m_c[7]) > maxValue) { maxValue = ::fabs(m_c[7]); bm = 7; }
	return maxValue;
}

double _double(const g0_t &x) {
	return 0.0;
}
double _double(const g1_t &x) {
	return 0.0;
}
double _double(const g2_t &x) {
	return 0.0;
}
double _double(const g3_t &x) {
	return 0.0;
}
double _double(const I_t &x) {
	return 0.0;
}
double _double(const scalar &x) {
	return x.m_c[0];
}
double _double(const vector &x) {
	return 0.0;
}
double _double(const bivector &x) {
	return 0.0;
}
double _double(const trivector &x) {
	return 0.0;
}
double _double(const pseudoscalar &x) {
	return 0.0;
}
double _double(const evensubalgebra &x) {
	return x.m_c[0];
}
double _double(const oddsubalgebra &x) {
	return 0.0;
}

void om::setIdentity() {
	m4sta::zero_16(m_m1);

	m4sta::zero_N(m_m2, 36);

	m4sta::zero_16(m_m3);

	m4sta::zero_1(m_m4);

	m_m1[0] = m_m1[5] = m_m1[10] = m_m1[15] = m_m2[0] = m_m2[7] = m_m2[14] = m_m2[21] = 
		m_m2[28] = m_m2[35] = m_m3[0] = m_m3[5] = m_m3[10] = m_m3[15] = m_m4[0] = 1.0;
}

void om::set(const om &src) {
	m4sta::copy_16(m_m1, src.m_m1);

	m4sta::copy_N(m_m2, src.m_m2, 36);

	m4sta::copy_16(m_m3, src.m_m3);

	m4sta::copy_1(m_m4, src.m_m4);

}
void om::set_grade_2_0()
{
	// Set image of g0^g1
	m_m2[0] = (m_m1[0]*m_m1[5]-m_m1[1]*m_m1[4]);
	m_m2[6] = (m_m1[0]*m_m1[9]-m_m1[1]*m_m1[8]);
	m_m2[12] = (m_m1[4]*m_m1[9]-m_m1[5]*m_m1[8]);
	m_m2[18] = (m_m1[0]*m_m1[13]-m_m1[1]*m_m1[12]);
	m_m2[24] = (-m_m1[12]*m_m1[5]+m_m1[13]*m_m1[4]);
	m_m2[30] = (-m_m1[12]*m_m1[9]+m_m1[13]*m_m1[8]);

}
void om::set_grade_2_1()
{
	// Set image of g0^g2
	m_m2[1] = (m_m1[0]*m_m1[6]-m_m1[2]*m_m1[4]);
	m_m2[7] = (m_m1[0]*m_m1[10]-m_m1[2]*m_m1[8]);
	m_m2[13] = (m_m1[10]*m_m1[4]-m_m1[6]*m_m1[8]);
	m_m2[19] = (m_m1[0]*m_m1[14]-m_m1[12]*m_m1[2]);
	m_m2[25] = (-m_m1[12]*m_m1[6]+m_m1[14]*m_m1[4]);
	m_m2[31] = (-m_m1[10]*m_m1[12]+m_m1[14]*m_m1[8]);

}
void om::set_grade_2_2()
{
	// Set image of g1^g2
	m_m2[2] = (m_m1[1]*m_m1[6]-m_m1[2]*m_m1[5]);
	m_m2[8] = (m_m1[1]*m_m1[10]-m_m1[2]*m_m1[9]);
	m_m2[14] = (m_m1[10]*m_m1[5]-m_m1[6]*m_m1[9]);
	m_m2[20] = (m_m1[1]*m_m1[14]-m_m1[13]*m_m1[2]);
	m_m2[26] = (-m_m1[13]*m_m1[6]+m_m1[14]*m_m1[5]);
	m_m2[32] = (-m_m1[10]*m_m1[13]+m_m1[14]*m_m1[9]);

}
void om::set_grade_2_3()
{
	// Set image of g0^g3
	m_m2[3] = (m_m1[0]*m_m1[7]-m_m1[3]*m_m1[4]);
	m_m2[9] = (m_m1[0]*m_m1[11]-m_m1[3]*m_m1[8]);
	m_m2[15] = (m_m1[11]*m_m1[4]-m_m1[7]*m_m1[8]);
	m_m2[21] = (m_m1[0]*m_m1[15]-m_m1[12]*m_m1[3]);
	m_m2[27] = (-m_m1[12]*m_m1[7]+m_m1[15]*m_m1[4]);
	m_m2[33] = (-m_m1[11]*m_m1[12]+m_m1[15]*m_m1[8]);

}
void om::set_grade_2_4()
{
	// Set image of g1^g3
	m_m2[4] = (m_m1[1]*m_m1[7]-m_m1[3]*m_m1[5]);
	m_m2[10] = (m_m1[1]*m_m1[11]-m_m1[3]*m_m1[9]);
	m_m2[16] = (m_m1[11]*m_m1[5]-m_m1[7]*m_m1[9]);
	m_m2[22] = (m_m1[1]*m_m1[15]-m_m1[13]*m_m1[3]);
	m_m2[28] = (-m_m1[13]*m_m1[7]+m_m1[15]*m_m1[5]);
	m_m2[34] = (-m_m1[11]*m_m1[13]+m_m1[15]*m_m1[9]);

}
void om::set_grade_2_5()
{
	// Set image of g2^g3
	m_m2[5] = (m_m1[2]*m_m1[7]-m_m1[3]*m_m1[6]);
	m_m2[11] = (-m_m1[10]*m_m1[3]+m_m1[11]*m_m1[2]);
	m_m2[17] = (-m_m1[10]*m_m1[7]+m_m1[11]*m_m1[6]);
	m_m2[23] = (-m_m1[14]*m_m1[3]+m_m1[15]*m_m1[2]);
	m_m2[29] = (-m_m1[14]*m_m1[7]+m_m1[15]*m_m1[6]);
	m_m2[35] = (m_m1[10]*m_m1[15]-m_m1[11]*m_m1[14]);

}
void om::set_grade_3_0()
{
	// Set image of g0^g1^g2
	m_m3[0] = (m_m1[0]*m_m2[14]-m_m1[4]*m_m2[8]+m_m1[8]*m_m2[2]);
	m_m3[4] = (m_m1[0]*m_m2[26]+m_m1[12]*m_m2[2]-m_m1[4]*m_m2[20]);
	m_m3[8] = (m_m1[0]*m_m2[32]+m_m1[12]*m_m2[8]-m_m1[8]*m_m2[20]);
	m_m3[12] = (m_m1[12]*m_m2[14]+m_m1[4]*m_m2[32]-m_m1[8]*m_m2[26]);

}
void om::set_grade_3_1()
{
	// Set image of g0^g1^g3
	m_m3[1] = (m_m1[0]*m_m2[16]-m_m1[4]*m_m2[10]+m_m1[8]*m_m2[4]);
	m_m3[5] = (m_m1[0]*m_m2[28]+m_m1[12]*m_m2[4]-m_m1[4]*m_m2[22]);
	m_m3[9] = (m_m1[0]*m_m2[34]+m_m1[12]*m_m2[10]-m_m1[8]*m_m2[22]);
	m_m3[13] = (m_m1[12]*m_m2[16]+m_m1[4]*m_m2[34]-m_m1[8]*m_m2[28]);

}
void om::set_grade_3_2()
{
	// Set image of g0^g2^g3
	m_m3[2] = (m_m1[0]*m_m2[17]-m_m1[4]*m_m2[11]+m_m1[8]*m_m2[5]);
	m_m3[6] = (m_m1[0]*m_m2[29]+m_m1[12]*m_m2[5]-m_m1[4]*m_m2[23]);
	m_m3[10] = (m_m1[0]*m_m2[35]+m_m1[12]*m_m2[11]-m_m1[8]*m_m2[23]);
	m_m3[14] = (m_m1[12]*m_m2[17]+m_m1[4]*m_m2[35]-m_m1[8]*m_m2[29]);

}
void om::set_grade_3_3()
{
	// Set image of g1^g2^g3
	m_m3[3] = (m_m1[1]*m_m2[17]-m_m1[5]*m_m2[11]+m_m1[9]*m_m2[5]);
	m_m3[7] = (m_m1[1]*m_m2[29]+m_m1[13]*m_m2[5]-m_m1[5]*m_m2[23]);
	m_m3[11] = (m_m1[1]*m_m2[35]+m_m1[13]*m_m2[11]-m_m1[9]*m_m2[23]);
	m_m3[15] = (m_m1[13]*m_m2[17]+m_m1[5]*m_m2[35]-m_m1[9]*m_m2[29]);

}
void om::set_grade_4_0()
{
	// Set image of g0^g1^g2^g3
	m_m4[0] = (m_m1[0]*m_m3[15]-m_m1[12]*m_m3[3]-m_m1[4]*m_m3[11]+m_m1[8]*m_m3[7]);

}
void om::set(const vector &ig0, const vector &ig1, const vector &ig2, const vector &ig3)
{
	// Set image of g0
	m_m1[0] = ig0.m_c[0];
	m_m1[4] = ig0.m_c[1];
	m_m1[8] = ig0.m_c[2];
	m_m1[12] = ig0.m_c[3];

	// Set image of g1
	m_m1[1] = ig1.m_c[0];
	m_m1[5] = ig1.m_c[1];
	m_m1[9] = ig1.m_c[2];
	m_m1[13] = ig1.m_c[3];

	// Set image of g2
	m_m1[2] = ig2.m_c[0];
	m_m1[6] = ig2.m_c[1];
	m_m1[10] = ig2.m_c[2];
	m_m1[14] = ig2.m_c[3];

	// Set image of g3
	m_m1[3] = ig3.m_c[0];
	m_m1[7] = ig3.m_c[1];
	m_m1[11] = ig3.m_c[2];
	m_m1[15] = ig3.m_c[3];

	om::set_grade_2_0();
	om::set_grade_2_1();
	om::set_grade_2_2();
	om::set_grade_2_3();
	om::set_grade_2_4();
	om::set_grade_2_5();
	om::set_grade_3_0();
	om::set_grade_3_1();
	om::set_grade_3_2();
	om::set_grade_3_3();
	om::set_grade_4_0();
}
void om::set(const double *M)
{
	// Set image of g0
	m_m1[0] = M[0];
	m_m1[4] = M[4];
	m_m1[8] = M[8];
	m_m1[12] = M[12];

	// Set image of g1
	m_m1[1] = M[1];
	m_m1[5] = M[5];
	m_m1[9] = M[9];
	m_m1[13] = M[13];

	// Set image of g2
	m_m1[2] = M[2];
	m_m1[6] = M[6];
	m_m1[10] = M[10];
	m_m1[14] = M[14];

	// Set image of g3
	m_m1[3] = M[3];
	m_m1[7] = M[7];
	m_m1[11] = M[11];
	m_m1[15] = M[15];

	om::set_grade_2_0();
	om::set_grade_2_1();
	om::set_grade_2_2();
	om::set_grade_2_3();
	om::set_grade_2_4();
	om::set_grade_2_5();
	om::set_grade_3_0();
	om::set_grade_3_1();
	om::set_grade_3_2();
	om::set_grade_3_3();
	om::set_grade_4_0();
}
double genrand() {
return (double)((double)(rand() & 0x7FFF) / 32768.0) + 
	(double)((double)(rand() & 0x7FFF) / (32768.0 * 32768.0)) + 
	(double)((double)(rand() & 0x7FFF) / (32768.0 * 32768.0 * 32768.0)) + 
	(double)((double)(rand() & 0x7FFF) / (32768.0 * 32768.0 * 32768.0 * 32768.0)); 
}
void genrand_seed(unsigned int seed) {
	srand(seed);
}

void genrand_timeSeed() {
	genrand_seed((unsigned int)time(NULL));
}

mv gp(const mv &a, const mv &b)
{
	double c[16];
	const double* _a[5];
	const double* _b[5];
	a.expand(_a);
	b.expand(_b);
	m4sta::zero_16(c);
	if (a.gu() & 1) {
		if (b.gu() & 1) {
			gp_default_0_0_0(_a[0], _b[0], c + 0);
		}
		if (b.gu() & 2) {
			gp_default_0_1_1(_a[0], _b[1], c + 1);
		}
		if (b.gu() & 4) {
			gp_default_0_2_2(_a[0], _b[2], c + 5);
		}
		if (b.gu() & 8) {
			gp_default_0_3_3(_a[0], _b[3], c + 11);
		}
		if (b.gu() & 16) {
			gp_default_0_4_4(_a[0], _b[4], c + 15);
		}
	}
	if (a.gu() & 2) {
		if (b.gu() & 1) {
			gp_default_1_0_1(_a[1], _b[0], c + 1);
		}
		if (b.gu() & 2) {
			gp_default_1_1_0(_a[1], _b[1], c + 0);
			gp_default_1_1_2(_a[1], _b[1], c + 5);
		}
		if (b.gu() & 4) {
			gp_default_1_2_1(_a[1], _b[2], c + 1);
			gp_default_1_2_3(_a[1], _b[2], c + 11);
		}
		if (b.gu() & 8) {
			gp_default_1_3_2(_a[1], _b[3], c + 5);
			gp_default_1_3_4(_a[1], _b[3], c + 15);
		}
		if (b.gu() & 16) {
			gp_default_1_4_3(_a[1], _b[4], c + 11);
		}
	}
	if (a.gu() & 4) {
		if (b.gu() & 1) {
			gp_default_2_0_2(_a[2], _b[0], c + 5);
		}
		if (b.gu() & 2) {
			gp_default_2_1_1(_a[2], _b[1], c + 1);
			gp_default_2_1_3(_a[2], _b[1], c + 11);
		}
		if (b.gu() & 4) {
			gp_default_2_2_0(_a[2], _b[2], c + 0);
			gp_default_2_2_2(_a[2], _b[2], c + 5);
			gp_default_2_2_4(_a[2], _b[2], c + 15);
		}
		if (b.gu() & 8) {
			gp_default_2_3_1(_a[2], _b[3], c + 1);
			gp_default_2_3_3(_a[2], _b[3], c + 11);
		}
		if (b.gu() & 16) {
			gp_default_2_4_2(_a[2], _b[4], c + 5);
		}
	}
	if (a.gu() & 8) {
		if (b.gu() & 1) {
			gp_default_3_0_3(_a[3], _b[0], c + 11);
		}
		if (b.gu() & 2) {
			gp_default_3_1_2(_a[3], _b[1], c + 5);
			gp_default_3_1_4(_a[3], _b[1], c + 15);
		}
		if (b.gu() & 4) {
			gp_default_3_2_1(_a[3], _b[2], c + 1);
			gp_default_3_2_3(_a[3], _b[2], c + 11);
		}
		if (b.gu() & 8) {
			gp_default_3_3_0(_a[3], _b[3], c + 0);
			gp_default_3_3_2(_a[3], _b[3], c + 5);
		}
		if (b.gu() & 16) {
			gp_default_3_4_1(_a[3], _b[4], c + 1);
		}
	}
	if (a.gu() & 16) {
		if (b.gu() & 1) {
			gp_default_4_0_4(_a[4], _b[0], c + 15);
		}
		if (b.gu() & 2) {
			gp_default_4_1_3(_a[4], _b[1], c + 11);
		}
		if (b.gu() & 4) {
			gp_default_4_2_2(_a[4], _b[2], c + 5);
		}
		if (b.gu() & 8) {
			gp_default_4_3_1(_a[4], _b[3], c + 1);
		}
		if (b.gu() & 16) {
			gp_default_4_4_0(_a[4], _b[4], c + 0);
		}
	}
	return mv_compress(c, 0.0, 31);
}
} // end of namespace m4sta
