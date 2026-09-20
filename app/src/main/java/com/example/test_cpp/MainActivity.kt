package com.example.test_cpp

import android.os.Build
import android.view.View
import android.view.WindowInsets
import android.view.WindowInsetsController

import com.google.androidgamesdk.GameActivity

class MainActivity : GameActivity()
{
    companion object
    {
        init
        {
            System.loadLibrary("test_cpp")
        }
    }

    override fun onWindowFocusChanged(
        hasFocus: Boolean)
    {
        super.onWindowFocusChanged(hasFocus)

        if(hasFocus)
        {
            hideSystemUi()
        }
    }

    private fun hideSystemUi()
    {
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.R)
        {
            window.insetsController?.apply {
                hide(
                    WindowInsets.Type.systemBars())

                systemBarsBehavior =
                    WindowInsetsController
                        .BEHAVIOR_SHOW_TRANSIENT_BARS_BY_SWIPE
            }
        }
        else
        {
            @Suppress("DEPRECATION")
            window.decorView.systemUiVisibility =
                View.SYSTEM_UI_FLAG_FULLSCREEN or
                        View.SYSTEM_UI_FLAG_HIDE_NAVIGATION or
                        View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY
        }
    }
}