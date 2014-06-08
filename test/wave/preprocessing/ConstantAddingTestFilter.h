#ifndef FILTERMOCK_H_
#define FILTERMOCK_H_
#include "wave/processing/Filter.h"
class ConstantAddingTestFilter: public virtual Filter {

public:

	ConstantAddingTestFilter(double value){
		this->value = value;
	}

	virtual void applyOn(Samples& samples) {
		for (int i = 0; i < samples.getNumberOfSamples(); ++i) {
			double oldValue = samples.getSample(i);
			samples.setSample(i, oldValue+value);
		}
	}

private:
	double value;

};

#endif /* FILTERMOCK_H_ */
