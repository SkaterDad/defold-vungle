package dev.skaterdad.defvungle;

import android.app.Activity;
import android.content.Context;
import android.graphics.PixelFormat;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.view.ViewGroup.MarginLayoutParams;
import android.view.WindowManager;
import android.widget.LinearLayout;
import android.view.Gravity;
import android.os.Build;

import com.vungle.warren.AdConfig;
import com.vungle.warren.InitCallback;
import com.vungle.warren.LoadAdCallback;
import com.vungle.warren.PlayAdCallback;
import com.vungle.warren.Vungle;
import com.vungle.warren.error.VungleException;

public class DefVungle {

    public static native void onVungleAdsReady(String placementId);
    public static native void onVungleAdsStart(String placementId);
    public static native void onVungleAdsError(String placementId, String message);
    public static native void onVungleAdsFinish(String placementId);
    public static native void onVungleAdsReward(String placementId);

    public static native void onVungleAdsInitializationError(String message);
    public static native void onVungleAdsInitialized();

    //-----

    private DefVungleListener defVungleAdsListener;
    private DefVungleInitializationListener defVungleAdsInitListener;
    private Activity activity;

    public DefVungle(Activity appActivity) {
        activity = appActivity;
    }

    public void initialize(String gameId) {
        Vungle.init(gameId, activity, new InitCallback() {
            @Override
            public void onSuccess() {
                DefVungle.onVungleAdsInitialized();
            }

            @Override
            public void onError(VungleException error) {
                DefVungle.onVungleAdsInitializationError(error.getLocalizedMessage());
            }

            @Override
            public void onAutoCacheAdAvailable(String placementId) {
                DefVungle.onVungleAdsReady(placementId);
            }
        });
    }

    public void load(String placementId) {
        if (Vungle.isInitialized()) {
            Vungle.loadAd(placementId, vungleLoadAdCallback);
        }
    }

    public void show(String placementId) {
        if (Vungle.canPlayAd(placementId)) { 
            Vungle.playAd(placementId, null, vunglePlayAdCallback);
        }
    }

    public boolean isReady(String placementId) {
        if (placementId == null || placementId.isEmpty()) {
            return false;
        }
        return Vungle.canPlayAd(placementId);
    }

    public boolean isInitialized() {
        return Vungle.isInitialized();
    }

    private final LoadAdCallback vungleLoadAdCallback = new LoadAdCallback() { 
        @Override
        public void onAdLoad(String placementId) { 
            DefVungle.onVungleAdsReady(placementId);
        } 

        @Override 
        public void onError(String placementId, VungleException error) { 
            DefVungle.onVungleAdsError(placementId, error.getLocalizedMessage());
        }
    };

    private final PlayAdCallback vunglePlayAdCallback = new PlayAdCallback() {
        @Override
        public void onAdStart(String id) { 
            DefVungle.onVungleAdsStart(id);
        }
        
        @Override
        public void onAdViewed(String id) { 
            // Ad has rendered
        }

        @Override
        public void onAdEnd(String id) {
            DefVungle.onVungleAdsFinish(id);
        }

        @Override
        public void onAdClick(String id) {
            // User clicked on ad
        }

        @Override
        public void onAdRewarded(String id) {
            DefVungle.onVungleAdsReward(id);
        }

        @Override
        public void onAdLeftApplication(String id) {
            DefVungle.onVungleAdsError(id, "User exited during ad.");
        }

        @Override
        public void onError(String id, VungleException exception) { 
            DefVungle.onVungleAdsError(id, error.getLocalizedMessage());
        }
    }

}
