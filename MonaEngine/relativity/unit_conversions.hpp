#pragma once
#include <cmath>
#include "Constants.hpp"

namespace Math {

	static inline double how_many_deg_in_angle(double rad) {
		return rad * (180 / pi); // 180/pi equivalent to 360/2pi
	}

	static inline double how_many_arcmin_in_angle(double rad) {
		return rad * (10800 / pi); // (180 * 60) / pi
	}

	static inline double how_many_arcsec_in_angle(double rad) {
		return rad * (648000 / pi); // (180 * 60 * 60) / pi
	}

	static inline double how_many_milliarcsec_in_angle(double rad) {
		return rad * (648000000 / pi); // (180 * 60 * 60 * 1000) / pi
	}

	static inline double deg_2_arcmin(double deg) {
		return deg * 60; // 60 arcminutes in 1 degree
	}

	static inline double deg_2_arcsec(double deg) {
		return deg * 60 * 60; // 60 * 60 = 3600 arcseconds in 1 degree
	}

	static inline double deg_2_milliarcsec(double deg) {
		return deg * 60 * 60 * 1000; // 60 * 60 * 1000 = 3 600 000 milliarcseconds in one degree
	}

	static inline double arcmin_2_arcsec(double arcmin) {
		return arcmin * 60; // 60 arc seconds in 1 arcminute
	}

	static inline double arcmin_2_milliarcsec(double arcmin) {
		return arcmin * 60 * 1000; // 60 * 1000 = 60 000 milliarcseconds in 1 arcminute
	}

	static inline double arcsec_2_milliarcsec(double arcsec) {
		return arcsec * 1000; // 1000 milliarcseconds in 1 arcsecond
	}

	struct arc_length {
		double deg;
		double arcmin;
		double arcsec;
		double milliarcsec;
	};

	 arc_length radian_to_arc(double rad) {
		double component_deg = std::floor(how_many_deg_in_angle(rad));

		double component_arcmin = std::floor(how_many_arcmin_in_angle(rad) - deg_2_arcmin(component_deg));

		double component_arcsec = std::floor(how_many_arcsec_in_angle(rad) -
			deg_2_arcsec(component_deg) -
			arcmin_2_arcsec(component_arcmin));

		double component_milliarcsec = std::floor(how_many_milliarcsec_in_angle(rad) -
			deg_2_milliarcsec(component_deg) -
			arcmin_2_milliarcsec(component_arcmin) -
			arcsec_2_milliarcsec(component_arcsec));

		return arc_length{
			component_deg,
			component_arcmin,
			component_arcsec,
			component_milliarcsec
		};
	}
} // namespace Math
