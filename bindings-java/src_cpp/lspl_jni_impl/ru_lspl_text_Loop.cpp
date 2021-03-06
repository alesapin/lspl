#include "lspl_jni/ru_lspl_text_Loop.h"

#include "lspl/text/Loop.h"
#include "lspl/text/JavaLoop.h"
#include "lspl/java/Utils.h"

using namespace lspl::java;
using namespace lspl::text;

/*
 * Class:     ru_lspl_text_Loop
 * Method:    getIterationCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ru_lspl_text_Loop_getIterationCount (JNIEnv * env, jobject obj) {
	try {
		return JavaTransition::get( env, obj )->transition.cast<Loop>()->getIterations().size();
	} catch ( const std::exception & ex ) {
		throwRuntimeException( env, ex.what() );
		return 0;
	} catch ( ... ) {
		throwRuntimeException( env, "Unknown error" );
		return 0;
	}
}

/*
 * Class:     ru_lspl_text_Loop
 * Method:    getIteration
 * Signature: (I)Lru/lspl/text/LoopIteration;
 */
JNIEXPORT jobject JNICALL Java_ru_lspl_text_Loop_getIteration (JNIEnv * env, jobject obj, jint index) {
	try {
		return JavaTransition::get( env, JavaTransition::get( env, obj )->transition.cast<Loop>()->getIterations().at( index ).get() )->object;
	} catch ( const std::exception & ex ) {
		throwRuntimeException( env, ex.what() );
		return 0;
	} catch ( ... ) {
		throwRuntimeException( env, "Unknown error" );
		return 0;
	}
}
