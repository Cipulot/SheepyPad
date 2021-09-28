#pragma once

#include "quantum.h"

#define xxx KC_NO

#define LAYOUT( \
	K00, K01, K02, K03, K04, \
	     K11, K12, K13, K14, \
	     K21, K22, K23, K24, \
	     K31, K32, K33, K34, \
	     K41, K42, K43, K44  \
) { \
	{ K00,   K01,   K02,   K03,   K04 }, \
	{ xxx,   K11,   K12,   K13,   K14 }, \
	{ xxx,   K21,   K22,   K23,   K24 }, \
	{ xxx,   K31,   K32,   K33,   K34 }, \
	{ xxx,   K41,   K42,   K43,   K44 }, \
	{ xxx,   xxx,   xxx,   xxx,   xxx }  \
}
