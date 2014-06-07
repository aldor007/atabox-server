/*
 * LengthProperty.cpp
 *
 *  Created on: 7 cze 2014
 *      Author: mj
 */

#include <wave/analysis/LengthProperty.h>

LengthProperty::LengthProperty() {
	// TODO Auto-generated constructor stub

}

double LengthProperty::getValue(Samples& samples) {
	return samples.getLenghtInSeconds();
}

string LengthProperty::getName() {
	return "length";
}
