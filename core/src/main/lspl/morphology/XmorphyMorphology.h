#pragma once

#include "Morphology.h"
#include <xmorphy/morph/Processor.h>
#include <xmorphy/graphem/Tokenizer.h>

#include <string>

namespace lspl {
namespace morphology {

class XmorphyMorphology : public Morphology
{
 public:
   void appendWordForms(const std::string &token, boost::ptr_vector<WordForm> &forms) override;

   std::unique_ptr<WordForm>
   synthesize(const std::string &token,
              text::attributes::SpeechPart requiredSpeechPart,
              uint64 requiredAttributesBits, std::string &formText) override;

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
