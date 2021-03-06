/*
 * Graphan.cpp
 *
 *  Created on: May 9, 2009
 *      Author: alno
 */
#include "../base/BaseInternal.h"

#include "Graphan.h"
#include "XmorphyGraphan.h"

namespace lspl { namespace graphan {

Graphan * Graphan::singletonInstance = 0;

Graphan::Graphan() {
}

Graphan::~Graphan() {
}

Graphan & Graphan::instance() {
	if ( !singletonInstance)
		singletonInstance = new XmorphyGraphan();

	return *singletonInstance;
}

void Graphan::shutdown() {
	if ( !singletonInstance)
		return;

	delete singletonInstance;
	singletonInstance = 0;
}

} }
