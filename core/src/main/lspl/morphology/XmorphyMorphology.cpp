#include "XmorphyMorphology.h"

#include <unordered_map>
#include <xmorphy/utils/UniString.h>
#include <xmorphy/tag/UniSPTag.h>
#include <xmorphy/tag/UniMorphTag.h>
#include <xmorphy/morph/WordForm.h>

namespace lspl {
namespace morphology {

using LSpeechPart = lspl::text::attributes::SpeechPart;
using XSpeechPart = X::UniSPTag;

namespace {


LSpeechPart getSpeechPart(const X::WordFormPtr & word_form, const X::MorphInfo & info)
{
  static const std::map<XSpeechPart, LSpeechPart> SP_MAPPING = {
      {XSpeechPart::X, LSpeechPart::WORD,},
      {XSpeechPart::NOUN, LSpeechPart::NOUN},
      {XSpeechPart::ADJ, LSpeechPart::ADJECTIVE},
      {XSpeechPart::VERB, LSpeechPart::VERB},
      {XSpeechPart::PRON, LSpeechPart::PRONOUN},
      {XSpeechPart::ADV, LSpeechPart::ADVERB},
      {XSpeechPart::CONJ, LSpeechPart::CONJUNCTION},
      {XSpeechPart::ADP, LSpeechPart::PREPOSITION},
      {XSpeechPart::PART, LSpeechPart::PARTICLE},
      {XSpeechPart::INTJ, LSpeechPart::INTERJECTION},
      {XSpeechPart::NUM, LSpeechPart::NUMERAL},
      {XSpeechPart::H, LSpeechPart::INTERJECTION},
      {XSpeechPart::DET, LSpeechPart::PRONOUN}};

    if (info.sp == XSpeechPart::VERB && (info.tag & X::UniMorphTag::Conv)) {
        return LSpeechPart::ADVERBIAL_PARTICIPLE;
    } else if (word_form->getType() == X::TokenTypeTag::NUMB) {
        return LSpeechPart::NUMERAL;
    }
    //std::cerr << "SEARCHING FOR:" << info.sp << std::endl;
    //std::cerr << "SPSIZE:" << SP_MAPPING.size() << std::endl;
    //std::cerr << "COUNT:" << SP_MAPPING.count(info.sp) << std::endl;
    return SP_MAPPING.at(info.sp);
}

enum class GramemeBits {
  rPlural = 0,
  rSingular = 1,
  rAllNumbers = (1 << rSingular) | (1 << rPlural),

  rNominativ = 2,
  rGenitiv = 3,
  rDativ = 4,
  rAccusativ = 5,
  rInstrumentalis = 6,
  rLocativ = 7,
  rVocativ = 8,
  rAllCases = (1 << rNominativ) | (1 << rGenitiv) | (1 << rDativ) |
              (1 << rAccusativ) | (1 << rInstrumentalis) | (1 << rVocativ) |
              (1 << rLocativ),

  rMasculinum = 9,
  rFeminum = 10,
  rNeutrum = 11,
  rMascFem = 12,
  rAllGenders = (1 << rMasculinum) | (1 << rFeminum) | (1 << rNeutrum),

  rPresentTense = 13,
  rFutureTense = 14,
  rPastTense = 15,
  rAllTimes = (1 << rPresentTense) | (1 << rFutureTense) | (1 << rPastTense),

  rFirstPerson = 16,
  rSecondPerson = 17,
  rThirdPerson = 18,
  rAllPersons =
      (1 << rFirstPerson) | (1 << rSecondPerson) | (1 << rThirdPerson),

  rImperative = 19,

  rAnimative = 20,
  rNonAnimative = 21,
  rAllAnimative = (1 << rAnimative) | (1 << rNonAnimative),

  rComparative = 22,

  rPerfective = 23,
  rNonPerfective = 24,

  rNonTransitive = 25,
  rTransitive = 26,

  rActiveVoice = 27,
  rPassiveVoice = 28,

  rIndeclinable = 29,
  rInitialism = 30,

  rPatronymic = 31,

  rToponym = 32,
  rOrganisation = 33,

  rQualitative = 34,
  rDeFactoSingTantum = 35,

  rInterrogative = 36,
  rDemonstrative = 37,

  rName = 38,
  rSurName = 39,
  rImpersonal = 40,
  rSlang = 41,
  rMisprint = 42,
  rColloquial = 43,
  rPossessive = 44,
  rArchaism = 45,
  rSecondCase = 46,
  rPoetry = 47,
  rProfession = 48,
  rSuperlative = 49,
  rPositive = 50,

  rShort = 51,
  rIndicative = 52,
  rUnkn = 63,
};

using XTag = X::UniMorphTag;
using LTag = lspl::text::attributes::AttributeValue;

struct TagAndBit
{
    LTag tag;
    GramemeBits bit;
};


uint64 getTagSet(const X::MorphInfo & mi)
{
    static const std::map<XTag, TagAndBit> TAG_MAPPING = {
        {XTag::UNKN, {LTag::UNDEFINED, GramemeBits::rUnkn}},
        {XTag::Nom, {LTag::NOMINATIVE, GramemeBits::rNominativ}},
        {XTag::Gen, {LTag::GENITIVE, GramemeBits::rGenitiv}},
        {XTag::Dat, {LTag::DATIVE, GramemeBits::rDativ}},
        {XTag::Acc, {LTag::ACCUSATIVE, GramemeBits::rAccusativ}},
        {XTag::Ins, {LTag::INSTRUMENTAL, GramemeBits::rInstrumentalis}},
        {XTag::Voc, {LTag::GENITIVE, GramemeBits::rVocativ}},
        {XTag::Loc, {LTag::PREPOSITIONAL, GramemeBits::rLocativ}},
        {XTag::Sing, {LTag::SINGULAR, GramemeBits::rSingular}},
        {XTag::Plur, {LTag::PLURAL, GramemeBits::rPlural}},
        {XTag::Masc, {LTag::MASCULINE, GramemeBits::rMasculinum}},
        {XTag::Fem, {LTag::FEMININE, GramemeBits::rFeminum}},
        {XTag::Neut, {LTag::NEUTER, GramemeBits::rNeutrum}},
        {XTag::Cmp, {LTag::COMPARATIVE, GramemeBits::rComparative}},
        {XTag::Sup, {LTag::SUPERLATIVE, GramemeBits::rSuperlative}},
        {XTag::Pres, {LTag::PRESENT, GramemeBits::rPresentTense}},
        {XTag::Past, {LTag::PAST, GramemeBits::rPastTense}},
        {XTag::Fut, {LTag::FUTURE, GramemeBits::rFutureTense}},
        {XTag::Anim, {LTag::ANIMATE, GramemeBits::rAnimative}},
        {XTag::Inan, {LTag::INANIMATE, GramemeBits::rNonAnimative}},
        {XTag::Short, {LTag::SHORT, GramemeBits::rShort}},
        {XTag::Ind, {LTag::INDICATIVE, GramemeBits::rIndicative}},
        {XTag::Imp, {LTag::IMPERATIVE, GramemeBits::rImperative}},
        {XTag::_1, {LTag::FIRST, GramemeBits::rFirstPerson}},
        {XTag::_2, {LTag::SECOND, GramemeBits::rSecondPerson}},
        {XTag::_3, {LTag::THIRD, GramemeBits::rThirdPerson}},
    };

    uint64 result{};
    for (auto itr = XTag::begin(); itr != XTag::end(); ++itr)
    {
        const auto & current_tag = *itr;
        if (current_tag == XTag::UNKN)
            continue;
        if (mi.tag.contains(current_tag) && TAG_MAPPING.count(current_tag))
        {
            uint64_t bit = static_cast<uint64_t>(TAG_MAPPING.at(current_tag).bit);
            result |= (1UL << bit);
        }
    }
    return result;
}

}

std::string XmorphyMorphology::upcase(const char *str) {
    utils::UniString tmpstr(str);
    tmpstr.toUpperCaseInPlace();
    return tmpstr.getRawString();
}

std::string XmorphyMorphology::upcase(const char *start, const char *end) {
    utils::UniString tmpstr(start, end);
    tmpstr.toUpperCaseInPlace();
    return tmpstr.getRawString();
}

std::string XmorphyMorphology::lowcase(const char *str) {
    utils::UniString tmpstr(str);
    tmpstr.toLowerCaseInPlace();
    return tmpstr.getRawString();
}

std::string XmorphyMorphology::lowcase(const char *start, const char *end) {
  utils::UniString tmpstr(start, end);
  tmpstr.toLowerCaseInPlace();
  return tmpstr.getRawString();
}

void XmorphyMorphology::appendWordForms(
    const std::string &token, boost::ptr_vector<WordForm> &forms) {

    utils::UniString word(token);
    auto token_ptr = tokenizer.analyzeSingleWord(word);
    auto word_form = analyzer.analyzeSingleToken(token_ptr);

    for (const auto & morph_info : word_form->getMorphInfo())
    {
        auto sp = getSpeechPart(word_form, morph_info);
        uint64 *tag_sets = new uint64[1];
        tag_sets[0] = getTagSet(morph_info);
        const utils::UniString & nf = morph_info.normalForm;
        utils::UniString stem = nf.subString(0, morph_info.stemLen);
        forms.push_back(new WordForm(sp, nf.getRawString(), stem.getRawString(), tag_sets, 1));
    }
}
}
}
