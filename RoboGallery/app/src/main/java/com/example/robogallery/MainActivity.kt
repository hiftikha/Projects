package com.example.robogallery

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.example.robogallery.ui.main.DetailFragment
import com.example.robogallery.ui.main.MainFragment

class MainActivity : AppCompatActivity(), FragmentListener {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.main_activity)
        if (savedInstanceState == null) {
            supportFragmentManager.beginTransaction()
                    .replace(R.id.container, MainFragment.newInstance())
                    .commitNow()
        }
    }

    override fun showDetailsFragment(index : Int) {
        val args = Bundle()
        args.putInt(DetailFragment.SELECTED_ROBOT, index)
        val detailFragment = DetailFragment.newInstance()
        detailFragment.arguments = args
        supportFragmentManager.beginTransaction().apply {
            replace(R.id.container, detailFragment)
                .addToBackStack(null)
                .commit()
        }
    }
}
