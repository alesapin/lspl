/*
 * CurrentAnnotationExpression.h
 *
 *  Created on: Nov 3, 2008
 *      Author: alno
 */

#ifndef _LSPL_PATTERNS_EXPRESSIONS_CURRENTANNOTATIONEXPRESSION_H_
#define _LSPL_PATTERNS_EXPRESSIONS_CURRENTANNOTATIONEXPRESSION_H_

#include "../../base/Base.h"
#include "Expression.h"
#include "../matchers/Variable.h"

namespace lspl { namespace patterns { namespace expressions {

class LSPL_EXPORT CurrentAnnotationExpression : public Expression {
public:
	CurrentAnnotationExpression();
	virtual ~CurrentAnnotationExpression();

	virtual void evaluateTo( const text::Transition * currentAnnotation, const matchers::Variable currentVar, const matchers::Context & ctx, ValueList & results ) const;

	virtual void dump( std::ostream & out, const std::string & tabs = "" ) const;
	virtual bool equals( const Expression & e ) const;

	virtual bool containsVariable( matchers::Variable var ) const;
	virtual bool containsVariables() const;
	virtual bool containsCurrentAnnotation() const;
};

} } }

#endif//_LSPL_PATTERNS_EXPRESSIONS_CURRENTANNOTATIONEXPRESSION_H_
