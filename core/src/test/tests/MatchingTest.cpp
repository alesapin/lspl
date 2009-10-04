/*
 * MatchingText.cpp
 *
 *  Created on: Sep 28, 2008
 *      Author: alno
 */

#include "Tests.h"

#include "../assertions/MatchingAssertions.h"

#include <iostream>
#include <fstream>

#include <lspl/Namespace.h>
#include <lspl/patterns/Pattern.h>
#include <lspl/patterns/PatternBuilder.h>
#include <lspl/text/Text.h>
#include <lspl/text/readers/PlainTextReader.h>
#include <lspl/dictionaries/MemoryDictionary.h>

using namespace lspl::assertions;

namespace lspl { namespace tests {

void testMatching() {
	std::cout << "Testing matching..." << std::endl;

	// Regexp tokens
	assertMatches( "����", 0, 1, "'����'" );
	assertMatches( "����", 0, 1, "'��.*�'" );
	assertMatches( "����", 0, 1, "'��.*�'" );
	assertMatches( "������", 0, 1, "'��.*�'" );
	assertNoMatches( "�����", "'��.*�'" );

	// Simple
	assertMatches( "���� ���� ����", 0, 2, "Act = N V" );
	assertMatches( "���� ���� ����", 0, 2, "Act = N<����> V" );
	assertMatches( "���� ���� ����", 0, 2, "Act = N V<N=V>" );
	assertMatches( "���� ���� ����", 0, 2, "Act = N { V<N=V> }<1,1>" );
	assertMatches( "���� ���� ����", 0, 2, "Act = N { { V<N=V> }<1,1> }<1,1>" );
	assertMatches( "���� ���� ����", 0, 2, "Act = N V<N.g=V.g>" );
	assertMatches( "���� ���� ����", 0, 2, "Act = N<g=fem> V" );
	assertMatches( "���� ���� ����", 0, 2, "Act = \"����\" V" );
	assertNoMatches( "���� ���� ����", "Act = N<����> V" );

	// Term
	assertMatches( "��������� ���� ������", 0, 3, "\"���������\" \"����\" \"������\"" );
	assertMatches( "��������� ���� ������", 0, 3, "N1<���������> { \"����\" \"������\" | \"�����-������\" }<1,1>" );

	// Loop restrictions: positive
	assertMatches( "���� ���� ����", 0, 2, "Act = {N} V" );
	assertMatches( "���� ���� ����", 0, 2, "Act = {N} V<N=V>" );
	assertMatches( "���� ���� ����", 0, 2, "Act = {N} V<N.g=V.g>" );

	// Loop restriction: empty loop
	assertMatches( "���� ���� ����", 0, 1, "Act = [A] N" );
	assertMatches( "���� ���� ����", 0, 1, "Act = {A} N" );
	assertMatches( "���� ���� ����", 0, 1, "Act = {A} N <A=N>" );

	// Multiple equality: positive
	assertMatches( "����� ����� ���� ����", 0, 3, "Act = A N V<A=N=V>" );
	assertMatches( "����� ����� ���� ����", 0, 3, "Act = A N V<A.g=N.g=V.g>" );

	// Multiple equality: negative
	assertNoMatches( "����� ����� ���� ����", "Act = A N V<A=N=V>" );
	assertNoMatches( "����� ��� ���� ����", "Act = A N V<A=N=V>" );
	assertNoMatches( "����� ����� ��� ����", "Act = A N V<A=N=V>" );
	assertNoMatches( "����� ����� ���� ����", "Act = A N V<A.g=N.g=V.g>" );

	// Base equality
	assertMatches( "����, ����, ��� � ���� ������?", 0, 3, "Act = W1 \",\" W2 <W1.b=W2.b>" );

	assertNoMatches( "��� ������� �� ����", "Act = N<g=fem> V" );
	assertNoMatches( "��� �������� �� ����", "Act = N V<N=V>" );
	assertNoMatches( "��� ������� �� ����", "Act = W1 W2 <W1.b=W2.b>" );

	assertMatches( "���� ���� ����", 0, 2, "Act = N V<N=V> ( N V )" );

	std::cout << "Testing simple reusing..." << std::endl;
	{
		NamespaceRef ns = new Namespace();

		assertMatches( ns, "����� ����� ��� �� �������", 0, 1, "AA = A (A) | Pa (Pa)" );
		assertMatches( ns, "����� ����� ��� �� �������", 0, 2, "TestA = AA N" );
		assertMatches( ns, "����� ����� ��� �� �������", 0, 2, "TestB = AA N <AA=N>" );
	}
	{
		NamespaceRef ns = new Namespace();

		assertNoMatches( ns, "���� ���� ����", "AA = A (A) | Pa (Pa)" );
		assertMatches( ns, "���� ���� ����", 0, 1, "TestA = {AA} N" );
		assertMatches( ns, "���� ���� ����", 0, 1, "TestB = {AA} N <Ap=N>" );
	}

	std::cout << "Testing matching in one namespace..." << std::endl;
	{
		NamespaceRef ns = new Namespace();

		assertMatches( ns, "���� ���� ����", 0, 1, "UN = N" );
		assertMatches( ns, "���� ���� ����", 0, 2, "AB = UN V" );
		assertMatches( ns, "���� ���� ����", 0, 2, "AC = UN V <UN=V>" );
	}

	std::cout << "Testing matching with compound attributes..." << std::endl;
	{
		NamespaceRef ns = new Namespace();
		patterns::PatternBuilderRef builder = new patterns::PatternBuilder( ns );

		builder->build( "UV = V (V AS src)" );
		builder->build( "UUV = UV ( UV.src )" );

		assertMatches( ns, "���� ���� ����", 0, 2, "AA = N UV (UV)" );
		assertMatches( ns, "���� ���� ����", 0, 2, "AB = N UUV <N=UUV> (UUV)" );
		assertMatches( ns, "��� ���� ����", 0, 2, "AC = N UUV <N=UUV> (UUV)" ); // TODO ��� ����� ��� ��������
	}

	std::cout << "Testing matching with dictionaries..." << std::endl;
	{
		base::Reference<dictionaries::MemoryDictionary> d = new dictionaries::MemoryDictionary( "DIC" );
		d->add( "����", "����" );

		NamespaceRef ns = new Namespace();
		ns->addDictionary( d );

		assertMatches( ns, "���� ���� ����", 1, 3, "AA = W1 W2 <DIC(W1,W2)>" );
		assertNoMatches( ns, "���� ���� ����", "AB = W1 W2 <DIC(W1,W2)>" );
	}
}

} }
