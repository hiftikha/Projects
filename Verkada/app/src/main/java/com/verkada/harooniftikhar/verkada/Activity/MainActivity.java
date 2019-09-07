package com.verkada.harooniftikhar.verkada.Activity;

import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

import com.verkada.harooniftikhar.verkada.Cell;
import com.verkada.harooniftikhar.verkada.Fragments.LaunchFragment;
import com.verkada.harooniftikhar.verkada.Interface.MainFragmentInteractionListener;
import com.verkada.harooniftikhar.verkada.R;
import com.verkada.harooniftikhar.verkada.Fragments.SearchFragment;
import com.verkada.harooniftikhar.verkada.Fragments.TableFragment;

import java.util.ArrayList;

/**
This activity has all of the core functionality of the app and controls the following fragments:
 * Launch Screen
 * Search Screen
 * Table Screen
 */

public class MainActivity extends AppCompatActivity implements MainFragmentInteractionListener.Activity {

    private static final String TAG = MainActivity.class.getSimpleName();

    private SearchFragment mSearchFragment;
    private TableFragment mTableFragment;
    private LaunchFragment mLaunchFragment;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Log.i(TAG, "created MainActivity");
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main_activity);
        goToSearch();
    }

    @Override
    protected void onResume() {
        Log.i(TAG, "onResume");
        super.onResume();
        //mVoyoAPI.enablePermissions(this);
    }

    @Override
    protected void onPause() {
        Log.i(TAG, "onPause");
        super.onPause();
    }

    @Override
    public void onStop() {
        Log.i(TAG, "onStop");
        super.onStop();
    }

    @Override
    public void onDestroy() {
        Log.i(TAG, "onDestroy");
        super.onDestroy();
        mLaunchFragment = null;
        mSearchFragment = null;
        mTableFragment = null;
    }

    @Override
    public void goToList(ArrayList<Cell> selected) {

        Log.i(TAG, "goToList");
        String fragTag = "ListFragment";

        Fragment table = new TableFragment();
        Bundle args = new Bundle();
        args.putSerializable("cells", selected);
        table.setArguments(args);

        FragmentTransaction transaction = getSupportFragmentManager().beginTransaction();

        // Replace whatever is in the fragment_container view with this fragment,
        // and add the transaction to the back stack so the user can navigate back
        transaction.add(R.id.fragment_search, table);
        transaction.addToBackStack(null);

        // Commit the transaction
        transaction.commit();

    }

    @Override
    public void goToSearch() {

        Log.i(TAG, "goToSearch");
        String fragTag = "SearchFragment";

        FragmentTransaction transaction = getSupportFragmentManager().beginTransaction();

        // Replace whatever is in the fragment_container view with this fragment,
        // and add the transaction to the back stack so the user can navigate back
        transaction.replace(R.id.main_activity, new SearchFragment());
        //transaction.addToBackStack(null);

        // Commit the transaction
        transaction.commit();
    }
}
