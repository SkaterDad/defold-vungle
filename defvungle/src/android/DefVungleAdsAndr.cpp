#if defined(DM_PLATFORM_ANDROID)
#include "../private_DefVungleCallback.h"
#include "../private_DefVungle.h"
#include "dev_skaterdad_defvungle_DefVungle.h"
#include "jni.h"

JNIEXPORT void JNICALL Java_dev_skaterdad_defvungle_DefVungle_onVungleAdsReady(JNIEnv *env, jclass jcls, jstring jstr)
{
  const char* ch = env->GetStringUTFChars(jstr, 0);
  dmVungleAds::AddToQueue((int)dmVungleAds::TYPE_IS_READY,(char*)"placementId", (char*)ch, NULL, NULL);
  env->ReleaseStringUTFChars(jstr, ch);
}

JNIEXPORT void JNICALL Java_dev_skaterdad_defvungle_DefVungle_onVungleAdsStart(JNIEnv *env, jclass jcls, jstring jstr)
{
  const char* ch = env->GetStringUTFChars(jstr, 0);
  dmVungleAds::AddToQueue((int)dmVungleAds::TYPE_DID_START,(char*)"placementId", (char*)ch, NULL, NULL);
  env->ReleaseStringUTFChars(jstr, ch);
}

JNIEXPORT void JNICALL Java_dev_skaterdad_defvungle_DefVungle_onVungleAdsError(JNIEnv *env, jclass jcls, jstring jstrPid, jstring jstrErr)
{
  const char* chPid = env->GetStringUTFChars(jstrPid, 0);
  const char* chErr = env->GetStringUTFChars(jstrErr, 0);
  dmVungleAds::AddToQueue((int)dmVungleAds::TYPE_DID_ERROR,(char*)"placementId", (char*)chPid, (char*)"message", (char*)chErr);
  env->ReleaseStringUTFChars(jstrPid, chPid);
  env->ReleaseStringUTFChars(jstrErr, chErr);
}

JNIEXPORT void JNICALL Java_dev_skaterdad_defvungle_DefVungle_onVungleAdsFinish(JNIEnv *env, jclass jcls, jstring jstr)
{
  const char* ch = env->GetStringUTFChars(jstr, 0);
  dmVungleAds::AddToQueue((int)dmVungleAds::TYPE_DID_FINISH,(char*)"placementId", (char*)ch, NULL, NULL);
  env->ReleaseStringUTFChars(jstr, ch);
}

JNIEXPORT void JNICALL Java_dev_skaterdad_defvungle_DefVungle_onVungleAdsReward(JNIEnv *env, jclass jcls, jstring jstr)
{
  const char* ch = env->GetStringUTFChars(jstr, 0);
  dmVungleAds::AddToQueue((int)dmVungleAds::TYPE_DID_REWARD,(char*)"placementId", (char*)ch, NULL, NULL);
  env->ReleaseStringUTFChars(jstr, ch);
}

//----

JNIEXPORT void JNICALL Java_dev_skaterdad_defvungle_DefVungle_onVungleAdsInitializationError(JNIEnv *env, jclass jcls, jstring jstr)
{
  const char* ch = env->GetStringUTFChars(jstr, 0);
  dmVungleAds::AddToQueue((int)dmVungleAds::TYPE_INIT_ERROR,(char*)"message", (char*)ch, NULL, NULL);
  env->ReleaseStringUTFChars(jstr, ch);
}

JNIEXPORT void JNICALL Java_dev_skaterdad_defvungle_DefVungle_onVungleAdsInitialized(JNIEnv *env, jclass jcls)
{
  dmVungleAds::AddToQueue((int)dmVungleAds::TYPE_INITIALIZED, NULL, NULL, NULL, NULL);
}

//--------------------------------------------

namespace dmVungleAds {

struct DefVungleClass
{
  jobject                 m_DUADS_JNI;

  jmethodID               m_initialize;
  jmethodID               m_show;
  jmethodID               m_load;
  jmethodID               m_isReady;
  jmethodID               m_isInitialized;
};

DefVungleClass g_duads;

void InitExtension() {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;
  ClassLoader class_loader = ClassLoader(env);
  jclass cls = class_loader.load("dev/skaterdad/defvungle/DefVungle");
  
  g_duads.m_initialize = env->GetMethodID(cls, "initialize", "(Ljava/lang/String;)V");
  g_duads.m_load = env->GetMethodID(cls, "load", "(Ljava/lang/String;)V");
  g_duads.m_show = env->GetMethodID(cls, "show", "(Ljava/lang/String;)V");
  g_duads.m_isReady = env->GetMethodID(cls, "isReady", "(Ljava/lang/String;)Z");
  g_duads.m_isInitialized = env->GetMethodID(cls, "isInitialized", "()Z");

  jmethodID jni_constructor = env->GetMethodID(cls, "<init>", "(Landroid/app/Activity;)V");
  g_duads.m_DUADS_JNI = env->NewGlobalRef(env->NewObject(cls, jni_constructor, dmGraphics::GetNativeAndroidActivity()));
}

void initialize(const char*game_id) {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;

  jstring appid = env->NewStringUTF(game_id);
  env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_initialize, appid);
  env->DeleteLocalRef(appid);
}

void FinalizeExtension() {
}

void load(char* placementId) {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;

  jstring jplacementId = env->NewStringUTF(placementId);
  env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_load, jplacementId);
  env->DeleteLocalRef(jplacementId);
}

void show(char* placementId) {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;

  jstring jplacementId = env->NewStringUTF(placementId);
  env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_show, jplacementId);
  env->DeleteLocalRef(jplacementId);
}

bool isReady(char* placementId) {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;
  
  jstring jplacementId = env->NewStringUTF(placementId);
  jboolean return_value = (jboolean)env->CallBooleanMethod(g_duads.m_DUADS_JNI, g_duads.m_isReady, jplacementId);
  env->DeleteLocalRef(jplacementId);

  return JNI_TRUE == return_value;
}

bool isInitialized() {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;
  
  jboolean return_value = (jboolean)env->CallBooleanMethod(g_duads.m_DUADS_JNI, g_duads.m_isInitialized);

  return JNI_TRUE == return_value;
}

} //namespaces

#endif
