#pragma once

#include "Graphan.h"
#include <xmorphy/graphem/Tokenizer.h>

namespace lspl {
namespace graphan
{

class XmorphyGraphan : public lspl::graphan::Graphan {

public:
    XmorphyGraphan() = default;
    ~XmorphyGraphan() override = default;

    void analyzeString(const std::string &str,
                   boost::ptr_vector<Unit> &units) override;
private:
    X::Tokenizer tokenizer;
};
} // namespace graphan
}
