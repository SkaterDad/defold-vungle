# DefVungle - Defold Vungle Video Ads

This is a [Defold Game Engine](https://defold.com) native extension which provides [Vungle Video Ads](https://vungle.com/monetize/) support.

Platforms supported are Android & Amazon Fire (aka. Android without Google Play services).  Most ad networks with rewarded video do not support these Amazon devices, but Vungle does!

*Disclaimer: This extension is independent and unofficial, and not associated with Vungle in any way.*

Vundle SDK Version 6.11.0

https://github.com/Vungle/Android-SDK/blob/master/CHANGELOG.md

## Installation

You can use the DefVungle extension in your own project by adding this project as a [Defold library dependency](http://www.defold.com/manuals/libraries/). Open your `game.project` file and add the latest release ZIP file URL to your dependencies:

> https://github.com/SkaterDad/defold-vungle/archive/1.1.0.zip

If you prefer to walk on the wild side, you could point directly to the latest code, but I would not recommend it!

## How to use

There is an example project in this repo which walks through the features.  Here is a general overview.

### 0. Set up an app on Vungle

Make sure you sign up on Vungle and create an application.

### 1. Initialize Vungle SDK

```lua
-- Define a callback function which handles Vungle-related events
local function defunityads_callback(self, msg_type, message)
  -- if msg_type == ____ then
  -- etc...
end

local function init_vungle()
  if vungle then
    vungle.init("my_vungle_app_id", defvungle_callback)
  end
end

```

### 2. Load some ads

```lua
local function load_vungle_ads()
  if vungle then
    vungle.load("VIDEO-12345")
    vungle.load("REWARDED-12345")
  end
end
```

### 3A. Show a video ad
```lua
  -- When ad is finished, the callback will receive a TYPE_DID_FINISH event.
  if vungle and vungle.isReady("VIDEO-12345") then
    vungle.show("VIDEO-12345")
  end
```

### 3B. Show a Rewarded Video Ad
```lua
-- When rewarded ad is finished, the callback will receive both TYPE_DID_FINISH and TYPE_DID_REWARD events.
  if vungle and vungle.isReady("REWARDED-12345") then
    vungle.show("REWARDED-12345")
  end
```

### 4. Clear the callback in a "final" script lifecycle method
```lua
function final(self)
    if vungle then
        vungle.setCallback()
    end
end
```

### 5. Set minimum Android API version

In `game.project`, set Android Minimum Sdk Version = 21.

## Lua Functions

```lua
vungle.initialize(app_id, callback)
vungle.isInitialized()
vungle.setCallback(callback)
vungle.load(placement_id)
vungle.isReady(placement_id)
vungle.show(placement_id)
```

## Lua Constants

```lua
vungle.TYPE_IS_READY
vungle.TYPE_DID_START
vungle.TYPE_DID_ERROR
vungle.TYPE_DID_FINISH
vungle.TYPE_DID_REWARD
vungle.TYPE_INITIALIZED
vungle.TYPE_INIT_ERROR
```

## Callback Example

```lua
local function vungle_ads_callback(self, msg_type, message)
    if msg_type == vungle.TYPE_IS_READY then
        print(message.placementId, " is ready")
        btn_ready(self, message.placementId)
    elseif msg_type == vungle.TYPE_DID_START then
        print(message.placementId, " started")
    elseif msg_type == vungle.TYPE_DID_ERROR then
        print(message.placementId, " error")
        print(message.message) -- error message
    elseif msg_type == vungle.TYPE_DID_FINISH then
        print(message.placementId, " Ad finished")
    elseif msg_type == vungle.TYPE_DID_REWARD then
        print(message.placementId, " Rewarded Ad Complete")
    elseif msg_type == vungle.TYPE_INITIALIZED then
        print("Vungle init successful!")
    elseif msg_type == vungle.TYPE_INIT_ERROR then
        print("Vungle init error")
        print(message.message)
    end
end
```

## Lessons Learned

When you set up an Amazon app in Vungle, those placements will only work on Amazon Fire devices.  If run on a regular Android device, even if downloaded from the Amazon Appstore, Vungle will return errors about OS mismatches and not serve you ads.   You will need a second app set up in Vungle, and submit 2 APKs to Amazon with different device targeting.

Upon initialization, the Vungle SDK starts to preload an interstitial ad automatically.  It does not do this for rewarded ads.

Vungle support says it's okay to call 'load' during or after an ad is shown, to prefetch for next time.

## Credits

Thanks to [AGulev](https://github.com/AGulev) for his excellent [DefVideoAds](https://github.com/AGulev/DefVideoAds) extension, which was forked to create this.
