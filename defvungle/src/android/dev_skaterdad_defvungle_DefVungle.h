#include <jni.h>
/* Header for class dev_skaterdad_defvungle_DefVungle */

#ifndef _Included_dev_skaterdad_defvungle_DefVungle
#define _Included_dev_skaterdad_defvungle_DefVungle
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     dev_skaterdad_defvungle_DefVungle
 * Method:    onVungleAdsReady
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_dev_skaterdad_defvungle_DefVungle_onVungleAdsReady
  (JNIEnv *, jclass, jstring);

/*
 * Class:     dev_skaterdad_defvungle_DefVungle
 * Method:    onVungleAdsStart
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_dev_skaterdad_defvungle_DefVungle_onVungleAdsStart
  (JNIEnv *, jclass, jstring);

/*
 * Class:     dev_skaterdad_defvungle_DefVungle
 * Method:    onVungleAdsError
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_dev_skaterdad_defvungle_DefVungle_onVungleAdsError
  (JNIEnv *, jclass, jstring);

/*
 * Class:     dev_skaterdad_defvungle_DefVungle
 * Method:    onVungleAdsFinish
 * Signature: (Ljava/lang/String)V
 */
JNIEXPORT void JNICALL Java_dev_skaterdad_defvungle_DefVungle_onVungleAdsFinish
  (JNIEnv *, jclass, jstring);

/*
 * Class:     dev_skaterdad_defvungle_DefVungle
 * Method:    onVungleAdsReward
 * Signature: (Ljava/lang/String)V
 */
JNIEXPORT void JNICALL Java_dev_skaterdad_defvungle_DefVungle_onVungleAdsReward
  (JNIEnv *, jclass, jstring);

//------

/*
* Class:     dev_skaterdad_defvungle_DefVungle
* Method:    onVungleAdsInitializationError
* Signature: (ILjava/lang/String;)V
*/
JNIEXPORT void JNICALL Java_dev_skaterdad_defvungle_DefVungle_onVungleAdsInitializationError
(JNIEnv *, jclass, jstring);

/*
* Class:     dev_skaterdad_defvungle_DefVungle
* Method:    onVungleAdsInitialized
* Signature: ()V
*/
JNIEXPORT void JNICALL Java_dev_skaterdad_defvungle_DefVungle_onVungleAdsInitialized
(JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif
#endif
