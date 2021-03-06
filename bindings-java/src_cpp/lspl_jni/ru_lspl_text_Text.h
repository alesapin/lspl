/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class ru_lspl_text_Text */

#ifndef _Included_ru_lspl_text_Text
#define _Included_ru_lspl_text_Text
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     ru_lspl_text_Text
 * Method:    create
 * Signature: (Ljava/lang/String;)Lru/lspl/text/Text;
 */
JNIEXPORT jobject JNICALL Java_ru_lspl_text_Text_create__Ljava_lang_String_2
  (JNIEnv *, jclass, jstring);

/*
 * Class:     ru_lspl_text_Text
 * Method:    create
 * Signature: (Ljava/lang/String;Lru/lspl/text/TextConfig;)Lru/lspl/text/Text;
 */
JNIEXPORT jobject JNICALL Java_ru_lspl_text_Text_create__Ljava_lang_String_2Lru_lspl_text_TextConfig_2
  (JNIEnv *, jclass, jstring, jobject);

/*
 * Class:     ru_lspl_text_Text
 * Method:    dump
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_ru_lspl_text_Text_dump
  (JNIEnv *, jobject);

/*
 * Class:     ru_lspl_text_Text
 * Method:    finalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ru_lspl_text_Text_finalize
  (JNIEnv *, jobject);

/*
 * Class:     ru_lspl_text_Text
 * Method:    internalGetWords
 * Signature: (I)[Lru/lspl/text/Word;
 */
JNIEXPORT jobjectArray JNICALL Java_ru_lspl_text_Text_internalGetWords
  (JNIEnv *, jobject, jint);

/*
 * Class:     ru_lspl_text_Text
 * Method:    internalGetMatches
 * Signature: (Lru/lspl/patterns/Pattern;)[Lru/lspl/text/Match;
 */
JNIEXPORT jobjectArray JNICALL Java_ru_lspl_text_Text_internalGetMatches
  (JNIEnv *, jobject, jobject);

#ifdef __cplusplus
}
#endif
#endif
