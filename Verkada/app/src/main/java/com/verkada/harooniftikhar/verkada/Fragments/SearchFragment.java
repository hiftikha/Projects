package com.verkada.harooniftikhar.verkada.Fragments;

import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.content.Context;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v7.widget.CardView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.GridLayout;
import android.widget.TextView;

import com.verkada.harooniftikhar.verkada.Interface.MainFragmentInteractionListener;
import com.verkada.harooniftikhar.verkada.R;


public class SearchFragment extends Fragment{
    private static final String TAG = SearchFragment.class.getSimpleName();

    private VerkadaPresenter mPresenter;
    private TextView searchButton, startButton, endButton;
    private GridLayout gridView;

    private MainFragmentInteractionListener.Activity mListener;

    public SearchFragment(){

    }

    @Override
    public void onAttach(Context context) {
        super.onAttach(context);
        if (context instanceof MainFragmentInteractionListener.Activity) {
            mListener = (MainFragmentInteractionListener.Activity) context;
        } else {
            throw new RuntimeException(context.toString()
                    + " must implement OnFragmentInteractionListener");
        }
    }

    @Override
    public void onStart() {
        Log.i(TAG, " onStart");
        super.onStart();
    }

    @Override
    public void onResume() {
        Log.i(TAG, "onResume");
        super.onResume();
        //backButton.setOnClickListener(clickListener);

        Log.i(TAG, "setting presenter's onResume");
//        mPresenter.onResume(this);
        Log.i(TAG, "successfully set presenter's onResume");
    }

    @Override
    public void onPause() {
        Log.i(TAG, " onPause");
        super.onPause();


    }

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        Log.i(TAG, "onCreate");
        super.onCreate(savedInstanceState);
        mPresenter = new VerkadaPresenter(getContext());
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        Log.i(TAG, "onCreateView");
        // Inflate the layout for this fragment
        Log.i("Verkada ", "about to inflate view");
        View view = inflater.inflate(R.layout.fragment_search, container, false);
        searchButton = view.findViewById(R.id.search_button);
        searchButton.setOnClickListener(mClickListener);
        startButton = view.findViewById(R.id.start_time);
        startButton.setOnClickListener(mClickListener);
        endButton = view.findViewById(R.id.end_time);
        endButton.setOnClickListener(mClickListener);
        gridView = view.findViewById(R.id.grid10x10);
        setGridEvent(gridView);
        Log.i("Verkada ", "done inflating view");
        return view;
    }

    @Override
    public void onDestroyView() {
        Log.i(TAG, "onDestroyView");
        super.onDestroyView();
        mPresenter.onDestroyView();
        // These no longer exist:
    }

    @Override
    public void onDetach() {
        Log.i(TAG, "onDetach");
        super.onDetach();
        mListener = null;
    }

    private View.OnClickListener mClickListener = new View.OnClickListener() {

        @Override
        public void onClick(View v) {
            Log.i(TAG, "onClickListener");
            switch (v.getId()){
                case R.id.search_button:
                    if(mPresenter.getStart() > mPresenter.getEnd() && mPresenter.getStart() !=0 && mPresenter.getEnd() != 0) {
                        mPresenter.createDialog("EndTime is earlier than StartTime");
                    }
                    else if(mPresenter.getStart() == 0 && mPresenter.getEnd() == 0){
                        mPresenter.createDialog("EndTime and StartTime not set");
                    }
                    else if(mPresenter.getStart() == 0 && mPresenter.getEnd() != 0){
                        mPresenter.createDialog("StartTime not set");
                    }
                    else if(mPresenter.getStart() != 0 && mPresenter.getEnd() == 0){
                        mPresenter.createDialog("EndTime not set");
                    }
                    else {
                        mPresenter.onSearchButtonClicked();
                        //searchButton.setBackgroundColor(getResources().getColor(R.color.transparent));
                        //startButton.setBackgroundColor(getResources().getColor(R.color.transparent));
                        //endButton.setBackgroundColor(getResources().getColor(R.color.transparent));

                        // no longer going to table fragment before getting json response
                        Log.i(TAG, "Time to make a Search!");
                    }
                    break;
                case R.id.start_time:
                    //startButton.setBackgroundColor(getResources().getColor(R.color.colorAccent));
                    mPresenter.createStartDialog();
                    Log.i(TAG,"Change start Time!");
                    break;
                case R.id.end_time:
                    //endButton.setBackgroundColor(getResources().getColor(R.color.colorAccent));
                    mPresenter.createEndDialog();
                    Log.i(TAG,"Change end Time!");
                    break;
            }
        }
    };

    private void setGridEvent(GridLayout gridLayout) {
        Log.i(TAG,"setGridEvent");
        Log.i(TAG,"Child count of gridLayout: " + String.valueOf(gridLayout.getChildCount()));
        for(int i = 0; i<gridLayout.getChildCount(); i++){
            CardView cardView =(CardView)gridLayout.getChildAt(i);
            final int finalI= i;
            cardView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    if(!mPresenter.getClicked(finalI)) {
                        view.setBackgroundColor(getResources().getColor(R.color.skyBlue));
                        mPresenter.setClicked(true,finalI);
                    }
                    else {
                        view.setBackgroundColor(getResources().getColor(R.color.transparent));
                        mPresenter.setClicked(false,finalI);
                    }
                    Log.i(TAG,"Cardview at " + String.valueOf(finalI) + " clicked!");
                }
            });
        }
    }

}

