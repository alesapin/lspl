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
    assertRightPart("белая шляпа", "Act = A N =text> N<c=gen> A", "ШЛЯПЫ БЕЛАЯ");
    assertRightPart("белая шляпа", "Act = A N =text> N A<g=masc>", "ШЛЯПА БЕЛЫЙ");
    assertRightPart("белая шляпа", "Act = A N =text> N A<g=masc,c=gen>","ШЛЯПА БЕЛОГО");
    assertRightPart("белая шляпа", "Act = A N =text> N<c=gen,n=plur> A<g=neut>", "ШЛЯП БЕЛОЕ");

    NamespaceRef ns = new Namespace();
    assertRightPartNS(ns, "красивый слон", "AN = A N <A=N> (N.n) =text> A N", "КРАСИВЫЙ СЛОН");
    assertRightPartNS(ns, "красивый слон", "ANN = A N <A=N> (N) =text> A N",
                      "КРАСИВЫЙ СЛОН");

    assertRightPartNS(ns, "владельцем торговых складов", "ANaa = N AN =text> AN N <AN.n ~> N.n>", "ТОРГОВЫХ СКЛАДОВ ВЛАДЕЛЬЦЕМ");
    assertRightPartNS(ns, "владельцем торговых складов", "ANab = N AN =text> AN N <N.n ~> AN.n>", "ТОРГОВЫХ СКЛАДОВ ВЛАДЕЛЬЦАМИ");
    assertRightPartNS(ns, "владельцем торговых складов",
                      "ANac = N AN =text> AN N <AN ~> N>",
                      "ТОРГОВЫХ СКЛАДОВ ВЛАДЕЛЬЦЕМ");

    assertRightPartNS(ns, "владельцем торговых складов",
                      "ANad = N AN =text> AN N <N ~> AN>",
                      "ТОРГОВЫХ СКЛАДОВ ВЛАДЕЛЬЦАМИ");

    /// Don't work for some reason
    //assertRightPartNS(ns, "владельцем торговых складов",
    //                  "ANae = N AN =text> AN N <N.c ~> AN.c>",
    //                  "ТОРГОВЫХ СКЛАДОВ ВЛАДЕЛЕЦ");

    assertRightPartNS(ns, "владельцем торговых складов",
                      "ANaf = N AN =text> AN N <N ~> AN>",
                      "ТОРГОВЫХ СКЛАДОВ ВЛАДЕЛЬЦАМИ");

    assertRightPartNS(ns, "владельцем торговых складов",
                      "ANag = N AN =text> AN N <N.t ~> AN.t>",
                      "ТОРГОВЫХ СКЛАДОВ ВЛАДЕЛЬЦЕМ");

    assertRightPartNS(ns, "владельцем торговых складов",
                      "ANba = N ANN =text> ANN N <N ~> ANN>",
                      "ТОРГОВЫХ СКЛАДОВ ВЛАДЕЛЬЦЕВ");

    assertRightPartNS(ns, "владельцем торговых складов",
                      "ANbb = N ANN =text> ANN N <ANN ~> N>",
                      "ТОРГОВЫХ СКЛАДОМ ВЛАДЕЛЬЦЕМ");

    assertRightPartNS(ns, "владельцем торговых складов",
                      "ANbc = N ANN =text> ANN N <ANN.c ~> N.c>",
                      "ТОРГОВЫХ СКЛАДАМИ ВЛАДЕЛЬЦЕМ");

    assertRightPartNS(ns, "владельцем торговых складов",
                      "ANbd = N ANN =text> ANN N <ANN.t ~> N.t>",
                      "ТОРГОВЫХ СКЛАДОВ ВЛАДЕЛЬЦЕМ");
}

static void testMoreComplexRightPart() {

  assertRightPart("они махали зелеными и синими ленточками",
                  "SCC = A1 Cn A2 N <A1=A2=N> =text> A1 N<c=gen> \"+++\" A2<c=ins> #N<A1 ~> N, A2 ~> N>",
                             "ЗЕЛЕНЫМИ ЛЕНТОЧКА +++ СИНИМИ ЛЕНТОЧКА");

  NamespaceRef ns = new Namespace();

  assertRightPartNS(ns, "красивый слон", "NG = {A} N <A=N> (N) =text> A #N <A~>N> \";\"",
                    "КРАСИВЫЙ ;");

  assertRightPartNS(ns, "он увидел красную узкую полосу далекого заката",
                    "SN = NG1 NG2<c=gen> =text> #NG1 NG2 \";\" #NG2",
                    "КРАСНАЯ УЗКАЯ ПОЛОСА ; ДАЛЕКИЙ ЗАКАТ ; ; ДАЛЕКИЙ ЗАКАТ ;");
}

cute::suite rightPartSuite() {
    cute::suite s;

    s += CUTE(testSimpleRightPart);
    s += CUTE(testMoreComplexRightPart);

    return s;
}

} // namespace tests
} // namespace lspl
