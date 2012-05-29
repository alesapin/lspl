#include <iostream>
#include <lspl/Namespace.h>
#include <lspl/patterns/PatternBuilder.h>
#include <lspl/patterns/Pattern.h>
#include <lspl/text/readers/PlainTextReader.h>
#include <lspl/text/Text.h>
#include <fstream>
#include <lspl/text/Match.h>
#include <cstdlib>
#include <lspl/transforms/TextTransformBuilder.h>

using namespace std;

int main(int argc, char** argv) {
	lspl::NamespaceRef ns = new lspl::Namespace();
	lspl::patterns::PatternBuilderRef builder = new lspl::patterns::PatternBuilder(ns, new lspl::transforms::TextTransformBuilder(ns));
	//������� ���� �������������� � ����������� ���
	builder->build("NA = {A}<1,3> =text> A '==NORMALIZE=>' #A");
	//������� ������ NA (�� ��� ��������!) � ��. �������, � ������ ��������������� (������ ������������)
	builder->build("NG = NA N1 N2 =text> '[' NA ']' N1");
	//������� �������������� � ������� NG � ��. ������� (�� ��� �� ��������! �.�. N2 �������� �� �����!)
	builder->build("NF = A1 NG =text> A1 '[' NG ']'");
	lspl::patterns::PatternRef pattern = ns->getPatternByName("NF");

	lspl::text::readers::PlainTextReader reader;
	lspl::text::TextRef text = reader.readFromStream( cin );

	lspl::text::MatchList matches = text->getMatches( pattern );

	for(int i=0; i<matches.size(); i++) {
		cout<<matches[i]->getVariants().at(0)->getTransformResult<std::string>()<<endl;
	}
				
	return 0;
}
