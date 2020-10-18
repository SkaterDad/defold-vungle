# Keep filenames and line numbers for stack traces
-keepattributes SourceFile,LineNumberTable

# Keep JavascriptInterface for WebView bridge
-keepattributes JavascriptInterface

# Sometimes keepattributes is not enough to keep annotations
-keep class android.webkit.JavascriptInterface {
   *;
}

# Keep all classes in Vungle Ads package
-keep class com.vungle3d.ads.** {
   *;
}

# Keep all classes in Vungle Services package
-keep class com.vungle3d.services.** {
   *;
}

-keep class com.agulev.defvungle.** {
	*;
}

-dontwarn com.google.ar.core.**

-keep public class android.net.http.SslError
-keep public class android.webkit.WebViewClient

-dontwarn android.webkit.WebView
-dontwarn android.net.http.SslError
-dontwarn android.webkit.WebViewClient

-dontwarn android.telephony.**
