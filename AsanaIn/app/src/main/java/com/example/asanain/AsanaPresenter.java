package com.example.asanain;

import android.app.AlertDialog;
import android.app.TimePickerDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.os.AsyncTask;
import android.os.Build;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.widget.ListAdapter;
import android.widget.SimpleAdapter;
import android.widget.TimePicker;
import android.widget.Toast;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Calendar;
import java.util.HashMap;
import java.util.List;
import java.util.TimeZone;

/**
 This presenter has all of the core logic of the app and communicates with the following fragments:
 * Launch Screen
 * Table Screen
 */

public class AsanaPresenter {

    private static final String TAG = AsanaPresenter.class.getSimpleName();

    private Context mContext;
    private TableFragment mTableFragment;

    ArrayList<Employee> EmployeeList;

    private MainFragmentInteractionListener.Activity mListener;

    public AsanaPresenter(){

    }

    public AsanaPresenter(Context context){
        mContext = context;
        mListener = (MainFragmentInteractionListener.Activity) context;
        EmployeeList = new ArrayList<>();
    }

    void onResume(Fragment fragment){
        Log.i(TAG, "onOverviewResume");
        if(fragment instanceof TableFragment){
            mTableFragment = (TableFragment) fragment;
        }
    }

    void onDestroyView(){
        Log.i(TAG, "onOverviewDestroyView");

        mTableFragment= null;
    }
}
