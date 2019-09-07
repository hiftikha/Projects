package com.verkada.harooniftikhar.verkada.Fragments;

import android.app.Dialog;
import android.support.v4.app.Fragment;
import android.content.Context;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;
import android.widget.TextView;

import com.verkada.harooniftikhar.verkada.Interface.MainFragmentInteractionListener;
import com.verkada.harooniftikhar.verkada.R;

public class LaunchFragment extends Fragment{
    private static final String TAG = LaunchFragment.class.getSimpleName();

    private VerkadaPresenter mPresenter;

    private MainFragmentInteractionListener mListener;

    public LaunchFragment(){

    }

    public void setPresenter(VerkadaPresenter presenter){ mPresenter = presenter;}

    @Override
    public void onStart() {
        super.onStart();
    }

    @Override
    public void onResume() {
        super.onResume();
        //backButton.setOnClickListener(clickListener);

        Log.i(TAG, "setting presenter's onoverviewresume");
        mPresenter.onResume(this);
        Log.i(TAG, "succesfully set presenter's onoverviewresume");
    }

    @Override
    public void onPause() {
        super.onPause();
        //if( controllerView != null ) controllerView.setOnClickListener(null);

    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        Log.i("Verkada ", "about to inflate view");
        View view = inflater.inflate(R.layout.fragment_launch, container, false);

        Log.i("Verkada ", "done inflating view");
        return view;
    }

    @Override
    public void onAttach(Context context) {
        super.onAttach(context);
        if (context instanceof MainFragmentInteractionListener.Activity) {
            mListener = (MainFragmentInteractionListener) context;
        } else {
            throw new RuntimeException(context.toString()
                    + " must implement OnFragmentInteractionListener");
        }
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
        super.onDetach();
        mListener = null;
    }

}
