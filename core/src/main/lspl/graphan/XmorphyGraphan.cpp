#include "XmorphyGraphan.h"
#include <xmorphy/utils/UniString.h>
#include <xmorphy/tag/TokenTypeTag.h>

namespace lspl {
namespace graphan {

static Unit * tokenToUnit(X::TokenPtr token) {
    Unit::Type result_type = Unit::Type::UNKNOWN;
    if (token->getType() == X::TokenTypeTag::PNCT)
        result_type = Unit::Type::PUNCT;
    else if (token->getType() == X::TokenTypeTag::WORD ||
             token->getType() == X::TokenTypeTag::WRNM)
        result_type = Unit::Type::WORD;

    return new Unit(token->toString().getRawString(), token->getStartPosByte(), result_type);
}

void XmorphyGraphan::analyzeString(const std::string &str,
                                   boost::ptr_vector<Unit> &units)
{
    auto tokens = tokenizer.analyze(utils::UniString(str));
    for (const auto & token : tokens)
        units.push_back(tokenToUnit(token));
}

}
}