#include "Tests.h"

#include "../assertions/MatchingAssertions.h"

#include <fstream>
#include <iostream>

#include <lspl/Namespace.h>
#include <lspl/dictionaries/MemoryDictionary.h>
#include <lspl/patterns/Pattern.h>
#include <lspl/patterns/PatternBuilder.h>
#include <lspl/patterns/expressions/AttributeExpression.h>
#include <lspl/patterns/expressions/ConstantExpression.h>
#include <lspl/patterns/expressions/VariableExpression.h>
#include <lspl/patterns/restrictions/AgreementRestriction.h>
#include <lspl/text/Text.h>
#include <lspl/text/readers/PlainTextReader.h>

using namespace lspl::assertions;
using namespace lspl::patterns::expressions;
using namespace lspl::patterns::restrictions;
using namespace lspl::patterns::matchers;
using namespace lspl::text::attributes;

namespace lspl {
namespace tests {

static void testSimpleRightPart() {
    assertRightPart("белая шляпа", "Act = A N =text> N<c=gen> A", "ШЛЯПА БЕЛАЯ");
}

cute::suite rightPartSuite() {
    cute::suite s;

    s += CUTE(testSimpleRightPart);

    return s;
}

} // namespace tests
} // namespace lspl
