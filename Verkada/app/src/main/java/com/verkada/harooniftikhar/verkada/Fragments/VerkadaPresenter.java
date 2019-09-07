package com.verkada.harooniftikhar.verkada.Fragments;

import android.app.AlertDialog;
import android.app.TimePickerDialog;
import android.content.DialogInterface;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.os.AsyncTask;
import android.os.Build;
import android.support.v4.app.Fragment;
import android.content.Context;
import android.util.Log;
import android.widget.TimePicker;

import com.verkada.harooniftikhar.verkada.Cell;
import com.verkada.harooniftikhar.verkada.Interface.MainFragmentInteractionListener;
import com.verkada.harooniftikhar.verkada.Motion;
import com.verkada.harooniftikhar.verkada.R;
import com.verkada.harooniftikhar.verkada.Server;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Calendar;
import java.util.List;
import java.util.TimeZone;
/**
 This presenter has all of the core logic of the app and communicates with the following fragments:
 * Launch Screen
 * Search Screen
 * Table Screen
 */

public class VerkadaPresenter {

    private static final String TAG = VerkadaPresenter.class.getSimpleName();

    private Context mContext;
    private SearchFragment mSearchFragment;
    private LaunchFragment mLaunchFragment;
    private TableFragment mTableFragment;
    private Boolean[] clicked;
    private int[][] motionZones;
    private ArrayList<Cell> zones;
    private Calendar now;
    private long startT = 0;
    private long endT = 0;
    private int startTimeHour = 0;
    private int startTimeMin = 0;
    private int endTimeHour = 0;
    private int endTimeMin = 0;
    public static List<List<Integer>> motionAt;

    private Server VerkadaServer;

    private MainFragmentInteractionListener.Activity mListener;
    private TimePickerDialog.OnTimeSetListener sTimeListener;
    private TimePickerDialog.OnTimeSetListener eTimeListener;

    public VerkadaPresenter(){

    }

    public VerkadaPresenter(Context context){
            mContext = context;
        clicked = new Boolean[100];
        Arrays.fill(clicked, Boolean.FALSE);
        zones = new ArrayList<>();
        mListener = (MainFragmentInteractionListener.Activity) context;
    }

    public void setClicked(Boolean[] clicked) {
        this.clicked = clicked;
    }

    public void setStartT(long startT) {
        this.startT = startT;
    }

    public void setEndT(long endT) {
        this.endT = endT;
    }

    public void createStartDialog(){
        Log.i(TAG,"startTime: " + startT);
        final Calendar cal = Calendar.getInstance();
        int hour = 0;
        int minute = 0;
        if(startTimeHour == 0 & startTimeMin == 0){
            hour = cal.get(Calendar.HOUR_OF_DAY);
            minute = cal.get(Calendar.MINUTE);
        }
        else{
            hour = startTimeHour;
            minute = startTimeMin;
        }

        sTimeListener = new TimePickerDialog.OnTimeSetListener() {
            @Override
            public void onTimeSet(TimePicker view, int hourOfDay, int minute) {
                Calendar cal = Calendar.getInstance();
                cal.set(Calendar.HOUR, hourOfDay);
                cal.set(Calendar.MINUTE, minute);
                startTimeHour = hourOfDay;
                startTimeMin = minute;
                startT = getSecondsUTC(cal.getTimeInMillis());
                Log.i(TAG,"startTime: " + hourOfDay + ":" + minute);
                Log.i(TAG,"startTime: " + startT);
            }
        };

        // Create a new instance of TimePickerDialog and return it
        TimePickerDialog dialog = new TimePickerDialog(mContext, TimePickerDialog.THEME_HOLO_DARK, sTimeListener, hour, minute, false);
        dialog.getWindow().setBackgroundDrawable(new ColorDrawable(Color.TRANSPARENT));
        dialog.show();
        Log.i(TAG,"TimePicker created");
    }

    public void createEndDialog() {
        Log.i(TAG, "endTime: " + endT);
        final Calendar cal = Calendar.getInstance();
        int hour = 0;
        int minute = 0;
        if(endTimeHour == 0 & endTimeMin == 0){
            hour = cal.get(Calendar.HOUR_OF_DAY);
            minute = cal.get(Calendar.MINUTE);
        }
        else{
            hour = endTimeHour;
            minute = endTimeMin;
        }

        eTimeListener = new TimePickerDialog.OnTimeSetListener() {
            @Override
            public void onTimeSet(TimePicker view, int hourOfDay, int minute) {
                Calendar cal = Calendar.getInstance();
                cal.set(Calendar.HOUR, hourOfDay);
                cal.set(Calendar.MINUTE, minute);
                endTimeHour = hourOfDay;
                endTimeMin = minute;
                endT = getSecondsUTC(cal.getTimeInMillis());
                Log.i(TAG, "endTime: " + hourOfDay + ":" + minute);
                Log.i(TAG, "endTime: " + endT);
            }
        };

        // Create a new instance of TimePickerDialog and return it
        TimePickerDialog dialog = new TimePickerDialog(mContext, TimePickerDialog.THEME_HOLO_DARK, eTimeListener, hour, minute, false);
        dialog.getWindow().setBackgroundDrawable(new ColorDrawable(Color.TRANSPARENT));
        dialog.show();
        Log.i(TAG,"TimePicker created");
    }

    public void createDialog(String error){
        AlertDialog.Builder builder;
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            builder = new AlertDialog.Builder(mContext, android.R.style.Theme_Material_Dialog_Alert);
        } else {
            builder = new AlertDialog.Builder(mContext);
        }
        builder.setTitle("Verkada Error")
                .setMessage(error)
                .setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int which) {

                    }
                })
                .setIcon(R.drawable.verkada)
                .show();
    }

    public long getStart(){
        return startT;
    }

    public long getEnd(){
        return endT;
    }

    public Boolean[] getClickedArray(){
        return clicked;
    }

    public Boolean getClicked(int i){
        return clicked[i];
    }

    public List<List<Integer>> getMotionAt() { return motionAt; }

    public ArrayList<Cell> getZones(){
        return zones;
    }

    public void setZones(ArrayList<Cell> zones) {
        this.zones = zones;
    }

    public void setClicked(Boolean click, int i) {
        clicked[i] = click;
    }

    private void calculateZones(){
        Log.i(TAG,"calculateZones");
        zones.clear();
        for (int cell = 0; cell < 100; cell++){
            if (clicked[cell]) {
                int row = cell/10;
                int col = cell%10;
                Log.i(TAG,"[" + row + " , " + col + "]");
                Cell clickedCell = new Cell(row,col);
                zones.add(clickedCell);
            }
        }
        Log.i(TAG,"subRegions selected: " + zones.size());
    }

    public int[][] fillZones(){
        //Log.i(TAG,"fillZones");
        int[][] motion = new int[zones.size()][2];
        for (int cell = 0; cell < zones.size(); cell++){
            motion[cell][0] = zones.get(cell).getCell()[0];
            motion[cell][1] = zones.get(cell).getCell()[1];
            //Log.i(TAG,"zone: " + motion[cell][0] + " , " + motion[cell][1]);
        }
        //Log.i(TAG,"zones selected: " + zones.size());
        return motion;
    }

    void onSearchButtonClicked(){
        now = Calendar.getInstance(TimeZone.getTimeZone("UTC"));
        Log.i(TAG,"Search begun");
        Log.i(TAG,"Time now is: " + now.getTimeInMillis()/1000);
        // startTime & endTime for when query was between now and an hour earlier from now
        long startTime = getSecondsUTC(now.getTimeInMillis()) - 3600;
        long endTime = getSecondsUTC(now.getTimeInMillis());
        calculateZones();
        motionZones = fillZones();
        Motion verkadaMotion = new Motion(motionZones, startT, endT);
        VerkadaServer = new Server(verkadaMotion);
        new HttpAsyncTask().execute("http://ec2-54-187-236-58.us-west-2.compute.amazonaws.com:8021/ios/search");
    }

    public long getSecondsUTC(long now){
        return now/1000;
    }

    private class HttpAsyncTask extends AsyncTask<String, Void, String> {
        @Override
        protected String doInBackground(String... urls) {

            return VerkadaServer.POST(urls[0], VerkadaServer.getMotion());
        }
        // onPostExecute displays the results of the AsyncTask.
        @Override
        protected void onPostExecute(String result) {
            Log.e(TAG, "onPostExecute");
            Log.e(TAG, "Data Sent!");
            Log.e(TAG, "Data Received: " + result);
            try {
               motionAt = VerkadaServer.motionAtParser(new JSONObject(result));
               printMotions();
                mListener.goToList(zones);
            } catch (JSONException e) {
                e.printStackTrace();
            }
        }
    }

    void printMotions(){
        for(List<Integer> motion: motionAt){
            Log.i(TAG,"motionPrinting: " + motion.get(0) + " " + motion.get(1));
        }
    }

    void setContext(Context context){
        mContext = context;
    }

    void onResume(Fragment fragment){
        Log.i(TAG, "onOverviewResume");
        if(fragment instanceof SearchFragment) {
            mSearchFragment = (SearchFragment) fragment;
        }
        else if(fragment instanceof LaunchFragment) {
            mLaunchFragment = (LaunchFragment) fragment;
        }
        else if(fragment instanceof TableFragment){
            mTableFragment = (TableFragment) fragment;
        }
    }

    void onDestroyView(){
        Log.i(TAG, "onOverviewDestroyView");
        mSearchFragment = null;
        mLaunchFragment = null;
        mSearchFragment = null;
    }
}
