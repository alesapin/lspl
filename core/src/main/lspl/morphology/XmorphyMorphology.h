#pragma once

#include "Morphology.h"
#include <xmorphy/morph/Processor.h>
#include <xmorphy/graphem/Tokenizer.h>

namespace lspl {
namespace morphology {
class XmorphyMorphology : public Morphology
{
 public:
    //std::string getAttributesString(uint64 attValues) override;
   void appendWordForms(const std::string &token, boost::ptr_vector<WordForm> &forms) override;
   std::string upcase(const char *str) override;
   std::string upcase(const char *start, const char *end) override;

   std::string lowcase(const char *str) override;
   std::string lowcase(const char *start, const char *end) override;

   ~XmorphyMorphology() override {};

 private:
   X::Tokenizer tokenizer;
   X::Processor analyzer;
};

}
} // namespace lspl
