#pragma once

//#include "m4sta.hpp"

// GLM 
//#define GLM_ENABLE_EXPERIMENTAL
//#define GLM_FORCE_RADIANS
//#define GLM_FORCE_DEPTH_ZERO_TO_ONE
//#include <glm.hpp>
//#include <gtc/constants.hpp>
//#include <gtx/quaternion.hpp>


namespace mve {

	//struct LorentzBoostParams {
	//	double rapidityx;
	//	double rapidityy;
	//	double rapidityz;
	//};

	/// <summary>
	/// Returns the Lorentz boost from a given rapidity. Assumes natural units where c=1!
	/// </summary>
	/// <param name="rapidity"></param>
	/// <returns>Lorentz boost matrix in GLSL convention</returns>
	glm::mat4 LorentzMatrixFromRapidity(m4sta::mv rapidity) {
		double x = rapidity.get_g1();	// Unsure whether it should be .get_g0_g1()?
		double y = rapidity.get_g2();	// Unsure whether it should be .get_g0_g2()?
		double z = rapidity.get_g3();	// Unsure whether it should be .get_g0_g3()?
		double x2 = x * x;
		double y2 = y * y;
		double z2 = z * z;
		double r = x2 + y2 + z2;
		//glm::mat4 L{ 1.0 };
		if (r >= 0.000001) {
			double g = sqrt(1.0 + r);
			
			r = 1.0 / r;

			double xy = (g - 1.0) * x * y * r;
			double yz = (g - 1.0) * y * z * r;
			double zx = (g - 1.0) * z * x * r;

			// This is essentially the 4x4 Lorentz boost matrix as you can find in
			// https://en.wikipedia.org/wiki/Lorentz_transformation#Coordinate_transformation
			// However it has been transposed to conform with the GLSL convention
			return glm::mat4{
				(g * x2 + y2 + z2) * r,						xy,						zx, -x,
									xy, (x2 + g * y2 + z2) * r,						yz, -y,
									zx,						yz, (x2 + y2 + g * z2) * r, -z,
									-x,						-y,						-z,  g
			};
		}
		else {
			return glm::mat4{ 1.0 };
		}
	}

	m4sta::mv transformWithLorentzMatrix(glm::mat4 L, m4sta::mv proper) {
		double t, x, y, z, tt, xx, yy, zz;
		t = proper.get_g0();
		x = proper.get_g1();
		y = proper.get_g2();
		z = proper.get_g3();
		
		// This *should* be transposed correctly 
		tt = L[0][3] * t + L[0][0] * x + L[0][1] * y + L[0][2] * z;
		xx = L[1][3] * t + L[1][0] * x + L[1][1] * y + L[1][2] * z;
		yy = L[2][3] * t + L[2][0] * x + L[2][1] * y + L[2][2] * z;
		zz = L[3][3] * t + L[3][0] * x + L[3][1] * y + L[3][2] * z;
		m4sta::mv ret{};
		ret.set_g0(tt);
		ret.set_g1(xx);
		ret.set_g2(yy);
		ret.set_g3(zz);
		return ret;
	}

	// Still need to investigate how to construct quaternions in STA
	glm::mat4 rotationMatrixFromSTA(m4sta::spinor3 quat) {
		throw std::runtime_error("rotationMatrixFromSTA not implemented yet!");
	}

}