#include "../../base/BaseInternal.h"

#include "AttributeKey.h"
#include "IndexedEntryManager.h"

namespace lspl { namespace text { namespace attributes {

class IndexedAttributeKeyManager : public IndexedEntryManager {
public:
	IndexedAttributeKeyManager() {
		add( 0, "un", "unedfined", "������������" );
		add( 1, "c", "case", "�����" );
		add( 2, "n", "number", "�����" );
		add( 3, "g", "gender", "���" );
		add( 4, "doc", "degree of comparsion", "������� ���������" );
		add( 5, "t", "tense", "�����" );
		add( 6, "a", "animate", "��������������" );
		add( 7, "f", "form", "�����" );
		add( 8, "m", "mode", "����������" );
		add( 9, "p", "person", "����" );
		add( 10, "r", "reflexive", "������������" );
		add( 11, "b", "base", "��������� �����" );
		add( 12, "x", "text", "�����" );
		add( 13, "st", "stem", "������" );
	};
};

static IndexedAttributeKeyManager indexedAttributeKeyManager;

const AttributeKey AttributeKey::UNDEFINED = AttributeKey( 0 );

const AttributeKey AttributeKey::CASE = AttributeKey( 1 );
const AttributeKey AttributeKey::NUMBER = AttributeKey( 2 );
const AttributeKey AttributeKey::GENDER = AttributeKey( 3 );
const AttributeKey AttributeKey::DOC = AttributeKey( 4 );
const AttributeKey AttributeKey::TENSE = AttributeKey( 5 );
const AttributeKey AttributeKey::ANIMATE = AttributeKey( 6 );
const AttributeKey AttributeKey::FORM = AttributeKey( 7 );
const AttributeKey AttributeKey::MODE = AttributeKey( 8 );
const AttributeKey AttributeKey::PERSON = AttributeKey( 9 );
const AttributeKey AttributeKey::REFLEXIVE = AttributeKey( 10 );
const AttributeKey AttributeKey::BASE = AttributeKey( 11 );
const AttributeKey AttributeKey::TEXT = AttributeKey( 12 );
const AttributeKey AttributeKey::STEM = AttributeKey( 13 );

/**
 * �������� ����� ���������� ������������������ ����������
 */
uint AttributeKey::count() {
	return indexedAttributeKeyManager.map.size();
}

/**
 * ����� �������� �� ��� ������������
 */
AttributeKey AttributeKey::findByAbbrevation( const std::string & abbrevation ) {
	IndexedAttributeKeyManager::Iterator i = indexedAttributeKeyManager.map.find( abbrevation );

	if ( i == indexedAttributeKeyManager.map.end() )
		return AttributeKey( 0 );

	return AttributeKey( (*i)->id );
}

/**
 * ���������������� ����� ��������
 */
AttributeKey AttributeKey::create( const std::string & abbrevation, const std::string & name, const std::string & title ) {
	return AttributeKey( indexedAttributeKeyManager.add( indexedAttributeKeyManager.map.size(), abbrevation, name, title ) );
}

const std::string & AttributeKey::getAbbrevation() const {
	return indexedAttributeKeyManager.at( index ).abbrevation;
}

const std::string & AttributeKey::getName() const {
	return indexedAttributeKeyManager.at( index ).name;
}

const std::string & AttributeKey::getTitle() const {
	return indexedAttributeKeyManager.at( index ).title;
}


} } } // namespace lspl::text::attributes
